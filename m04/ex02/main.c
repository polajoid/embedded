#include "module_four.h"


void	print_value(char val)
{
	PORTB = 0x00;
	if (val >= 8)
	{
		val -= 8;
		PORTB |= (1 << PB4);
	}
	if (val >= 4)
	{
		val -= 4;
		PORTB |= (1 << PB2);
	}
	if (val >= 2)
	{
		val -= 2;
		PORTB |= (1 << PB1);
	}
	if (val > 0)
		PORTB |= (1 << PB0);
}

void	init_switch_interrupt(void)
{
	SET_IN(D, 2);
	EICRA = (1 << ISC01);
	EIMSK = (1 << INT0);



	SET_IN(D, 4);
	PCICR = (1 << PCIE2);
	PCMSK2 = (1 << PCINT20);
}

volatile char	value = 0;

int main(void)
{
	cli();
	SET_OUT(B, 0);
	SET_OUT(B, 1);
	SET_OUT(B, 2);
	SET_OUT(B, 4);
	init_switch_interrupt();
	sei();
	while (1)
	{
		if (value < 0)
			value = 0;
		else if (value > 15)
			value = 15;
		print_value(value);
	}
}

ISR(INT0_vect)
{
	value++;
}

ISR(PCINT2_vect)
{
	value--;
}
