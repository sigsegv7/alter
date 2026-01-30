/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _MM_VMM_H_
#define _MM_VMM_H_ 1

#include <sys/param.h>
#include <os/btl.h>

/* Address conversion macros */
#define vma_to_pma(vma) \
    (uintptr_t)PTR_NOFFSET(vma, btl_kernel_base())
#define pma_to_vma(pma) \
    PTR_OFFSET(pma, btl_kernel_base())

#define PAGESIZE 4096

#endif  /* !_MM_VMM_H_ */
