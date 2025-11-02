#ifndef I2C_H
# define I2C_H

/* Thoses macro should be written on TWCR */
# define START_CONDITION (1 << TWINT | 1 << TWSTA | 1 << TWEN ) & ~(1 << TWSTO)
# define ENTER_MASTERTRANSMIT (1 << TWINT | 1 << TWEN) & ~(1 << TWSTA | 1 << TWSTO)
# define STOP_CONDITION (1 << TWINT | 1 << TWSTO | 1 << TWEN) & ~(1 << TWSTA)

# define MASTER_ADDR 0x20
# define SLAVE_ADDR 0x27
/*
Boards I2C adresses :
 ---------------------
| A0 | A1 | A2 | addr |
|---------------------|
| 0  | 0  | 0  | 0x27 |
| 0  | 0  | 1  | 0x23 |
| 0  | 1  | 0  | 0x25 |
| 0  | 1  | 1  | 0x21 |
| 1  | 0  | 0  | 0x26 |
| 1  | 0  | 1  | 0x22 |
| 1  | 1  | 0  | 0x24 |
| 1  | 1  | 1  | 0x20 |
 ---------------------
*/

#endif
