#include "main.h"
#include "expander.h"
#include "d7s.h"
#include "led.h"


uint16_t nb = 0;

uint8_t select[4] = {
	D7S_SELECT_0, D7S_SELECT_1, D7S_SELECT_2, D7S_SELECT_3
};

uint8_t print[10] = {
	D7S_PRINT_0, D7S_PRINT_1, D7S_PRINT_2, D7S_PRINT_3,
	D7S_PRINT_4, D7S_PRINT_5, D7S_PRINT_6, D7S_PRINT_7,
	D7S_PRINT_8, D7S_PRINT_9
};

uint8_t dash_42[4] = {
	D7S_PRINT_DASH, D7S_PRINT_2, D7S_PRINT_4, D7S_PRINT_DASH
};


uint16_t ft_pow10(uint8_t idx)
{
	if (idx == 0) return 1;
	if (idx == 1) return 10;
	if (idx == 2) return 100;
	if (idx == 3) return 1000;
	return 1;
}

ISR(TIMER0_COMPA_vect)
{
	static uint8_t idx = 0;
	uint8_t digit = nb / ft_pow10(idx) % 10;
	uint8_t cmd[5] = {2, select[(idx + 3) % 4] & g_led_i2c_states, D7S_PRINT_CLEAR, select[idx] & g_led_i2c_states, print[nb / ft_pow10(idx) % 10]};
	if (!digit && idx && nb < ft_pow10(idx)) cmd[4] = D7S_PRINT_CLEAR;
	if (nb == -1) cmd[4] = dash_42[idx];
	EXP_ADDR(i2c_send_to(g_expander_addr, cmd, 5, &g_i2c_status));
	idx++; idx %= 4;
}

void d7s_init()
{
	SET(TCCR0A, WGM01); // Config Timer0 for CTC
	SET_MSK(TCCR0B, MSK(CS02) | MSK(CS00)); // Select prescaler 1024 and start the clock
	SET(TIMSK0, OCIE0A); // Enable interrupt on match with OCR0A
	OCR0A = 80; // Around 500Hz
}

void d7s_set_number(uint16_t n) { nb = n; }
