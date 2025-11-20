#ifndef RTC_H
# define RTC_H

# include <avr/io.h>

void	rtc_get_time(uint8_t *data);

uint8_t	rtc_get_seconds(void);
uint8_t	rtc_get_minutes(void);
uint8_t rtc_get_hours(void);
uint8_t rtc_get_days(void);
uint8_t rtc_get_months(void);
uint8_t	rtc_get_years(void);

void	rtc_set_time_deci(uint8_t s, uint8_t mi, uint8_t h, uint8_t d, uint8_t mo, uint16_t y);

uint16_t rtc_time_update();
uint16_t rtc_date_update();
uint16_t rtc_year_update();

#endif
