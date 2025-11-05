ARV_FLAGS = -mmcu=atmega328p -DF_CPU=16000000UL

CFLAGS = -Wall -Wextra -Werror -O2 -MMD -MP


BAUD_RATE = 115200

CHIP_PORT = /dev/ttyUSB0

CHIP_NAME = atmega328p 

PROGRAMMER = arduino 


SRC_DIR = src

OBJ_DIR = objs

BUILD_DIR = build

DEP_DIR = deps

HEADER_DIR = include


SRCS = main.c \
	   led.c \
	   timer.c

HEADER = main.h \
		 led.h	\
		 timer.h

OBJS = $(SRCS:%.c=${OBJ_DIR}/%.o)

DEPS = $(SRCS:%.c=$(DEP_DIR)/%.d)


INCLUDE = -I $(HEADER_DIR) 

BUILD = $(BUILD_DIR)/main.out

BIN_FILE = $(BUILD_DIR)/main.bin

HEX_FILE = $(BUILD_DIR)/main.hex


all: hex flash
-include $(DEPS)

hex: $(HEX_FILE)

$(HEX_FILE): $(BIN_FILE)
	avr-objcopy -I binary -O ihex $< $@

$(BIN_FILE): $(BUILD)
	avr-objcopy -O binary $< $@

$(BUILD): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	avr-gcc $(CFLAGS) $(ARV_FLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR) $(DEP_DIR)
	avr-gcc $(CFLAGS) $(ARV_FLAGS) $(INCLUDE) \
		-c $< -o $@ \
		-MF $(DEP_DIR)/$(notdir $(basename $<)).d -MT $@


flash: $(HEX_FILE)
	avrdude -v -c $(PROGRAMMER) -p $(CHIP_NAME) -b $(BAUD_RATE) -P $(CHIP_PORT) $(HEX_FILE) -U flash:w:$(HEX_FILE) 

clean:
	rm -rdf $(OBJ_DIR) $(BUILD_DIR) $(DEP_DIR)
#kill the screen window by pressing (in screen session) ctr+a -> k -> y

re: clean all

show: all
	screen $(CHIP_PORT) $(BAUD_RATE)
#	sudo cu -l $(CHIP_PORT) -s $(BAUD_RATE)
##press MAJ ` (~) and . and ENTER to quit cu

.PHONY: all hex flash clean re
