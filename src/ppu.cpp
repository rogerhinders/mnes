/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  <copyright holder> <email>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <cstdio>
#include "ppu.h"
#include "regs.h"
#include "tables.h"

PPU::PPU( CPU* cpu, u32* screen, MMU* mmu ) {
    this->screen = screen;
    scanLine = 241;
    clockCycles = 0;
    this->cpu = cpu;
    this->mmu = mmu;
    
    //init oam
    for( int i=0; i<NUM_SPRITES; i++ )
        oam.push_back( OAM( i, this->mmu ));
}

u8 PPU::update() {
    clockCycles += cpu->T * CLOCK_DIVIDER_NTSC;
    if(clockCycles>=341) {
        clockCycles = clockCycles % 341;
        scanLine = ( scanLine + 1 ) % NUM_SCANLINES_NTSC;

        if( scanLine < 240 ) { //render screen
            if( scanLine == 0 ) //vbl ended, reset vbl and hit bit in stat regs
                mmu->cpuMem[ REG_PPU_STAT ] &= 0x3f;

            drawLine();
        } else { //vblank..
            if( scanLine==240 ) {
                mmu->cpuMem[ REG_PPU_STAT ] |= 0x80; //set vbl bit in stat reg

                //exec nmi if enabled
                if( mmu->cpuMem[ REG_PPU_CTRL_1 ] & 0x80 )
                    cpu->execNMI();
            }
        }
        if(scanLine==239)
            return 1; //tell opengl to draw screen!
    }
    return 0;
}

void PPU::drawLine() {
    drawLineBG();

    //update sprites
    u8 oamLine;
    u32 screenOfs = SCREEN_W_EXT * scanLine;
    u32 pixel;
    for( int i=NUM_SPRITES-1; i>=0; i-- ) {
        oam[i].updateAttributes();
        if(oam[i].intersectsScanline( scanLine, oamLine ) && oam[i].y < 0xef) {
            oam[i].updatePixels( oamLine );
            //write to screen
            for(int j=0; j<OAM::w; j++) {
                if( oam[i].line[j] != 0xffffff ) {
                    pixel = palColors[ tmpBgPal[ 0 ] ];
                    
                    //check for hit flag 
                    if( ( oam[i].number == 0 ) && ( screen[ oam[i].x + j + screenOfs ] != pixel ) )
                        mmu->cpuMem[ REG_PPU_STAT ] |= 0x40;

                    //check for sprite priority and draw
                    if( !( oam[i].priority && ( screen[ oam[i].x + j + screenOfs ] != pixel ) ) )
                        screen[ oam[i].x + j + screenOfs ] = oam[i].line[j];
                }
            }
        }
    }
}

void PPU::drawLineBG() {

    u8 tileNum;
    u8 mapX;
    u8 mapY = scanLine/8;
    u16 ntOfs;
    u16 ntBase = 0x2000;
    u16 numPattern = mmu->cpuMem[REG_PPU_CTRL_1] & PPU_CTRL_1_PATTERN_TABLE_BG;
    u32 tileOfs;
    u8 pixel;

    for( int x=0; x<SCREEN_W_EXT; x++) {
        mapX = x/8;
        //read the palette
        readPalBG( mapX, mapY );

        ntOfs = ntBase + ( mapX + 32 * mapY );
        tileNum = mmu->ppuRead8( ntOfs );
        tileOfs = ( tileNum * 64 ) + ( x & 7 ) + 8 * ( scanLine & 7 );

        if(!numPattern)
            pixel = mmu->patternTable0[ tileOfs ];
        else
            pixel = mmu->patternTable1[ tileOfs ];

            screen[ x + SCREEN_W_EXT * scanLine ] = palColors[ tmpBgPal[ pixel ] ];
    }

}

inline void PPU::readPalBG( u8 mapX, u8 mapY ) {
    u8 palNum = ( mmu->ppuRead8( 0x2300 + palAttr[ mapY ][ mapX ] ) >> palAttrShift[ mapY ][ mapX ] ) & 3;
    u8 palOfs = palNum * 4 + 1;
    tmpBgPal[0] = mmu->ppuRead8( 0x3f00 );
    tmpBgPal[1] = mmu->ppuRead8( 0x3f00 + palOfs );
    tmpBgPal[2] = mmu->ppuRead8( 0x3f00 + palOfs + 1 );
    tmpBgPal[3] = mmu->ppuRead8( 0x3f00 + palOfs + 2 );
}
