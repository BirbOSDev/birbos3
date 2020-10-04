// Defines, use with OR for type_attr
#pragma once
#define PRESENT_BIT 0b10000000 // Sets gate as present
#define DPL_ZERO    0b00000000 // Sets minimimum privilege level to 0
#define DPL_MAX     0b01100000 // Sets minimum privilege level to 3
#define S_INTERRUPT 0b00000000 // Storage segment for interrupt/trap gates
#define S_TASK      0b00010000 // Storage segment for task gates
#define TYPE_32TASK 0b00000101 // 80386 32 bit task gate type
#define TYPE_16INT  0b00000110 // 80286 16 bit interrupt gate
#define TYPE_16TRAP 0b00000111 // 80286 16 bit trap gate
#define TYPE_32INT  0b00001110 // 80386 32 bit interrupt gate
#define TYPE_32TRAP 0b00001111 // 80386 32 bit trap gate
