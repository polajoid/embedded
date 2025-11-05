#include "main.h"
#include "timer.h"
#include "uart.h"

void	print_deca(uint16_t value)
{
	if (value >= 10)
	{
		print_deca(value / 10);
		print_deca(value % 10);
	}
	else
		uart_tx(value + '0');
	return ;
}

/* Configure ADC to 8 bit with AVCC as reference */
void	init_ADC(void)
{

	SET(ADMUX, REFS0);
	/* VREF = AVCC */

	CLEAR(ADMUX, ADLAR);
	/* No left adjust the result. To keep full precision of 10 bits. We must first check low then high register */

	SET(ADCSRA, ADPS2);
	SET(ADCSRA, ADPS1);
	SET(ADCSRA, ADPS0);
	/* ADC needs an input clock frequency between 50kHz and 200khz. Prescaler 124 is necessary since F_CPU is 16000000 */ 

	SET(ADCSRA, ADEN);
	/* enables the ADC */
	SET(ADCSRA, ADATE);
	/* enable the auto trigger-> when ? decided by bits in registrer B */
	SET(ADCSRB, ADTS1);
	SET(ADCSRB, ADTS0);
	/* when timer0 compare match A it triggers ADC conversion ? but automatic? */

	SET(ADCSRA, ADIE);
	/* when conversion is complete and data registers are updated interruption is given by ADC. In interrupt vector we can print the converted value */

	/* by default ADC will convert value on ADC0. This is precisely the analog we want to convert */

	DIDR0 = (1 << ADC5D | 1 << ADC4D | 1 << ADC3D);
	/* powerconsumption tells us to disable digital input unused */
}

int	main(void)
{	
	SET_INPUT(C, 0);
	SET_INPUT(C, 1);
	SET_INPUT(C, 2);
	/* RV1 is on PC0 */

	init_uart(F_CPU / (8 * 115200) - 1);
	init_timer0();
	init_ADC();
	sei();
	while (1) ;
}

ISR(ADC_vect)
{
	static uint8_t	count = 0;
	uint16_t	value = ADCL;
	value += ((ADCH >> 1) & 1) * 512 + (ADCH & 1) * 256;
	/* only need to read in the high register */
	print_deca(value);
	
	if (count == 2)
	{
		CLEAR(ADMUX, MUX1);
		uart_printstr("\n\r");
	}
	else
	{
		if (!count)
			SET(ADMUX, MUX0);
		else 
		{
			SET(ADMUX, MUX1); 
			CLEAR(ADMUX, MUX0);
		}
		uart_printstr(", ");
	}
	;
	count = (count + 1) % 3;
	/* ADC looks for OCF0A flag in TIFR0 but if no interruption this flag is never clear */
	SET(TIFR0, OCF0A);
}
