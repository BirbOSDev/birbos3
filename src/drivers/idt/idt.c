// IDT driver
#include <stddef.h>
#include <stdint.h>
struct IDTDescriptor {
  uint16_t offset_1; // offset bits 0..15
  uint16_t selector; // a code segment selector in GDT or LDT
  uint8_t zero;      // unused, set to zero
  uint8_t type_attr; // type and attributes, see comments below
  uint16_t offset_2; // offset bits 16..31
} __attribute__((packed));

struct IDTPointer {
  uint16_t size;
  uint32_t offset;
} __attribute__((packed));

struct IDTDescriptor idt[256];
struct IDTPointer idtp;

extern void _idt_load();

void idt_setup_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t type_attr) {
  // Sets up an IDT gate
  // num:  which gate to set up
  // base: address of interrupt service routine
  // sel:  code segment selector in GDT/LDT
  // type_attr: same as type_attr in the struct
  idt[num].base_lo = (base & 0xFFFF);
  idt[num].base_hi = (base >> 16) & 0xFFFF;
  idt[num].selector = sel;
  idt[num].zero = 0;
  idt[num].type_attr = type_attr;
}

void idt_install() {
  // Installs the IDT.
  // Calculate IDT size
  idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
  // Set IDT pointer
  idtp.base = &idt;
  // Set IDT to zeros
  memset(&idt, 0, sizeof(struct idt_entry) * 256);
  // Run the IDT load assembly routine
  _idt_load();
}
