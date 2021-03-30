#include "LPC23xx.h"

void init_LED(void);
void LED_ON(void);
void LED_OFF(void);
void LED_FLAGA_ON(void);
void LED_FLAGA_OFF(void);

void init_LED(void)
{
	FIO2DIR |= 0x00000003;
	PINSEL4 |= 0x00000000;
	PINMODE4 |= 0x00000000;
}

void LED_ON(void)	//informuje, ze uklad pracuje - adc, spi, timer
{
	FIO2SET = 0x00000001;
}

void LED_OFF(void)	//informuje, ze uklad jest wylaczony
{
	FIO2CLR = 0x00000001;
}

void LED_FLAGA_ON(void)	//informuje, ze flaga=1
{
	FIO2SET = 0x00000002;
}

void LED_FLAGA_OFF(void)	//informuje, ze flaga=0
{
	FIO2CLR = 0x00000002;
}