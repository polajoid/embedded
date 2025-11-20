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


void	eeprom_printhexa(const uint8_t n)
{
	static const char hex[] = "0123456789abcdef";

	uart_tx(hex[n / 16]);
	uart_tx(hex[n % 16]);
}

void	eeprom_print(uint16_t highlight)
/* From previous ex00 */
{
	uint16_t	i = 0;
	char		line[16];
	while (EECR & (1 << EEPE))
		;
	while (i < 1024)
		/* There is 1kb inside the ATMEGA. This loop parse through all of it */
	{
		print_sevendigit(i, 0);
		uart_tx(' ');
		/* Printing the raw address of the eeprom */
		for (uint8_t j = 0; j < 16; j++)
		/* Printing every colums of the eeprom */
		{
			EEAR = i + j;
			SET(EECR, EERE);
			/* Reading the data corresponding to the addres in the EEAR registry */
			if ((i + j) == highlight)
			{
				uart_printstr("\x1b[31m");
				/* Just highlighting the address given as a parameter */
				eeprom_printhexa(EEDR);
				uart_printstr("\x1b[0m");
			}
			else
				eeprom_printhexa(EEDR);
			if (((j % 2) && j) || j == 1)
				uart_tx(' ');
			line[j] = EEDR;
		}
		uart_print_line(line);
		uart_printstr("\r\n");
		i = i + 16;
		/* Jump to the next raw. One raw is 16 byte */
	}
}

void	eeprom_printstr(uint16_t address)
{
	uint8_t value = ft_eeprom_read_byte(address);

	while (!value)
	{
		uart_tx(value);
		value = ft_eeprom_read_byte(++address);
	}
}

uint8_t	ft_eeprom_read_byte(const uint16_t address)
{
	while (EECR & (1 << EEPE))
		;
	/* waiting for a write to finished */
	EEAR = address;
	SET(EECR, EERE);
	return (EEDR);
}

void	ft_eeprom_write_byte(const uint16_t address, uint8_t value)
{
	while ((EECR & (1 << EEPE)) || (SPMCSR & (1 << SPMEN)))
		;
	EEAR = address;
	EEDR = value;
	CLEAR(EECR, EEPE);
	SET(EECR, EEMPE);
	/* Master Write Enable: necessary for a write */
	CLEAR(EECR, EEPM1);
	CLEAR(EECR, EEPM0);
	SET(EECR, EEPE);
	/* Start the write immediatly */
}

uint16_t	eeprom_malloc(const uint8_t k_len, const uint8_t v_len)
/* This function returns an address where the program can write the pair key/value. Two types of possible errors: previous write failure is error 1024 and no space left in eeprom for the pair is error 1025 */
{
	const uint16_t	required_space = k_len + v_len + 3;
	uint16_t	current_address = 0;
	uint8_t		tmp;
	uint16_t	available_space = 0;

	while (current_address < 1024)
	{
		tmp = ft_eeprom_read_byte(current_address);
		if (tmp != KEY_TOKEN)
			available_space++; 
		/* Everytime there is no keytoken means the memory is empty hence, free to use */
		else
		{
			while (ft_eeprom_read_byte(current_address) != END_VALUE_TOKEN && current_address < 1024)
				++current_address;
			/* But if there is, the program jumps to the end of the pair key/value */
			if (current_address == 1024)
			{
				uart_printstr("Memory corruption\n\r");
				return (1024);
			}
			available_space = 0;
		}
		if (available_space == required_space)
			return (current_address - available_space + 1) ;
		current_address++;
	}
	uart_printstr("No space left\r\n");
	return (1025);
}

void	eeprom_erase(const uint16_t address)
{
	while ((EECR & (1 << EEPE)) || (SPMCSR & (1 << SPMEN)))
		;
	EEAR = address;
	CLEAR(EECR, EEPE);
	SET(EECR, EEMPE);
	/* Master Write Enable: necessary for a write */
	SET(EECR, EEPM0);
	SET(EECR, EEPE);
}

uint8_t eeprom_erase_n(const uint16_t address, const uint8_t len)
{
	uint8_t i = 0;
	while (ft_eeprom_read_byte(address + i) != END_VALUE_TOKEN 
			&& i < 32 && address + i < 1024)
		eeprom_erase(address + i++);
	eeprom_erase(address + i);
	return (len);
}
