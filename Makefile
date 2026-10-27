CC = i686-elf-gcc
LD = i686-elf-ld
ASM = nasm
SRC = src
BIN = bin
CFLAGS = -ffreestanding -m32 -I$(SRC)

BOOTLOADER = $(BIN)/boot.bin
KERNEL = $(BIN)/kernel.bin
OS_IMAGE = $(BIN)/os-image.bin

LDSCRIPT = $(SRC)/linker/kernel.ld

C_SOURCES = $(shell find $(SRC) -name '*.c')
ASM_SOURCES = $(filter-out $(SRC)/bootloader/boot.asm, $(shell find $(SRC) -name '*.asm'))

C_OBJECTS = $(patsubst $(SRC)/%.c, $(BIN)/%.o, $(C_SOURCES))
ASM_OBJECTS = $(patsubst $(SRC)/%.asm, $(BIN)/%.o, $(ASM_SOURCES))

OBJECTS = $(BIN)/kernel/kernel_entry.o $(filter-out $(BIN)/kernel/kernel_entry.o, $(ASM_OBJECTS) $(C_OBJECTS))

all: $(OS_IMAGE)

$(OS_IMAGE): $(BOOTLOADER) $(KERNEL)
	cat $(BOOTLOADER) $(KERNEL) > $@

$(BOOTLOADER): $(SRC)/bootloader/boot.asm
	@mkdir -p $(dir $@)
	$(ASM) $< -f bin -o $@

$(KERNEL): $(OBJECTS) $(LDSCRIPT)
	$(LD) -T $(LDSCRIPT) -e start -o $@ --oformat binary $(OBJECTS)

$(BIN)/%.o: $(SRC)/%.asm
	@mkdir -p $(dir $@)
	$(ASM) $< -f elf32 -o $@

$(BIN)/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN)/*

run:
	qemu-system-i386 -drive format=raw,file=$(OS_IMAGE),if=floppy -m 128M

run_hdd:
	qemu-system-i386 -drive format=raw,file=$(OS_IMAGE),if=ide -m 128M

.PHONY: all clean run run_hdd
