/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <machine/pio.h>
#include <sys/cdefs.h>
#include <sys/types.h>

uint8_t
md_inb(uint16_t port)
{
    uint8_t result;
    __asmv("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

uint16_t
md_inw(uint16_t port)
{
    uint16_t val;
    __asmv("inw %w1, %w0" : "=a" (val) : "Nd" (port));
    return val;
}

uint32_t
md_inl(uint16_t port)
{
    uint32_t val;
    __asmv("inl %w1, %0" : "=a" (val) : "Nd" (port));
    return val;
}

void
md_outb(uint16_t port, uint8_t val)
{
    __asmv("out %%al, %%dx" : :"a" (val), "d" (port));
}

void
md_outw(uint16_t port, uint16_t val)
{
    __asmv("outw %w0, %w1" : : "a" (val), "Nd" (port));
}

void
md_outl(uint16_t port, uint32_t val)
{
    __asmv("outl %0, %w1" : : "a" (val), "Nd" (port));
}
