/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sys/types.h>
#include <sys/cdefs.h>
#include <machine/idt.h>
#include <machine/gdt.h>

__align(8) static struct idt_gate idt[256];
static struct idtr idtr = {
    .limit = sizeof(idt) - 1,
    .base = (uintptr_t)&idt[0]
};

void
md_idt_set_gate(uint8_t vector, uintptr_t isr, uint8_t type, uint8_t ist)
{
    struct idt_gate *gate;

    gate = &idt[vector];
    gate->offset_low   = (isr & 0xFFFF);
    gate->offset_mid   = (isr >> 16) & 0xFFFF;
    gate->offset_high  = (isr >> 32) & 0xFFFFFFFF;
    gate->p = 1;
    gate->dpl = (type == IDT_USER_GATE) ? 3 : 0;
    gate->zero = 0;
    gate->zero1 = 0;
    gate->reserved = 0;
    gate->type = type;
    gate->ist = ist;
    gate->segment_sel = GDT_KCODE;
}

void
md_idt_load(void)
{
    __asmv("lidt %0" :: "m" (idtr) : "memory");
}
