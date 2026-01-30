/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _MU_ASWAP_H_
#define _MU_ASWAP_H_ 1

#include <sys/types.h>

/* Represents the swap element */
typedef size_t swap_atom_t;

/*
 * Perform an atomic swap operator
 *
 * Returns the value at 'ptr' before it was swapped
 * with 'v'
 */
size_t mu_aswap(swap_atom_t *ptr, swap_atom_t v);

#endif  /* !_MU_ASWAP_H_ */
