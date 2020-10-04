#include "stdlib.h"

size_t strlen(const char* str) {
    asm volatile ("1: jmp 1b");
    size_t len = 0;
    terminal_putchar('h');
    while (str[len] != 0) {
        len++;
    }
    return len;
}

