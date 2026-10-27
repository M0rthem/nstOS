ENTRY(start)

SECTIONS
{
    . = 0x1000;

    .text : { *(.text) }
    .rodata : { *(.rodata*) }
    .data : { *(.data) }

    . = ALIGN(4096);
    .pagetables : { *(.pagetables) }
    
    .bss : {
        *(COMMON)
	*(.bss)
    }

    /DISCARD/ : {
        *(.eh_frame)
        *(.comment)
        *(.note*)
    }
}
