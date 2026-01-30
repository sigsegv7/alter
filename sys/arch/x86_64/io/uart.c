/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sys/param.h>
#include <sys/types.h>
#include <machine/uart.h>
#include <machine/pio.h>
#include <mu/uart.h>

#define DEFAULT_PORT UART_COM1

static uint16_t commap[] = {
    UART_COM1, UART_COM2,
    UART_COM3, UART_COM4
};

static void
init_uart(uint16_t port)
{
    uint8_t reg;

    /* Clear DLAB bit */
    reg = md_inb(UART_LCR(port));
    reg &= ~UART_LCR_DLAB;
    reg &= ~UART_PARITY_MASK;
    reg |= UART_LCR_STOP;
    md_outb(UART_LCR(port), reg);

    /* Disable interrupts */
    md_outb(UART_INTEN(port), 0);

    /* Set DLAB */
    reg = md_inb(UART_LCR(port));
    reg |= UART_LCR_DLAB;
    md_outb(UART_LCR(port), reg);

    /* 38400 baud */
    md_outb(UART_DIVLOW(port), 0x03);
    md_outb(UART_DIVHIGH(port), 0x00);

    reg &= ~UART_LCR_DLAB;
    md_outb(UART_LCR(port), reg);
}

void
mu_uart_writed(const char *s, size_t len)
{
    for (size_t i = 0; i < len; ++i) {
        md_outb(DEFAULT_PORT, s[i]);
    }
}

void
mu_uart_init(void)
{
    for (int i = 0; i < NELEM(commap); ++i) {
        init_uart(commap[i]);
    }
}
