#include "module/rgb.h"
#include "main.h"

void	rgb_gpio_blink(uint8_t rotation)
{
	if (!rotation)
	{
		CLEAR(PORTD, 3);
		SET(PORTD, 5);
	}
	else if (rotation == 1)
	{
		CLEAR(PORTD, 5);
		SET(PORTD, 6);
	}
	else
	{
		CLEAR(PORTD, 6);
		SET(PORTD, 3);
	}
}

void	rgb_gpio_init(void)
{
	SET_OUTPUT(DDRD, 5);
	SET_OUTPUT(DDRD, 6);
	SET_OUTPUT(DDRD, 3);
}

void rgb_gpio_clear()
{
	CLEAR_MSK(PORTD, MSK(PD3) | MSK(PD5) | MSK(PD6));
}
