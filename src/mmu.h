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


#ifndef MMU_H
#define MMU_H

#include "types.h"
#include "cart.h"
#include "cpu.h"
#include "input.h"

#define CPU_MEM_SIZE 0x10000
#define PPU_MEM_SIZE 0x4000
#define NT_SIZE 0x400
#define PATTERN_SIZE 0x1000
#define OAM_MEM_SIZE 0x100

class CPU;
class MMU {

public:
    u8 cpuMem[CPU_MEM_SIZE];
    u8 ppuMem[PPU_MEM_SIZE];
    u8 oamMem[OAM_MEM_SIZE];
    
    //special pattern tables with rearranged color bits
    //for easier/faster access to ppu code
    u8 patternTable0[PATTERN_SIZE*4];
    u8 patternTable1[PATTERN_SIZE*4];
    
    MMU( Cart* cartridge, Input* input );
    void setCPU(CPU* cpu);
    u8 memRead8( u16 addr );
    u16 memRead16( u16 addr );
    void memWrite8( u16 addr, u8 val );
    void memWrite16( u16 addr, u16 val );
    u8 ppuRead8( u16 addr );
    void ppuWrite8( u16 addr, u8 val ); 
    
    u8 ioRead( u16 addr );
    void ioWrite( u16 addr, u8 val );
    u16 vramPtr;
    u8 ppuW1;
    u8 ppuW2;
private:
    u8 ntMem0[NT_SIZE];
    u8 ntMem1[NT_SIZE];
    u8 ntMem2[NT_SIZE];
    u8 ntMem3[NT_SIZE];
    
    Cart* cart;
    CPU* cpu;
    Input* input;
    u8 ppuFlipFlop;

    void writePattern( u16 addr, u8 val );
    void DMA( u16 addr );
};

#endif // MMU_H
