#include "main.h"
#include "delay.h"
#include "light.h"

void	init_i2c(void)
{
	SET(TWSR, TWPS0); //set prescaler 4
	TWBR = 18; //set corresponding value for 100khz
}

void	master_start_condition(void)
{
	TWCR = MSK(TWINT) | MSK(TWSTA) | MSK(TWEN); //Enable I2C interrput , enable I2C , enable master mode
	while (!(TWCR & (1 << TWINT))); //Wait I2C to finish its current job
	while ((TWSR & 0xF8) != 0x08); //Wait for acknowledgment
}

void	master_send_address(void)
{
	TWDR = 0x27 << 1;
	TWCR = MSK(TWINT) | MSK(TWEN);
	while (!(TWCR & (1 << TWINT)));
	while ((TWSR & 0xF8) != 0x18); //Wait for acknowledgment
}

void	master_send_data(unsigned char data)
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN); ////Enable I2C interrput , enable I2C
	while (!(TWCR & (1<<TWINT)));
	while ((TWSR & 0xF8) != 0x28); //Wait for acknowledgment
}

void	master_stop_condition(void)
{
	TWCR = MSK(TWINT) | MSK(TWSTO) | MSK(TWEN);
	SET_ON(B, 4);
}

int	main(void)
/* master_com */
{
	SET_OUTPUT(B, 0);
	SET_OUTPUT(B, 1);
	SET_OUTPUT(B, 2);
	SET_OUTPUT(B, 4);
	init_i2c();
	while (1) 
	{
		master_start_condition();
		SET_ON(B, 0);
		master_send_address();
		SET_ON(B, 1);
		master_send_data('a');
		SET_ON(B, 2);
		master_stop_condition();
		_delay_ms(1000);
		PORTB = 0;

		master_start_condition();
		SET_ON(B, 0);
		master_send_address();
		SET_ON(B, 1);
		master_send_data('b');
		SET_ON(B, 2);
		master_stop_condition();
		_delay_ms(1000);
		PORTB = 0;
	}
}

/* void	set_slave(uint8_t address) */
/* { */
/* 	TWAR = address << 1; */
/* 	TWCR = MSK(TWEA) | MSK(TWEN); */
/* } */

/* unsigned char	slave_receive(void) */
/* { */
/* 	TWCR = MSK(TWINT) | (1 << TWEN) | (1 << TWEA) ; //Enable I2C interrput , enable I2C , enable I2C ACK */
/* 	while (!(TWCR & (1 << TWINT))); */
/* 	while ((TWSR & 0xF8) != 0x80); */
/* 	return TWDR; */
/* } */

/* void	slave_address(void) */
/* { */
/* 	TWCR = (1 << TWEN) | (1 << TWEA); //Enable I2C interrput , enable I2C , enable I2C ACK */
/* 	while (!(TWCR & (1 << TWINT))); */
/* 	while ((TWSR & 0xF8) != 0x60); */ 
/* } */

/* void	slave_stop(void) */
/* { */
/* 	TWCR = MSK(TWINT) | MSK(TWEA) | MSK(TWSTA); */
/* 	while ((TWSR & 0xF8) != 0xA0); */
/* } */

/* int	main(void) */
/* { */
/* 	init_i2c(); */
/* 	SET_OUTPUT(B, 0); */
/* 	SET_OUTPUT(B, 1); */
/* 	SET_OUTPUT(B, 2); */
/* 	set_slave(0x27); */
/* 	while (1) */
/* 	{ */
/* 		slave_address(); */
/* 		unsigned char input = slave_receive(); */
/* 		if (input == 'a') */
/* 			TOGGLE(PORTB, 1); */
/* 		if (input == 'b') */
/* 			TOGGLE(PORTB, 2); */
/* 		slave_stop(); */
/* 	} */
/* } */
