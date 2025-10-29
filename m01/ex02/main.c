#include "module_one.h"

//Here we need to have LED D2 to turn on every second for 0.1s.
//Frequency of event is still 1hz but we have a nested event that need us to use something else than CTC

int main(void)
{
	SET_OUT(B, 1); //Output mode. same reason as before
	
	//Set up of the Timer1 registrer
	TCCR1A = (1 << COM1A1); //toggle OC1A again	
	TCCR1B = (1 << CS12); //still a presquale of 256

	//Here: setting up the registers to use PWM -> when MAX is reached overflow to BOT
	TCCR1B |= (1 << WGM13 | 1 << WGM12); 
	TCCR1A |= (1 << WGM11);

	//we want a cycle to be 1hz so : F_CPU / (1mhz * pres) - 1 -> 62499
	ICR1 = 62499; //compiler set up first high then low 8bit registry so no problem here
	//all we need now is to set up a TOP value (OCR1A) for toggling the port : 10 % of 62499
	OCR1A = 6250;
	while (1) 
	{
	}
}
