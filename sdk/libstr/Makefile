#
# Copyright (c) 2025, Ian Moffett and Lunota Software.
# Provided under the BSD-3 clause.
#

CFILES = $(shell find . -name "*.c")
OFILES = $(CFILES:.c=.o)
CFLAGS = $(SYS_CFLAGS) -I../libsys/inc/ -I../inc/ -Iinc -D_ALTER_SOURCE

.PHONY: all
all: $(OFILES)
	$(AR) rcs ../libstr.a $(OFILES)

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@
