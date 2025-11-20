#include "main.h"
#include "i2c.h"
#include "uart.h"
#include "spi.h"
#include "rtc.h"
#include "expander.h"
#include "d7s.h"
#include "adc.h"
#include "temperature.h"
#include "led.h"
#include "button.h"
#include "rgb.h"


void init()
{
	sei();
	i2c_init();
	uart_init();
	spi_init();
	expander_init();
	adc_init();
	temperature_init();
	led_init();
	button_init();
	d7s_init(); // last thing to do with i2c
	rgb_init();
	mode_init();
}
