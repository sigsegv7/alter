/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _OS_BTL_H_
#define _OS_BTL_H_ 1

#include <sys/types.h>

/*
 * Represents a boot translation layer screen
 * descriptor
 *
 * @width:      Framebuffer width
 * @height:     Framebuffer height
 * @pitch:      Framebuffer pitch
 * @address:    Framebuffer MMIO base
 */
struct btl_screen {
    uint64_t width;
    uint64_t height;
    uint64_t pitch;
    uint32_t *address;
};

/*
 * Boot translation layer protocol structure
 *
 * @kernel_base: Kernel load base
 * @screen:      Screen in use
 */
struct btl_proto {
    uintptr_t kernel_base;
    struct btl_screen screen;
};

/*
 * Initialize the boot protocol translation layer
 *
 * Returns zero on success
 */
int btl_init(void);

/*
 * Obtain the protocol descriptor in-use
 *
 * @res: Result is written here
 *
 * Returns zero on success
 */
int btl_get_proto(struct btl_proto *res);

/* Protocol backends */
int btl_limine_init(struct btl_proto *res);

#endif  /* !_OS_BTL_H_ */
