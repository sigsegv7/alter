#
# Copyright (c) 2026, Ian Moffett.
# Provided under the BSD-3 clause.
#

BOOT_PROTO  = limine
ARCH_TARGET = x86_64

CC = \
	$(shell pwd)/var/cc/gcc/bin/$(ARCH_TARGET)-pc-lunota-gcc
LD = \
    $(shell pwd)/var/cc/toolchain/build-binutils/bin/$(ARCH_TARGET)-pc-lunota-ld
AR = \
	 $(shell pwd)/var/cc/toolchain/build-binutils/bin/$(ARCH_TARGET)-pc-lunota-ar

SYS_CFLAGS =			\
	-nostdlib			\
	-nostdinc			\
	-ffreestanding		\
	-fexceptions		\
	--std=gnu11			\
	-mcmodel=kernel		\
	-Wno-attributes		\
	-fno-stack-protector

ifeq ($(ARCH),x86_64)
	SYS_CFLAGS += 		\
		-mno-sse		\
		-mno-sse2		\
		-mno-sse3		\
		-mno-avx		\
		-mno-avx2		\
		-mno-80387		\
		-mno-3dnow
endif

PASSDOWN_ARGS = 				\
	ARCH_TARGET=$(ARCH_TARGET)  \
	CC=$(CC)					\
	LD=$(LD)					\
	SYS_CFLAGS="$(SYS_CFLAGS)"  \
	BOOT_PROTO=$(BOOT_PROTO)
