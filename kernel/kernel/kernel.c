
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

/** This is the entry point to the kernel. In its current form, the kernel
 *  simply initializes a simple terminal in VGA text mode and prints a simple
 *  'hello world message'.
 * 
 */
void kernel_main(void) {
    /* Initialize the terminal interface */
    initialize_terminal();

    /* Note: Newline support has not been implemented */
    write_string_to_terminal("Hello, kernel world!\n");
}
