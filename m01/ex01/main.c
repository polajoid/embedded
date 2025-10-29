#include "module_one.h"

int main(void)
{
	SET_OUT(B, 1);
	//LED 1 is in output mode. According to man, input mode will disable pin com. No PORT so no initial poweroff

	//Set up of the Timer1 registrer
	//We want timer to self-return to 0 after reaching a certain max value
	//It is the purpose of CTC mode (Clear Timer on Compare). It is activate through Timer1 register B
	//Hence, first registre (A) will not be used so: 
	TCCR1B = (1 << WGM12 | 1 << CS12); //activate CTC mode withc CS12 (datasheets table 15-5) 
									   //WGW is : Wave Generation Mode + 256 prescale -> no need to count until ->msHz onyl until 256/msHz
	TCCR1A = (1 << COM1A0); //toggle OC1A (so PB1) on compare match
	//Which max for CTC ? 
	//Every 0.5s -> toggle LED so frequency of toggle is 2hz
	//answer : 31250 -> (F_CPU / (target_frequency * presquale)) - 1 (because we start the count from 0)
	OCR1A = 31249;
	while (1) 
	{
	}
}
