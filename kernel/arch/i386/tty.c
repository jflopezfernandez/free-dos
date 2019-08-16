
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <string.h>

#include <kernel/tty.h>

#include "vga.h"

/** This preprocessor macro defines the number of columns in VGA text mode.
 * 
 */
#define VGA_WIDTH (80)

/** This preprocessor macro defines the number of rows in VGA text mode.
 * 
 */
#define VGA_HEIGHT (25)

/** This variable keeps track of the current row in the VGA text mode buffer. It
 *  is critical to keep track of the row because this is the variable that makes
 *  terminal scrolling possible, as well as being the variable that indicates
 *  when terminal scrolling should take place.
 * 
 */
size_t current_terminal_row = 0;

/** This variable keeps track of the current column in the VGA text mode buffer.
 *  It is used for indicating when we've reached the end of the current line and
 *  need to move to the next line, as well as for simulating cursor reset when
 *  a newline character is detected.
 * 
 */
size_t current_terminal_column = 0;

/** This variable contains the color for the current terminal. Technically
 *  speaking, it contains two colors: the foreground color and the background
 *  color, which can be set by calling the vga_entry_color function. This
 *  variable can then be used as the second input to the vga_entry function.
 * 
 */
uint8_t terminal_color;

/** This is the pointer used to hold the address of the VGA text mode buffer.
 *  The VGA text mode buffer itself is located at 0xB8000, but the VGA
 *  monochrome text buffer is located at 0xB0000, giving us at least two options
 *  with respect to the text buffer we use. This is the variable used for
 *  selecting the desired text buffer.
 * 
 */
uint16_t* terminal_buffer = NULL;

/* TODO: Documentation */
void initialize_terminal(void) {
    /* Shouldn't this be done using set_terminal color??? */
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

    terminal_buffer = (uint16_t *) 0xB8000;

    for (size_t y = 0; y < VGA_HEIGHT; ++y) {
        for (size_t x = 0; x < VGA_WIDTH; ++x) {
            const size_t index = y * VGA_WIDTH + x;

            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

/** TODO: Documentation????????????????????????????????????????????????????????
 * 
 *  TODO: Shouldn't this function handle setting the terminal color in
 *        initialize_terminal? Possible refactor into set_term_color(fg, bg) and
 *        call vga_entry_color to get uint8_t value.
 * 
 */
void set_terminal_color(uint8_t color) {
    terminal_color = color;
}

/* TODO: Documentation */
void terminal_put_entry_at(char c, uint8_t color, size_t x, size_t y) {
    /** The VGA text mode buffer is (spoiler alert) a buffer. Specifically,
     *  however, it is a one-dimensional buffer, in which we are trying to store
     *  two-dimensional data (two-dimensional because we have rows and columns,
     *  not all of which will be full all of the time, and we need to be able
     *  to go back and extend a line without having to shift everything over in
     *  memory).
     * 
     *  To solve this dimensionality dilemma, we need to calculate an offset for
     *  the current row and column position of the output, and to do this, we
     *  simply multiply y by the width of a line and add x. This allows us to
     *  essentially divide the text buffer into 25 equal segments of 80
     *  characters each, allowing us to treat this one-dimensional segment as a
     *  two-dimensional structure for our screen output.
     * 
     */
    const size_t index = y * VGA_WIDTH + x;

    terminal_buffer[index] = vga_entry(c, color);
}

/* TODO: Documentation */
void terminal_putchar(char c) {
    terminal_put_entry_at(c, terminal_color, current_terminal_column, current_terminal_row);

    if (++current_terminal_column == VGA_WIDTH) {
        current_terminal_column = 0;

        if (++current_terminal_row == VGA_HEIGHT) {
            /** Since we've had to increment the current terminal row, this is
             *  where a terminal scroll is handled. To do this, we'll need to
             *  have a memory buffer in which to hold the scroll back. Ideally,
             *  we'll also have a memory buffer in which to house terminal
             *  command history.
             * 
             *  TODO: This code, written as-is, simply wraps output from the
             *        bottom to the top, rather than 'scrolling' the terminal
             *        up. This needs to be fixed as soon as possible, as terminal
             *        output would be completely rewritten, possibly overwriting
             *        valuable log or error output.
             * 
             */
            current_terminal_row = 0;
        }
    }
}

/* TODO: Documentation */
void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        terminal_putchar(data[i]);
    }
}

/** This function is a wrapper around the terminal_write function. It serves as
 *  a more user-friendly interface that saves the caller from having to
 *  calculate the length of their output string on every call.
 * 
 */
void write_string_to_terminal(const char* str) {
    terminal_write(str, strlen(str));
}
