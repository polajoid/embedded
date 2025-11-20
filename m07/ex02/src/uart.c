#include "uart.h"
#include "main.h"

void	uart_printhexa(uint8_t n)
{
	if (n >= 16)
	{
		uart_printhexa(n / 16);
		uart_printhexa(n % 16);
	}
	else
	{
		if (n >= 10)
			uart_tx(n - 10 + 'A');
		else
			uart_tx(n + '0');
	}
	return ;
}

void	uart_printdeca(uint8_t n)
{
	if (n >= 10)
	{
		uart_printdeca(n / 10);
		uart_printdeca(n % 10);
	}
	else
		uart_tx(n + '0');
}

void	uart_print_line(const char *line)
{
	uart_tx('|');
	for (uint8_t i = 0; i < 16; i++)
	{
		if (line[i] >= ' ' && line[i] <= 'z')
			uart_tx(line[i]);
		else
			uart_tx('.');
	}
	uart_tx('|');
}

void	uart_tx(const char c)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}

void	uart_printstr(const char * str)
{
	while (*str)
	{
		uart_tx(*str);
		str++;
	}
}

uint8_t	uart_getline(char *buff, const uint8_t size)
/* Give a buffer vor the res and the maximal size of the buffer. Last bit of the buff will be NULL */
{
	static uint8_t	i = 0;
	char			c;

	c = uart_rx();
	if (c >= ' ' && c <= 'z')
	{
		uart_tx(c);	
		if (i < size - 1)
			buff[i] = c;
		i++;
	}
	if (c == '\r')
	{
		uart_printstr("\r\n");
		if (i < size - 1)
			buff[i] = '\0';
		else
			buff[size - 1] = '\0';
		i = 0;
		return (0);
	}
	if (c == 127)
	{
		if (i)
		{
			i--;
			uart_printstr("\b \b");
		}
		if (i < size)
			buff[i] = '\0';
	}
	return (1);
}

unsigned char	uart_rx(void)
{
	while (!(UCSR0A & (1 << RXC0)))
		;
	return (UDR0);
}

void	init_uart(uint16_t ubbr)
{
	SET(UCSR0A, U2X0);
	SET(UCSR0B, TXEN0);
	SET(UCSR0B, RXEN0);

	SET(UCSR0C, UCSZ00);
	SET(UCSR0C, UCSZ01);

	UBRR0H = (uint8_t)(ubbr >> 8);
	UBRR0L = (uint8_t)ubbr;
}
