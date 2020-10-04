global _idt_load
extern idtp
_idt_load:
    lidt [idtp]
    ret
