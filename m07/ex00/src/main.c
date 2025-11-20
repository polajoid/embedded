#include "main.h"
#include "uart.h"

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

int	main(void)
{
	uint16_t i = 0;

	init_uart(F_CPU / (8 * 115200) - 1);
	EEARH &= ~(1 << EEAR8);
	/* ATMega328p doesn't use 9 bit address, only 8. Hence this bit must be set to 0 */
	while (i < 1023)
	{
		print_sevendigit(i, 0);\
		uart_tx(' ');
		for (uint8_t j = 0; j < 16; j++)
		{
			EEAR = i + j;
			/* We ask here (Eeprom address register low) which address we want to access. So we go from 0x00 to 0xFF */
			EECR = (1 << EERE);
			/* Enable read on the memory bit writing this bit to 0 and all the others to 0 */
			eeprom_printhexa(EEDR);
			if (((j % 2) && j) || j == 1)
				uart_tx(' ');
		}
		uart_printstr("\r\n");
		i = i + 16;
	}
	while (1)
	{
	}
}

