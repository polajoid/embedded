#include "module_two.h"

//here us of the asynchronous receiver transmitter
//Only one USART so -> 0 

void	uart_tx(char c)
{
	while (!(UCSR0A & (1 << UDRE0))) //wait to make sure the data transmit buff is empty
		;							//can't write until the flag UDRE is not set
	UDR0 = c; //when empty the buff can be written and then transmit
}

void	uart_init(unsigned int ubrr) //ubrr should be the baud rate
//From datasheets: initialization is: setting the baud rate, setting the frame format and enabling the transmitter/the receiver
{
	UCSR0A |= (1 << U2X0); //to be in asynchronou double speed mode -> Baud = target_frequence (1hz) / 8 (UBRR0 + 1) according to datasheets
	UCSR0B |= (1 << TXEN0); //enable transmitter no receive for no
	UCSR0C |= ~(2 << UMSEL01 | 1 << UMSEL00); //put USART in asynchronous mode: so UART (man p144) 
	
	//to put 8 bit character size we need two set up three bit the UCSZ0[2:0] in UCSR0B for 2 and in UCSRBC for 1 and 0 UCSZ0[]. 8 bit is 011
	UCSR0C |= (1 << UCSZ01 | 1 << UCSZ00);
	UCSR0B &= ~(1 << UCSZ02); //unecessary since this bit is 0 but for good measure here	

	//Baud rate is set up with High and Low registry. For High regystry only the first 4 bits [3:0] are used
	UBRR0H = (unsigned char)(ubrr >> 8); //according to man frequency ?
	UBRR0L = (unsigned char)ubrr;
}

int main(void)
{
	//calculate ubrr = F_CPU (16M)/ (speed_var(8) * BAUD (115.2k)) - 1 -> 16.34. Speed var is 8 because double speed mode is activated. if normal speed mode -> ubbr is 8
	uart_init(16);
	while (1)
	{
		uart_tx('Z');
		_delay_ms(1000);
	}
}
