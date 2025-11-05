#include "led.h"
#include "main.h"

void	set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	OCR0A = g;
	OCR0B = r;
	OCR2B = b;
}

void	init_LED()
{
	/* led set up */
	SET_OUTPUT(D, 5);
	SET_OUTPUT(D, 6);
	SET_OUTPUT(D, 3);

	SET_OUTPUT(B, 0);
	SET_OUTPUT(B, 1);
	SET_OUTPUT(B, 2);
	SET_OUTPUT(B, 4);
}

void	ratio(uint8_t value)
{
	TURN_OFF(B, 0);
	TURN_OFF(B, 1);
	TURN_OFF(B, 2);
	TURN_OFF(B, 4);
	if (value > 63)
		TURN_ON(B, 0);
	if (value > 127)
		TURN_ON(B, 1);
	if (value > 190)
		TURN_ON(B, 2);
	if (value == 255)
		TURN_ON(B, 4);
}


void	wheel(uint8_t pos)
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
