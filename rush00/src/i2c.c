#include <main.h>

/* i2c data are send and received on the slave devices by reading or writin from registers in the slave decide */

/* uint8_t	init_ic2(void) */
/* /1* returns 1 if master, 0 if slave *1/ */
/* /1* TWCR -> TWI Control Register. Use to enable the TWI, to initiate a Master with start condition by applying a START condition *1/ */
/* { */
/* 	TWCR = (1 << TWEA); */
/* 	/1* TWI Enable Acknowledge Bit ! *1/ */
/* 	TWSR = */ 
/* } */

/* uint8_t	master_send_data(void) */
/* /1* to write: master send first a start condition with the slave address with last bit at 0 (for write) *1/ */
/* /1* then slave answer positevly with a bit *1/ */
/* { */
/* 	TWCR = START_CONDITION; */
/* 	TWCR = ENTER_MASTER */
/* } */

/* uint8_t master_read_data(void) */
/* { */

/* } */

/* uint8_t	slave_send_data(void) */
/* { */

/* } */

/* uint8_t	slare_read_data(void) */
/* { */

/* } */
