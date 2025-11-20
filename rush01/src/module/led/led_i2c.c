#include "main.h"
#include "expander.h"
#include "led.h"


uint8_t g_led_i2c_states = 0xFF;

void led_i2c_check_state()
{
	uint8_t byte;
	EXP_ADDR(i2c_send_byte_to(g_expander_addr, 0, &g_i2c_status));
	EXP_ADDR(i2c_receive_from(g_expander_addr, I2C_NACK, &byte, 1, &g_i2c_status));
	if (GET_VALUE(byte, SW3)) SET(g_led_i2c_states, LED_I2C_D11); else CLEAR(g_led_i2c_states, LED_I2C_D11);
}
