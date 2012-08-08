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


#ifndef PPU_H
#define PPU_H

#include <vector>
#include "cpu.h"
#include "timing.h"
#include "mmu.h"
#include "oam.h"

#define NUM_SPRITES 64

class PPU {
public:
    u16 scanLine;
    u16 clockCycles;
    
    PPU( CPU* cpu, u32* screen, MMU* mmu );
    u8 update();
private:    
    CPU* cpu;
    MMU* mmu;
    u32* screen;
    u32 tmpBgPal[4];
    u32 tmpLine[SCREEN_W_INT];
    std::vector<OAM> oam;
    
    void drawLine();
    void drawLineBG();
    void readPalBG( u8 mapX, u8 mapY );
};

#endif // PPU_H
