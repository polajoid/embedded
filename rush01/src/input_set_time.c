#include "main.h"
#include "uart.h"
#include "rtc.h"


uint8_t	ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

uint8_t	check_time(uint8_t checker[3])
{
	if (checker[0] > 59) return (1);
	if (checker[1] > 59) return (1);
	if (checker[2] > 23) return (1);
	return (0);
}

uint8_t	check_date(uint8_t checker[2], uint16_t year)
{
	if (year > 9999)
		return (1);
	if (checker[1] > 12 || !checker[1])
		return (1);
	if (!checker[0] || checker[0] > 31)
		return (1);
	if (checker[0] == 31 && (checker[1] == 2 ||
				checker[1] == 4 || checker[1] == 6 ||
				checker[1] == 9 || checker[1] == 11))
		return (1);
	if (checker[1] == 2)
	{
		if (checker[0] == 29)
			if (year % 4)
				return (1);
		if (checker[0] == 30)
			return (1);
	}
	return (0);
}

uint8_t	input_set_time(void)
{
	char	input[22];
	
	uart_printstr("Enter date + hour. Required format is: DD/MM/AAAA hh :mm :ss > ");
	if (uart_getline(input, 22)) 
		return (1);
	uint8_t		checker[2];
	uint8_t		time_chk[3];
	uint16_t	year;

	if (!ft_isnum(input[0]) || !ft_isnum(input[1])) return (1);
	checker[0] = (input[0] - '0') * 10 + (input[1] - '0');
	if (input[2] != '/') return (1);
	if (!ft_isnum(input[3]) || !ft_isnum(input[4])) return (1);
	checker[1] = (input[3] - '0') * 10 + (input[4] - '0');
	if (input[5] != '/') return (1);
	year = 0;
	for (uint8_t i = 6; i < 10; i++)
	{
		if (!ft_isnum(input[i])) return (1);
		else
			year = (input[i] - '0') + year * 10;
	}
	if (input[10] != ' ') return (1);
	if (check_date(checker, year)) 
	{
		uart_printstr("Wrong date\r\n");
		return (1);
	}
	if (!ft_isnum(input[11]) || !ft_isnum(input[12])) return (1);
	time_chk[2] = (input[11] - '0') * 10 + (input[12] - '0');
	if (input[13] != ' ' || input[14] != ':') return (1);
	if (!ft_isnum(input[15]) || !ft_isnum(input[16])) return (1);
	time_chk[1] = (input[15] - '0') * 10 + (input[16] - '0');
	if (input[17] != ' ' || input[18] != ':') return (1);
	if (!ft_isnum(input[19]) || !ft_isnum(input[20])) return (1);
	time_chk[0] = (input[19] - '0') * 10 + (input[20] - '0');
	if (check_time(time_chk))
	{
		uart_printstr("\r\nWrong hour\r\n");
		return (1);
	}
	rtc_set_time_deci(time_chk[0], time_chk[1], time_chk[2], checker[0], checker[1], year);
	uart_printstr("\n\rCorrect date. Updating RTC\r\n");
	return (0);
}
