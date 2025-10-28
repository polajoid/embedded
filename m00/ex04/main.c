#include "module_zero.h"

void	print_value(unsigned char	val)
//printing number from the highest bit (2^3) to the lowest (2^0)
{
	PORTB = 0x00;
	if (val >= 8)
	{
		val -= 8;
		PORTB |= (1 << PB4);
	}
	if (val >= 4)
	{
		val -= 4;
		PORTB |= (1 << PB2);
	}
	if (val >= 2)
	{
		val -= 2;
		PORTB |= (1 << PB1);
	}
	if (val > 0)
		PORTB |= (1 << PB0);
}

int main(void)
{
	DDRB = (1 << PD0 | 1 << PD1 | 1 << PD2 | 1 << PD4);
	//all 4 on output mode: but D4 is on PB4
	DDRD &= ~(1 << PD2 & 1 << PD4);
	//SW1 is on D2 and SW2 is on PD4

	unsigned char		value = 1;	
	PORTB = (1 << PB0);
	//value being set to 1, one led will be on;

	while (1)
	{
		if (~PIND & (1 << PD2)) //switch is pressed
		{
			_delay_ms(20);
			if (~PIND & (1 << PD2) && value < 15) //make sure wasn't a rebound
				print_value(++value);
			while (~PIND & (1 << PD2))
				;
		}
		if (~PIND & (1 << PD4))
		{
			_delay_ms(20);
			if (~PIND & (1 << PD4) && value > 0)
				print_value(--value);
			while (~PIND & (1 << PD4))
				;
		}
	}
}
