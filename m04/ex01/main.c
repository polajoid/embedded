#include "module_four.h"

/*Timer 1 control led PB1 and timer 0 control % of light on */

void	init_timer0(void)
{
	TCCR0A = (1 << WGM00);
	TCCR0B = (1 << WGM02);
	/* set PWP mode */

	/* prescaler = F_CPU / 20 
	 * but 20hz is impossible to reach for timer0*/ 
	TCCR0B |= (1 << CS01);

	TIMSK0 = (1 << TOIE0);
	/* when overflow, interrupt */
}
/* timer0 must send 20 signal in 1 sec. So target frequency is 20hz */

void	init_timer1(void)
{
	TCCR1A = (1 << WGM11);
	TCCR1B = (1 << WGM13 | 1 << WGM12);
	/* fast PWM mode 8 bits but predefine TOP as ICR1 */
	TCCR1B |= (1 << CS10);
	/* set no prescaler for high frequency */
	TCCR1A |= (1 << COM1A1); 
	/* toggle the led with PB1 */
	ICR1 = F_CPU / (1 * 2000);
	/* same formula to have a 1s PWM sequence but target hz is 2000*/
	OCR1A = 0;
	/* compare is set on OCR1A */
}

int main(void)
{
	cli();
	init_timer0();
	init_timer1();
	SET_OUT(B, 1);
	sei();
	/* uint8_t round = 0; */
	while (1)
	{
		/* while (round++ < 10) */
		/* { */
		/* 	OCR1A += 800; */
		/* 	_delay_ms(50); */
		/* } */
		/* while (--round > 0) */
		/* { */
		/* 	OCR1A -= 800; */
		/* 	_delay_ms(50); */
		/* } */
	}
}

/* tell the timer0 to send signal every 100ms */

ISR(TIMER0_OVF_vect)
{
	static uint8_t	i = 0;
	if (!i)
		OCR1A += 800;
	else
		OCR1A -= 800;
	if (!OCR1A)
		i = 0;
	if (OCR1A == 8000)
		i = 1;
	_delay_ms(50);
}
