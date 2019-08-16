
#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

/* TODO: Documentation */
void initialize_terminal(void);

/* TODO: Documentation */
void terminal_putchar(char c);

/* TODO: Documentation */
void terminal_write(const char* data, size_t size);

/** This function is a wrapper around the terminal_write function. It serves as
 *  a more user-friendly interface that saves the caller from having to
 *  calculate the length of their output string on every call.
 * 
 */
void write_string_to_terminal(const char* str);

#endif // _KERNEL_TTY_H
