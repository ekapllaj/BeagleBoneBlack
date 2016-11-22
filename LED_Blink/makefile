CROSS_COMPILE=arm-none-eabi


all: start.s main.c
	$(CROSS_COMPILE)-as start.s -o start.o
	$(CROSS_COMPILE)-gcc -c main.c -o main.o
	$(CROSS_COMPILE)-ld start.o main.o -T memmap.ld -o main.elf
	$(CROSS_COMPILE)-objcopy -O binary main.elf main.bin
copy:
	cp main.bin /srv/tftp/
clean:
	rm -rf *.o

