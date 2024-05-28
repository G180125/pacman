#--------------------------------------Makefile-------------------------------------
SRCDIR = src
OBJDIR =object
CFILES = $(wildcard $(SRCDIR)/*.c)
#OFILES = $(CFILES:.c=.o)
# Define objects for all sources
OFILES := $(subst $(SRCDIR),$(OBJDIR),$(CFILES:.c=.o))

GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib

all: clean kernel8.img run

boot.o: src\boot.S
	aarch64-none-elf-gcc $(GCCFLAGS) -c src\boot.S -o $(OBJDIR)\boot.o
	
#The stem of the pattern must match exactly
$(OBJDIR)/%.o: src/%.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: boot.o $(OFILES)
	aarch64-none-elf-ld -nostdlib $(OBJDIR)\boot.o $(OFILES) -T src\link.ld -o $(OBJDIR)\kernel8.elf
	aarch64-none-elf-objcopy -O binary $(OBJDIR)\kernel8.elf kernel8.img

clean:
	del $(OBJDIR)\kernel8.elf $(OBJDIR)\*.o *.img

run:
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial stdio 