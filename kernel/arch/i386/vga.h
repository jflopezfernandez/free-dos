 
/** Copyright (C) 2019 Jose Fernando Lopez Fernandez
 *
 *  This file is part of the FreeDOS Operating System.
 *
 *  The FreeDOS Operating System is free software: you can redistribute
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

#ifndef ARCH_I386_VGA_H
#define ARCH_I386_VGA_H

#include <stdint.h>

/** This is the address of the VGA text mode buffer into which the terminal can
 *  begin to write. This address is the location of the beginning of the first
 *  line on the screen.
 * 
 */
#define VGA_TEXT_MODE_BUFFER (uint16_t *) 0xB8000

/** This enumeration contains the hardware text mode color constants used by
 *  the VGA text mode buffer.
 * 
 */
enum vga_color_t {
    VGA_COLOR_BLACK,
    VGA_COLOR_BLUE,
    VGA_COLOR_GREEN,
    VGA_COLOR_CYAN,
    VGA_COLOR_RED,
    VGA_COLOR_MAGENTA,
    VGA_COLOR_BROWN,
    VGA_COLOR_LIGHT_GREY,
    VGA_COLOR_DARK_GREY,
    VGA_COLOR_LIGHT_BLUE,
    VGA_COLOR_LIGHT_GREEN,
    VGA_COLOR_LIGHT_CYAN,
    VGA_COLOR_LIGHT_RED,
    VGA_COLOR_LIGHT_MAGENTA,
    VGA_COLOR_LIGHT_BROWN,
    VGA_COLOR_WHITE
};

/** This function combines the foreground and background color inputs into one
 *  unsigned 8-bit value usable in VGA text mode.
 * 
 *  TODO: Write better documentation for vga_entry_color()
 * 
 */
static inline uint8_t vga_entry_color(enum vga_color_t foreground_color, enum vga_color_t background_color) {
    return foreground_color | background_color << 4;
}

/** This function combines an unsigned character value with the color specified
 *  using the vga_entry_color function to create a single unsigned 16-bit value
 *  that can be used as output in VGA text mode.
 * 
 *  TODO: Write better documentation for vga_entry
 * 
 */
static inline uint16_t vga_entry(unsigned char character, uint8_t color) {
    return (uint16_t) character | (uint16_t) color << 8;
}

#endif // ARCH_I386_VGA_H
