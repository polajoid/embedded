ARV_FLAGS = -mmcu=atmega328p -DF_CPU=16000000UL

SRC = main.c

BUILD = main.out

CHIP_NAME = atmega328p 

PROGRAMMER = arduino 

BIN_FILE = main.bin

HEX_FILE = main.hex

all: hex flash

hex: $(HEX_FILE)

$(HEX_FILE): $(BIN_FILE)
	avr-objcopy -I binary -O ihex $< $@

$(BIN_FILE): $(BUILD)
	avr-objcopy -O binary $< $@

$(BUILD): $(SRC)
	avr-gcc $(ARV_FLAGS) -o $@ $<

flash:
	avrdude -v -c $(PROGRAMMER) -p $(CHIP_NAME) -b 115200 -P /dev/ttyUSB0 $(HEX_FILE) -U flash:w:$(HEX_FILE) 

clean:
	rm -rdf $(BIN_FILE) $(HEX_FILE) $(BUILD)

re: clean all

.PHONY: all hex flash clean re
