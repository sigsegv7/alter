/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sys/status.h>
#include <os/btl.h>
#include <string.h>

#ifndef _BOOT_PROTO
#error "Boot protocol undefined!"
#else
#define BOOT_PROTO _BOOT_PROTO
#endif

static struct btl_proto proto;

int
btl_get_proto(struct btl_proto *res)
{
    if (res == NULL) {
        return STATUS_INVALID_ARG;
    }

    *res = proto;
    return STATUS_SUCCESS;
}

int
btl_init(void)
{
    switch (*BOOT_PROTO) {
    case 'l':
        if (strcmp(BOOT_PROTO, "limine") == 0) {
            return btl_limine_init(&proto);
        }

        break;
    }

    return STATUS_FAILURE;
}
