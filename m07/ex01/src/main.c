#include "main.h"
#include "libft.h"
#include "uart.h"
#include "eeprom.h"

uint8_t	isvalid_input(const char *buff, uint16_t *address, uint16_t *value)
{
	char	str_address[9];
	char	str_value[3];

	if (ft_strlen(buff) != 11)
		return (0);
	if (buff[8] != ' ')
		return (0);
	ft_copy(buff, str_address, 9);
	ft_copy(&buff[9], str_value, 3);
	if (ft_strlen(str_address) != 8 || ft_strlen(str_value) != 2)
		{uart_printstr(str_address); uart_printstr(" "); uart_printstr(str_value); uart_tx(' '); return (0);}
	if (ft_atoihex(str_address) >= 1024 || ft_atoihex(str_value) >= 256)
		return (0);
	*address = ft_atoihex(str_address);
	*value = ft_atoihex(str_value);
	return (1);
}

int	main(void)
{
	char	buff[16];
	uint16_t	value;
	uint16_t	address;
	init_uart(F_CPU / (8 * 115200) - 1);
	EEARH &= ~(1 << EEAR8);

	while (1)
	{
		if (!uart_getline(buff, 16))
		{
			/* uart_printstr("Checking input... "); */
			if (!isvalid_input(buff, &address, &value))
				uart_printstr("Unvalid input...");
			else
			{	
				/* uart_printstr("Valid input: "); */
				/* uart_printhexa(address); */
				/* uart_tx(' '); */
				/* uart_printhexa(value); */

				if (value != ft_eeprom_read_byte(address))
				{
					ft_eeprom_write_byte(address, value);
					eeprom_print(address);
				}
			}
			uart_printstr("\r\n");
			/* else if (check_byte_value(buff[])) */
			/* { */

/* 			} */
		}
	}
}
