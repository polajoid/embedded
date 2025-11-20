#include "main.h"
#include "button.h"


void button_init()
{
	button_gpio_init();
	button_i2c_init();
}
