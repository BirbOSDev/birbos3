CC = i686-elf-gcc
AS = nasm
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra

all: kernel.bin
%.o: %.c
	${CC} -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

%.o: %.s
	${AS} -f elf32 $< -o $@

%.0: %.asm
	${AS} -f elf32 $< -o $@

drivers/%.o: drivers/%.c
	${CC} -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

drivers/%.o: drivers/%.asm
	${AS} -f elf32 $< -o $@
kernel.bin: boot.o kernel.o drivers/vga.o drivers/stdlib.o
	${CC} -T linker.ld -o $@ -ffreestanding -O2 -nostdlib $^ -lgcc

clean:
	rm -rf *.o
	rm -rf *.bin
	rm -rf drivers/*/*.o drivers/*.o
qemu:
	qemu-system-i386 -kernel kernel.bin
.PHONY: clean qemu