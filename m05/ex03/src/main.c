#include "main.h"
#include "timer.h"
#include "uart.h"

void	print_hexa(uint16_t value)
{
	if (value > 16)
	{
		print_hexa(value / 16);
		print_hexa(value % 16);
	}
	else
	{
		if (value >= 10)
			uart_tx(value - 10 + 'a');
		else
			uart_tx(value + '0');
	}
	return ;
}


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

void	init_ADC(void)
{

	SET(ADMUX, REFS1);
	SET(ADMUX, REFS0);
	/* measurement of temperature requires both setting according to man. Voltage reference is 1.1V*/

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

	SET(ADMUX, MUX3);
	/* SET(ADMUX, MUX2); */
	/* SET(ADMUX, MUX1); */
	/* allow temperature censor check */

	DIDR0 = (1 << ADC5D | 1 << ADC4D | 1 << ADC3D | 1 << ADC2D | 1 << ADC1D | 1 << ADC0D);
	/* powerconsumption tells us to disable digital input unused */
}

int	main(void)
{	
	init_uart(F_CPU / (8 * 115200) - 1);
	init_timer0();
	init_ADC();
	sei();
	while (1) ;
}

ISR(ADC_vect)
{
	uint16_t	value = ADCL + (ADCH << 8);
	value = -0.0000089 * value * value + 0.78867 * value - 251.3554;
	/* not precise formula from solving two points graph formula */
	print_deca(value);
	uart_printstr("\n\r");
	
	/* ADC looks for OCF0A flag in TIFR0 but if no interruption this flag is never clear */
	SET(TIFR0, OCF0A);
}
