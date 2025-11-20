#ifndef EEPROM_H
# define EEPROM_H

# include <avr/eeprom.h>

void	print_sevendigit(uint16_t n, uint8_t depth);
void	eeprom_printhexa(uint8_t n);
void	eeprom_print(uint16_t highlight);
uint8_t	ft_eeprom_read_byte(uint16_t address);
void	ft_eeprom_write_byte(uint16_t address, uint8_t value);

#endif
