
#ifndef _STRING_H
#define _STRING_H 1

#include <sys/cdefs.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int memcmp(const void* s1, const void* s2, size_t size);

void* memcpy(void* __restrict dest, const void* __restrict src, size_t size);

void* memmove(void* dest, const void* __restrict src, size_t size);

/** This function sets the first n bytes of the specified buffer with a constant
 *  byte value.
 * 
 */
void* memset(void* buffer, int value, size_t buffer_length);

/** This is the canonical strlen function found in the C standard library. It
 *  will eventually be moved to the libc module, but as it is immediately
 *  necessary it is being written here now.
 * 
 */
size_t strlen(const char* str);

#ifdef __cplusplus
}
#endif

#endif // _STRING_H
