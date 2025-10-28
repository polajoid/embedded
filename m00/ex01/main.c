#include "module_zero.h"

int	main(void)
{
	DDRB = (1 << PB0);
	//DDRx (Data Direction Register) : direction des ports (entree ou sortie)
	//Port D peut recevoir de l'info car il est en mode output
	PORTB = (1 << PB0);
	//La led est sur le port 0 donc on l'active en mettant le bit a 1 ?
	//PORTx : Qu'est ce que je dis a mon port.
	//c'est un port de sortie du fait de DDRD donc il lit les 4 octets de droite
}
