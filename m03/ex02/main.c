#include "module_three.h"

/* Purpose write a program controlling LED RGD D5 */

void	init_rgb()
{
	SET_OUT(D, 5);
	SET_OUT(D, 6);
	SET_OUT(D, 3);
	/* init of the three led */
	
	TCCR1A = (1 << COM1B0); 
	/* port OC1A is toggle here on compare and untoggle*/
	TCCR1A |= (1 << WGM10);
	TCCR1B = (1 << WGM12);
	/* for fast pwm 8 bits */
	TCCR1B |= (1 << CS12);
	/* for presquler 256 */
}

void	set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	PORTD = (r <<);
}

void wheel(uint8_t pos)
{
	pos = 255 - pos;
	if (pos < 85)
	{
		set_rgb(255 - pos * 3, 0, pos * 3);
	}
	else if (pos < 170)
	{
		pos = pos - 85;
		set_rgb(0, pos * 3, 255 - pos * 3);
	} 
	else 
	{
		pos = pos - 170;
		set_rgb(pos * 3, 255 - pos * 3, 0);
	}
}

int main(void)
{
	while (1)
	{
	}
}

