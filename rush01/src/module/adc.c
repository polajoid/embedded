#include "main.h"
#include "adc.h"


void adc_init()
{
	SET_MSK(ADCSRA, MSK(ADEN) |  MSK(ADPS2) | MSK(ADPS1) | MSK(ADPS0)); // Enable and set Prescaler
}

uint16_t adc_get_value(uint8_t component)
{
	ADMUX = MSK(REFS0) | (component << MUX0); // Reference AVCC, 10 bit, MUX to select ADC
	if (component == ADC_TEMP) ADMUX |= MSK(REFS1); // Reference internal 1.1V for internal temp
	SET(ADCSRA, ADSC); // Start Conversion
	while (!GET_VALUE(ADCSRA, ADIF)); // Wait for the conversion to finish
	SET(ADCSRA, ADIF); // Clear conversion flag
	return ADC; // Return conversion result
}

uint16_t adc_pot_update() { return adc_get_value(ADC_POT); }
uint16_t adc_ldr_update() { return adc_get_value(ADC_LDR); }
uint16_t adc_ntc_update() { return adc_get_value(ADC_NTC); }
uint16_t adc_temp_update() { return adc_get_value(ADC_TEMP); }
