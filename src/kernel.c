#include <stdint.h>

typedef struct __attribute__((packed)) idt_entry {
  uint16_t low_offset;
  uint16_t selector;
  char reserved;
  struct __attribute__((packed)) {
    unsigned char gate_type : 4;
    unsigned char zero : 1;
    unsigned char dpl : 2;
    unsigned char P : 1;
  };
  uint16_t high_offset;
} idt_entry;

typedef struct idt_descript32m {
  uint16_t size;
  uint32_t offset;
} idt_descript32m;

idt_descript32m idt_descriptor;
idt_entry idtTable[256];

void idt_stub_hdlr() { __asm__ volatile("iret"); }

// void set_new_idt_entry(int ) {}

void setupIdt() {
  idt_entry stub_entry;
  stub_entry.low_offset = (uint32_t)idt_stub_hdlr & 0xFFFF;
  stub_entry.selector = 0x8;
  stub_entry.reserved = 0;
  stub_entry.gate_type = 0xE;
  stub_entry.zero = 0;
  stub_entry.dpl = 0;
  stub_entry.P = 1;
  stub_entry.high_offset = ((uint32_t)idt_stub_hdlr >> 16) & 0xFFFF;

  for (int i = 0; i != 256; i++) {
    idtTable[i].low_offset = stub_entry.low_offset;
    idtTable[i].selector = stub_entry.selector;
    idtTable[i].reserved = stub_entry.reserved;
    idtTable[i].gate_type = stub_entry.gate_type;
    idtTable[i].zero = stub_entry.zero;
    idtTable[i].dpl = stub_entry.dpl;
    idtTable[i].P = stub_entry.P;
    idtTable[i].high_offset = stub_entry.high_offset;
  }

  idt_descriptor.size = sizeof(idtTable) - 1;
  idt_descriptor.offset = (uint32_t)idtTable;
  __asm__ volatile("lidt (%0)" : : "r"(&idt_descriptor));
}

void main() {
  char *hello_str = "Hello World!";
  unsigned short *now_pos = (unsigned short *)0xb8000;
  for (int i = 0; i != 12; i++) {
    *now_pos = hello_str[i] | (0x0F << 8);
    now_pos += 1;
  }

  while (1) {
  }
  return;
}