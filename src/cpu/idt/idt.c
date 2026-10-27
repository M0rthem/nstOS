#include <stdint.h>

#include "drivers/vga/exp/vga.h"


extern double sys_uptime;
extern void print_uptime(void);

typedef struct __attribute__((packed)) idt_entry {
  uint16_t low_offset;
  uint16_t selector;
  uint8_t reserved;
  uint8_t atr;
  uint16_t high_offset;
} idt_entry;

typedef struct __attribute__((packed)) idt_descript32m {
  uint16_t size;
  uint32_t offset;
} idt_descript32m;

idt_descript32m idt_descriptor;
idt_entry idtTable[256];

enum typesIdtGates32Enm {
  task_gate_32_E = 0x5,
  interrupt_gate_32_E = 0xE,
  trap_gate_32_E = 0xF
};

void idt_stub_hdlr() { return; }

void set_new_idt_32_entry(int num_interrupt, enum typesIdtGates32Enm type_int,
                          void (*handler)(void)) {
  if (num_interrupt >= 256 || num_interrupt < 0) {
    return;
  }

  uintptr_t handler_int = (uintptr_t)handler;
  idtTable[num_interrupt].low_offset = handler_int & 0xFFFF;
  idtTable[num_interrupt].selector = 0x8;
  idtTable[num_interrupt].reserved = 0;
  idtTable[num_interrupt].atr = 0x8E;
  idtTable[num_interrupt].high_offset = (handler_int >> 16) & 0xFFFF;
}

extern void isr_stub(void);
void timer_isr(void);
void page_fault_isr(void);
void setupIdt() {

  for (int i = 0; i != 256; i++) {
    set_new_idt_32_entry(i, interrupt_gate_32_E, isr_stub);
  }
  set_new_idt_32_entry(0x0E, interrupt_gate_32_E, page_fault_isr);
  set_new_idt_32_entry(0x20, interrupt_gate_32_E, timer_isr);
  idt_descriptor.size = sizeof(idtTable) - 1;
  idt_descriptor.offset = (uint32_t)(uintptr_t)idtTable;
  __asm__ volatile("lidt (%0)" : : "r"(&idt_descriptor));
  __asm__ volatile("sti");
}

void idt_timer_hdlr(void) {
  sys_uptime += 0.0549254;
  print_uptime();
  __asm__ volatile("outb %%al, %%dx" : : "a"(0x20), "d"(0x20));
}


void idt_page_fault_hdlr(void) {
    print_s((unsigned short *)VGA_START_TEXT, "im in pagging");	
    while(1) {}    
}
