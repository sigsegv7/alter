/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _MACHINE_PIO_H_
#define _MACHINE_PIO_H_ 1

#include <sys/types.h>

uint8_t md_inb(uint16_t port);
uint16_t md_inw(uint16_t port);
uint32_t md_inl(uint16_t port);

void md_outb(uint16_t port, uint8_t val);
void md_outw(uint16_t port, uint16_t val);
void md_outl(uint16_t port, uint32_t val);

#endif  /* !_MACHINE_PIO_H_ */
