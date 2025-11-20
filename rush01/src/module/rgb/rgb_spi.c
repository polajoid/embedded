#include "main.h"
#include "lib/spi.h"

void	rgb_spi_blink(uint8_t rotation)
{
	uint8_t	red = 0x00;
	uint8_t	green = 0x00;
	uint8_t	blue = 0x00;
	if (!rotation)
	{
		blue = 0x00;
		red = 0xFF;
	}
	else if (rotation == 1)
	{
		red = 0x00;
		green = 0xFF;
	}
	else
	{
		green = 0x00;
		blue = 0xFF;
	}
	spi_start_frame();
	for (uint8_t i = 0; i < 3; i++)
		spi_send_RGB(0x05, red, green, blue);
	spi_end_frame();
}

void rgb_spi_clear()
{
	spi_start_frame();
	for (uint8_t i = 0; i < 3; i++)
		spi_send_RGB(0x00, 0, 0, 0);
	spi_end_frame();
}
