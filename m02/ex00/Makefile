ARV_FLAGS = -mmcu=atmega328p -DF_CPU=16000000UL

CFLAGS = -Wall -Wextra -Werror

BAUD_RATE = 115200

CHIP_PORT = /dev/ttyUSB0

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
	avr-gcc $(CFLAGS) -O2 $(ARV_FLAGS) -o $@ $<

flash:
	avrdude -v -c $(PROGRAMMER) -p $(CHIP_NAME) -b $(BAUD_RATE) -P $(CHIP_PORT) $(HEX_FILE) -U flash:w:$(HEX_FILE) 

clean:
	rm -rdf $(BIN_FILE) $(HEX_FILE) $(BUILD)
#kill the screen window by pressing (in screen session) ctr+a -> k -> y

re: clean all

show: all
	screen $(CHIP_PORT) $(BAUD_RATE)

.PHONY: all hex flash clean re
