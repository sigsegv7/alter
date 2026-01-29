#
# Copyright (c) 2026, Ian Moffett.
# Provided under the BSD-3 clause.
#

.PHONY: all
all: boot

.PHONY: sys
boot:
	cd arch/$(ARCH_TARGET); make $(PASSDOWN_ARGS)

.PHONY: clean
distclean:
	cd arch/$(ARCH_TARGET); make distclean
