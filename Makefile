CC = i686-elf-gcc
LD = i686-elf-ld
ASM = nasm
SRC = src
BIN = bin

BOOTLOADER = $(BIN)/boot.bin
KERNEL = $(BIN)/kernel.bin
OS_IMAGE = $(BIN)/os-image.bin

all: $(OS_IMAGE)

$(OS_IMAGE): $(BOOTLOADER) $(KERNEL)
	cat $(BOOTLOADER) $(KERNEL) > $@

$(BOOTLOADER): $(SRC)/boot.asm
	$(ASM) $^ -f bin -o $@

$(KERNEL): $(BIN)/kernel_entry.o $(BIN)/kernel.o
	$(LD) -Ttext 0x1000 -e start -o $@ --oformat binary $^

$(BIN)/kernel_entry.o: $(SRC)/kernel_entry.asm
	$(ASM) $^ -f elf32 -o $@

$(BIN)/kernel.o: $(SRC)/kernel.c
	$(CC) -ffreestanding -m32 -c $^ -o $@

clean:
	rm -f $(BIN)/*.bin $(BIN)/*.o $(OS_IMAGE)

run:
	qemu-system-i386 -drive format=raw,file=$(OS_IMAGE),if=floppy -m 128M