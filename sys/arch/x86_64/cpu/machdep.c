/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sys/types.h>
#include <machine/msr.h>
#include <machine/idt.h>
#include <mu/cpu.h>
#include <mm/pool.h>

void
mu_cpu_conf(struct cpu_info *ci)
{
    if (ci == NULL) {
        return;
    }

    md_wrmsr(IA32_GS_BASE, (uintptr_t)ci);
    mm_pool_init(ci);
    md_idt_load();
}

struct cpu_info *
mu_cpu_self(void)
{
    return (void *)md_rdmsr(IA32_GS_BASE);
}
