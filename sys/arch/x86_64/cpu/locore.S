/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

    .text
    .globl _start
    .extern kmain
_start:
    cli
    cld

    xor %rbp, %rbp
    call kmain

1:  cli
    hlt
    jmp 1b
