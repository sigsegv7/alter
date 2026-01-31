/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sys/types.h>
#include <sys/units.h>
#include <os/spinlock.h>
#include <os/panic.h>
#include <mm/pool.h>
#include <mm/frame.h>
#include <mm/vmm.h>

#define POOLSIZE_BYTES (UNIT_MIB * 8)
#define POOLSIZE_PAGES (POOLSIZE_BYTES / PAGESIZE)

void *
mm_pool_allocate(size_t sz)
{
    struct cpu_info *ci = mu_cpu_self();
    void *tmp;

    spinlock_acquire(&ci->tlsf_lock, true);
    tmp = tlsf_malloc(ci->tlsf_ctx, sz);
    spinlock_release(&ci->tlsf_lock);
    return tmp;
}

void
mm_pool_free(void *pool)
{
    struct cpu_info *ci = mu_cpu_self();

    spinlock_acquire(&ci->tlsf_lock, true);
    tlsf_free(ci->tlsf_ctx, pool);
    spinlock_release(&ci->tlsf_lock);
}

void
mm_pool_init(struct cpu_info *ci)
{
    void *pool_virt_base;
    uintptr_t pool_pma;

    if (ci == NULL) {
        return;
    }

    pool_pma = mm_frame_alloc(POOLSIZE_PAGES);
    if (pool_pma == 0) {
        panic("pool: could not initialize root pool\n");
    }

    pool_virt_base = pma_to_vma(pool_pma);
    ci->tlsf_ctx = tlsf_create_with_pool(pool_virt_base, POOLSIZE_BYTES);
}
