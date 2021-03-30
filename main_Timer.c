#include <LPC23xx.H>   

void init_Timer (void);
void Timer_irq (void) __irq;
void Timer_ON(void);
void Timer_OFF(void);

volatile unsigned char flaga;

void init_Timer(void)
{  
  T0MR0 = 11999;	//rejestr porównania, 1msec = 12000-1 at 12.0 MHz
  T0MCR = 3;	//Ustawienie przerwania i resetu dla MR0
  VICVectAddr4 = (unsigned long)Timer_irq;	//Adres porprogramu przerwania
  VICVectCntl4 = 3;	//use it for Timer0 Interrupt
  VICIntEnable = (1 << 4);	//aktywacja przerwania Timer0
}
  
void Timer_irq (void) __irq
{
  static int clk_cntr;

  clk_cntr++;
  if (clk_cntr >= 250) //Ustaw flage co 0,25 sekundy
		{
    clk_cntr = 0;
		flaga = 1;
		}

  T0IR = 1;	//zeruj flage przerwania
  VICVectAddr = 0;	//zerowanie adresu
}

void Timer_ON(void)
{
	T0TCR = 1; //uruchom Timer0
}

void Timer_OFF(void)
{
	T0TCR = 0; //zatrzymaj Timer0
}
