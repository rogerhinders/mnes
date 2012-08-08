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
#include "header.h"

Header::Header() {

}

void Header::readHeader( u8* rom ) {
    fileId = rom[FILE_ID]<<24|rom[FILE_ID+1]<<16|rom[FILE_ID+2]<<8|rom[FILE_ID+3];
    numPrgPages = rom[NUM_PRG_PAGES];
    numChrPages = rom[NUM_CHR_PAGES];
    cartTypeLSB = rom[CART_TYPE_LSB];
    cartTypeMSB = rom[CART_TYPE_MSB];
    numRamPages = rom[NUM_RAM_PAGES];
    reserved0 = rom[RESERVED_0];
    reserved1 = rom[RESERVED_1];
    reserved2 = rom[RESERVED_2];
    reserved3 = rom[RESERVED_3];
    reserved4 = rom[RESERVED_4];
    reserved5 = rom[RESERVED_5];
    isGarbage = rom[IS_GARBAGE];
    
    numMapper = ( cartTypeMSB & 0xf0 ) | ( ( cartTypeLSB >> 4 ) & 0x0f );
    hasFourScreen = ( cartTypeLSB >> 3) & 1;
    hasPatch = ( cartTypeLSB >> 2) & 1;
    hasSRAM = ( cartTypeLSB >> 1) & 1;
    mirrorType = cartTypeLSB & 1;
    isPC10 = ( cartTypeMSB >> 1) & 1;
    isVSUnisystem = cartTypeMSB & 1;

    printf("------ ROM INFO ------\n");
    printf("PRG pages: %d\n",numPrgPages);
    printf("CHR pages: %d\n",numChrPages);
    printf("RAM pages: %d\n",numRamPages);
    printf("Mapper: %d\n",numMapper);
    printf("4 screen: %s\n",(hasFourScreen) ? "yes" : "no");
    printf("Patch: %s\n",(hasPatch) ? "yes" : "no");
    printf("SRAM: %s\n",(hasSRAM) ? "yes" : "no");
    printf("Mirror type: %s\n",(mirrorType) ? "vertical" : "horizontal");
    printf("PC10: %s\n",(isPC10) ? "yes" : "no");
    printf("VS Unisystem: %s\n",(isVSUnisystem) ? "yes" : "no");
    printf("----------------------\n");
}
