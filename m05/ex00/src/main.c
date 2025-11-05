#include "main.h"
#include "timer.h"
#include "uart.h"

void	print_hexa(uint8_t value)
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

/* Configure ADC to 8 bit with AVCC as reference */
void	init_ADC(void)
{

	SET(ADMUX, REFS0);
	/* VREF = AVCC */
	SET(ADMUX, ADLAR);
	/* Left adjust the result. Precision required is 8 bit. Man explain only high data register is sufficient for 8 bit precision when left adjusted */

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

	DIDR0 = (1 << ADC5D | 1 << ADC4D | 1 << ADC3D | 1 << ADC1D);
	/* powerconsumption tells us to disable digital input unused */
}

int	main(void)
{	
	SET_INPUT(C, 0);
	/* RV1 is on PC0 */

	init_uart(F_CPU / (8 * 115200) - 1);
	init_timer0();
	init_ADC();
	sei();
	while (1) ;
}

ISR(ADC_vect)
{
	uint8_t	value = ADCH;
	/* only need to read in the high register */
	print_hexa(value);
	uart_printstr("\n\r");
	/* ADC looks for OCF0A flag in TIFR0 but if no interruption this flag is never clear */
	SET(TIFR0, OCF0A);
}
