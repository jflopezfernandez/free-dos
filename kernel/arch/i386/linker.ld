
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