/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _KERN_MMIO_H_
#define _KERN_MMIO_H_ 1

#include <sys/cdefs.h>

/*
 * mmio_write<n> - Writes to MMIO address with specific size
 *
 * @addr: Address to write to.
 * @val: Value to write.
 *
 * These functions will add the higher half
 * offset (VM_HIGHER_HALF) if the MMIO address
 * is less than VM_HIGHER_HALF as it'll be safe
 * to assume it's a physical address. Page faults
 * from writes could be due to the resulting virtual
 * address not being mapped.
 */
#define _MMIO_WRITE_TYPE(TYPE, SUFFIX)                  \
    static inline void                                  \
    mmio_write##SUFFIX(volatile void *addr, TYPE val)   \
    {                                                   \
                                                        \
        *(volatile TYPE *)addr = val;                   \
        __barrier();                                    \
    }

/*
 * mmio_read<n> - Does the same as mmio_write<n> but for reading
 *
 * @addr: Address to read from.
 */
#define _MMIO_READ_TYPE(TYPE, SUFFIX)                   \
    static inline TYPE                                  \
    mmio_read##SUFFIX(volatile void *addr)              \
    {                                                   \
        __barrier();                                    \
        return *(volatile TYPE *)addr;                  \
    }


/*
 * To write to an MMIO address of, for example,
 * 8 bits, use mmio_write8(addr, val)
 */
_MMIO_WRITE_TYPE(uint8_t, 8)
_MMIO_WRITE_TYPE(uint16_t, 16)
_MMIO_WRITE_TYPE(uint32_t, 32)
#if __SIZEOF_SIZE_T__ == 8
_MMIO_WRITE_TYPE(uint64_t, 64)
#endif
__extension__

/*
 * To read from an MMIO address of, for example,
 * 8 bits, use mmio_read8(addr)
 */
_MMIO_READ_TYPE(uint8_t, 8)
_MMIO_READ_TYPE(uint16_t, 16)
_MMIO_READ_TYPE(uint32_t, 32)
#if __SIZEOF_SIZE_T__ == 8
_MMIO_READ_TYPE(uint64_t, 64)
#endif
__extension__


#endif  /* !_KERN_MMIO_H_ */
