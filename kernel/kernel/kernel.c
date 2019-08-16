 
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

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <kernel/tty.h>

#if defined(__linux__)
#error "This platform is not supported."
#endif

#if !defined(__i386__)
#error "The kernel requires an ix86-elf compiler."
#endif

/* TODO: Remove this function */
static void say_hello(void) {
    write_string_to_terminal("Hello, kernel world!\n");
}

/** This is the entry point to the kernel. In its current form, the kernel
 *  simply initializes a simple terminal in VGA text mode and prints a simple
 *  'hello world message'.
 * 
 */
void kernel_main(void) {
    /* Initialize the terminal interface */
    initialize_terminal();

    for (size_t i = 0; i < 5; ++i) {
        say_hello();
    }
}
