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

    /* Disable the legacy i8259s */
    mov $0xFF, %al
    out %al, $0x21
    out %al, $0xA1

    /* Call the kernel */
    xor %rbp, %rbp
    call kmain

1:  cli
    hlt
    jmp 1b
