[bits 32]
[extern main]
[extern setupIdt]

global start
start:
    
    call setupIdt
    jmp main
    jmp $
