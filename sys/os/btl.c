/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <os/btl.h>

#ifndef _BOOT_PROTO
#error "Boot protocol undefined!"
#else
#define BOOT_PROTO _BOOT_PROTO
#endif

int
btl_init(void)
{
    return 0;
}
