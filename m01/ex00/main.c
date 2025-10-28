#include "module_one.h"

void	my_delay_ms(unsigned int ms)
//creating my own delay
{
	volatile unsigned int x;
	//use of volatile is necessary because flag optimization will prune the x
	while (ms)
	{
		x = 1100;
		while (x)
			x--;
		ms--;
	}
}

int main(void)
{
	DDRB |= (1 << PB1);
	PORTB &= ~(1 << PB1);
	//LED D2 at PB1 is ready to receive input. Initial state is off.
	
	while (1)
	{
		my_delay_ms(500);
		//Frequency is the number of occurrences of a repeating event per unit of time
		//If we want 1hz we want an event to repeat each second so each 1000ms
		//Hence every 500ms, the LED switch off or switch on so that every second the LED switch on
		PORTB ^= (1 << PB1);
		//LED D2 change it's state
	}
}
