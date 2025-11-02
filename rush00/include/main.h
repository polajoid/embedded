#ifndef MAIN_H
# define MAIN_H

# include <avr/io.h>
# include <util/delay.h>
# include <util/twi.h>


# ifndef UART_BAUDRATE
#  define UART_BAUDRATE 115200
# endif


# define MSK(bit) (1 << bit)

# define SET_MSK(reg, msk) reg |= (msk)
# define CLEAR_MSK(reg, msk) reg &= ~(msk)

# define SET(reg, pin) SET_MSK(reg, MSK(pin))
# define CLEAR(reg, pin) CLEAR_MSK(reg, MSK(pin))

# define SET_OUTPUT(x, a) DDR##x |= (1 << P##x##a)
# define SET_INPUT(x, a) DDR##x &= ~(1 << P##x##a)

# define IS_PRESSED(x, pin) !GET_VALUE(PIN##x, pin)

# define SET_ON(x, pin) SET(PORT##x, pin)
# define SET_OFF(x, pin) CLEAR(PORT##x, pin)
# define TOGGLE(PORTx, pin) PORTx ^= (MSK(pin))

# define GET_VALUE(reg, pin) ((reg >> pin) & 1)

#endif
