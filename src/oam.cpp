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
#include "oam.h"
#include "regs.h"
#include "tables.h"

OAM::OAM( u8 number, MMU* mmu ) {
    this->number = number;
    this->mmu = mmu;
    memAddr = number * 4;
    updateAttributes();
}

void OAM::updateAttributes() {
    y = mmu->oamMem[ memAddr ];
    x = mmu->oamMem[ memAddr + 3 ];

    if( mmu->cpuMem[ REG_PPU_CTRL_1 ] & PPU_CTRL_1_SPRITE_SIZE ) {
        h = 16;
        tileNum = ( mmu->oamMem[ memAddr + 1 ] >> 1 ) * 2;
        tileNum2 = tileNum+1;

        if( !mmu->oamMem[ memAddr + 1 ] & OAM_8x16_PATTERN )
            pattern = &mmu->patternTable0[0];
        else
            pattern = &mmu->patternTable1[0];
    } else {
        h = 8;
        tileNum = mmu->oamMem[ memAddr + 1 ];

        if( !( mmu->cpuMem[REG_PPU_CTRL_1] & PPU_CTRL_1_PATTERN_TABLE_OAM ) )
            pattern = &mmu->patternTable0[0];
        else
            pattern = &mmu->patternTable1[0];
    }

    palette = mmu->oamMem[ memAddr + 2 ] & OAM_PALETTE;
    priority = mmu->oamMem[ memAddr + 2 ] & OAM_PRIORITY;
    horizontalFlip = mmu->oamMem[ memAddr + 2 ] & OAM_HORIZONTAL_FLIP;
    verticalFlip = mmu->oamMem[ memAddr + 2 ] & OAM_VERTICAL_FLIP;
}

void OAM::updatePixels(u8 oamLine) {

    u32 tileOfs = ( tileNum * 64 ) + w * (oamLine&7);

    u8 palOfs = palette * 4;
    u8 pixel;
    u8 flippedX;

    tmpOamPal[1] = mmu->ppuRead8( 0x3f11 + palOfs );
    tmpOamPal[2] = mmu->ppuRead8( 0x3f11 + palOfs + 1 );
    tmpOamPal[3] = mmu->ppuRead8( 0x3f11 + palOfs + 2 );

    for( int ix=0; ix<w; ix++) {

        if( horizontalFlip )
            flippedX = (~ix) & 7;
        else
            flippedX = ix;

        pixel = pattern[ tileOfs + flippedX ];
        if(pixel)
            line[ ix ] = palColors[ tmpOamPal[ pixel ] ];
        else
            line[ ix ] = 0xffffff;
    }
}

u8 OAM::intersectsScanline( u8 scanLine, u8& whichLine ) {
    u8 eval = ( ( scanLine >= ( y + 1 ) ) && ( scanLine < ( y + h + 1 ) ) );

    if(eval) {
        for( int i = 0; i<h; i++ ) {
            if( ( y + i + 1 ) == scanLine ) {
                whichLine = i;
                break;
            }
        }
    }
    return eval;
}
