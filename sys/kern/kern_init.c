/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <os/syslog.h>
#include <os/btl.h>
#include <mu/uart.h>
#include <mu/cpu.h>
#include <mm/frame.h>

#define ALTER_VERSION "0.0.1"

struct cpu_info g_bsp;

int
kmain(void)
{
    /* Initialize boot protocol translation */
    btl_init();

    /* Initialize platform UART */
    mu_uart_init();

    /* Write version to console */
    printf("booting alter [v%s]\n", ALTER_VERSION);

    /* Initialize the frame manager */
    mm_frame_init();

    /* Initialize bootstrap processor */
    mu_cpu_conf(&g_bsp);

    for (;;);
}
