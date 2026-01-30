/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sys/units.h>
#include <sys/param.h>
#include <sys/types.h>
#include <os/syslog.h>
#include <os/btl.h>
#include <mm/frame.h>
#include <mm/vmm.h>
#include <string.h>

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

/* Bitmap */
static uint8_t *bitmap = NULL;
static size_t last_bit = 0;
static size_t bitmap_size = 0;

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
 * Set a range within the bitmap
 *
 * @start: Start address of range
 * @end:   End address of range
 * @alloc: If true, set range as allocated
 */
static void
bitmap_set_range(uintptr_t start, uintptr_t end, bool alloc)
{
    /* Clamp to page boundary */
    start = ALIGN_DOWN(start, PAGESIZE);
    end = ALIGN_UP(end, PAGESIZE);

    for (uintptr_t addr = start; addr < end; addr += PAGESIZE) {
        if (alloc) {
            SETBIT(bitmap, addr / PAGESIZE);
        } else {
            CLRBIT(bitmap, addr / PAGESIZE);
        }
    }
}

static void
bitmap_populate(void)
{
    struct btl_memmap_entry entry;
    uintptr_t start, end;

    for (size_t i = 0;; ++i) {
        if (btl_get_mementry(i, &entry) != 0) {
            break;
        }

        /* Get the range */
        start = entry.base;
        end = entry.base + entry.length;

        /* Is it allocated? */
        if (entry.type == BTL_MEM_USABLE) {
            bitmap_set_range(start, end, false);
            continue;
        }

    }
}

/*
 * Allocate a bitmap
 */
static void
bitmap_allocate(void)
{
    struct btl_memmap_entry entry;

    for (size_t i = 0;; ++i) {
        if (btl_get_mementry(i, &entry) != 0) {
            break;
        }

        /* Drop unusable entries */
        if (entry.type != BTL_MEM_USABLE) {
            continue;
        }

        /* Drop entries that are too small */
        if (entry.length < bitmap_size) {
            continue;
        }

        /* Set the bitmap and populate */
        bitmap = pma_to_vma(entry.base);
        memset(bitmap, 0xFFFFFFFF, bitmap_size);
        bitmap_populate();
        break;
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

    /* Compute the bitmap size */
    bitmap_size = mem_usable_top / PAGESIZE;
    bitmap_size /= 8;
}

/*
 * Allocate one or more physical memory frames
 */
static uintptr_t
frame_alloc(size_t count)
{
    ssize_t start_idx = -1;
    size_t frames_found = 0;
    uintptr_t start, end;
    size_t max_bit;

    max_bit = mem_usable_top / PAGESIZE;
    for (size_t i = last_bit; i < max_bit; ++i) {
        if (!TESTBIT(bitmap, i)) {
            if (start_idx < 0)
                start_idx = i;
            if ((++frames_found) >= count)
                break;

            continue;
        }

        start_idx = -1;
    }

    if (start_idx < 0) {
        return 0;
    }

    start = start_idx * PAGESIZE;
    end = start + (count * PAGESIZE);
    bitmap_set_range(start, end, true);
    return start;
}

uintptr_t
mm_frame_alloc(size_t count)
{
    uintptr_t phys;

    phys = frame_alloc(count);
    if (phys == 0) {
        last_bit = 0;
        phys = frame_alloc(count);
    }

    return phys;
}

void
mm_frame_free(uintptr_t base, size_t count)
{
    uintptr_t range_end;

    base = ALIGN_DOWN(base, PAGESIZE);
    range_end = base + (count * PAGESIZE);
    bitmap_set_range(base, range_end, false);
}

void
mm_frame_init(void)
{
    /* First probe physical memory */
    trace(LOG_INFO, "probing physical memory");
    frame_probe();

    /* Allocate a bitmap */
    bitmap_allocate();
}
