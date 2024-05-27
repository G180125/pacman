
#--------------------------------------Makefile-------------------------------------
SRCDIR = src
OBJDIR = build
HEADER := -I ./header
CFILES = $(wildcard $(SRCDIR)/*.c)
OFILES := $(subst $(SRCDIR),$(OBJDIR),$(CFILES:.c=.o))
GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib 

all: clean my_script uart0_build kernel8.img
mac: clean_mac my_script uart0_build kernel8.img

my_script:
	./script/script.sh

# Ensure the build directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

uart0_build: ./src/uart0.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c  $(HEADER) ./src/uart0.c -o ./build/uart.o

./build/boot.o: ./src/boot.S
	aarch64-none-elf-gcc $(GCCFLAGS) -c  $(HEADER) ./src/boot.S -o ./build/boot.o

./build/%.o: ./src/%.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c $(HEADER) $< -o $@

kernel8.img: ./build/boot.o $(OFILES)
	aarch64-none-elf-ld -nostdlib ./build/boot.o $(OFILES) -T ./src/link.ld -o ./build/kernel8.elf
	aarch64-none-elf-objcopy -O binary ./build/kernel8.elf kernel8.img

clean:
	del .\build\kernel8.elf .\build\*.o *.img

clean_mac:
	rm -rf build/*.o build/kernel8.elf *.img

# Run emulation with QEMU FOR MAC
run_mac: 
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial stdio

# Run emulation with QEMU FOR WINDOW
run_window: 
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial stdio
