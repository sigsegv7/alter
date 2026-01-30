/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _OS_SYSLOG_H_
#define _OS_SYSLOG_H_

#include <sys/types.h>
#include <sys/stdarg.h>

#define SYSLOG_BUFSZ 64

typedef enum {
    LOG_INFO,
    LOG_ERROR
} log_level_t;

/*
 * Print a formatted string to the console
 */
ssize_t printf(const char *fmt, ...);

/*
 * Same as above but with va_list
 */
ssize_t vprintf(const char *fmt, va_list ap);

/*
 * Preferred logging function
 *
 * @level: Log level
 * @fmt:   Format string
 */
void trace(log_level_t level, const char *fmt, ...);

#endif  /* !_OS_SYSLOG_H_ */
