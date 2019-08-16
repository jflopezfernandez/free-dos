 
/** Copyright (C) 2019 Jose Fernando Lopez Fernandez
 *
 *  This file is part of the FreeDOS C Standard Library.
 *
 *  The FreeDOS C Standard Library is free software: you can redistribute
 *  it and/or modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <string.h>

/** This function sets the first n bytes of the specified buffer with a constant
 *  byte value.
 * 
 */
void* memset(void* buffer, int value, size_t buffer_length) {
    unsigned char* typecast_buffer = (unsigned char *) buffer;

    for (size_t i = 0; i < buffer_length; ++i) {
        typecast_buffer[i] = value;
    }

    return buffer;
}
