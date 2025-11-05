#include "main.h"
#include "timer.h"
#include "led.h"

void	init_ADC(void)
{
	SET(ADMUX, REFS0);
	/* Voltage back to AVCC*/

	SET(ADMUX, ADLAR);
	/* No left adjust the result. To keep full precision of 10 bits. We must first check low then high register */

	SET(ADCSRA, ADPS2);
	SET(ADCSRA, ADPS1);
	SET(ADCSRA, ADPS0);
	/* ADC needs an input clock frequency between 50kHz and 200khz. Prescaler 128 is necessary since F_CPU is 16000000 */ 

	SET(ADCSRA, ADEN);
	/* enables the ADC */
	SET(ADCSRA, ADATE);
	/* enable the auto trigger-> when ? decided by bits in registrer B */
	SET(ADCSRB, ADTS2);
	SET(ADCSRB, ADTS1);
	/* when timer1 compare match A it triggers ADC conversion*/

	SET(ADCSRA, ADIE);
	/* when conversion is complete and data registers are updated interruption is given by ADC. In interrupt vector we can print the converted value */

	CLEAR(ADMUX, MUX0);
	/* CLEAR(ADMUX, MUX2); */
	/* CLEAR(ADMUX, MUX1); */
	/* CLEAR(ADMUX, MUX0); */
	/* The CLEAR are unecessary since the initial set is 0. There presence is to indicate ADC will look at value at ADC0 */

	DIDR0 = (1 << ADC5D | 1 << ADC4D | 1 << ADC3D | 1 << ADC2D | 1 << ADC1D);
	/* Powerconsumption tells us to disable digital input unused. The only one we use here is ADC0D*/
}

int	main(void)
{
	init_LED();
	init_timer0();
	init_timer1();
	init_timer2();
	init_ADC();
	sei();
	while (1) ;
}

ISR(ADC_vect)
{
	uint8_t	value = ADCH;
	/* We will set 8bit precision and left adjust */
	ratio(value);
	wheel(value);
	/* ADC looks for OCF0A flag in TIFR0 but if no interruption this flag is never clear */
	SET(TIFR1, TOV1);
}
