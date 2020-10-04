CC = i686-elf-gcc
AS = nasm
CFLAGS = -std=gnu99 -ffreestanding -O0 -Wall -Wextra -g

all: kernel.bin kernel.sym
%.o: %.c
	${CC} -c $< -o $@ ${CFLAGS}

%.o: %.s
	${AS} -f elf32 $< -o $@

%.0: %.asm
	${AS} -f elf32 $< -o $@

drivers/%.o: drivers/%.c
	${CC} -c $< -o $@ ${CFLAGS}

drivers/%.o: drivers/%.asm
	${AS} -f elf32 $< -o $@
kernel.bin: boot.o kernel.o drivers/vga.o drivers/stdlib.o
	${CC} -T linker.ld -o $@ -ffreestanding -nostdlib $^ -lgcc -g
kernel.sym: kernel.bin
	objcopy --only-keep-debug kernel.bin kernel.sym

clean:
	rm -rf *.o
	rm -rf *.bin
	rm -rf drivers/*/*.o drivers/*.o
qemu:
	qemu-system-i386 -kernel kernel.bin -s -S
.PHONY: clean qemu