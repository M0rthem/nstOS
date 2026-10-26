#include <stdint.h>
#include "drivers/vga/exp/vga.h"

void print_s(unsigned short *vga_start, char *str){ 
  unsigned short *now_pos =(unsigned short *) vga_start;
  char *now_char = str;
  while (*now_char != '\0') {
    *now_pos = *now_char | (0x0F << 8);
    now_pos += 1;
    now_char++;
  }
}

