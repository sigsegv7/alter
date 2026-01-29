#
# Copyright (c) 2026, Ian Moffett.
# Provided under the BSD-3 clause.
#

MBR_PATH = mbr.asm
NASM = nasm
NASM_FLAGS = -fbin

.PHONY: all
all: pad mbr

.PHONY: pad
pad:
	dd if=/dev/zero of=tail.bin bs=512 count=4096

.PHONY: mbr
mbr:
	$(NASM) $(NASM_FLAGS) $(MBR_PATH) -o head.bin
	cat head.bin tail.bin >mbr.bin
	rm head.bin tail.bin

.PHONY: clean
clean:
	rm -f *.bin
