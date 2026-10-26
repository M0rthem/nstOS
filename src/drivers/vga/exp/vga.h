#ifndef VGA_H
#define VGA_H

#define VGA_START_TEXT 0x000B8000

void print_s(unsigned short *vga_start, char *str);

#endif
