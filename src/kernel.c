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