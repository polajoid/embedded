#ifndef SPI_H
# define SPI_H

# include <avr/io.h>
# include <util/delay.h>
# include <avr/interrupt.h>

void	spi_init();

void	spi_master_transmit(char data);
void	spi_start_frame(void);
void	spi_end_frame(void);

void	spi_send_RGB(uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue);

#endif
