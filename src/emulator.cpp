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


#include "emulator.h"
#include "disassembler.h"
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "tables.h"
#include "regs.h"

using namespace std;

Emulator::Emulator( const char* path, u32* screen ) {
    this->screen = screen;
    
    input = new Input();
    rom = new Cart( path );
    mmu = new MMU( rom, input );
    cpu = new CPU( mmu );
    ppu = new PPU( cpu, this->screen, mmu );
    mmu->setCPU(cpu);

}

Emulator::~Emulator() {
    delete rom;
    delete cpu;
    delete mmu;
    delete ppu;
}

void Emulator::run() {
    while(!ppu->update()) {
        cpu->execInstr( mmu->memRead8( cpu->PC ) );

        //printf("PC: %x \n",cpu->PC);

    }

}

void Emulator::setKey( u8 key, u8 event ) {
    input->setButtonState( key, event );
}