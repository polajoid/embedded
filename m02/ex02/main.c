#include "module_two.h"

void	uart_tx(char c)
{
	while (!(UCSR0A & (1 << UDRE0)))
		;							
	UDR0 = c;
}

unsigned char	uart_rx(void)
//waiting for the receive buff to be complete
{
	while (!(UCSR0A & (1 << RXC0)))
		;
	return (UDR0);
}
void	uart_init(unsigned int ubrr)
{
	UCSR0A |= (1 << U2X0); //double speed asynchronous
	UCSR0B |= (1 << TXEN0 | 1 << RXEN0); //to allow transmit
	
	UCSR0C |= (1 << UCSZ01 | 1 << UCSZ00);
	UCSR0B &= ~(1 << UCSZ02); //both line to make 8bits tx and rx

	UBRR0H = (unsigned char)(ubrr >> 8); 	
	UBRR0L = (unsigned char)ubrr;
}

int main(void)
{
	uart_init(16);
	unsigned char c;
	while (1)
	{
		c = uart_rx();
		uart_tx(c);
	}
}
