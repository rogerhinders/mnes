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


#ifndef EMULATOR_H
#define EMULATOR_H

#include "cart.h"
#include "cpu.h"
#include "mmu.h"
#include "ppu.h"
#include "input.h"

class Emulator {

public:
    Emulator( const char* path, u32* screen );
    ~Emulator();
    void run();
    void setKey(u8 key,u8 event);

private:
    u32* screen;
    Cart* rom;
    CPU* cpu;
    MMU* mmu;
    PPU* ppu;
    Input* input;
};

#endif // EMULATOR_H
