 
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

/** The most important piece to create is the multiboot header, as it must be
 *  defined very early in the kernel binary, or the bootloader will fail to
 *  recognize it.
 *
 *  We begin by declaring some constants for the multiboot header.
 *
 *      ALIGN       Align loaded modules on page boundaries
 *
 *      MEMINFO     Provide a memory map
 *
 *      FLAGS       This is the multiboot 'flag' field
 *
 *      MAGIC       This 'magic number' lets the bootloader find the header
 *
 *      CHECKSUM    This is a checksum of the previously-declared constants, to
 *                  prove to the bootloader that we are genuinely a multiboot
 *                  header.
 *
 *  Documentation for the multiboot standard may be found at the Free Software
 *  Foundation's website:
 *
 *      https://www.gnu.org/software/grub/manual/multiboot/multiboot.html
 *
 */
.set ALIGN,     1<<0
.set MEMINFO,   1<<1
.set FLAGS,     ALIGN | MEMINFO
.set MAGIC,     0x1BADB002
.set CHECKSUM,  -(MAGIC + FLAGS)

/** Declare a multiboot header that marks the program as a kernel. These are
 *  'magic' values that are documented in the multiboot standard. The bootloader
 *  will search for this signature in the first 8 KiB of the kernel file,
 *  aligned at a 32-bit boundary. The signature is in its own section so the
 *  header can be forced to be within the first 8KiB of the kernel file.
 *
 */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/** The multiboot standard does not define the value of the stack pointer
 *  register(esp), and it is up to the kernel to provide a stack. The following
 *  commands allocate room for a small stack by creating a symbol at the bottom
 *  of it, allocating 16,384 bytes for it, and finally creating a symbol at the
 *  top. The stack grows downwards on x86. The stack is in its own section so it
 *  can be marked 'nobits', which means the kernel file is smaller because it
 *  does not contain an uninitialized stack. The stack on x86 must be 16-byte
 *  aligned according to the System V ABI standard and de-facto extensions. The
 *  compiler will assume the stack is properly aligned and failure to align the
 *  stack will result in undefined behavior.
 *
 */
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

/** The linker script specifies _start as the entry point to the kernel and the
 *  bootloader will jump to this position once the kernel has been loaded. It
 *  doesn't make any sense to return from this function as the bootloader is
 *  gone.
 *
 *  Once the _start subroutine has been entered, the bootloader has loaded us
 *  into 32-bit protected mode on an x86 machine. Interrupts and paging are
 *  disabled, and the processor state is as defined in the multiboot standard
 *  (see above).
 *
 *  The kernel has full control of the CPU but it can only
 *  make use of hardware features and any code it provides support for itself.
 *  There is no printf function, unless the kernel provides its own <stdio.h>
 *  header and a printf implementation. There are no security restrictions, no
 *  safeguards, no debugging mechanisms, etc. There is only what the kernel
 *  explicitly provides itself. It has complete and absolute control over the
 *  machine.
 *
 */
.section .text
.global _start
.type _start, @function
_start:
    /** To set up a stack, we set the esp register to point to the top of the
     *  stack (as it grows downwards on x86 systems). This is necessarily done
     *  in assembly as languages such as C cannot function without a stack.
     *
     */
    mov $stack_top, %esp

    /** This is a good place to initialize crucial processor state before the
     *  high-level kernel is entered. It's best to minimize the early
     *  environment where crucial features are offline. Note that the processor
     *  is not fully initialized yet: floating-point and instruction set
     *  extensions have not been initialized yet. The global descriptor table
     *  (GDT) should be loaded here, and paging should be enabled here as well.
     *  C++ features such as global constructors and exceptions will require
     *  runtime support to work as well.
     *
     *  TODO: Initialize floating-point instructions
     *  TODO: Initialize instruction-set extensions
     *  TODO: Load global descriptor table (GDT)
     *  TODO: Enable paging
     */

    /** Enter the high-level kernel. The ABI requires the stack to be 16-byte
     *  aligned at the time of the call instruction (which afterwards pushes the
     *  return pointer of size 4 bytes). The stack was originally 16-byte
     *  aligned and we've since pushed a multiple of 16 bytes to the stack
     *  (pushed 0 bytes so far), so the alignment has thus been preserved and
     *  the call is well-defined.
     *
     */
    call kernel_main

    /** If the system has nothing more to do, put the computer into an infinite
     *  loop. To do that:
     *
     *      1) Disable interrupts with cli (clear interrupt enable in eflags).
     *         They are already disabled by the bootloader, so this is not
     *         really needed, but why not, right? Mind that you might later
     *         enable interrupts and return from kernel_main (which would also
     *         not really make sense, but again, why not?).
     *
     *      2) Wait for the next interrupt to arrive with hlt (halt
     *         instruction). Since they are disabled this will lock up the
     *         computer.
     *
     *      3) Jump to the hlt instruction if it ever wakes up due to a
     *         non-maskable interrupt occurring, or due to system management
     *         mode.
     *
     */
    cli
1:  hlt
    jmp 1b

/** Set the size of the _start symbol to the current location ('.') minus its
 *  start location. This is useful when debugging or when you implement call
 *  tracing.
 *
 */
.size _start, . - _start
