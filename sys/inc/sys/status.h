/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _SYS_STATUS_H_
#define _SYS_STATUS_H_ 1

#define STATUS_SUCCESS      0   /* Success */
#define STATUS_FAILURE      1   /* Failure */
#define STATUS_NOT_FOUND    2   /* Resource not found */
#define STATUS_NO_MEM       3   /* Out of memory */
#define STATUS_DENIED       4   /* Access denied */
#define STATUS_BUSY         5   /* Resource is busy */
#define STATUS_INVALID_ARG  6   /* Invalid argument */

typedef int status_t;

#endif  /* !_SYS_STATUS_H_ */
