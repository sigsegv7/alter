/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _OS_SPINLOCK_H_
#define _OS_SPINLOCK_H_ 1

#include <sys/types.h>
#include <sys/status.h>
#include <mu/aswap.h>

#define SPINLOCK_NAMELEN 16

/*
 * Represents a spinlock that can be acquired and
 * released.
 */
struct spinlock {
    swap_atom_t atom;
};

/*
 * Acquire a spinlock
 *
 * @lock:   Spinlock to acquire
 * @irqmut: If set mutate IRQs
 */
status_t spinlock_acquire(struct spinlock *lock, bool irqmut);

/*
 * Release a spinlock
 *
 * @lock:  Spinlock to release
 */
status_t spinlock_release(struct spinlock *lock);

#endif  /* !_OS_SPINLOCK_H_ */
