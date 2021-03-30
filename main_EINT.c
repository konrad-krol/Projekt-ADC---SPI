#include "LPC23xx.h"

extern void LED_ON(void);
extern void LED_OFF(void);
extern void LED_FLAGA_OFF(void);
extern void Timer_ON(void);
extern void Timer_OFF(void);

void init_EINT(void);
void Start_eint_irq(void) __irq;
void Stop_eint_irq(void) __irq;

void init_EINT(void)
{//EINT0 (P2.10) - START, EINT1 (P2.11) - STOP
	FIO2DIR |= 0x00000000;
	PINSEL4 |= 0x00500000;	//Ustawi GPIO jako EINT0 oraz EINT1
	PINMODE4 |= 0x00000000;
	EXTMODE = 0x03;	//wyzwalanie zboczem
	EXTPOLAR = 0x03;	//wyzwalanie zboczem narastajacym
	VICIntSelect = 0x00000000;	//rejestr wyboru przerwania jako IRQ
	VICVectAddr14 = (unsigned) Start_eint_irq;	//przypisanie adresu podprogramu do obslugi przerwania EINT0
	VICVectPriority14= 2;	//ustawienie priorytetu przerwania EINT0
	VICVectAddr15 = (unsigned) Stop_eint_irq;	//przypisanie adresu podprogramu do obslugi przerwania EINT1
	VICVectPriority15= 1;	//ustawienie priorytetu przerwania EINT1
	VICIntEnable = 0x0000C000;	//wlaczenie przerwania
}

void Start_eint_irq(void) __irq
{
	Timer_ON();
	LED_ON();
	
	EXTINT = 0x00000001;//zerowanie flagi przerwania EINT0
	VICVectAddr = 0x00000000;//zerowanie adresu
}

void Stop_eint_irq(void) __irq
{
	Timer_OFF();
	LED_OFF();
	LED_FLAGA_OFF();
	
	EXTINT = 0x00000002;//zerowanie flagi przerwania EINT1
	VICVectAddr = 0x00000000;//zerowanie adresu
}
