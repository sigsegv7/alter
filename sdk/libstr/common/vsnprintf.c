/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sys/types.h>
#include <sys/stdarg.h>
#include <string.h>

static inline void
printc(char *buf, size_t size, size_t *off, char c)
{
    if (*off < size - 1) {
        buf[(*off)++] = c;
    }
    buf[*off] = 0;
}

static void
printstr(char *buf, size_t size, size_t *off, const char *s)
{
    while (*off < size - 1 && *s != '\0') {
        buf[(*off)++] = *(s)++;
    }
    buf[*off] = 0;
}

int
snprintf(char *s, size_t size, const char *fmt, ...)
{
    va_list ap;
    int ret;

    va_start(ap, fmt);
    ret = vsnprintf(s, size, fmt, ap);
    va_end(ap);
    return ret;
}

int
vsnprintf(char *s, size_t size, const char *fmt, va_list ap)
{
    size_t tmp_len, num_len, off = 0;
    size_t num = 0;
    char c, c1, num_buf[256] = {0};
    const char *tmp_str;
    uint8_t pad_width = 0;

    while (off < (size - 1)) {
        while (*fmt && *fmt != '%') {
            printc(s, size, &off, *fmt++);
        }
        if (*(fmt)++ == '\0' || off == size - 1) {
            return off;
        }

        /*
         * Handle a case where we have "%0N". For example:
         * "%04d"
         */
        if (*fmt == '0') {
            ++fmt;
            while (*fmt >= '0' && *fmt <= '9') {
                pad_width = pad_width * 10 + (*fmt - '0');
                ++fmt;
            }
        }

        c = *fmt++;
        switch (c) {
        case 'c':
            c1 = (char )va_arg(ap, int);
            printc(s, size, &off, c1);
            break;
        case '%':
            printc(s, size, &off, c);
            break;
        case 'd':
            num = va_arg(ap, int64_t);
            itoa(num, num_buf, 10);

            if (pad_width > 0) {
                num_len = strlen(num_buf);
                for (size_t i = num_len; i < pad_width; ++i)
                    printc(s, size, &off, '0');
                pad_width = 0;
            }
            printstr(s, size, &off, num_buf);
            break;
        case 'p':
            num = va_arg(ap, uint64_t);
            itoa(num, num_buf, 16);
            tmp_len = strlen(num_buf);

            /* Add '0x' prefix */
            printc(s, size, &off, '0');
            printc(s, size, &off, 'x');

            /* XXX: Assumes 64-bit */
            for (size_t i = 0; i < 18 - tmp_len; ++i) {
                printc(s, size, &off, '0');
            }

            printstr(s, size, &off, num_buf + 2);
            break;
        case 'x':
            num = va_arg(ap, uint64_t);
            itoa(num, num_buf, 16);
            tmp_len = strlen(num_buf);
            printstr(s, size, &off, num_buf + 2);
            break;
        case 's':
            tmp_str = va_arg(ap, const char *);
            printstr(s, size, &off, tmp_str);
            break;
        }
    }

    return 0;
}
