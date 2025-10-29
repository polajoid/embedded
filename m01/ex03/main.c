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
	SET_IN(D, 3);

	while (1) 
	{	
		if (~PIND & (1 << PD2))
		{
			_delay_ms(20); //avoid rebound
			if (~PIND & (1 << PD2) && counter < 10) 
				change_timer(++counter); //change cyclic ratio (here increment)
			while (~PIND & (1 << PD2))
				;
		}
		if (~PIND & (1 << PD4))
		{
			_delay_ms(20);
			if (~PIND & (1 << PD4) && counter > 1)
				change_timer(--counter);
			while (~PIND & (1 << PD4))
				;
		}
	}
}
