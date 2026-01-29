/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

    .text
    .globl md_gdt_load
md_gdt_load:
    /*
     * [RDI]: GDTR
     */
    push %r12
    push %r13
    push %r14
    push %r15
    push %rbx
    push %rbp

    lgdt (%rdi)                 /* Load our own GDT */
    push $0x08                  /* Kernel CS */
    lea 1f(%rip), %rbx          /* Drop point */
    push %rbx                   /* RIP */
    lretq                       /* Flush prefetch + reload CS */
1:  mov $0x10, %ax              /* Kernel DS */
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %ss
    mov %ax, %fs
    xor %ax, %ax
    mov %ax, %gs

    pop %rbp
    pop %rbx
    pop %r15
    pop %r14
    pop %r13
    pop %r12
    retq

     .section .data
    .globl g_GDT
g_GDT:
.NULL:
    .word 0x0000
    .word 0x0000
    .byte 0x00
    .byte 0b00000000
    .byte 0b00000000
    .byte 0x00
.CODE:
    .word 0x0000
    .word 0x0000
    .byte 0x00
    .byte 0b10011010
    .byte 0b00100000
    .byte 0x00
.DATA:
    .word 0x0000
    .word 0x0000
    .byte 0x00
    .byte 0b10010010
    .byte 0b00000000
    .byte 0x00
.UCODE:
    .word 0x0000
    .word 0x0000
    .byte 0x00
    .byte 0b11111010
    .byte 0b10101111
    .byte 0x00
.UDATA:
    .word 0x0000
    .word 0x0000
    .byte 0x00
    .byte 0b11110010
    .byte 0b00000000
    .byte 0x00
.TSS:
    .quad 0x00
    .quad 0x00

    .globl g_GDTR
g_GDTR:
    .word g_GDTR - g_GDT
    .quad g_GDT
