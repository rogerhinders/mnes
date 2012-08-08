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


#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include "types.h"

#define BTN_A      7
#define BTN_B      6
#define BTN_SELECT 5
#define BTN_START  4
#define BTN_UP     3
#define BTN_DOWN   2
#define BTN_LEFT   1
#define BTN_RIGHT  0

#define BTN_PRESSED 1

#define BTN_RELEASED 0


class Input {

public:
    Input();
    void setButtonState( u8 button, u8 state );
    void recordButtons();
    u8 readInput();
private:
    u8 btnStat[8];
    std::vector<u8> buttonRecord;
};

#endif // INPUT_H
