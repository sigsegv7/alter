/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sys/types.h>
#include <sys/status.h>
#include <boot/limine.h>
#include <os/btl.h>

#define FRAMEBUFFER fb_resp->framebuffers[0]

/* Framebuffer */
static struct limine_framebuffer_response *fb_resp = NULL;
static volatile struct limine_framebuffer_request fb_req = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

/* HHDM */
static struct limine_hhdm_response *hhdm_resp = NULL;
static volatile struct limine_hhdm_request hhdm_req = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};

static int
limine_getscr_info(struct btl_proto *res)
{
    struct btl_screen *screen;

    if (res == NULL) {
        return STATUS_INVALID_ARG;
    }

    screen = &res->screen;
    screen->width = FRAMEBUFFER->width;
    screen->height = FRAMEBUFFER->height;
    screen->pitch = FRAMEBUFFER->pitch;
    screen->address = FRAMEBUFFER->address;
    return STATUS_SUCCESS;
}

int
btl_limine_init(struct btl_proto *res)
{
    if (res == NULL) {
        return STATUS_INVALID_ARG;
    }

    fb_resp = fb_req.response;
    hhdm_resp = hhdm_req.response;
    res->kernel_base = hhdm_resp->offset;

    if (limine_getscr_info(res) != STATUS_SUCCESS) {
        return -1;
    }

    return 0;
}
