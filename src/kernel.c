void main() {
  *(unsigned short *)0xb8000 = 'Q' | (0x0F << 8);
  while (1) {
  }
  return;
}