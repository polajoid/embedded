#include "timer.h"
#include "main.h"

/* For a 50hz frequence on the converter we need a timer0 with thoses modes:
 * - CTC mode
 * - prescaler at 1024
 * - OCRA = 155 */
/* Frequency of interruption is F_CPU/(2 * prescaler * (1 + OCR0A)) */

/* We want in this exercice to have a timer 0 and timer 2 that control intensity of RGB at D5 */
/* But timer 0 was used previously to control ADC. */
/* and we can't put timer0 in 50hz without using OCR0A */
/* So I will be using timer1 to control autotrigger of ADC */

void	init_timer0(void)
{
	SET(TCCR0A, COM0A1);
	SET(TCCR0A, COM0B1);
	/* port OC0A and port OC0B are toggle here on compare*/

	SET(TCCR0A, WGM01);
	SET(TCCR0A, WGM00);
	/* Use of fast PWM wit 255 has TOP*/
	
	SET(TCCR0B, CS02);
	SET(TCCR0B, CS00);
	/* for presquler 1024*/

	OCR0A = 0;
	OCR0B = 0;
}

void	init_timer1(void)
{
	SET(TCCR1B, WGM13);
	SET(TCCR1B, WGM12);
	SET(TCCR1A, WGM11);
	SET(TCCR1A, WGM10);
	
	SET(TCCR1B, CS12);
	SET(TCCR1B, CS10);

	OCR1A = 155;
}

void	init_timer2(void)
{
	SET(TCCR2A, COM2B1);
	SET(TCCR2A, WGM21);
	SET(TCCR2A, WGM20);
	/* Also Fast PWM with 255 as TOP */
	
	SET(TCCR2B, CS22);
	SET(TCCR2B, CS21);
	SET(TCCR2B, CS20);
	/* Timer2 has different bit setup to enable 1024 prescaler */

	OCR2B = 0;
}
