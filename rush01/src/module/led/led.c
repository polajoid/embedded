#include "main.h"
#include "led.h"

void led_init()
{
	led_gpio_init();
}

void led_check_state()
{
	led_gpio_check_state();
	led_i2c_check_state();
}
