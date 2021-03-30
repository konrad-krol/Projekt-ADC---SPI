#include "LPC23xx.h"

void init_ADC(void);
int start_ADC(void);

void init_ADC(void){
	PCONP |= (1<<12);       					/*wlacz przetwornik, bit PCAD*/
	AD0CR |= (1<<21);							/* aktywuj przetwornik, bit PDN*/
	PCLKSEL0 |=(0<<25)|(0<<24);	/*wybor zrodla sygnalu*/
	PINSEL1  |=(0<<15)|(1<<14);					/* Enable AD0 and AD1 inputs , pin P0.23 oraz P0.24 na 01*/
	
	AD0CR = ( 0x01 << 0 ) |						/*preskaler, SEL=1,select channel 0~7 on ADC0 */
	( ( 12000000 / 1000000 - 1 ) << 8 ) |		/* CLKDIV = Fpclk / 1000000 - 1 */
	( 0 << 16 ) | 								/* BURST = 0, no BURST, software controlled */
	( 0 << 17 ) | 								/* liczba okresów zegara przypadajaca na cykl przetwarzania przetwornika, CLKS = 0, 11 clocks/10 bits */
	( 1 << 21 ) | 								/* ograniczenie zasilania ukladu przetwornika ,PDN = 1, normal operation */
	( 0 << 24 ) | 								/* START = 0 then A/D conversion stops */
	( 0 << 27 ); 								/* EDGE = 0 (CAP/MAT singal falling,trigger A/D conversion) */
}

int start_ADC(void)
{
	int val;
	AD0CR |= ( 1 << 24 );           			/* Przetwornik wlaczony - Bity 26:24 = 001 - start konwersji */
	do 
		{
			val = AD0GDR;           		/* Read A/D Data Register*/
		} 
	while ((val & 0x80000000) == 0);		/*koniec gdy warunek zwroci  FALSE*/
	val = (val >> 6) & 0x03FF;
	return val;
}
