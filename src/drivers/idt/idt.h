#pragma once
extern void idt_setup_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t type_attr);
extern void idt_install();
