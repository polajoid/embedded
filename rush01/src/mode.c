#include "main.h"
#include "rtc.h"
#include "d7s.h"
#include "adc.h"
#include "temperature.h"
#include "led.h"
#include "button.h"
#include "rgb.h"


uint8_t mode = 0;

uint16_t (*mode_update[NB_MODE])() = {
	adc_pot_update,
	adc_ldr_update,
	adc_ntc_update,
	adc_temp_update,
	rgb_update,
	temperature_c_update,
	temperature_f_update,
	temperature_humidity_update,
	rtc_time_update,
	rtc_date_update,
	rtc_year_update
};


void mode_inc()
{
	if (mode == 4) rgb_clear();
	mode++;
	if (mode >= NB_MODE) mode = 0;
	led_display_bin(mode);
}

void mode_dec()
{
	if (mode == 4) rgb_clear();
	mode--;
	if (mode >= NB_MODE) mode = NB_MODE - 1;
	led_display_bin(mode);
}

ISR(TIMER2_OVF_vect)
{
	d7s_set_number(mode_update[mode]());
	led_check_state();
}

void mode_init()
{
	SET_MSK(TCCR2B, MSK(CS22) | MSK(CS21) | MSK(CS20)); // Select prescaler 1024 and start the clock
	SET(TIMSK2, TOIE2); // Enable interrupt on overflow (Around every 16ms)
}
