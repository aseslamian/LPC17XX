#include "delay.h"
#include<lpc17xx.h>

void delayUs( unsigned long int delay ) {

	/*
	// 100M(sec)/1000(us) = 100K	
	unsigned long int i, delay2 = 10000; // 100,000 ----Speed----> 10,000

	for( i=0; i<delay; i++ ) {
		while (delay2 > 0) --delay2;
	}*/
	
	
	delayUs_Timer0(delay);
}

void delayUs_Timer0( unsigned long int delay ) {
	LPC_TIM0->TCR = 0x02;		// reset timer
	LPC_TIM0->PR  = 0x00;		// set prescaler to zero
	LPC_TIM0->MR0 = delay * ((100000000/4)/(1000000-1));
	LPC_TIM0->IR  = 0xff;		// reset all interrrupts
	LPC_TIM0->MCR = 0x04;		// stop timer on match
	LPC_TIM0->TCR = 0x01;		// start timer

	// wait until delay time has elapsed
	while (LPC_TIM0->TCR & 0x01);
}
void delayMs_Timer0( unsigned long int delay ) {

	LPC_TIM0->TCR = 0x02;		// reset timer
	LPC_TIM0->PR  = 0x00;		// set prescaler to zero
	LPC_TIM0->MR0 = delay * ((100000000/4)/(1000-1));
	LPC_TIM0->IR  = 0xff;		// reset all interrrupts
	LPC_TIM0->MCR = 0x04;		// stop timer on match
	LPC_TIM0->TCR = 0x01;		// start timer

	// wait until delay time has elapsed
	while (LPC_TIM0->TCR & 0x01);
}
void delayS_Timer0( unsigned long int delay ) {

	LPC_TIM0->TCR = 0x02;		// reset timer
	LPC_TIM0->PR  = 0x00;		// set prescaler to zero
	LPC_TIM0->MR0 = delay * (100000000/4);
	LPC_TIM0->IR  = 0xff;		// reset all interrrupts
	LPC_TIM0->MCR = 0x04;		// stop timer on match
	LPC_TIM0->TCR = 0x01;		// start timer

	// wait until delay time has elapsed
	while (LPC_TIM0->TCR & 0x01);
}

