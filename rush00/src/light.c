/* Here are define function to light on/off LED according to game situation */

#include <main.h>
#include "delay.h"
#include "input.h"

void	init_LED(void)
{
	SET_OUTPUT(D, 3);
	SET_OUTPUT(D, 5);
	SET_OUTPUT(D, 6);

	SET_OUTPUT(B, 0);
	SET_OUTPUT(B, 1);
	SET_OUTPUT(B, 2);
	SET_OUTPUT(B, 4);
}

void	LED_turnoff_b(void)
{
	SET_OFF(B, 0);
	SET_OFF(B, 1);
	SET_OFF(B, 2);
	SET_OFF(B, 4);
}

void	LED_turnoff_d(void)
{
	SET_OFF(D, 3);
	SET_OFF(D, 5);
	SET_OFF(D, 6);
}

void	LED_waiting_state(void)
{
	SET_ON(D, 3);
	SET_ON(D, 5);
	SET_ON(D, 6);
	LED_turnoff_b();
}

void	LED_player_ready_state(void)
{
	SET_ON(D, 3);
	SET_OFF(D, 5);
	SET_OFF(D, 6);
	LED_turnoff_b();
}

uint8_t	LED_countdown(void)
{
	LED_turnoff_b();
	LED_turnoff_d();

	SET_ON(B, 0);
	if (delay_check(1000, &button_pressed)) return 1;
	SET_ON(B, 1);
	if (delay_check(1000, &button_pressed)) return 1;
	SET_ON(B, 2);
	if (delay_check(1000, &button_pressed)) return 1;
	SET_ON(B, 4);
	if (delay_check(1000, &button_pressed)) return 1;

	LED_turnoff_b();
	return 0;
}

void	LED_show_winner(void)
{
	LED_turnoff_b();
	SET_OFF(D, 3);
	SET_OFF(D, 5);
	SET_ON(D, 6);
}

void	LED_show_loser(void)
{
	LED_turnoff_b();
	SET_OFF(D, 3);
	SET_ON(D, 5);
	SET_OFF(D, 6);
}
