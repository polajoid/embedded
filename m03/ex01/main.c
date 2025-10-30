#include "module_three.h"

/* Purpose write a program controlling LED RGD D5 */

int main(void)
{
	SET_OUT(D, 5);
	SET_OUT(D, 6);
	SET_OUT(D, 3);
	/* input mode because output mode burns my eyes */
	while (1)
	{
		PORTD = (1 << PD5);
		_delay_ms(1000);
		PORTD = (1 << PD6);
		_delay_ms(1000);
		PORTD = (1 << PD3);
		_delay_ms(1000);
		PORTD = (1 << PD5 | 1 << PD6); //new colors are just a combinais of RGB
		_delay_ms(1000);
		PORTD = (1 << PD6 | 1 << PD3);
		_delay_ms(1000);
		PORTD = (1 << PD5 | 1 << PD3);
		_delay_ms(1000);
		PORTD = (1 << PD5 | 1 << PD6 | 1 << PD3);
		_delay_ms(1000);
	}
}

