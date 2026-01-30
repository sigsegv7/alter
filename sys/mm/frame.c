/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sys/units.h>
#include <sys/types.h>
#include <os/syslog.h>
#include <os/btl.h>
#include <mm/frame.h>

/*
 * Memory type table used to convert type constants to
 * human readable strings
 */
static const char *typetab[] = {
    [BTL_MEM_USABLE] = "usable",
    [BTL_MEM_RESERVED] = "reserved",
    [BTL_MEM_ACPI_RECLAIM] = "ACPI reclaim",
    [BTL_MEM_ACPI_NVS] = "ACPI NVS",
    [BTL_MEM_BAD] = "bad",
    [BTL_MEM_BOOTLOADER] = "bootloader",
    [BTL_MEM_KERNEL] = "alter.sys",
    [BTL_MEM_FRAMEBUFFER] = "framebuffer"
};

/* Memory stats */
static size_t mem_total = 0;
static size_t mem_usable = 0;
static uintptr_t mem_usable_top = 0;

/*
 * Helper to print sizes in human readable units
 */
static inline void
print_size(const char *title, size_t count)
{
    if (count >= UNIT_GIB) {
        trace(LOG_INFO, "%s: %d GiB", title, count / UNIT_GIB);
    } else if (count >= UNIT_MIB) {
        trace(LOG_INFO, "%s: %d MiB", title, count / UNIT_MIB);
    } else {
        trace(LOG_INFO, "%s: %d bytes", title, count);
    }
}

/*
 * Scan physical memory and collect statistics about it
 * for future allocations
 */
static void
frame_probe(void)
{
    struct btl_memmap_entry entry;

    for (size_t i = 0;; ++i) {
        if (btl_get_mementry(i, &entry) != 0) {
            break;
        }

        /* Compute the highest address */
        mem_total += entry.length;
        if ((entry.base + entry.length) >= mem_usable_top) {
            mem_usable_top = entry.base + entry.length;
        }

        trace(
            LOG_INFO,
            "%p - %p : %s",
            entry.base,
            entry.base + entry.length,
            typetab[entry.type]
        );

        /* Get total usable memory */
        if (entry.type == BTL_MEM_USABLE) {
            mem_usable += entry.length;
        }

        /* Skip unusable entries */
        if (entry.type != BTL_MEM_USABLE) {
            continue;
        }
    }

    /* Print statistics */
    print_size("installed memory", mem_total);
    print_size("usable memory", mem_usable);
    printf("usable top @ %p\n", mem_usable_top);
}

void
frame_init(void)
{
    /* First probe physical memory */
    trace(LOG_INFO, "probing physical memory");
    frame_probe();
}
