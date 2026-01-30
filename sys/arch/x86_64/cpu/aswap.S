/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

    .text
    .globl mu_aswap
mu_aswap:
    xchg %rsi, (%rdi)
    mov %rsi, %rax
    retq
