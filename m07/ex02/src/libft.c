#include "libft.h"

uint8_t	ft_strlen(const char *s)
{
	uint8_t	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_copy(const char *s1, char *s2, uint8_t size)
{
	s2[--size] = '\0';
	if (s1 < s2)
	{
		while (size-- > 0)
			s2[size] = s1[size];
		return ;
	}
	while (size > 0)
	{
		*s2++ = *s1++;
		size--;
	}
}

uint16_t	hex_to_dec(const char c)
{
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= '0' && c <= '9')
		return (c - '0');
	else
		return (256);
}

uint16_t	ft_atoihex(const char *n)
{
	uint16_t	res = 0;
	
	while (*n)
	{
		if (hex_to_dec(*n) == 256)
			return (1024);
		res = res * 16 + hex_to_dec(*n);
		n++;
	}
	return (res);
}

uint8_t	ft_strncmp(const char *s1, const char *s2, uint8_t n)
{
	uint8_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || !s1[i] || !s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
