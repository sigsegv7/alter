/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _MM_POOL_H_
#define _MM_POOL_H_ 1

#include <sys/types.h>
#include <mu/cpu.h>

/*
 * Initialize a pool for a specific processor
 *
 * @ci: Descriptor of target processor
 */
void mm_pool_init(struct cpu_info *ci);

/*
 * Free memory allocated with mm_pool_allocate()
 *
 * @pool: Base of memory to free
 */
void mm_pool_free(void *pool);

/*
 * Allocate memory
 *
 * @sz: Number of bytes to allocate
 */
void *mm_pool_allocate(size_t sz);

#endif  /* !_MM_POOL_H_ */
