/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _MM_FRAME_H_
#define _MM_FRAME_H_ 1

#include <sys/types.h>

/*
 * Allocate one or more page frames
 *
 * @count: Number of page frames to allocate
 */
uintptr_t mm_frame_alloc(size_t count);

/*
 * Free one or more page frames
 *
 * @base: Base of memory to free
 * @count: Number of frames to free
 */
void mm_frame_free(uintptr_t base, size_t count);

/*
 * Initialize the frame manager
 */
void mm_frame_init(void);

#endif  /* !_MM_FRAME_H_ */
