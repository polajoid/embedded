ARV_FLAGS = -mmcu=atmega328p -DF_CPU=16000000UL
#first flag: my device, does avr-gcc support it

SRC = main.c

BUILD = main.out

BIN_FILE = main.bin

HEX_FILE = main.hex

CHIP_NAME = atmega328p 

PROGRAMMER = arduino

all: hex flash

hex: $(HEX_FILE)

$(HEX_FILE): $(BIN_FILE)
	avr-objcopy -I binary -O ihex $< $@
#from binary to COPY_FLAG-> hex file include location

$(BIN_FILE): $(BUILD)
	avr-objcopy -O binary $< $@
#from exec to binary

$(BUILD): $(SRC)
	avr-gcc $(ARV_FLAGS) -o $@ $<
#from c to binary

flash:
	avrdude -v -c $(PROGRAMMER) -p $(CHIP_NAME) -b 115200 -P /dev/ttyUSB0 $(HEX_FILE) -U flash:w:$(HEX_FILE)
#-p flag is mandatatory->tells which chip will it be copy too
#-P is for the Port where program will fin the script
#-U is for execute a special operation on the memory. here memory is flash. w for read from HEX_FILE and Write it to the flash

clean:
	rm -rdf $(BIN_FILE) $(HEX_FILE) $(BUILD)

re: clean all

.PHONY: all hex flash clean re
