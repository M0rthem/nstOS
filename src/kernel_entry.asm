[bits 32]
[extern print_hello]
[extern setupIdt]
[extern idt_stub_hdlr]
[extern idt_timer_hdlr]

global start
start:
    mov al, 0x11
    out 0x20, al
    out 0xA0, al
    mov al, 0x20
    out 0x21, al
    mov al, 0x28
    out 0xA1, al

    call setupIdt
    int 0xC8
    jmp $

global isr_stub
isr_stub:
    pusha
    call print_hello
    popa
    iret

global timer_isr
timer_isr:
    pusha
    call idt_timer_hdlr
    popa
    iret
