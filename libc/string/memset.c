
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
