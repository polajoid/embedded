#include "main.h"
#include "led.h"


uint8_t sw1_pressed = 0;
uint8_t sw2_pressed = 0;


ISR(INT0_vect)
{
	if (!sw1_pressed)
		mode_inc();
	sw1_pressed = !sw1_pressed;
	DEBOUNCE;
	SET(EIFR, INTF0);
}

ISR(PCINT2_vect)
{
	if (!sw2_pressed)
		mode_dec();
	sw2_pressed = !sw2_pressed;
	DEBOUNCE;
	SET(PCIFR, PCIF2);
}

void button_gpio_init()
{
	SET_INPUT(DDRD, PD2);
	SET_INPUT(DDRD, PD4);

	sw1_pressed = IS_PRESSED(PIND, PD2);
	sw2_pressed = IS_PRESSED(PIND, PD4);

	SET(EIMSK, INT0); // Enable INT0 (SW1) interrupt
	SET(EICRA, ISC00); // Interrupt on change
	SET(PCICR, PCIE2); // Make activatable interrupt on PCINT23:16
	SET(PCMSK2, PCINT20); // Enable interrupt on change of PCINT20 (SW2)
}
