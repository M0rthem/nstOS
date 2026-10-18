CC = i686-elf-gcc
LD = i686-elf-ld
ASM = nasm
SRC = src
BIN = bin
CFLAGS = -ffreestanding -m32 -I$(SRC)

BOOTLOADER = $(BIN)/boot.bin
KERNEL = $(BIN)/kernel.bin
OS_IMAGE = $(BIN)/os-image.bin

C_SOURCES = $(shell find $(SRC) -name '*.c')

C_OBJECTS = $(patsubst $(SRC)/%.c, $(BIN)/%.o, $(C_SOURCES))

ASM_OBJECTS = $(BIN)/kernel_entry.o

OBJECTS = $(ASM_OBJECTS) $(C_OBJECTS)

all: $(OS_IMAGE)

$(OS_IMAGE): $(BOOTLOADER) $(KERNEL)
	cat $(BOOTLOADER) $(KERNEL) > $@

$(BOOTLOADER): $(SRC)/boot.asm
	$(ASM) $^ -f bin -o $@

$(KERNEL): $(OBJECTS)
	$(LD) -Ttext 0x1000 -e start -o $@ --oformat binary $^

$(BIN)/kernel_entry.o: $(SRC)/kernel_entry.asm
	@mkdir -p $(dir $@)
	$(ASM) $^ -f elf32 -o $@

$(BIN)/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN)/*

run:
	qemu-system-i386 -drive format=raw,file=$(OS_IMAGE),if=floppy -m 128M

run_hdd:
	qemu-system-i386 -drive format=raw,file=$(OS_IMAGE),if=ide -m 128M
