/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _MU_CPU_H_
#define _MU_CPU_H_ 1

#include <sys/types.h>

/*
 * Set an IRQ mask state
 *
 * @mask: If true, IRQs are masked and disabled
 */
void mu_irq_set_mask(bool mask);

#endif  /* !_MU_CPU_H_ */
