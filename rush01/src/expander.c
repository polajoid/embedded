#include "main.h"
#include "expander.h"


uint8_t g_expander_addr = 0;

void expander_init()
{
	expander_find_addr();
	uint8_t cmd_set_outputs[3] = {6, 1, 0}; // Configuration input/output
	i2c_send_to(g_expander_addr, cmd_set_outputs, 3, &g_i2c_status); // Send configuration
}

void expander_find_addr()
{
	for (uint8_t addr = EXPANDER_I2C_ADDR_MIN; addr <= EXPANDER_I2C_ADDR_MAX; addr++)
		if (!i2c_start(addr, I2C_WRITE, &g_i2c_status))
			{ i2c_stop(); g_expander_addr = addr; break; }
}
