
[BITS 32]
global _start
_start:
    mov esp, _sys_stack
    jmp stublet
	
MBALIGN  equ  1 << 0 
MEMINFO  equ  1 << 2
FLAGS    equ  MBALIGN | MEMINFO
MAGIC    equ  0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)


segment .text
global _multiboot_header
_multiboot_header:
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

       dd 0
    dd 0
    dd 0
    dd 0
    dd 0

    dd 1
    dd 0
    dd 0
    dd 0


stublet:
    extern _birbkernel
    push eax
    push ebx
    call _birbkernel
    jmp $

_sys_stack: