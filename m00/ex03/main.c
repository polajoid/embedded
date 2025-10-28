#include "module_zero.h"

int main(void)
{
	DDRB |= (1 << PB0);
	PORTB &= ~(1 << PB0);
	//led is off. on PB0 is set/modyfied here
	
	DDRD &= ~(1 << PD2);
	PORTD |= (1 << PD2);
	//Switch 1 on PortD2 -> this port becomes input
	//State of PD2 at the beginning: activated

	while (1)
	{
		if (!(PIND & (1 << PD2))) //switch is pressed but is it a rebound ?
		{
			_delay_ms(20); //let's wait to see if the state of the switch is the same.
			if (!(PIND & (1 << PD2))) //yes it is so we can invert the led state
			{
				PORTB ^= (1 << PB0);
				while (!(PIND & (1 << PD2))) //if the button is still pressed, wait for release
					;
			}
		}
	}
}
