 
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

/** The bootloader will look at this image and start execution at the symbol
 *  designated as the entry point.
 *
 */
ENTRY(_start)

/** Tell the linker where the various sections of the object files will be put
 *  in the final kernel image.
 *
 */
SECTIONS
{
    /** Begin putting sections at 1 MiB, a conventional place for kernels to be
     *  loaded at by the bootloader.
     *
     */
    . = 1M;

    /** First put the multiboot header, as it is required to be put very early
     *  in the image or the bootloader won't recognize the file format. The text
     *  section should then follow the multiboot header.
     *
     */
    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }

    /** Read-only data
     *
     */
    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    /** Read-write data (initialized)
     *
     */
    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    /** Read-write data (uninitialized) and stack
     *
     */
    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }

    /** The compiler may produce other sections, and by default it will place
     *  them in a segment with the same name. Simply add stuff here as needed.
     *
     */
}
