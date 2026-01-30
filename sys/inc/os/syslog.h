/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _OS_SYSLOG_H_
#define _OS_SYSLOG_H_

#include <sys/stdarg.h>

#define SYSLOG_BUFSZ 128

/*
 * Print a formatted string to the console
 */
void printf(const char *fmt, ...);

#endif  /* !_OS_SYSLOG_H_ */
