/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sys/types.h>
#include <os/syslog.h>
#include <io/cons.h>
#include <mu/uart.h>
#include <string.h>

/*
 * Write a raw string to the console
 *
 * TODO: This perhaps needs locking
 */
static size_t
write_str(const char *s)
{
    size_t len;

    if (s == NULL) {
        return 0;
    }

    len = strlen(s);
    mu_uart_writed(s, len);
    cons_puts(&g_root_cons, s, len);
    return len;
}

ssize_t
vprintf(const char *fmt, va_list ap)
{
    char buf[SYSLOG_BUFSZ];

    if (fmt == NULL) {
        return -1;
    }

    vsnprintf(buf, sizeof(buf), fmt, ap);
    write_str(buf);
}

ssize_t
printf(const char *fmt, ...)
{
    va_list ap;
    size_t count;

    if (fmt == NULL) {
        return -1;
    }

    va_start(ap, fmt);
    count = vprintf(fmt, ap);
    va_end(ap);
    return count;
}

void
trace(log_level_t level, const char *fmt, ...)
{
    size_t count, pad_count;
    va_list ap;
    char c;

    va_start(ap, fmt);
    count = vprintf(fmt, ap);
    va_end(ap);

    switch (level) {
    case LOG_ERROR:
        c = '*';
        break;
    default:
        c = '.';
        break;
    }

    pad_count = SYSLOG_BUFSZ - count - 1;
    for (size_t i = 0; i < pad_count; ++i) {
        printf("%c", c);
    }
    printf("\n");
}
