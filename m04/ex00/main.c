#include "module_four.h"

/* Purpose write a program controlling LED RGD D5 */

volatile uint8_t	button_new_state = 0;

int main(void)
{
	/* disable global interrupt during init */
	cli();
	SET_OUT(B, 0);
	SET_IN(D, 2);
	PORTB = (1 << PORTB0);

	/* PD2 can make a global interrupt of type INT0. So we enable them */
	EIMSK = (1 << INT0);
	/* here we say the interrupt take place when the button is pressed (falling edge, 12.2.1) */
	EICRA = (1 << ISC01);

	/* we enable global interrupt */
	sei();
	while (1)
	{
		if (button_new_state)
		{
			/* we wait 20ms after the button change state to avoid rebound */
			_delay_ms(20);
			button_new_state = 0;
			sei();
		}
	}
}

ISR(INT0_vect, ISR_BLOCK)
{
	cli();
	PORTB ^= (1 << PORTB0);
	button_new_state = 1;
	/* here we change at what moment the interrupt takes place: if the button is pressed the next interrupt will be when the button is released */
	EICRA ^= (1 << ISC00);
}
