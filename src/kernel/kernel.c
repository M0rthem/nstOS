#include <stdint.h>

#include "cpu/idt/exp/idt.h"
#include "cpu/pagging/exp/pagging.h"

#include "drivers/pit/exp/pit.h"
#include "drivers/vga/exp/vga.h"

#include "asm/exp/asm.h"



#define MAX_LEN_UINT32 10

void uint_to_str(uint32_t number, char *string);

void kernel_start() {
	PAG_setup_identity_1Mb();
	setupIdt();
	setupPIT();
	while(1){ ASM_hlt(); }
}

void print_hello(void) {
  char *hello_str = "Hello World!";
  print_s((unsigned short *)VGA_START_TEXT, hello_str); 
}

uint32_t tick = 0;
double sys_uptime = 0;

void print_uptime(void) {
  char uptime_str[MAX_LEN_UINT32 + sizeof("uptime")] = "uptime";
  uptime_str[6] = ' ';
  uint_to_str((uint32_t)sys_uptime, &(uptime_str[7]));
  print_s((unsigned short*)VGA_START_TEXT, uptime_str);
}

int reverse_bytestring(char *byte_start, char *byte_end){
  unsigned int count_reverse = 0;
  char *left = byte_start;
  char *right = byte_end;
  if(left > right){
    return -1;
  }
  while(left != right){
     *left ^= *right;
     *right ^= *left;
     *left ^= *right;
     if(left + 1 == right){
        break;
     }
    left++;
    right--;
  }
  return 0;
}

void uint_to_str(uint32_t number, char *string) {
  if(number == 0){
    string[0] = '0';
    string[1] = '\0';
    return;
  }
  unsigned char count_symbols = 0;
  while(number != 0){
    string[count_symbols] = number % 10 + 48;
    count_symbols++;
    number /= 10;  
  }
  string[count_symbols] = '\0';
  reverse_bytestring(&string[0], &string[count_symbols - 1]);
}
