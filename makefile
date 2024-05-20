
#--------------------------------------Makefile-------------------------------------
SRCDIR = src
OBJDIR = build
HEADER := -I ./header
CFILES = $(wildcard $(SRCDIR)/*.c)
OFILES := $(subst $(SRCDIR),$(OBJDIR),$(CFILES:.c=.o))
GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib

all: clean uart0_build kernel8.img



./build/boot.o: ./src/boot.S
	aarch64-none-elf-gcc $(GCCFLAGS) -c  $(HEADER) ./src/boot.S -o ./build/boot.o



./build/mm_s.o: ./src/mm.S
	aarch64-none-elf-gcc $(GCCFLAGS) -c  $(HEADER) ./src/mm.S -o ./build/mm_s.o

./build/entry.o: ./src/entry.S
	aarch64-none-elf-gcc $(GCCFLAGS) -c -I ./header ./src/entry.S -o ./build/entry.o

./build/irq_s.o: ./src/irq.S
	aarch64-none-elf-gcc $(GCCFLAGS) -c  ./src/irq.S -o ./build/irq_s.o


./build/%.o: ./src/%.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c $(HEADER) $< -o $@





uart0_build: ./src/uart0.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c  $(HEADER) ./src/uart0.c -o ./build/uart.o


	

kernel8.img: ./build/boot.o  ./build/entry.o ./build/irq_s.o ./build/mm_s.o  $(OFILES)
	aarch64-none-elf-ld -nostdlib ./build/boot.o ./build/entry.o ./build/irq_s.o ./build/mm_s.o  $(OFILES) -T ./src/link.ld -o ./build/kernel8.elf
	aarch64-none-elf-objcopy -O binary ./build/kernel8.elf kernel8.img

clean:
	del .\build\kernel8.elf .\build\*.o *.img

# Run emulation with QEMU FOR MAC
run_mac: 
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial stdio


# Run emulation with QEMU FOR WINDOW
run_window: 
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial stdio
