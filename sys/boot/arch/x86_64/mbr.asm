[bits 16]
[org 0x7C00]

;;
;; Loader entrypoint, BIOS passes control to us
;; here.
;;
_start:
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax
    jmp 0x00:entry

entry:
    cli
    cld
hang:
    hlt
    jmp hang

times 510 - ($ - $$) db 0
dw 0xAA55
