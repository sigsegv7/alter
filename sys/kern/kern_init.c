/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <os/syslog.h>
#include <os/btl.h>
#include <os/panic.h>
#include <io/cons.h>
#include <mu/uart.h>
#include <mu/cpu.h>
#include <mm/frame.h>

#define ALTER_VERSION "0.0.2"

struct console g_root_cons;
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

    /* Initialize the root console */
    if (console_init(&g_root_cons) != STATUS_SUCCESS) {
        panic("failed to initialize root console\n");
    }

    trace(LOG_INFO, "console online");
    for (;;);
}
