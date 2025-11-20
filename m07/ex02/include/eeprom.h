#ifndef EEPROM_H
# define EEPROM_H

# include <avr/eeprom.h>

void	print_sevendigit(uint16_t n, uint8_t depth);
void	eeprom_printhexa(const uint8_t n);
void	eeprom_print(uint16_t highlight);

uint8_t	ft_eeprom_read_byte(const uint16_t address);
void	ft_eeprom_write_byte(const uint16_t address, uint8_t value);

void	eeprom_printstr(uint16_t address);

uint16_t	eeprom_malloc(const uint8_t k_len, const uint8_t v_len);

void	eeprom_erase(const uint16_t address);
uint8_t eeprom_erase_n(const uint16_t address, const uint8_t len);

#endif
