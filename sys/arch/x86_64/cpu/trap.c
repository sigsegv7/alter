/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#include <sys/param.h>
#include <os/panic.h>
#include <machine/frame.h>
#include <machine/trap.h>

/* Used to convert trap codes to strings */
static const char *traptab[] = {
    [TRAP_DIVERR] = "divide error",
    [TRAP_DBG]    = "debug exception",
    [TRAP_NMI]    = "non-maskable interrupt",
    [TRAP_BP]     = "breakpoint",
    [TRAP_OF]     = "overflow",
    [TRAP_BR]     = "bound range exceeded",
    [TRAP_UD]     = "undefined opcode",
    [TRAP_NM]     = "no math coprocessor",
    [TRAP_DF]     = "double fault",
    [TRAP_CPR]    = "reserved exception",
    [TRAP_TS]     = "invalid TSS",
    [TRAP_NP]     = "segment not present",
    [TRAP_SS]     = "stack segment fault",
    [TRAP_GP]     = "general protection fault",
    [TRAP_PF]     = "page fault"
};

/* Forward declaration */
void trap_dispatch(struct trapframe *tf);

void
trap_dispatch(struct trapframe *tf)
{
    const char *str;

    if (tf->vector >= NELEM(traptab)) {
        panic("fatal unknown vector %x\n", tf->vector);
    }

    panic("fatal %s\n", traptab[tf->vector]);
}
