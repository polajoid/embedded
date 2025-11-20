#include "main.h"
#include "module/rtc.h"
#include "lib/uart.h"
#include "lib/i2c.h"

uint8_t	status;
uint8_t current_century = 20;

uint16_t rtc_time_update(void)
{ 
	uint16_t	buff;
	uint16_t	res;

	buff = rtc_get_minutes();
	res = buff;
	buff = rtc_get_hours();
	res += buff * 100;
	return (res);
}


uint16_t rtc_date_update(void) 
{ 	
	uint16_t	buff;
	uint16_t	res;

	buff = rtc_get_months();
	res = buff;
	buff = rtc_get_days();
	res += buff * 100;
	return (res); 
}


uint16_t rtc_year_update(void)
{ 	

	uint8_t		buff;
	uint16_t	res;

	i2c_start(0x51, I2C_WRITE, &status);
	i2c_write(0x08, &status);
	i2c_stop();
	i2c_start(0x51, I2C_READ, &status);
	i2c_read(I2C_NACK, &buff, &status);
	i2c_stop();
	res = (current_century * 100) + ((buff >> 4) * 10) + (buff & 0x0F);
	return (res);

}

uint8_t	rtc_get_seconds(void)
{
	uint8_t	res;
	i2c_start(0x51, I2C_WRITE, &status);
	i2c_write(0x02, &status);
	i2c_stop();
	i2c_start(0x51, I2C_READ, &status);
	i2c_read(I2C_NACK, &res, &status);
	i2c_stop();
	res = (((res >> 4) & 0x07) * 10 + (res & 0x0F));
	return (res);
}

uint8_t	rtc_get_minutes(void)
{
	uint8_t	res;
	i2c_start(0x51, I2C_WRITE, &status);
	i2c_write(0x03, &status);
	i2c_stop();
	i2c_start(0x51, I2C_READ, &status);
	i2c_read(I2C_NACK, &res, &status);
	i2c_stop();
	res = (((res >> 4) & 0x07) * 10 + (res & 0x0F));
	return (res);
}

uint8_t	rtc_get_hours(void)
{
	uint8_t	res;
	i2c_start(0x51, I2C_WRITE, &status);
	i2c_write(0x04, &status);
	i2c_stop();
	i2c_start(0x51, I2C_READ, &status);
	i2c_read(I2C_NACK, &res, &status);
	i2c_stop();
	res = (((res >> 4) & 0x03) * 10 + (res & 0x0F));
	return (res);
}

uint8_t	rtc_get_days(void)
{	
	uint8_t	res;
	i2c_start(0x51, I2C_WRITE, &status);
	i2c_write(0x05, &status);
	i2c_stop();
	i2c_start(0x51, I2C_READ, &status);
	i2c_read(I2C_NACK, &res, &status);
	i2c_stop();
	res = (((res >> 4) & 0x03) * 10 + (res & 0x0F));
	return (res);
}

uint8_t	rtc_get_months(void)
{
	uint8_t	res;
	i2c_start(0x51, I2C_WRITE, &status);
	i2c_write(0x07, &status);
	i2c_stop();
	i2c_start(0x51, I2C_READ, &status);
	i2c_read(I2C_NACK, &res, &status);
	i2c_stop();
	res = (((res >> 4) & 0x01) * 10 + (res & 0x0F));
	return (res);
}

uint8_t	rtc_get_years(void)
{
	uint8_t	res;
	i2c_start(0x51, I2C_WRITE, &status);
	i2c_write(0x08, &status);
	i2c_stop();
	i2c_start(0x51, I2C_READ, &status);
	i2c_read(I2C_NACK, &res, &status);
	i2c_stop();
	res = ((res >> 4) * 10 + (res & 0x0F));
	return (res);
}

void	rtc_set_time_bdc(uint8_t time[6])
{
	i2c_start(0x51, I2C_WRITE, &status);
	i2c_write(0x02, &status);
	for (uint8_t i = 0; i < 4; i++)
		i2c_write(time[i], &status);
	i2c_write(0x07, &status);
	i2c_write(time[4], &status);
	i2c_write(time[5], &status);
	i2c_stop();
}

void	rtc_init(void)
{
/* 	uint8_t	res; */
/* 	i2c_start(0x51, I2C_WRITE, &status); */
/* 	i2c_write(0x07, &status); */
/* 	i2c_stop(); */
/* 	i2c_start(0x51, I2C_READ, &status); */
/* 	i2c_read(I2C_NACK, &res, &status); */
/* 	i2c_stop(); */
/* 	previous_century = res >> 7; */
/* 	return ; */
}

/* Here value send to this function MUST be correct */
void	rtc_set_time_deci(uint8_t s, uint8_t mi, uint8_t h, uint8_t d, uint8_t mo, uint16_t y)
{
	uint8_t	time[6];

	time[0] = ((s / 10) << 4) + s % 10;
	time[1] = ((mi / 10) << 4) + mi % 10;
	time[2] = ((h / 10) << 4) + h % 10;
	time[3] = ((d / 10) << 4) + d % 10;
	time[4] = ((mo / 10) << 4) + mo % 10;
	current_century = y / 100;
	y = y % 100;
	time[5] = ((y / 10 << 4) + y % 10);
	rtc_set_time_bdc(time);
}
