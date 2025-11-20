#ifndef MODE_H
# define MODE_H

# include <avr/eeprom.h>

uint8_t		check_key(uint16_t *i, const char *key, const uint8_t key_length);
uint16_t	matching_address(uint16_t address, const char *buff, const uint8_t len);

uint16_t	read_mode(const char *buff);
uint8_t		write_mode(const char *buff);
uint8_t		forget_mode(const char *buff);

#endif
