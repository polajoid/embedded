#include "module_one.h"

void	my_delay_ms(uint16_t ms)
//creating my own delay
{
	volatile uint32_t x;
	//use of volatile is necessary because flag optimization will prune the x
	while (ms)
	{
		x = F_CPU / 10000 / 4; //4 bits, trying to have 1hz
		while (x)
			x--;
		ms--;
	}
}

int main(void)
{
	SET_IN(B, 1);
	PORTB &= ~(1 << PB1);
	//LED D2 at PB1 is ready to receive input. Initial state is off.
	
	while (1)
	{
		my_delay_ms(500);
		//Frequency is the number of occurrences of a repeating event per unit of time
		//If we want 1hz we want an event to repeat each second so each 1000ms
		//Hence every 500ms, the LED switch off or switch on so that every second the LED switch on
		PORT_TOGGLE(B, 1);
		//LED D2 change it's state, one bitwise operation
	}
}
