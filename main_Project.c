//Konrad Król
//243176
//TN Czwartek 16:00-18:15

#include "LPC23xx.h"

extern void init_ADC(void);
extern int start_ADC(void);
extern void init_Timer(void);
extern void init_EINT(void);
extern void init_LED(void);
extern void LED_FLAGA_ON(void);
extern void LED_FLAGA_OFF(void);
extern void init_SPI(void);
extern void send_SPI(int text);
extern volatile unsigned char flaga;

int main(void)
{
	int wynik_adc = 0;
	
	SCS |= 0x00000001;	//aktywacja FGPIO
	init_LED();
	init_EINT();
	init_Timer();
	init_ADC();
	init_SPI();
	
	while(1)
	{
		if(flaga == 1)
		{
			LED_FLAGA_ON();
			wynik_adc = start_ADC();
			send_SPI(wynik_adc);
			flaga = 0;
			LED_FLAGA_OFF();
		}
			
	}
	
}