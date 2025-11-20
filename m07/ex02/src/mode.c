#include "mode.h"
#include "eeprom.h"
#include "parsing.h"
#include "main.h"
#include "uart.h"

uint8_t	check_key(uint16_t *i, const char *key, const uint8_t key_length)
{
	uint8_t	value;
	uint8_t	iter = 0;

	while (iter < key_length)
	{
		value = ft_eeprom_read_byte(++(*i));
		if (value != key[iter] || value == END_VALUE_TOKEN)
			return (0);
		iter++;
	}
	return (1);
}

uint16_t	print_value(const uint16_t address)
{
	uint8_t	value = ft_eeprom_read_byte(address);
	uart_tx('"');
	for (uint16_t i = 1; value != END_VALUE_TOKEN && i < 1024 && i < 32; i++)
	{
		uart_tx(value);
		value = ft_eeprom_read_byte(address + i);
	}
	uart_tx('"');
	uart_printstr("\r\n");
	return (0);
}

uint16_t	read_mode(const char *buff)
{
	const char *key = isolate_key(buff);
	if (!key)
		return (1);
	const char *key_end = find_quote(key);
	const uint8_t	key_length = key_end - key;

	/* uart_printstr("Key to read is: "); */
	/* for (uint16_t i = 0; i < key_length; i++) */
	/* 	uart_tx(key[i]); */
	/* uart_printstr(" with length of "); */
	/* uart_printdeca(key_length); */
	/* uart_printstr("\r\n"); */

	for (uint16_t i = 0; i < 1024; i++)
	{
		if (ft_eeprom_read_byte(i) == KEY_TOKEN)
			if (matching_address(i + 1, key, key_length))
				return (print_value(i + 1 + key_length + 1));
	}
	uart_printstr("empty\r\n");
	return (1);
}

uint8_t	write_mode(const char *buff)
{
	const char	*key = isolate_key(buff);
	if (!key)
		return (1);
	const char	*key_end = find_quote(key);
	const uint8_t	key_length = key_end - key;

	for (uint16_t i = 0; i < 1024; i++)
	{
		if (ft_eeprom_read_byte(i) == KEY_TOKEN)
		{
			if (matching_address(i + 1, key, key_length)) 
			{
				uart_printstr("Already exist\r\n");
				return (1);
			}	
		}
	}

	const char	*value = isolate_key(key_end + 1);
	if (!value)
		return (1);
	const char	*value_end = find_quote(value);
	const uint8_t	value_length = value_end - value;

	/* uart_printstr("key: "); */
	/* for (uint8_t i = 0; i < key_length; i++) */
	/* 	uart_tx(key[i]); */
	/* uart_printstr(" key_length: "); */
	/* uart_printdeca(key_length); */

	/* uart_printstr(" value: "); */
	/* for (uint8_t i = 0; i < value_length; i++) */
	/* 	uart_tx(value[i]); */
	/* uart_printstr(" value_length: "); */
	/* uart_printdeca(value_length); */

	/* uart_printstr("\r\n"); */
	uint16_t address = eeprom_malloc(key_length, value_length);
	if (address == 1024 || address == 1025)
		return (0);

	ft_eeprom_write_byte(address++, KEY_TOKEN);
	for (uint16_t i = 0; i < key_length; i++)
		ft_eeprom_write_byte(address++, key[i]);
	ft_eeprom_write_byte(address++, VALUE_TOKEN);
	for (uint16_t i = 0; i < value_length; i++)
		ft_eeprom_write_byte(address++, value[i]);
	ft_eeprom_write_byte(address, END_VALUE_TOKEN);
	uart_printstr("done: 0x");
	uart_printhexa(address);
	uart_printstr("\r\n");
	return (address);
}

uint16_t	matching_address(uint16_t address, const char *buff, const uint8_t len)
{
	uint8_t i = 0;
	
	while (i < len)
	{
		if (ft_eeprom_read_byte(address + i) != (uint8_t)buff[i])
		{
			/* uart_tx(ft_eeprom_read_byte(address + i)); */
			return (0);
		}
		i++;
	}
	if (ft_eeprom_read_byte(address + i) != VALUE_TOKEN)
		return (0);
	return (1);
}

uint8_t	forget_mode(const char *buff)
{	
	const char	*key = isolate_key(buff);
	if (!key)
		return (1);
	const char	*key_end = find_quote(key);
	const uint8_t	key_length = key_end - key;

	for (uint16_t i = 0; i < 1024; i++)
	{
		if (ft_eeprom_read_byte(i) == KEY_TOKEN)
		{
			if (matching_address(i + 1, key, key_length))
			{
				return (eeprom_erase_n(i, key_length));
			}
		}
	}
	uart_printstr("not found\r\n");
	return (0);
}
