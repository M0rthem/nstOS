#include <stdint.h>

#define MAX_LEN_UINT32 10
void uint_to_str(uint32_t number, char *string);

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
void setupIdt() {

  for (int i = 0; i != 256; i++) {
    set_new_idt_32_entry(i, interrupt_gate_32_E, isr_stub);
  }
  set_new_idt_32_entry(0x20, interrupt_gate_32_E, timer_isr);
  set_new_idt_32_entry(0x08, interrupt_gate_32_E,
                       timer_isr); /*now timer is 0x08*/
  idt_descriptor.size = sizeof(idtTable) - 1;
  idt_descriptor.offset = (uint32_t)(uintptr_t)idtTable;
  __asm__ volatile("lidt (%0)" : : "r"(&idt_descriptor));
  __asm__ volatile("sti");
}

void print_s(unsigned short *vga_start, char *str);
void print_hello(void) {
  char *hello_str = "Hello World!";
  print_s((unsigned short *)0xb8000, hello_str); 
}

uint32_t tick = 0;

void print_tick(void) {
  char tick_str[MAX_LEN_UINT32 + sizeof("tick")] = "tick";
  tick_str[4] = ' ';
  uint_to_str(tick, &(tick_str[5]));
  print_s((unsigned short *)0xb8020, tick_str);
}
void idt_timer_hdlr(void) {
  tick++;
  print_tick();
  __asm__ volatile("outb %%al, %%dx" : : "a"(0x20), "d"(0x20));
}

void uint_to_str(uint32_t number, char *string) {
  if(number == 0){
    string[0] = '0';
    string[1] = '\n';
    return;
  }
  char buffer[MAX_LEN_UINT32];
  unsigned char count_symbols = 0;
  while(number != 0){
    buffer[count_symbols] = number % 10 + 48;
    count_symbols++;
    number /= 10;  
  }
  for(int i = 0; i != count_symbols; i++){
    string[i] = buffer[count_symbols - i - 1];
  }  
  string[count_symbols] = '\0';
}

void print_s(unsigned short *vga_start, char *str){ 
  unsigned short *now_pos =(unsigned short *) vga_start;
  char *now_char = str;
  while (*now_char != '\0') {
    *now_pos = *now_char | (0x0F << 8);
    now_pos += 1;
    now_char++;
  }
}
