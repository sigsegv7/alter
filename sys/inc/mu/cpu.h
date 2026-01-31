/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _MU_CPU_H_
#define _MU_CPU_H_ 1

#include <sys/types.h>

/*
 * Represents a logical processor
 *
 * @id: Logical processor ID (assigned by us)
 */
struct cpu_info {
    uint32_t id;
};

extern struct cpu_info g_bsp;

/*
 * Configure a processor descriptor
 *
 * @ci: Processor descriptor to initialize
 */
void mu_cpu_conf(struct cpu_info *ci);

/*
 * Get a reference to the current processor descriptor
 *
 * Returns NULL on failure
 */
struct cpu_info *mu_cpu_self(void);

/*
 * Set an IRQ mask state
 *
 * @mask: If true, IRQs are masked and disabled
 */
void mu_irq_set_mask(bool mask);

/*
 * Get the IRQ mask state
 *
 * Returns true if IRQs are masked
 */
bool mu_irq_get_mask(void);

/*
 * Spinwait hint for the processor
 */
void mu_cpu_spinwait(void);

/*
 * Halt the current processor until the next
 * interrupt
 */
void mu_cpu_hlt(void);

#endif  /* !_MU_CPU_H_ */
