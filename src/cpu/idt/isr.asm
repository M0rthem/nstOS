[bits 32]
[extern idt_stub_hdlr]
[extern idt_timer_hdlr]

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

