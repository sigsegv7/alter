/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sys/param.h>
#include <sys/types.h>
#include <io/cons.h>
#include <io/consfont.h>
#include <os/btl.h>
#include <os/spinlock.h>
#include <os/panic.h>
#include <mm/pool.h>
#include <string.h>

#include <os/syslog.h>

#define DEFAULT_FG 0x808080
#define DEFAULT_BG 0x000000

/*
 * Obtain the framebuffer index
 */
static inline size_t
fbdev_get_index(const struct btl_screen *fbdev, uint32_t x, uint32_t y)
{
    if (fbdev == NULL) {
        return 0;
    }

    return x + y * (fbdev->pitch / 4);
}

/*
 * Clear the entire console
 *
 * @cons: Console to clear
 */
static void
cons_clear(struct console *cons)
{
    struct btl_screen *fbdev;

    cons->tx = 0;
    cons->ty = 0;

    fbdev = &cons->screen;
    memset(fbdev->address, cons->bg, fbdev->height * fbdev->pitch);
}

/*
 * Render a character to the screen
 *
 * @cons: Console to blit char to
 * @c:    Char to blit
 */
static void
cons_blit_char(struct console *cons, char c)
{
    struct btl_screen *fbdev;
    const uint8_t *glyph;
    size_t idx;

    if (cons == NULL) {
        return;
    }

    glyph = &g_CONS_FONT[(int)c * 16];
    fbdev = &cons->screen;

    for (int cy = 0; cy < FONT_HEIGHT; ++cy) {
        idx = fbdev_get_index(
            &cons->screen,
            cons->tx + (FONT_WIDTH - 1),
            cons->ty + cy
        );

        for (int cx = 0; cx < FONT_WIDTH; ++cx) {
            fbdev->address[idx--] = ISSET(glyph[cy], BIT(cx)) ? cons->fg : cons->bg;
        }
    }
}

/*
 * Insert a newline to the console
 *
 * @cons: Target console
 */
static void
cons_newline(struct console *cons)
{
    struct btl_screen *fbdev;

    if (cons == NULL) {
        return;
    }

    fbdev = &cons->screen;
    cons->tx = 0;
    cons->ty += FONT_HEIGHT;
    if (cons->ty >= fbdev->height - FONT_HEIGHT) {
        cons_clear(cons);
    }
}

/*
 * Returns true if the given character is a special
 * character, and handles it for the given console.
 */
static bool
cons_is_special(struct console *cons, char c)
{
    if (cons == NULL) {
        return false;
    }

    switch (c) {
    case '\n':
        cons_newline(cons);
        return true;
    }

    return false;
}

static void
__cons_putch(struct console *cons, char c)
{
    struct btl_screen *fbdev;

    if (cons == NULL) {
        return;
    }

    if (cons_is_special(cons, c)) {
        return;
    }

    fbdev = &cons->screen;
    cons_blit_char(cons, c);
    cons->tx += FONT_WIDTH;
    if (cons->tx >= fbdev->width - FONT_WIDTH) {
        cons_newline(cons);
    }
}

void
cons_puts(struct console *cons, const char *s, size_t len)
{
    if (cons == NULL) {
        return;
    }

    if (!cons->present) {
        return;
    }

    for (size_t i = 0; i < len; ++i) {
        __cons_putch(cons, *(s++));
    }
}

status_t
console_init(struct console *console)
{
    struct btl_proto proto;

    if (console == NULL) {
        return STATUS_INVALID_ARG;
    }

    if (btl_get_proto(&proto) < 0) {
        return STATUS_FAILURE;
    }

    memcpy(&console->screen, &proto.screen, sizeof(console->screen));
    console->fg = DEFAULT_FG;
    console->bg = DEFAULT_BG;

    console->rows = console->screen.height / FONT_HEIGHT;
    console->cols = console->screen.width / FONT_WIDTH;
    console->present = 1;
    return STATUS_SUCCESS;
}
