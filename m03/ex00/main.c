#include "module_two.h"

void	uart_tx(char c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	else if (c >= 'A' && c <= 'Z')
		c += 32;
	while (!(UCSR0A & (1 << UDRE0)))
		;							
	UDR0 = c;
}

void	uart_init(unsigned int ubrr)
{
	UCSR0A |= (1 << U2X0); //double speed asynchronous
	UCSR0B |= (1 << TXEN0 | 1 << RXEN0 | 1 << RXCIE0); //RXCIE0 enable interrupt when RX buff is complete
	
	UCSR0C |= (1 << UCSZ01 | 1 << UCSZ00);
	UCSR0B &= ~(1 << UCSZ02); //both line to make 8bits tx and rx

	UBRR0H = (unsigned char)(ubrr >> 8); 	
	UBRR0L = (unsigned char)ubrr;
	sei();
}

int main(void)
{
	uart_init(16);
	while (1)
	{
	}
}

ISR(USART_RX_vect)
{
	uart_tx(UDR0);
}
