#include "main.h"
#include "uart.h"
#include "rtc.h"

int main()
{
	init();
	rtc_init();
	// startup_routine();
	while (1)
	{
		input_set_time();
	}
}
