/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sys/types.h>
#include <os/syslog.h>
#include <os/panic.h>
#include <os/spinlock.h>
#include <mu/cpu.h>
#include <string.h>

static struct spinlock lock;
static char panic_buf[256];
static va_list panic_ap;

__no_return void
panic(const char *fmt, ...)
{
    mu_irq_set_mask(true);

    /*
     * We'll acquire this lock and never release it so that on a
     * multiprocessor system, processors don't cause a race if multiple
     * panics stack.
     */
#if defined(_ALTER_MULTICORE)
    spinlock_acquire(&lock, true);
#endif  /* _ALTER_MULTICORE */

    va_start(panic_ap, fmt);
    vsnprintf(panic_buf, sizeof(panic_buf), fmt, panic_ap);
    printf("panic: %s", fmt);

    for (;;) {
        mu_cpu_hlt();
    }
}
