/*
BALTHAZAR 2020 Turbosavski

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

#include "quantum.h"

// 7x11 => diode dir = ROW2COL
// we scan 7 rows       left half 1-7            right half 1-7
// notation: K(col:01-11)(row:1-7)
#define LAYOUT_all( \
     K011, K012, K013, K014, K015, K016, K017,     K111, K112, K113, K114, K115, K116, K117, \
    K031, K021, K022, K023, K024, K025, K026, K027, K101, K102, K103, K104, K105, K106, K107, \
    K051, K041, K032, K033, K034, K035, K036, K037, K091, K092, K093, K094, K095, K096, K097, \
    K061, K062, K042, K043, K044, K045, K046, K047, K081, K082, K083, K084, K085, K086, K087, \
          K063, K052, K053, K054, K055, K056, K057, K071, K072, K073, K074, K075, K076, K077,  \
    	     K064,                                                          K065, K066, K067 \
) { \
    { K011, K021, K031, K041, K051, K061, K071, K081, K091, K101, K111 }, \
    { K012, K022, K032, K042, K052, K062, K072, K082, K092, K102, K112 }, \
    { K013, K023, K033, K043, K053, K063, K073, K083, K093, K103, K113 }, \
    { K014, K024, K034, K044, K054, K064, K074, K084, K094, K104, K114 }, \
    { K015, K025, K035, K045, K055, K065, K075, K085, K095, K105, K115 }, \
    { K016, K026, K036, K046, K056, K066, K076, K086, K096, K106, K116 }, \
    { K017, K027, K037, K047, K057, K067, K077, K087, K097, K107, K117 }, \
}

