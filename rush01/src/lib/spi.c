#include "lib/spi.h"
#include "main.h"
#include "module/rgb.h"

/* Il y a 4 lignes en SPI: */
	/* - une ligne SCK (clock, comme en i2c) */
	/* - une ligne Master output Slave Input */
	/* - une ligne Master Input Slave Output */
	/* - une line SS */

/* La ligne SS controle les communications. Elle est gere par le software: quand elle est basse le master communique avec le slave. Quand elle est haute les communications n'ont pas lieu. */
/* A priori selon le schema de la board, il n'y a pas de cable SS. Ni de cable MISO */

void spi_init()
/* Initialisation du SPI en mode master (car on communique avec des LEDs qui sont des slaves) */
{
	SET_OUTPUT(DDRB, 3);
	SET_OUTPUT(DDRB, 5);
	SET_OUTPUT(DDRB, 2);
	SET(PORTB, 2);

	SET(SPCR, SPE);
	SET(SPCR, MSTR); //SPI devient en master mode
	SET(SPCR, SPR0); //La frequence de SCK est de F_CPU/16 ici
}

void	spi_master_transmit(char data)
/* Comme dans SPI: on ecrit dans le registre de donnees puis on attend que la transmission ait eu lieu en regardant les flags */
{
	SPDR = data; //Soit on envoit d'abord le 2^7 bit soit le 2^0. Par defaut 2^7 d'abord
	while (!(SPSR & (1 << SPIF))) ; 
}

/* Les LEDs RGB recoivent un signal de 32bit qu'elles savent decode. Elles fonctionnent avec le PWM et peuvent donc faire pas mal de couleur. Dans la transmission en 32 bit: */
	/* - 1er byte: 3bits a 1 et 5bits pour la luminosite (de base 0/256) */
	/* - 2e byte: 8bits pour le bleu */
	/* - 3e byte: 8bits pour le vert */
	/* - 4e byte: 8bits pour le rouge */

/* On apelle 'frame' une transmission de 32bits (4bytes, 4 appels a transmit data). Pour initialiser une transmission au LED il faut envoyer un frame avec que des 0 puis un frame de set-up de la LED1 (D6), un autre frame de set up de la LED2 (D7) et enfin un autre frame de set-up de la LED3 (D8) */

void	spi_start_frame(void)
{
	for (uint8_t i = 0; i < 4; i++)
		spi_master_transmit(0x00);
}

void	spi_end_frame(void)
{
	for(uint8_t i = 0; i < 4; i++)
		spi_master_transmit(0xFF);
}

void	spi_send_RGB(uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue)
{
	spi_master_transmit((brightness & 0b00011111) | (0b11100000));
	spi_master_transmit(blue);
	spi_master_transmit(green);
	spi_master_transmit(red);
}


