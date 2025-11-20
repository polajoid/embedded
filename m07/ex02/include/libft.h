#ifndef LIBFT_H
# define LIBFT_H

# include <avr/io.h>

uint8_t	ft_strncmp(const char *s1, const char *s2, uint8_t n);
uint16_t	ft_atoihex(const char *n);

void	ft_copy(const char *s1, char *s2, uint8_t size);
uint8_t	ft_strlen(const char *s);

#endif
