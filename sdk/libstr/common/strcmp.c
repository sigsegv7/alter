/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sys/types.h>
#include <string.h>

int
strcmp(const char *s1, const char *s2)
{
    while (*s1 == *s2++) {
        if (*s1++ == 0) {
            return (0);
        }
    }

    return (*(uint8_t *)s1 - *(uint8_t *)--s2);
}
