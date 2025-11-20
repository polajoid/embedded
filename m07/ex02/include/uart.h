#ifndef UART_H
# define UART_H

# include <avr/io.h>

void	init_uart(uint16_t ubbr);
void	uart_printstr(const char * str);
void	uart_tx(const char c);
unsigned char	uart_rx(void);

void	uart_printdeca(uint8_t n);
void	uart_printhexa(uint8_t n);
void	uart_print_line(const char *buff);

uint8_t	uart_getline(char *buff, const uint8_t size);

#endif
