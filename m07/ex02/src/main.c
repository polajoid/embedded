#include "main.h"
#include "libft.h"
#include "uart.h"
#include "eeprom.h"
#include "parsing.h"
#include "mode.h"

void	select_mode(const char *buff)
{
	if (!ft_strncmp(buff, "READ ", 5))
		read_mode(&buff[5]);
	else if (!ft_strncmp(buff, "WRITE ", 6))
		write_mode(&buff[6]);
	else if (!ft_strncmp(buff, "FORGET ", 7))
		forget_mode(&buff[7]);
	else if (!ft_strncmp(buff, "PRINT ", 6) || !ft_strncmp(buff, "PRINT", 6))
		eeprom_print(1025);
	return ;
}
int	main(void)
{
	char	buff[32];
	uint8_t	begin = 0;
	init_uart(F_CPU / (8 * 115200) - 1);
	EEARH &= ~(1 << EEAR8);
	
	/* if (ft_eeprom_read_byte(0x8) == END_VALUE_TOKEN) */
	/* 	eeprom_erase(0x8); */	
	/* if (ft_eeprom_read_byte(0x1B) == END_VALUE_TOKEN) */
	/* 	eeprom_erase(0x1B); */
	/* if (ft_eeprom_read_byte(0xA) != KEY_TOKEN) */
	/* 	ft_eeprom_write_byte(0xA, KEY_TOKEN); */
	/* if (ft_eeprom_read_byte(0xA + 32) != END_VALUE_TOKEN) */
	/* 	ft_eeprom_write_byte(0xA + 32, END_VALUE_TOKEN); */

	while (1)
	{
		if (!begin)
		{
			uart_printstr("> ");
			begin++;
		}
		if (!uart_getline(buff, 32))
		{
			/* const char	*key = isolate_key(buff); */
			/* const char	*value = isolate_key(key); */
			select_mode(buff);
			begin = 0;
		}
	}
}
