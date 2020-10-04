#include "drivers/vga.h"
//#include "drivers/gdt/gdt.h"
//#include "drivers/idt/idt.h"
#include "drivers/stdlib.h"


#if defined(__linux__)
#error "You are using a linux compiler, a baremetal compiler is required"
#endif


#if !defined(__i386__)
#error "This will not work on x86_64"
#endif

void _birbkernel(void){
    terminal_initialize();
    terminal_putchar('x');
    asm("int 3");
    terminal_writestring("[Works] VGA.c\n");
    for(;;){};
}