#include "module_zero.h"

int	main(void)
{
	DDRB = ~(1 << PB0); //;led is put in input mode -> so 0
	DDRD &= ~(1 << PD2); //switch is on a port d, the 3 third one, also input mode
	PORTB &= ~(1 << PB0); //led is off at the beginning
	
	const unsigned char	led_on = (1 << PB0); //
	const unsigned char	led_off = 0;
	while (1)
	{
		if (~PIND & (1 << PD2)) //inverse logic: if switch is pressed, PD2 bit is set to 0
			PORTB = led_on;
		else
			PORTB = led_off;
	}
}
