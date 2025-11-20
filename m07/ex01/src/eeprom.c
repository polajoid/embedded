#include "uart.h"
#include "eeprom.h"
#include "main.h"

void	print_sevendigit(uint16_t n, uint8_t depth)
{
	static const char hex[] = "0123456789abcdef";

	if (depth < 7)
		print_sevendigit(n >> 4, depth + 1);
	uart_tx(hex[n & 0xF]);
}


void	eeprom_printhexa(uint8_t n)
{
	static const char hex[] = "0123456789abcdef";

	uart_tx(hex[n / 16]);
	uart_tx(hex[n % 16]);
}

void	eeprom_print(uint16_t highlight)
/* From previous ex00 */
{
	uint16_t	i = 0;
	while (EECR & (1 << EEPE))
		;
	while (i < 1024)
	{
		print_sevendigit(i, 0);\
		uart_tx(' ');
		for (uint8_t j = 0; j < 16; j++)
		{
			EEAR = i + j;
			SET(EECR, EERE);
			if ((i + j) == highlight)
			{
				uart_printstr("\x1b[31m");
				eeprom_printhexa(EEDR);
				uart_printstr("\x1b[0m");
			}
			else
				eeprom_printhexa(EEDR);
			if (((j % 2) && j) || j == 1)
				uart_tx(' ');
		}
		uart_printstr("\r\n");
		i = i + 16;
	}
}

uint8_t	ft_eeprom_read_byte(uint16_t address)
{
	while (EECR & (1 << EEPE))
		;
	/* waiting for a write to finished */
	EEAR = address;
	SET(EECR, EERE);
	return (EEDR);
}

void	ft_eeprom_write_byte(uint16_t address, uint8_t value)
{
	while ((EECR & (1 << EEPE)) || (SPMCSR & (1 << SPMEN)))
		;
	EEAR = address;
	EEDR = value;
	CLEAR(EECR, EEPE);
	SET(EECR, EEMPE);
	/* Master Write Enable: necessary for a write */
	/* SET(EECR, EEPM1); */
	/* SET(EECR, EEPM0); */
	SET(EECR, EEPE);
	/* Start the write immediatly */
}
