/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <os/btl.h>

int
kmain(void)
{
    /* Initialize boot protocol translation */
    btl_init();

    for (;;);
}
