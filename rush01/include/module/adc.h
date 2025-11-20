#ifndef ADC_H
# define ADC_H

void adc_init();

uint16_t adc_pot_update();
uint16_t adc_ldr_update();
uint16_t adc_ntc_update();
uint16_t adc_temp_update();

# define ADC_POT PC0
# define ADC_LDR PC1
# define ADC_NTC PC2
# define ADC_TEMP 8

#endif
