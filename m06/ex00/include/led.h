#ifndef LED_H
# define LED_H

#include <avr/io.h>

void	ratio(uint8_t value);
void	wheel(uint8_t pos);
void	set_rgb(uint8_t r, uint8_t g, uint8_t b);
void	init_LED();

#endif
