[bits 32]
[extern print_hello]
[extern setupIdt]
[extern idt_stub_hdlr]
[extern idt_timer_hdlr]


global start
start:

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