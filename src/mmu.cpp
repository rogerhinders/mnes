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
#include "mmu.h"
#include "regs.h"

MMU::MMU( Cart* cartridge, Input* input ) {
    this->cart = cartridge;
    this->input = input;
    ppuFlipFlop = 0;
    
    //init "fake" patterns
    for( int i = 0; i<(PATTERN_SIZE*2 ); i++ )
        ppuWrite8( i, ppuRead8( i ) );
}

void MMU::setCPU( CPU* cpu ) {
    this->cpu = cpu;
}

u8 MMU::memRead8( u16 addr ) {
    u8* p = &cpuMem[0];
    
    if( addr <= 0x1fff ) {        // 0000h-07FFh Internal 2K Work RAM (mirrored to 800h-1FFFh)
        p = &cpuMem[0];
        addr &= 0x07ff;
    } else if( addr <= 0x3fff ) { // 2000h-2007h Internal PPU Registers (mirrored to 2008h-3FFFh)
        p = &cpuMem[0];
        addr =  (addr & 0x07) + 0x2000;
        
        if( addr == REG_PPU_STAT ) //read to stat reg resets flip flop
            ppuFlipFlop = 0;
        
        return ioRead( addr );
    } else if( addr <= 0x4017 ) { // 4000h-4017h Internal APU Registers
        
        if(addr==REG_JOYP_1)
            return input->readInput();
            
        p = &cpuMem[0];
    } else if( addr <= 0x5fff ) { // 4018h-5FFFh Cartridge Expansion Area almost 8K
        p = &cart->rom[0];
    } else if( addr <= 0x7fff) {  // 6000h-7FFFh Cartridge SRAM Area 8K
        p = &cart->rom[0];
    } else {                      // 8000h-FFFFh Cartridge PRG-ROM Area 32K
        p = &cart->rom[0];
        
        //if only 16kb prg, enable mirroring
        if((cart->hdr->numPrgPages==1) && (addr>=0xc000))
            addr -= 0x4000;
            
        //start of rom in file
        addr -= 0x7ff0;
    }
    return p[addr];
}

void MMU::memWrite8( u16 addr, u8 val ) {
    u8* p = &cpuMem[0];
    
    if( addr <= 0x1fff ) {        // 0000h-07FFh Internal 2K Work RAM (mirrored to 800h-1FFFh)
        p = &cpuMem[0];
        addr &= 0x07ff;
    } else if( addr <= 0x3fff ) { // 2000h-2007h Internal PPU Registers (mirrored to 2008h-3FFFh)
        p = &cpuMem[0];
        addr =  ( addr & 0x07 ) + 0x2000;
        ioWrite( addr, val );
    } else if( addr <= 0x4017 ) { // 4000h-4017h Internal APU Registers
        if( addr == REG_SPR_RAM_DMA )
            DMA( val << 8 );

        if( addr==REG_JOYP_1 ) {
            if( val & 1 )
                input->recordButtons();
        }

        p = &cpuMem[0];
    } else if( addr <= 0x5fff ) { // 4018h-5FFFh Cartridge Expansion Area almost 8K
        p = &cart->rom[0];
    } else if( addr <= 0x7fff) {  // 6000h-7FFFh Cartridge SRAM Area 8K
        p = &cart->rom[0];
        
        //if((addr>=0x6004)&&(addr<6200)) 
            printf("%c",val);
    } else {                      // 8000h-FFFFh Cartridge PRG-ROM Area 32K
        p = &cart->rom[0];
        
        //temporary mapper0 stuff:
        
       // if(addr>=0xc000)
       //     addr -= 0x4000;
        //start of rom in file
        addr -= 0x7ff0;
    }
    p[addr] = val;
}

u16 MMU::memRead16( u16 addr ) {
   // printf("read16:%x\n",addr);
    return memRead8( addr+1 )<<8|memRead8( addr );
}

void MMU::memWrite16( u16 addr, u16 val ) { 
    memWrite8( addr,val&0xff );
    memWrite8( addr+1,val>>8 );
}

u8 MMU::ppuRead8( u16 addr ) {
    
    u8* p = &ppuMem[0];
    
    if( addr <= 0x1fff ) { //pattern table 0-1
        p = &cart->rom[0];
        addr += cart->chrRomOffset;
    } else if( addr <= 0x23ff ) { //NT0
        addr -= 0x2000;
        p = &ntMem0[0];
    } else if( addr <= 0x27ff ) { //NT1
        addr -= 0x2400;
        
        if(cart->hdr->mirrorType==HORIZONTAL_MIRROR)
            p = &ntMem0[0];
        if(cart->hdr->mirrorType==VERTICAL_MIRROR)
            p = &ntMem1[0];
        if(cart->hdr->hasFourScreen)
            p = &ntMem1[0];
            
    } else if( addr <= 0x2bff ) { //NT2
        addr -= 0x2800;
        
        if(cart->hdr->mirrorType==HORIZONTAL_MIRROR)
            p = &ntMem1[0];
        if(cart->hdr->mirrorType==VERTICAL_MIRROR)
            p = &ntMem0[0];
        if(cart->hdr->hasFourScreen)
            p = &ntMem2[0];
            
    } else if( addr <= 0x2fff ) { //NT3
        addr -= 0x2c00;
        
        if(cart->hdr->mirrorType==HORIZONTAL_MIRROR)
            p = &ntMem1[0];
        if(cart->hdr->mirrorType==VERTICAL_MIRROR)
            p = &ntMem1[0];
        if(cart->hdr->hasFourScreen)
            p = &ntMem3[0];
            
    } else if( addr <= 0x3eff ) { //NT mirroring,recursive
        return ppuRead8( addr - 0x1000 );
    } else if( addr <= 0x3f1f ) {

    } else if( addr <= 0x3fff ) {
        addr = 0x3f00 | ( ( ( addr & 0xff ) - 0x20 ) & 0x1f );
    }
    
    return p[addr];
}

void MMU::ppuWrite8( u16 addr, u8 val ) {
    
    u8* p = &ppuMem[0];
    
    if( addr <= 0x1fff ) { //pattern table 0-1
        writePattern( addr, val );
        p = &cart->rom[0];
        addr += cart->chrRomOffset;
    } else if( addr <= 0x23ff ) { //NT0
        addr -= 0x2000;
        p = &ntMem0[0];
    } else if( addr <= 0x27ff ) { //NT1
        addr -= 0x2400;
        
        if(cart->hdr->mirrorType==HORIZONTAL_MIRROR)
            p = &ntMem0[0];
        if(cart->hdr->mirrorType==VERTICAL_MIRROR)
            p = &ntMem1[0];
        if(cart->hdr->hasFourScreen)
            p = &ntMem1[0];
            
    } else if( addr <= 0x2bff ) { //NT2
        addr -= 0x2800;
        
        if(cart->hdr->mirrorType==HORIZONTAL_MIRROR)
            p = &ntMem1[0];
        if(cart->hdr->mirrorType==VERTICAL_MIRROR)
            p = &ntMem0[0];
        if(cart->hdr->hasFourScreen)
            p = &ntMem2[0];
            
    } else if( addr <= 0x2fff ) { //NT3
        addr -= 0x2c00;
        
        if(cart->hdr->mirrorType==HORIZONTAL_MIRROR)
            p = &ntMem1[0];
        if(cart->hdr->mirrorType==VERTICAL_MIRROR)
            p = &ntMem1[0];
        if(cart->hdr->hasFourScreen)
            p = &ntMem3[0];
            
    } else if( addr <= 0x3eff ) { //NT mirroring,recursive
        ppuWrite8( addr - 0x1000, val );
        return;
    } else if( addr <= 0x3f1f ) {

    } else if( addr <= 0x3fff ) {
        addr = 0x3f00 | ( ( ( addr & 0xff ) - 0x20 ) & 0x1f );
    }
    
    p[addr] = val;
}

u8 MMU::ioRead( u16 addr ) {
    u8 ret;
    switch( addr ) {
        case REG_PPU_CTRL_1:
            break;
        case REG_PPU_CTRL_2:
            break;
        case REG_PPU_STAT:
            ppuFlipFlop = 0;
            ret = cpuMem[ REG_PPU_STAT ];
            cpuMem[ REG_PPU_STAT ] &= 0x7f;
            return ret;
            break;
        case REG_SPR_RAM_ADDR:
            break;
        case REG_SPR_RAM_DATA:
            return oamMem[ cpuMem[ REG_SPR_RAM_ADDR ] ];
            break;
        case REG_PPU_BG_SCR:
            break;
        case REG_VRAM_ADDR:
            break;
        case REG_VRAM_RW_DATA:
            ret = ppuRead8( vramPtr );
            if( !( cpuMem[ REG_PPU_CTRL_1 ] & PPU_CTRL_1_VRAM_INC ) )
                vramPtr = ( vramPtr + 1 ) & 0x3fff;
            else
                vramPtr = ( vramPtr + 32 ) & 0x3fff;
            
            ppuW1 = ( vramPtr & 0x3f00 ) >> 8;
            ppuW2 = vramPtr & 0xff;
            return ret;
            break;
    }
    return 0;
}

void MMU::ioWrite( u16 addr, u8 val ) {
    switch( addr ) {
        case REG_SPR_RAM_ADDR:
            break;
        case REG_SPR_RAM_DATA:
            oamMem[ cpuMem[ REG_SPR_RAM_ADDR ] ] = val;
            cpuMem[ REG_SPR_RAM_ADDR ]++;
            break;
        case REG_PPU_BG_SCR:
            ppuFlipFlop ^= 1;
            break;
        case REG_VRAM_ADDR:
            if( !ppuFlipFlop ) { //write 1
                ppuW1 = val;
                vramPtr = ( ( vramPtr & 0xff ) | ( ( ppuW1 << 8 ) & 0x3f00 ) ) & 0x3fff;
            } else { //write 2
                ppuW2 = val;
                vramPtr = ( ( vramPtr & 0x3f00 ) | ( ppuW2 & 0xff ) ) & 0x3fff;
            }

            ppuFlipFlop ^= 1; //flip between w1/w2
            break;
        case REG_VRAM_RW_DATA:
            ppuWrite8( vramPtr, val ); 
            if( !( cpuMem[ REG_PPU_CTRL_1 ] & PPU_CTRL_1_VRAM_INC ) )
                vramPtr = ( vramPtr + 1 ) & 0x3fff;
            else
                vramPtr = ( vramPtr + 32 ) & 0x3fff;

            ppuW1 = ( vramPtr & 0x3f00 ) >> 8;
            ppuW2 = vramPtr & 0xff;
            break;
    }
}

void MMU::writePattern( u16 addr, u8 val ) {
    u8* p = &patternTable0[0];

    if(addr>0xfff) {
        addr -= 0x1000;
        p = &patternTable1[0];
    }

    u8 c;
    u8 y = addr & 7;
    u8 numTile = addr >> 4;
    u8 isMsb = ( addr & 0xf ) > 7;
    u16 offset;

    for(int numPixel=0;numPixel<8;numPixel++) {
        //loop through and fetch all bits from byte,
        //from left to right.
        c = ( val >> ( ( ~numPixel ) & 7 ) ) & 1;

        //calculate pixel offset in destination array
        offset = 64 * numTile + numPixel + y * 8;

        //write bit to pixel array

        p[offset] = ( p[offset] | ( c << isMsb ) ) & 3;
    }
}

void MMU::DMA( u16 addr ) {
    //printf("dma occured,src %x\n",addr);
    //printf("\n\n\n");
    cpu->T += 512;
    for( int i=0; i<OAM_MEM_SIZE; i++) {
    //    printf("%x,",memRead8(addr+i));
        ioWrite( REG_SPR_RAM_DATA, memRead8( addr + i ) );
    }
}
