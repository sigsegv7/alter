/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <string.h>

void *
memcpy(void *dest, const void *src, size_t count)
{
    if (dest == NULL || src == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        ((char *)dest)[i] = ((char *)src)[i];
    }

    return dest;
}
