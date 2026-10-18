#ifndef ASM_H
#define ASM_H

#include <stdint.h>

static inline void ASM_outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}
static inline void ASM_hlt() {
    __asm__ volatile ("hlt");
}

#endif

