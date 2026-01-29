#
# Copyright (c) 2026, Ian Moffett.
# Provided under the BSD-3 clause.
#

.PHONY: all
all: boot

.PHONY: boot
boot:
	cd boot/$(ARCH_TARGET); make $(PASSDOWN_ARGS)

.PHONY: clean
clean:
	cd boot/$(ARCH_TARGET); make $(PASSDOWN_ARGS) clean
