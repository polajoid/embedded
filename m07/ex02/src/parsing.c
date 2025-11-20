#include "parsing.h"
#include "uart.h"

const char	*find_quote(const char *buff)
{
	if (*buff != '"' && *buff)
		buff = find_quote(++buff);
	return (buff);
}

const char	*isolate_key(const char *buff)
{
	buff = find_quote(buff);
	if (*find_quote(++buff))
	{
		if (buff[0] == '"')
			return (0);
		return (buff);
	}
	return (0);
}
