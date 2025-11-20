#ifndef EXPANDER_H
# define EXPANDER_H

# include "i2c.h"

void expander_init();
void expander_find_addr();

# define EXP_ADDR(i2c_func) if (i2c_func) expander_find_addr();

// Port 0 below
# define D9 3
# define D10 2
# define D11 1
# define SW3 0
# define D7S_CA1 4
# define D7S_CA2 5
# define D7S_CA3 6
# define D7S_CA4 7

// Port 1 below
# define D7S_A 0
# define D7S_B 1
# define D7S_C 2
# define D7S_D 3
# define D7S_E 4
# define D7S_F 5
# define D7S_G 6
# define D7S_DP 7

extern uint8_t g_expander_addr;
# define EXPANDER_I2C_ADDR_MIN 0b00100000
# define EXPANDER_I2C_ADDR_MAX 0b00100111
/* Expander I2C address
[0|0|1|0|0|A0|A1|A2]
*/

/*
Command		Register
	0	Input port 0					|--> does nothing if try to write at it
	1	Input port 1					|
	2	Output port 0				|--> reflect the value that is in the flip-flop controlling the output selection, not the actual pin value
	3	Output port 1				|
	4	Polarity Inversion port 0		|--> invert input polarity ()
	5	Polarity Inversion port 1		|
	6	Configuration port 0		|--> set input(1)/output(0), default input(1)
	7	Configuration port 1		|
*/

#endif
