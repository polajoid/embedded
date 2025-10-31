#include "module_two.h"

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

int main(void)
{
	const char	welcome[] = "Enter your login:\n\r";
	const char	output_user[] = "\tusername: ";
	const char	output_pass[] = "\n\r\tpassword: ";

	const char	username[] = "spectre";
	const char	password[] = "bosslady";
	
	unsigned char	input;
	uint16_t		checker1;
	uint16_t		checker2;
	uint16_t		i;

	uart_init(16);
	while (1)
	{
		checker1 = 0;
		i = 0;
		uart_printstr(welcome);
		uart_printstr(output_user);
		input = uart_rx();
		while (input != '\r')
		{
			uart_tx(input);
			if (input == 127)
			{
				if (i)
					uart_printstr("\b \b");
				if (i > 0)
					checker1 &= ~(1 << i--);
				input = uart_rx();
				continue ;
			}
			if (i < 7)
			{
				if (username[i] != input)
					checker1 |= (1 << i);
			}
			else
				checker1 |= (1 << i);
			i++;
			input = uart_rx();
			if (i > 15)
				break;
		}
		if (i > 15) 
		{
			uart_printstr("\r\noverflow protection, try again.\r\n");
			continue ;
		}
		i = 0;
		checker2 = 0;
		uart_printstr(output_pass);
		input = uart_rx();
		while (input != '\r')
		{
			uart_tx('*');
			if (input == 127)
			{
				if (i)
					uart_printstr("\b \b");
				if (i > 0)
					checker2 &= ~(1 << i--);
				input = uart_rx();
				continue ;
			}
			if (i < 8)
			{
				if (password[i] != input)
					checker2 |= (1 << i);
			}
			else
				checker2 |= (1 << i);
			i++;
			input = uart_rx();
			if (i > 15)
			{
				uart_printstr("\r\noverflow protection, try again.\r\n");
				break ;
			}
		}
		if (i > 15)
			continue ;
		uart_printstr("\n\r");
		if (!checker1 && !checker2)
			break ;
		else
			uart_printstr("Bad combinaison username/password\n");
		uart_printstr("\n\r");
	}
	uart_printstr("C'est moi Boss Lady\n\r");
	uart_printstr("J'ai tout paye no credit\r\n");
}
