#include "main.h"


#define STEP_MS 10

/*
Execute _delay_ms(STEP_MS) multiple times and the function f() between each time.
The longer f() take, the less delay_check() is precise.
If f() == 0, the delay continue.
If f() != 0, the delay stop and the return value of f() is returned.
*/
uint8_t delay_check(double ms, uint8_t (*f)(void))
{
	uint8_t ret;

	for (double i = 0; i < (ms / STEP_MS); i++)
	{
		_delay_ms(STEP_MS);
		if (ret = f()) return ret;
	}
}
