/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sys/types.h>
#include <os/syslog.h>
#include <mu/uart.h>
#include <string.h>

static void
write_str(const char *s)
{
    size_t len;

    if (s == NULL) {
        return;
    }

    len = strlen(s);
    mu_uart_writed(s, len);
}

void
printf(const char *fmt, ...)
{
    char buf[SYSLOG_BUFSZ];
    va_list ap;

    if (fmt == NULL) {
        return;
    }

    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    write_str(buf);
}
