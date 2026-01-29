#
# Copyright (c) 2026, Ian Moffett.
# Provided under the BSD-3 clause.
#

include mk/default.mk

.PHONY: all
all: sys
	cd sys/boot/arch/$(ARCH_TARGET); ./iso

.PHONY: sys
sys:
	cd sys/; make $(PASSDOWN_ARGS)

.PHONY: clean
distclean:
	cd sys/; make distclean PASSDOWN_ARGS=$(PASSDOWN_ARGS)
