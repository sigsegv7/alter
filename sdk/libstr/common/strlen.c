/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sys/types.h>
#include <string.h>

size_t
strlen(const char *str)
{
    size_t len = 0;

    if (str == NULL) {
        return 0;
    }

    while (str[len++] != '\0');
    return len - 1;
}
