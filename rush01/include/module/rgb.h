#ifndef RGB_H
# define RGB_H

#include <avr/io.h>

void rgb_init();
void rgb_gpio_init();

void	rgb_mode(void);

void	rgb_gpio_init(void);
void	rgb_gpio_blink(uint8_t rotation);

void	rgb_spi_blink(uint8_t rotation);

uint16_t rgb_update();

void rgb_clear();
void rgb_spi_clear();
void rgb_gpio_clear();

#endif
