#include "module_three.h"

void	init_rgb()
{
	/* led set up */
	SET_OUT(D, 5);
	SET_OUT(D, 6);
	SET_OUT(D, 3);

	/* first counter */
	TCCR0A = (1 << COM0A1 | 1 << COM0B1 | 1 << WGM01 | 1 << WGM00);
	TCCR0B = (1 << CS01);
	OCR0A = 0;
	OCR0B = 0;

	/* secound counter */
	TCCR2A = (1 << COM2B1 | 1 << WGM21 | 1 << WGM20);	
	TCCR2B = (1 << CS21);
	OCR2B = 0;
}

void	set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	OCR0A = g;
	OCR0B = r;
	OCR2B = b;
}

void	uart_tx(char c)
{
	while (!(UCSR0A & (1 << UDRE0)))
		;							
	UDR0 = c;
}

void	uart_printstr(const char * str)
{
	while (*str)
		uart_tx(*str++);
}

unsigned char	uart_rx(void)
{
	while (!(UCSR0A & (1 << RXC0)))
		;
	return (UDR0);
}

void	uart_init(unsigned int ubrr)
{
	UCSR0A |= (1 << U2X0);
	UCSR0B |= (1 << TXEN0 | 1 << RXEN0);
	UCSR0C |= (1 << UCSZ01 | 1 << UCSZ00);
	UCSR0B &= ~(1 << UCSZ02);

	UBRR0H = (unsigned char)(ubrr >> 8); 	
	UBRR0L = (unsigned char)ubrr;
}

uint8_t	add_to_color(unsigned char c, uint8_t power)
/* to convert from a char to a cool RGB HEX nb */
{
	uint8_t	res;

	if (c >= 'A' && c <= 'F')
		res = c - 'A' + 10;
	else
		res = c - '0';
	if (power)
		res *= 16;
	return (res);
}

int main(void)
{
	init_rgb();
	uart_init(16);
	
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;

	unsigned char	input;
	uint32_t		i;

	uart_printstr("Enter HEX RGB: ");
	input = uart_rx();
	while (1)
	{
		red = 0;
		blue = 0;
		green = 0;
		uart_tx(input);
		while (input != '#')
		{
			uart_printstr("\r\nWrong first symbol. Redo: ");
			input = uart_rx();
			uart_tx(input);
		}
		i = 0;
		input = uart_rx();
		while ((input >= '0' && input <= '9') || (input >= 'A' && input <= 'F'))
		{
			uart_tx(input);
			if (input == '\r' || i > 7)
				break ;
			if (i < 2)
				red += add_to_color(input, i % 2);
			else if (i < 4)
				green += add_to_color(input, i % 2);
			else if (i < 6)
				blue += add_to_color(input, i % 2);
			i++;
			input = uart_rx();
		}
		uart_tx(input);
		if (i != 6)
			uart_printstr("\n\rWrong. Redo: ");
		else
			set_rgb(red, green, blue);
		uart_printstr("\r\nEnter HEX RGB: ");
		input = uart_rx();
	}
}

