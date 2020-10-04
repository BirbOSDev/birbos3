; GDT flushing code
; Used by the GDT driver
global _gdt_flush
extern gp
_gdt_flush:
    ; Load the new GDT.
    lgdt [gp]
    ; Reload segment registers
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ; Do a far jump to load the CS register.
    jmp 0x08:finishflush
finishflush:
    ret
