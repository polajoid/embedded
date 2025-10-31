#include "module_one.h"

//Cyclic value of previous exersice are given as macro here
# define TEN_PERCENT 6250

void	change_timer(unsigned int counter)
{
	OCR1A = TEN_PERCENT * counter;
}

int main(void)
{
	unsigned int	counter = 1;
	SET_OUT(B, 1);
	
	TCCR1A = (1 << COM1A1); 
	TCCR1B = (1 << CS12); 

	TCCR1B |= (1 << WGM13 | 1 << WGM12); 
	TCCR1A |= (1 << WGM11);

	ICR1 = 62499;
	OCR1A = TEN_PERCENT * counter;
	//Classic set up here
	
	//Setting up also both switch:
	SET_IN(D, 2);
	SET_IN(D, 4);

	uint16_t sw1_prev_state = 0;
	uint16_t sw2_prev_state = 0;
	
	while (1) 
	{
		uint16_t sw1_current_state = ~PIND & (1 << PD2);
		uint16_t sw2_current_state = ~PIND & (1 << PD4);
		if (!sw1_current_state && sw1_prev_state && counter < 10)
			change_timer(++counter); //change cyclic ratio (here increment)
		if (!sw2_current_state && sw2_prev_state && counter > 1)
			change_timer(--counter);
		sw1_prev_state = sw1_current_state;
		sw2_prev_state = sw2_current_state;
		_delay_ms(20); //avoid rebound
	}
}
