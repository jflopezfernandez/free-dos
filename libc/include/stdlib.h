 
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

#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

/** This function abruptly terminates the calling process. In technical terms,
 *  this call results in the abnormal termination of the process, possibly
 *  resulting in deadlocks and data corruption. As POSIX.1 standard permits
 *  implementations to choose whether to flush streams, FreeDOS will attempt to
 *  close and flush streams owned by the current process.
 * 
 */
__attribute__((noreturn))
void abort(void);

#ifdef __cplusplus
}
#endif

#endif // _STDLIB_H
