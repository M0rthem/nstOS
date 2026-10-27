[bits 32]
[extern idt_stub_hdlr]
[extern idt_timer_hdlr]
[extern idt_page_fault_hdlr]

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

global page_fault_isr
page_fault_isr:
    pusha
    call idt_page_fault_hdlr
    popa
    iret


