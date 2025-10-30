#ifndef MODULE_THREE_H
# define MODULE_THREE_H

# ifndef F_CPU 
#  define F_CPU 16000000UL
# endif

# define SET_OUT(x, a) DDR##x |= (1 << P##x##a)
# define SET_IN(x, a) DDR##x &= ~(1 << P##x##a)

# define PORT_TOGGLE(x, a) PIN##x ^= (1 << P##x##a)

# include <avr/io.h>
# include <util/delay.h>
# include <avr/interrupt.h>

#endif
