[BITS 16]
[ORG 0x7c00]

KERNEL_LOCATION equ 0x1000

BOOT_DISK: db 0
mov [BOOT_DISK], dl

CODE_OFFSET equ 0x8
DATA_OFFSET equ 0x10

start:
cli ;Clear interrupts
mov ax, 0x00
mov ds, ax
mov es, ax
mov ss, ax
mov sp, 0x7c00
sti ;Enable interrupts

;load kernel into KERNEL_LOCATION
mov ah, 0x2
mov al, 20
mov ch, 0x0
mov cl, 0x2
mov dh, 0x0 
mov bx, KERNEL_LOCATION
mov dl, BOOT_DISK
int 0x13

;clear screen
mov ah, 0x0
mov al, 0x3
int 0x10
;load kernel

jmp load_PM

;GDT Implementation
gdt_start:
    null_descriptor:
        dd 0x0
        dd 0x0
    code_descriptor:
        ;Code segment descriptor
        dw 0xFFFF   ;Limete
        dw 0x0000   ;Base
        db 0x00     ;Base
        db 10011010b;Access byte
        db 11001111b;Flags
        db 0x00     ;Base
    data_descriptor:
        ;Data    segment descriptor
        dw 0xFFFF   ;Limete
        dw 0x0000   ;Base
        db 0x00     ;Base
        db 10010010b;Access byte
        db 11001111b;Flags
        db 0x00     ;Base

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1;Sizw GDT - 1
    dd gdt_start

load_PM:
    cli
    lgdt[gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp CODE_OFFSET:PModeMain


[BITS 32]
PModeMain:

mov ax, DATA_OFFSET
mov ds, ax
mov es, ax
mov fs, ax
mov ss, ax
mov gs, ax
mov ebp, 0x90000
mov esp, ebp

in al, 0x92
or al, 2
out 0x92, al

jmp KERNEL_LOCATION

times 510 - ($ - $$) db 0
    
dw 0xAA55