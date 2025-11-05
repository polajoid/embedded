#include "timer.h"
#include "main.h"

/* For a 50hz frequence on the converter we need a timer0 with thoses modes:
 * - CTC mode
 * - prescaler at 1024
 * - OCRA = 155 */
/* Frequency of interruption is F_CPU/(2 * prescaler * (1 + OCR0A)) */

void	init_timer0(void)
{
	SET(TCCR0A, WGM01);
	/* enable CTC */
	SET(TCCR0B, CS02);
	SET(TCCR0B, CS00);
	/* prescaler at 1024 */
	OCR0A = 155;
	/* CTC max for a frequency of 50.08hz */


	/* for debugging (GREEN light blinking): */
	/* SET_OUTPUT(D, 6); */
	/* TURN_ON(D, 6); */
	/* SET(TCCR0A, COM0A0); */
}
