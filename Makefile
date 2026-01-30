#
# Copyright (c) 2026, Ian Moffett.
# Provided under the BSD-3 clause.
#

include mk/default.mk

.PHONY: all
all: headers sdk sys
	cd sys/boot/arch/$(ARCH_TARGET); ./iso

.PHONY: sdk
sdk:
	cd sdk/; make $(PASSDOWN_ARGS)

.PHONY: headers
headers:
	mkdir -p sdk/inc/sys
	rsync -avr sys/inc/sys/*.h sdk/inc/sys

.PHONY: sys
sys:
	cd sys/; make $(PASSDOWN_ARGS)

.PHONY: clean
distclean:
	cd sys/; make distclean PASSDOWN_ARGS=$(PASSDOWN_ARGS)
