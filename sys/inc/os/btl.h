/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _OS_BTL_H_
#define _OS_BTL_H_ 1

#include <sys/status.h>
#include <sys/types.h>

/*
 * Valid memory types
 */
typedef enum {
    BTL_MEM_USABLE,
    BTL_MEM_RESERVED,
    BTL_MEM_ACPI_RECLAIM,
    BTL_MEM_ACPI_NVS,
    BTL_MEM_BAD,
    BTL_MEM_BOOTLOADER,
    BTL_MEM_KERNEL,
    BTL_MEM_FRAMEBUFFER
} btl_memtype_t;

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
 * Represents a valid memory map entry
 *
 * @base:   Memory entry base
 * @length: Length of memory entry
 * @type:   Memory entry type
 */
struct btl_memmap_entry {
    uint64_t base;
    uint64_t length;
    btl_memtype_t type;
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
 */
status_t btl_init(void);

/*
 * Obtain a memory map entry by index
 *
 * @index: Index of memory map entry to obtain
 * @res:   Result of memory map descriptor
 */
status_t btl_get_mementry(size_t index, struct btl_memmap_entry *res);

/*
 * Obtain the protocol descriptor in-use
 *
 * @res: Result is written here
 */
status_t btl_get_proto(struct btl_proto *res);

/* Protocol backends */
status_t btl_limine_init(struct btl_proto *res);

#endif  /* !_OS_BTL_H_ */
