/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

    .text
    .globl mu_irq_set_mask
mu_irq_set_mask:
    test $1, %rdi
    jnz .irq_mask
    jmp .irq_unmask
.irq_mask:
    cli
    jmp .exit
.irq_unmask:
    sti
    jmp .exit
.exit:
    retq

    .globl mu_irq_get_mask
mu_irq_get_mask:
    pushfq
    pop %rax
    shr $9, %rax
    and $1, %rax
    retq

    .globl mu_cpu_spinwait
mu_cpu_spinwait:
    pause
    retq
