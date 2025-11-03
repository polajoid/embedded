#include "module_four.h"

/* Purpose write a program controlling LED RGD D5 */

int main(void)
{
	cli();
	/* disable global interrupt during init */
	SET_OUT(B, 0);
	SET_IN(D, 2);

	/* SW2 is on D2 hence connected to PIN Change Interrupt 18 */
	PCMSK2 = (1 << PCINT18);
	/* activation of Interrupt when PD2 changes */
	PCICR = (1 << PCIE2);
	/* on the register of the interrupt -> allow interrupt for PCINT23:16 */

	sei();
	while (1)
	{
	}
}

ISR()
{
	PORTB ^= (1 << PORTB0);
}

