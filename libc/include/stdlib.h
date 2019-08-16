
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
