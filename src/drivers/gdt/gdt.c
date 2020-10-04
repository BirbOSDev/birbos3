// GDT driver
#include <stddef.h>
#include <stdint.h>
#define MAX32BIT 0xFFFFFFFF // For readability.
struct gdt_entry {
  // first double word
  uint16_t limit_low; // first 16 bits in the segment limiter
  uint16_t base_low;  // first 16 bits in the base address
  // second double word
  uint8_t base_middle; // the next 8 bits of the base address
  uint8_t access;      // goes over type, privilege level and present flag
  uint8_t granularity; // goes over bits 16-19 in the segment limiter, attributes and granularity
  uint8_t base_high;   // last 8 bits of the base address
} __attribute__((packed)); // prevent padding bytes

struct gdt_descriptor {
  uint16_t size; // aka LIMIT
  uint32_t offset; // aka BASE
} __attribute__((packed)); // prevent padding bytes

struct gdt_entry gdt[3]; // Actual GDT table
struct gdt_descriptor gp; // GDT pointer

// This requires some ASM code to flush the GDT.
extern void _gdt_flush();

void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran) {
  // Sets up a GDT entry
  // num: Which entry in the GDT table to set up
  // base: Address on which the segment starts
  // limit: Size of the segment
  // access: Defines the type, privilege level and present flag
  // gran: Granularity.
  gdt[num].base_low = (base & 0xFFFF);
  gdt[num].base_middle = (base >> 16) & 0xFF;
  gdt[num].base_high = (base >> 24) & 0xFF;

  gdt[num].limit_low = (limit & 0xFFFF);
  gdt[num].granularity = ((limit >> 16) & 0x0F);

  gdt[num].granularity |= (gran & 0xF0);
  gdt[num].access = access;
}

void gdt_install() {
  // Installs the GDT

  // Calculate the GDT size
  gp.size = (sizeof(struct gdt_entry) * 3) - 1;
  // Set the GDT address
  gp.offset = &gdt;

  // Set up the null descriptor
  gdt_set_gate(0,0,0,0,0);
  // Set up the code and data segments
  gdt_set_gate(1, 0, MAX32BIT, 0x9A, 0xCF);
  gdt_set_gate(2, 0, MAX32BIT, 0x92, 0xCF);

  // Flush the GDT.
  _gdt_flush();
}
