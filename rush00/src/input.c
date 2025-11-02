#include "main.h"


uint8_t button_pressed()
{
	return IS_PRESSED(D, PD2);
}
