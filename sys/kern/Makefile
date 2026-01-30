#
# Copyright (c) 2026, Ian Moffett.
# Provided under the BSD-3 clause.
#

CFILES = $(shell find . -name "*.c")
CFILES += $(shell find ../os -name "*.c")
CFILES += $(shell find ../mm -name "*.c")
CFILES += $(shell find ../proto -name "*.c")
DFILES = $(CFILES:.c=.d)
OFILES = $(CFILES:.c=.o)

CFLAGS = 					\
	$(SYS_CFLAGS) 			\
	-I../../sdk/libstr/inc/ \
	-I../inc/ 				\
	-D_KERNEL				\
	-MMD					\
	-D_BOOT_PROTO="\"$(BOOT_PROTO)\""

.PHONY: all
all: $(OFILES)

-include $(DFILES)
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
