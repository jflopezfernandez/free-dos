
#ifndef ARCH_I386_VGA_H
#define ARCH_I386_VGA_H

#include <stdint.h>

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
