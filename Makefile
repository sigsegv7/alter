#
# Copyright (c) 2026, Ian Moffett.
# Provided under the BSD-3 clause.
#

include mk/default.mk

.PHONY: all
all: sys

.PHONY: sys
sys:
	cd sys/; make PASSDOWN_ARGS=$(PASSDOWN_ARGS)

.PHONY: clean
clean:
	cd sys/; make clean PASSDOWN_ARGS=$(PASSDOWN_ARGS)
