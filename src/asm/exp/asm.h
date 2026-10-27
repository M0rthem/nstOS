#ifndef ASM_H
#define ASM_H

#include <stdint.h>

static inline void ASM_outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}
static inline void ASM_hlt() {
    __asm__ volatile ("hlt");
}


#define DEFINE_CR_ACCESSORS(name, reg) \
    static inline uintptr_t read_##name(void) { \
        uintptr_t v; \
        asm volatile("mov %%" reg ", %0" : "=r"(v)); \
        return v; \
    } \
    static inline void write_##name(uintptr_t v) { \
        asm volatile("mov %0, %%" reg :: "r"(v) : "memory"); \
    }


DEFINE_CR_ACCESSORS(cr0, "cr0")
DEFINE_CR_ACCESSORS(cr2, "cr2")
DEFINE_CR_ACCESSORS(cr3, "cr3")
DEFINE_CR_ACCESSORS(cr4, "cr4")

#endif

