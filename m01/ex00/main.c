#include "module_one.h"

void	my_ms_delay(unsigned int ms)
{
	unsigned int x;
	while (ms--)
	{
		x = 2600;
		while (x--)
			;
	}
}

int main(void)
{
	DDRB |= (1 << PB1);
	PORTB &= ~(1 << PB1);
	//LED D2 at PB1 is ready to receive input. Initial state is off.
	
	while (1)
	{
		my_ms_delay(500);
		//Frequency is the number of occurrences of a repeating event per unit of time
		//If we want 1hz we want an event to repeat each second so each 1000ms
		//Hence every 500ms, the LED switch off or switch on so that every second the LED switch on
		PORTB ^= (1 << PB1);
		//LED D2 change it's state
	}
}
