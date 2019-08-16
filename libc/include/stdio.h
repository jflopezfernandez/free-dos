
#ifndef _STDIO_H
#define _STDIO_H 1

#include <kernel/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

/* TODO: Implement printf */
/* int printf(const char* __restrict format, ...); */

int putchar(int c);

int puts(const char* str);

#ifdef __cplusplus
}
#endif

#endif // _STDIO_H
