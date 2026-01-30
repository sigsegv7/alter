/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sys/types.h>
#include <os/spinlock.h>
#include <mu/aswap.h>
#include <mu/cpu.h>

status_t
spinlock_acquire(struct spinlock *lock, bool irqmut)
{
    bool irq_mask;

    if (lock == NULL) {
        return STATUS_INVALID_ARG;
    }

    /* Mask IRQs if we can */
    irq_mask = mu_irq_get_mask();
    if (irqmut && !irq_mask) {
        mu_irq_set_mask(true);
    }

    while (mu_aswap(&lock->atom, 1)) {
        mu_cpu_spinwait();
    }

    /* Unmask IRQs if we masked them */
    if (irqmut && !irq_mask) {
        mu_irq_set_mask(false);
    }

    return STATUS_SUCCESS;
}

status_t
spinlock_release(struct spinlock *lock)
{
    if (lock == NULL) {
        return STATUS_INVALID_ARG;
    }

    mu_aswap(&lock->atom, 0);
    return STATUS_SUCCESS;
}
