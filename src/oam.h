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


#ifndef OAM_H
#define OAM_H

#include "types.h"
#include "mmu.h"

#define OAM_PALETTE 0x3
#define OAM_PRIORITY 0x20
#define OAM_HORIZONTAL_FLIP 0x40
#define OAM_VERTICAL_FLIP 0x80

#define OAM_8x16_PATTERN 0x1
#define OAM_8x16_TILENUM 0xfe

class OAM {

public:
    u8 number;
    u8 y;
    u8 x;
    static const u8 w = 8;
    u32 line[w];
    u8 h;
    u16 memAddr;
    u8 horizontalFlip;
    u8 verticalFlip;
    u8 priority;
    u8 palette;
    u8 tileNum, tileNum2;
    u8* pattern;

    OAM( u8 number, MMU* mmu );
    void updateAttributes();
    void updatePixels(u8 oamLine);
    u8 intersectsScanline( u8 scanLine, u8& whichLine );
private:
    MMU* mmu;
    u32 tmpOamPal[4];
};

#endif // OAM_H
