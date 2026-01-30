#
# Copyright (c) 2026, Ian Moffett.
# Provided under the BSD-3 clause.
#

.PHONY: all
all: target kern arch boot

.PHONY: target
target:
	mkdir -p target/inc/machine
	rsync -avr inc/arch/$(ARCH_TARGET)/* target/inc/machine

.PHONY: kern
kern:
	cd kern/; make

.PHONY: arch
arch:
	cd arch/; make $(PASSDOWN_ARGS)

.PHONY: boot
boot:
	cd boot/arch/$(ARCH_TARGET); make $(PASSDOWN_ARGS)

.PHONY: clean
distclean:
	cd boot/$(ARCH_TARGET); make $(PASSDOWN_ARGS) distclean
