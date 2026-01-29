/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _SYS_CDEFS_H_
#define _SYS_CDEFS_H_ 1

#define __asmv      __asm__ __volatile__
#define __attr(x)   __attribute__((x))
#define __align(n)  __attr(aligned((n)))
#define __packed    __attr(packed)
#define __no_return __attr(noreturn)

#endif  /* !_SYS_CDEFS_H_ */
