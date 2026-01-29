#
# Copyright (c) 2025, Ian Moffett and Lunota Software.
# Provided under the BSD-3 clause.
#

.PHONY: all
all: libstr

.PHONY: libstr
libstr:
	cd libstr/; $(MAKE) CC=$(CC) SYS_CFLAGS="$(SYS_CFLAGS)" LD=$(LD) AR=$(AR)
