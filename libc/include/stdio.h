 
/** Copyright (C) 2019 Jose Fernando Lopez Fernandez
 *
 *  This file is part of the FreeDOS C Standard Library.
 *
 *  The FreeDOS C Standard Library is free software: you can redistribute
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
