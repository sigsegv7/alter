/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _OS_PANIC_H_
#define _OS_PANIC_H_ 1

#include <sys/cdefs.h>
#include <sys/stdarg.h>

/*
 * Indicate to the user that something terrible has happened and
 * the system needs to halt.
 */
__no_return void panic(const char *fmt, ...);

#endif  /* !_OS_PANIC_H_ */
