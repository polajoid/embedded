#include "main.h"
#include "i2c.h"


#define ADDR_TEMP_SENSOR 0x38

uint8_t check_sensor_calibration(uint8_t status_cmd)
{
	i2c_send_byte_to(ADDR_TEMP_SENSOR, status_cmd, &g_i2c_status); // Send "get status" command to the sensor
	uint8_t data;
	i2c_receive_from(ADDR_TEMP_SENSOR, I2C_NACK, &data, 1, &g_i2c_status); // Get the response from the sensor
	return (GET_VALUE(data, 3));
}

void temperature_init()
{
	uint8_t init_cmd[3] = {0xBE, 0x08, 0x00};
	const uint8_t status_cmd = 0x71;
	while (!check_sensor_calibration(status_cmd)) {
		i2c_send_to(ADDR_TEMP_SENSOR, init_cmd, 3, &g_i2c_status);
		_delay_ms(10); // Time needed by the sensor for initialization
	}
}

uint8_t *temperature_measure() { static uint8_t ret[7] = {0x71, 0x5d, 0xd4, 0xd6, 0x2e, 0x1a, 0xff}; return ret; } // TODO
/* {
	uint8_t measure_cmd[3] = {0xAC, 0x33, 0x00};
	static uint8_t measure_response[7];
	const uint8_t status_cmd = 0x71;

	// check for 3s delay with rtc
	cli();
	uart_printstr("HERE 1\n");
	i2c_send_to(ADDR_TEMP_SENSOR, measure_cmd, 3, &g_i2c_status);
	i2c_stop();
	do {
		_delay_ms(80); // Time needed by the sensor for measurement
		i2c_send_byte_to(ADDR_TEMP_SENSOR, status_cmd, &g_i2c_status);
		i2c_receive_from(ADDR_TEMP_SENSOR, I2C_NACK, measure_response, 1, &g_i2c_status);
	} while (GET_VALUE(measure_response[0], 7));
	i2c_receive_from(ADDR_TEMP_SENSOR, I2C_NACK, measure_response, 7, &g_i2c_status);
	uart_printstr("HERE 2\n");
	sei();
	return (measure_response);
} */

uint16_t temperature_c_update()
{
	uint8_t *measures = temperature_measure();
	uint32_t temp_raw = ((uint32_t)(measures[3] & 0x0F) << 16) | ((uint32_t)measures[4] << 8) | measures[5];
	return temp_raw / 5242.88 - 50;
}

uint16_t temperature_f_update() { return temperature_c_update() * 9 / 5 + 32; }

uint16_t temperature_humidity_update()
{
	uint8_t *measures = temperature_measure();
	uint32_t hum_raw = ((uint32_t)measures[1] << 12) | ((uint32_t)measures[2] << 4) | (measures[3] >> 4);
	return hum_raw / 10485.76;
}
