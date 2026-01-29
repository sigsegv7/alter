/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <string.h>

void *
memset(void *s, int c, size_t n)
{
    if (s == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < n; ++i) {
        ((int8_t *)s)[i] = c;
    }

    return s;
}
