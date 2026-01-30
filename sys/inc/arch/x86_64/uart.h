/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _MACHINE_UART_H_
#define _MACHINE_UART_H_ 1

#include <sys/param.h>

/* COM ports */
#define UART_COM1   0x3F8
#define UART_COM2   0x2F8
#define UART_COM3   0x3F8
#define UART_COM4   0x2E8
#define UART_REG_OFF(COM, REG) ((COM) + (REG))

/* Valid UART 8250 registers */
#define UART_RXTX(COM)  (COM)
#define UART_INTEN(COM) UART_REG_OFF((COM), 0x01)
#define UART_LCR(COM)   UART_REG_OFF((COM), 0x03)

#define UART_DIVLOW(COM) UART_REG_OFF((COM), 0x00)
#define UART_DIVHIGH(COM) UART_REG_OFF((COM), 0x01)

#define UART_LCR_DLAB       BIT(7)
#define UART_LCR_STOP       BIT(2)
#define UART_PARITY_MASK    (0x07 << 3)

#endif  /* !_MACHINE_UART_H_ */
