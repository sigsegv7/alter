#
# Copyright (c) 2026, Ian Moffett.
# Provided under the BSD-3 clause.
#

MISC_OFILES = $(shell find ../../ -name "*.o")
ASMFILES = $(shell find . -name "*.S")
ASMOFILES = $(ASMFILES:.S=.S.o)

LDFLAGS =					\
	-L../../../sdk/			\
	-lstr

.PHONY: all
all: $(ASMOFILES)
	$(LD) $(MISC_OFILES) -Tconf/link.lds -o ../../alter.sys $(LDFLAGS)

%.S.o: %.S
	$(CC) -c $< $(SYS_CFLAGS) -o $@
