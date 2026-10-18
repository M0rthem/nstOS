[bits 32]
[extern print_hello]
[extern setupIdt]
[extern kernel_start]
[extern idt_stub_hdlr]
[extern idt_timer_hdlr]

global start
start:
    ;remaping the PIC
    mov al, 0x11
    out 0x20, al
    out 0xA0, al
    mov al, 0x20
    out 0x21, al
    mov al, 0x28
    out 0xA1, al

	
    call kernel_start
    jmp $


global isr_stub
isr_stub:
    pusha
    nop
    popa
    iret

global timer_isr
timer_isr:
    pusha
    call idt_timer_hdlr
    popa
    iret
