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


#ifndef HEADER_H
#define HEADER_H

#include "types.h"

#define HEADER_SIZE 0x10

#define FILE_ID 0x00
#define NUM_PRG_PAGES 0x04
#define NUM_CHR_PAGES 0x05
#define CART_TYPE_LSB 0x06
#define CART_TYPE_MSB 0x07
#define NUM_RAM_PAGES 0x08
#define RESERVED_0 0x09
#define RESERVED_1 0x0a
#define RESERVED_2 0x0b
#define RESERVED_3 0x0c
#define RESERVED_4 0x0d
#define RESERVED_5 0x0e
#define IS_GARBAGE 0x0f

#define HORIZONTAL_MIRROR 0
#define VERTICAL_MIRROR 1
class Header {

public:
    Header();
    void readHeader( u8* rom );

    u32 fileId;
    u8 numPrgPages;
    u8 numChrPages;
    u8 cartTypeLSB;
    u8 cartTypeMSB;
    u8 numRamPages;
    u8 reserved0;
    u8 reserved1;
    u8 reserved2;
    u8 reserved3;
    u8 reserved4;
    u8 reserved5;
    u8 isGarbage;
    
    //cartTypeLSB cartTypeMSB derived data
    u8 numMapper;
    u8 hasFourScreen;
    u8 hasPatch;
    u8 hasSRAM;
    u8 mirrorType;
    u8 isPC10;
    u8 isVSUnisystem;
};

#endif // HEADER_H
