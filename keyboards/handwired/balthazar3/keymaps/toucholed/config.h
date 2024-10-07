/*
Copyright 2024 g1smo

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

//#define OLED_FONT_H "glcdfont.c"

// Invalid row/col, bootmagic is used just to clear EEPROM
#define BOOTMAGIC_ROW 13
#define BOOTMAGIC_COLUMN 13

// EEPROM size; whether password is set (1 byte) + password hash (16 bytes)
#define EECONFIG_KB_DATA_SIZE 17
