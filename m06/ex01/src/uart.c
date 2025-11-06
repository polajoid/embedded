#include "uart.h"
#include "main.h"

void	print_hexa(uint8_t c)
{
	if (c >= 16)
	{
		print_hexa(c / 16);
		print_hexa(c % 16);
	}
	else
	{
		if (c >= 10)
			uart_tx(c - 10 + 'a');
		else
			uart_tx(c + '0');
	}
	return ;
}

void	print_hex_value(char c)
{
	print_hexa(c);
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

void	init_uart(uint16_t ubbr)
/* init of usart0 with double speed mode in transmit mode only. baud rate is 115 200 */
{
	SET(UCSR0A, U2X0);
	SET(UCSR0B, TXEN0);

	SET(UCSR0C, UCSZ00);
	SET(UCSR0C, UCSZ01);
	/* UART will use 8 bit transmission */

	UBRR0H = (uint8_t)(ubbr >> 8);
	UBRR0L = (uint8_t)ubbr;
}
