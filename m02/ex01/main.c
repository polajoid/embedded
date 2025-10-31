#include "module_two.h"

void	uart_printstr(const char * str)
//a combination of previous function that send every char of the string until '\0' is reached
{
	while (*str)
	{
		while (!(UCSR0A & (1 << UDRE0)))
			;
		UDR0 = *str++;
	}
}

void	uart_init(unsigned int ubrr)
{
	UCSR0A |= (1 << U2X0);
	UCSR0B |= (1 << TXEN0); 
	UCSR0C |= ~(2 << UMSEL01 | 1 << UMSEL00); 
	
	UCSR0C |= (1 << UCSZ01 | 1 << UCSZ00);
	UCSR0B &= ~(1 << UCSZ02);

	UBRR0H = (unsigned char)(ubrr >> 8); 	
	UBRR0L = (unsigned char)ubrr;
	
	//interruption is the key to send the string. When interruption flag is send, the function is activate	
	sei();
	//but interrupt will be send by clock?
}


void	timer1_init(void)
//Timer1 on CTC mode when OCR1A reached, sending interrupt signal
//putting 1024 prescaler (every 2ms interruption so hz target is 0.5hz) -> same OCR1A
{
	TCCR1B = (1 << WGM12 | 1 << CS12 | 1 << CS10);
	TCCR1A = (1 << COM1A0);
	TIMSK1 |= (1 << OCIE1A); //New : to allow interupt from  TIMER1 COMPA
	OCR1A = 31249;
}

int main(void)
{
	uart_init(16);
	timer1_init();
	while (1)
	{
	}
}

ISR(TIMER1_COMPA_vect)
//When interruption from timer is give, what is happening: 
{
	uart_printstr("Hello World!\n\r");
}
