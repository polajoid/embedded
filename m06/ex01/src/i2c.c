#include "i2c.h"
#include "main.h"
#include "uart.h"

void	i2c_init(void)
{
	/* so we wan 100khz on i2c bus and we have this equation: SCLfrq = F_CPU / (16 + 2 * TWBR * prescaler) */
	/* Hence, I set up TWBR at 72 and an prescaler of 1. which doesn't need set up because it's 2 bits cleared*/
	TWBR = 72;
	/* SDA is on port PC4 and SCL is ont port PC5 */
	SET_INPUT(C, 4);
	SET_INPUT(C, 5);

	SET(TWCR, TWEN);
	/* Bit to Enable TWI operation. I am activating TWI interface */
	SET(TWCR, TWEA);
	/* ACK signal will be sent : I can confirm if my data is correctly transmitted on the TWI bus*/
	uart_printstr("I2C has been initialized\n\r");
}

void	i2c_start(void)
{
	/* MCU is the master, T Sensor is the slave. I need to send message asking for a start on the bus and with address of T Sensor */
	/* Step one: write what I want to do */
	SET(TWCR, TWSTA);

	/* Step two: write the TWINT bit to start communication */
	SET(TWCR, TWINT);

	/* Step three: wait for the start condition to be correctly transmit */
	/* When the TWINT flag is set (so becomes = 1), it means the start condition has been transmitted and we can read change in status */
	while (!(TWCR & (1 << TWINT))) ;
	if ((uint8_t)(TWSR) == 0x08)
		uart_printstr("START condition has been transmitted\n\r");
	else if ((uint8_t)(TWSR) == 0x10)
		uart_printstr("Repeated START condition has been transmitted\n\r");
	else
	{
		uart_printstr("Hein?? TWSR: 0x");	
		print_hexa((uint8_t)(TWSR));
		uart_printstr("\r\n");
	}
}

void	i2c_stop(void)
{
	/* Step one: write that I will send a stop condition: */
	SET(TWCR, TWEN);

	/* Step two: clear the TWINT to send the stop condition */
	SET(TWCR, TWINT);
	uart_printstr("Stop condition has been transmitted\n\r");
}

/* ACK means pulling of SDA line down by the slave. SDA down => SLC down. If slave needs more time it can keep SCL line down */ 
/* By default the i2c address of the ATH20 temp sensor is 0x38 and cannot be change */

void	i2c_write(unsigned char data)
{
	/* The next if condition should only be sent when we are at the beginning of a transmission from MCU to temp sens */
	if ((uint8_t)(TWSR) == 0x08 || (uint8_t)(TWSR) == 0x10)
	{
		/* Write SLA+W to TWR. +0 is to state that I want to write, since read is with 1 but totally uncessary */
		TWDR = (0x38 << 1) + 0; 
		SET(TWCR, TWINT);
		/* Again for for TWINT to be set again, then check status flag; has the address been correctly transmitted ? */
		while (!(TWCR & (1 << TWINT))) ;
		uart_printstr("SLA+W has been transmitted. ");
		if ((uint8_t)(TWSR) == 0x18)
			uart_printstr("ACK received\r\n");
		else if ((uint8_t)(TWSR) == 0x20)
			uart_printstr("NOT ACK received\r\n");
		else if ((uint8_t)(TWSR) == 0x38)
			uart_printstr("Arbitration lost in SLA+W. Please restart by sending START condition after the bus becomes free\r\n");
		else
		{
			uart_printstr("What the fuck?? TWSR: 0x");
			print_hexa((uint8_t)(TWSR));
			uart_printstr("\r\n");
		}
	}

	TWDR = data;
	CLEAR(TWCR, TWSTA);
	/* This line changed everything. Pretty weird tbh */
	SET(TWCR, TWINT);
	while (!(TWCR & (1 << TWINT))) ;
	uart_printstr("Data byte has been transmitted. ");
	if ((uint8_t)(TWSR) == 0x28)
		uart_printstr("ACK received\r\n");
	else if ((uint8_t)(TWSR) == 0x30)
		uart_printstr("NOT ACK received\r\n");
	else if ((uint8_t)(TWSR) == 0x38)
		uart_printstr("Arbitration lost in data byte. Please restart by sending START condition after the bus becomes free\r\n");
	else
	{
		uart_printstr("Fuck please work fucking twat: 0x");
		print_hexa((uint8_t)(TWSR));
		uart_printstr("\r\n");
	}
}

void	i2c_read(void)
{
	/* If it is the first read transmit, I need to send the address. So I take the previous code for write but I set up the last bite of the TWDR to 1 to tell the MCU (master) wants to read */
	if ((uint8_t)(TWSR) == 0x08 || (uint8_t)(TWSR) == 0x10)
	{
		/* Write SLA+W to TWR. +1 is to state that I want to read */
		TWDR = (0x38 << 1) + 1; 
		SET(TWCR, TWINT);
		/* Again for for TWINT to be set again, then check status flag; has the address been correctly transmitted ? */
		while (!(TWCR & (1 << TWINT))) ;
		uart_printstr("SLA+W has been transmitted. ");
		if ((uint8_t)(TWSR) == 0x40)
			uart_printstr("ACK received\r\n");
		else if ((uint8_t)(TWSR) == 0x48)
			uart_printstr("NOT ACK received\r\n");
		else if ((uint8_t)(TWSR) == 0x10)
			uart_printstr("Arbitration lost in SLA+W. Please restart by sending START condition after the bus becomes free\r\n");
		else
		{
			uart_printstr("What the fuck?? TWSR: 0x");
			print_hexa((uint8_t)(TWSR));
			uart_printstr("\r\n");
		}
	}

	CLEAR(TWCR, TWSTA);
	SET(TWCR, TWINT);
	while (!(TWCR & (1 << TWINT))) ;
	if ((uint8_t)(TWSR) == 0x50 || (uint8_t)(TWSR) == 0x58)
	{
		uart_printstr("Data byte received. It is: ");
		uint8_t	transmit = TWDR;
		print_hexa(transmit);
		if ((uint8_t)(TWSR) == 0x50)
			uart_printstr(" . ACK returned\r\n");
		else
			uart_printstr(" . NOT ACK returned\r\n");
	}
	else
	{
		uart_printstr("What the fuck?? TWSR: 0x");
		print_hexa((uint8_t)(TWSR));
		uart_printstr("\r\n");
	}
}
