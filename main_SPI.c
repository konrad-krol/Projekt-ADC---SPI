#include "LPC23xx.h"

void init_SPI(void);
void send_SPI(int text);

void init_SPI(void)
{
	FIO0DIR |= 0x0004C000; //P0.15-P0.18 - SPI, P0.14 - wybor SLAVE'A
	FIO0SET = 0x00004000;	//P0.14 - SS=1
	PINSEL0 |= 0xC0000000;
	PINMODE1 |= 0x00000000;
	PINSEL1 |= 0x0000403F;	//P0.15-P0.18
	PINMODE1 |= 0x00000000;
	//S0SPCR = 0x0A74;	//LSB pierwszy, Master, CPOL=1, CPHA=0, 10 bitów
	S0SPCR = (1 << 2) |	//BitEnable=1 - okreslona ilosc wyslanych danych
		(0 << 3) |	//CPHA=0 - dane probkowane na zboczu aktywujacym
		(1 << 4) |	//CPOL=1 - polaryzacja sygnalu zegarowego: aktywowany w stanie niskim
		(1 << 5) |  //MSTR=1 - tryb pracy Master
		(1 << 6) |	//LBSF=1 - bit LSB pierwszy
		(0 << 7) |	//SPIE=0 - przerwania wylaczone
		(0 << 8) | (1 << 9) | (0 << 10) | (1 << 11);	//10 bitow wysylanych danych
	
}

void send_SPI(int text)
{
	FIO0CLR = 0x00004000;	//P0.14 - SS wybor Slave
	S0SPDR = text;
	
	while (!(S0SPSR & 0x80));
	
	FIO0SET = 0x00004000;	//P0.14 - SS wybor Slave
}