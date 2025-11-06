#include "main.h"
#include "i2c.h"
#include "uart.h"

int	main(void)
{
	init_uart(F_CPU / (8 * 115200) - 1);
	i2c_init();
	_delay_ms(40);
	i2c_start();
	/* Temp should init: */ 
	i2c_write(0xBE);
	/* Trigger temp measurement: */ 
	i2c_write(0xAC);
	/* Temp datasheets ask for us to wait 40ms */
	i2c_start();
	_delay_ms(80);
	for (int i = 0; i < 8; i++)
		i2c_read();
	i2c_stop();
	while (1);
}
