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


#include <iostream>
#include <fstream>
#include <iomanip>
#include "cart.h"

using namespace std;

Cart::Cart( const char* path ) {
    ifstream file( path, ios::in|ios::binary|ios::ate );
    ifstream::pos_type size;

    if( file.is_open() ) {
        size = file.tellg();
        rom = new u8[size];
        file.seekg( 0, ios::beg );
        file.read( ( char* ) rom, size );
        file.close();

        //read the cart header
        hdr = new Header();
        hdr->readHeader( rom );
    } else {
        cout << "ERROR: CANNOT OPEN FILE!" << endl;
    }
    chrRomOffset = HEADER_SIZE + hdr->numPrgPages * 0x4000 + hdr->hasPatch * 512;
}

Cart::~Cart() {
    delete[] rom;
    delete hdr;
}