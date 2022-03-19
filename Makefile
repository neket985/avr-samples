FILENAME   = main
DEVICE     = atmega16
PROGRAMMER = usbasp

COMPILE    = avr-gcc -Wall -Os -mmcu=$(DEVICE)


default: compile upload clean
all: compile

compile:
	$(COMPILE) -c $(FILENAME).c -o $(FILENAME).o
	$(COMPILE) -o $(FILENAME).elf $(FILENAME).o
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex 
	#avr-size --format=avr --mcu=$(DEVICE) $(FILENAME).elf fixme avr-size: неверный аргумент --format: avr
	avr-size --format=gnu $(FILENAME).elf

upload:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -U flash:w:$(FILENAME).hex:i

clean:
	rm $(FILENAME).o
	rm $(FILENAME).elf
	rm $(FILENAME).hex
