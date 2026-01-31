/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _IO_CONS_H_
#define _IO_CONS_H_ 1

#include <sys/types.h>
#include <sys/status.h>
#include <os/spinlock.h>
#include <os/btl.h>

/*
 * Represents a system console
 *
 * @present: If set, console is present
 * @tx: Text X position
 * @ty: Text Y position
 * @cols: Left to right
 * @rows: Top to bottom
 * @fg: Foreground
 * @bg: Background
 * @lock: Protects this structure
 * @screen: Console screen
 */
struct console {
    uint8_t present : 1;
    size_t tx;
    size_t ty;
    size_t cols;
    size_t rows;
    uint32_t fg;
    uint32_t bg;
    struct spinlock lock;
    struct btl_screen screen;
};

extern struct console g_root_cons;

/*
 * Initialize the console
 */
status_t console_init(struct console *console);

/*
 * Write to the console
 *
 * @cons: Console to write to
 * @s:    String to write to console
 * @len:  Length of string in bytes
 */
void cons_puts(struct console *cons, const char *s, size_t len);

#endif  /* !_IO_CONS_H_ */
