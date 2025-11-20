#include "main.h"
#include "module/rgb.h"
#include "lib/spi.h"
#include "rtc.h"

uint8_t color;

void	rgb_mode(void)
/* TEST: RGB LEDs. RED 1s, GREEN 1s, BLUE 1s, redo */
/* PB2 is SS, PB3 is MISO and PB4 is SCK */
{
	uint8_t rotation = 0;
	spi_init();
	rgb_gpio_init();
	while (1)
	{
		rgb_spi_blink(rotation);
		rgb_gpio_blink(rotation);
		rotation = (rotation + 1) % 3;
		_delay_ms(1000);
	}
}

void rgb_init()
{
	rgb_gpio_init();
	rgb_clear();
}

uint16_t rgb_update()
{
	static uint8_t sec = -1; if (sec == -1) sec = rtc_get_seconds() - 1;
	uint8_t new_sec = rtc_get_seconds();
	if (sec == new_sec) return -1;
	rgb_spi_blink(color);
	rgb_gpio_blink(color);
	color++; color %= 3;
	sec = new_sec;
	return -1;
}

void rgb_clear()
{
	rgb_gpio_clear();
	rgb_spi_clear();
	color = 0;
}
