#include "main.h"
#include "led.h"


const uint8_t leds_gpio_pins[NB_GPIO_LED] = {D1, D2, D3, D4};


void led_gpio_init()
{
	for (uint8_t led = 0; led < NB_GPIO_LED; led++)
	{
		SET_OUTPUT(DDRB, leds_gpio_pins[led]);
		SET_OFF(PORTB, leds_gpio_pins[led]);
	}
}

void led_display_bin(uint8_t nb)
{
	for (uint8_t led = 0; led < NB_GPIO_LED; led++)
	{
		if (nb & (1 << led))
			SET(PORTB, leds_gpio_pins[led]);
		else
			CLEAR(PORTB, leds_gpio_pins[led]);
	}
}

void led_gpio_check_state()
{
	if (IS_PRESSED(PIND, PD2)) CLEAR(g_led_i2c_states, LED_I2C_D9); else SET(g_led_i2c_states, LED_I2C_D9);
	if (IS_PRESSED(PIND, PD4)) CLEAR(g_led_i2c_states, LED_I2C_D10); else SET(g_led_i2c_states, LED_I2C_D10);
}
