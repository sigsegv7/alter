/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <os/btl.h>
#include <mu/uart.h>

int
kmain(void)
{
    /* Initialize boot protocol translation */
    btl_init();

    /* Initialize platform UART */
    mu_uart_init();

    for (;;);
}
