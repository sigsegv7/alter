#
# Copyright (c) 2026, Ian Moffett.
# Provided under the BSD-3 clause.
#

MISC_OFILES = $(shell find ../../ -name "*.o")
ASMFILES = $(shell find . -name "*.S")
ASMOFILES = $(ASMFILES:.S=.S.o)
CFILES = $(shell find . -name "*.c")
OFILES = $(CFILES:.c=.o)
DFILES = $(shell find . -name "*.d")

CFLAGS = 				\
	$(SYS_CFLAGS)		\
	-I../../inc			\
	-I../../target/inc/	\
	-D_KERNEL


LDFLAGS =					\
	-L../../../sdk/			\
	-lstr

.PHONY: all
all: $(ASMOFILES) $(OFILES)
	$(LD) $(MISC_OFILES) -Tconf/link.lds -o ../../alter.sys $(LDFLAGS)

%.S.o: %.S
	$(CC) -c $< $(CFLAGS) -o $@

-include $(DFILES)
%.o: %.c
	$(CC) -c $< $(CFLAGS) -I../../inc/ -MMD -o $@
