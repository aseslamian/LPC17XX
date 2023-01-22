#include <lpc17xx.h>
#include "gpio.h"


/*
Example : Port2 Pin17 = 217  ----> pin = 217
*/
void pinMode( unsigned char pin, char inputResistor, unsigned char status ) {

	if( pin<=31 ) {	// PORT0
		pin -= 0;

		if( status ) 	LPC_GPIO0->FIODIR |=  (1<<pin);
		else 					LPC_GPIO0->FIODIR &= ~(1<<pin);

		// input Resistor
		switch( inputResistor ) {

			case PullUp 	:
				if( pin <=15 ) 	{
					LPC_PINCON->PINMODE0 &= ~(3<<2*pin);
				}
				else {
					LPC_PINCON->PINMODE1 &= ~(3<<2*(pin-16));
				}
			break;

			case Repeater : 
					if( pin <=15 ) {
						LPC_PINCON->PINMODE0 |=  (1<<(2*pin + 0));
						LPC_PINCON->PINMODE0 &= ~(1<<(2*pin + 1));
					}
					else {
						LPC_PINCON->PINMODE1 |=  (1<<(2*(pin-16) + 0));
						LPC_PINCON->PINMODE1 &= ~(1<<(2*(pin-16) + 1));
					}
			break;

			case Neither 	:
				if( pin <=15 ) {
					LPC_PINCON->PINMODE0 &= ~(1<<(2*pin + 0));
					LPC_PINCON->PINMODE0 |=  (1<<(2*pin + 1));
				}
				else {
					LPC_PINCON->PINMODE1 &= ~(1<<(2*(pin-16) + 0));
					LPC_PINCON->PINMODE1 |=  (1<<(2*(pin-16) + 1));
				}
			break;

			case PullDown : 
				if( pin <=15 ) {
					LPC_PINCON->PINMODE0 |= (3<<2*pin);
				}
				else {
					LPC_PINCON->PINMODE1 |= (3<<2*(pin-16));
				}
			break;

			default : while(1); // با اين کار نشون ميديم که خطايي رخ داده
		}
	}
	else if( pin>=32  && pin<=63  ) {	// PORT1
		pin -= 32;
		if( status ) 	LPC_GPIO1->FIODIR |=  (1<<pin);
		else 					LPC_GPIO1->FIODIR &= ~(1<<pin);

		// input Resistor
		switch( inputResistor ) {
			
			case PullUp 	:
				if( pin <=15 ) 	{
					LPC_PINCON->PINMODE2 &= ~(3<<2*pin);
				}
				else {
					LPC_PINCON->PINMODE3 &= ~(3<<2*(pin-16));
				}
			break;
			
			case Repeater : 
					if( pin <=15 ) {
						LPC_PINCON->PINMODE2 |=  (1<<(2*pin + 0));
						LPC_PINCON->PINMODE2 &= ~(1<<(2*pin + 1));
					}
					else {
						LPC_PINCON->PINMODE3 |=  (1<<(2*(pin-16) + 0));
						LPC_PINCON->PINMODE3 &= ~(1<<(2*(pin-16) + 1));
					}
			break;
			
			case Neither 	:
				if( pin <=15 ) {
					LPC_PINCON->PINMODE2 &= ~(1<<(2*pin + 0));
					LPC_PINCON->PINMODE2 |=  (1<<(2*pin + 1));
				}
				else {
					LPC_PINCON->PINMODE3 &= ~(1<<(2*(pin-16) + 0));
					LPC_PINCON->PINMODE3 |=  (1<<(2*(pin-16) + 1));
				}
			break;
			
			case PullDown : 
				if( pin <=15 ) {
					LPC_PINCON->PINMODE2 |= (3<<2*pin);
				}
				else {
					LPC_PINCON->PINMODE3 |= (3<<2*(pin-16));
				}
			break;
			
			default : while(1); // با اين کار نشون ميديم که خطايي رخ داده
		}
	}
	else if( pin>=64  && pin<=95  ) {	// PORT2
		pin -= 64;

		if( status ) 	LPC_GPIO2->FIODIR |=  (1<<pin);
		else 					LPC_GPIO2->FIODIR &= ~(1<<pin);

		// input Resistor
		switch( inputResistor ) {
			
			case PullUp 	:
				if( pin <=15 ) 	{
					LPC_PINCON->PINMODE4 &= ~(3<<2*pin);
				}
				else {
					LPC_PINCON->PINMODE5 &= ~(3<<2*(pin-16));
				}
			break;
			
			case Repeater : 
					if( pin <=15 ) {
						LPC_PINCON->PINMODE4 |=  (1<<(2*pin + 0));
						LPC_PINCON->PINMODE4 &= ~(1<<(2*pin + 1));
					}
					else {
						LPC_PINCON->PINMODE5 |=  (1<<(2*(pin-16) + 0));
						LPC_PINCON->PINMODE5 &= ~(1<<(2*(pin-16) + 1));
					}
			break;
			
			case Neither 	:
				if( pin <=15 ) {
					LPC_PINCON->PINMODE4 &= ~(1<<(2*pin + 0));
					LPC_PINCON->PINMODE4 |=  (1<<(2*pin + 1));
				}
				else {
					LPC_PINCON->PINMODE5 &= ~(1<<(2*(pin-16) + 0));
					LPC_PINCON->PINMODE5 |=  (1<<(2*(pin-16) + 1));
				}
			break;
			
			case PullDown : 
				if( pin <=15 ) {
					LPC_PINCON->PINMODE4 |= (3<<2*pin);
				}
				else {
					LPC_PINCON->PINMODE5 |= (3<<2*(pin-16));
				}
			break;
			
			default : while(1); // با اين کار نشون ميديم که خطايي رخ داده
		}
	}
	else if( pin>=96  && pin<=127 ) {	// PORT3
		pin -= 96;

		if( status ) 	LPC_GPIO3->FIODIR |=  (1<<pin);
		else 					LPC_GPIO3->FIODIR &= ~(1<<pin);

		// input Resistor
		switch( inputResistor ) {
			
			case PullUp 	:
				if( pin <=15 ) 	{
					LPC_PINCON->PINMODE6 &= ~(3<<2*pin);
				}
				else {
					LPC_PINCON->PINMODE7 &= ~(3<<2*(pin-16));
				}
			break;
			
			case Repeater : 
					if( pin <=15 ) {
						LPC_PINCON->PINMODE6 |=  (1<<(2*pin + 0));
						LPC_PINCON->PINMODE6 &= ~(1<<(2*pin + 1));
					}
					else {
						LPC_PINCON->PINMODE7 |=  (1<<(2*(pin-16) + 0));
						LPC_PINCON->PINMODE7 &= ~(1<<(2*(pin-16) + 1));
					}
			break;
			
			case Neither 	:
				if( pin <=15 ) {
					LPC_PINCON->PINMODE6 &= ~(1<<(2*pin + 0));
					LPC_PINCON->PINMODE6 |=  (1<<(2*pin + 1));
				}
				else {
					LPC_PINCON->PINMODE7 &= ~(1<<(2*(pin-16) + 0));
					LPC_PINCON->PINMODE7 |=  (1<<(2*(pin-16) + 1));
				}
			break;
			
			case PullDown : 
				if( pin <=15 ) {
					LPC_PINCON->PINMODE6 |= (3<<2*pin);
				}
				else {
					LPC_PINCON->PINMODE7 |= (3<<2*(pin-16));
				}
			break;
			
			default : while(1); // با اين کار نشون ميديم که خطايي رخ داده
		}
	}
	else if( pin>=128 && pin<=159 ) {	// PORT4
		pin -= 128;

		if( status ) 	LPC_GPIO4->FIODIR |=  (1<<pin);
		else 					LPC_GPIO4->FIODIR &= ~(1<<pin);

		// input Resistor
		switch( inputResistor ) {
			
			case PullUp 	:
				if( pin <=15 ) 	{
					LPC_PINCON->PINMODE8 &= ~(3<<2*pin);
				}
				else {
					LPC_PINCON->PINMODE9 &= ~(3<<2*(pin-16));
				}
			break;
			
			case Repeater : 
					if( pin <=15 ) {
						LPC_PINCON->PINMODE8 |=  (1<<(2*pin + 0));
						LPC_PINCON->PINMODE8 &= ~(1<<(2*pin + 1));
					}
					else {
						LPC_PINCON->PINMODE9 |=  (1<<(2*(pin-16) + 0));
						LPC_PINCON->PINMODE9 &= ~(1<<(2*(pin-16) + 1));
					}
			break;
			
			case Neither 	:
				if( pin <=15 ) {
					LPC_PINCON->PINMODE8 &= ~(1<<(2*pin + 0));
					LPC_PINCON->PINMODE8 |=  (1<<(2*pin + 1));
				}
				else {
					LPC_PINCON->PINMODE9 &= ~(1<<(2*(pin-16) + 0));
					LPC_PINCON->PINMODE9 |=  (1<<(2*(pin-16) + 1));
				}
			break;
			
			case PullDown : 
				if( pin <=15 ) {
					LPC_PINCON->PINMODE8 |= (3<<2*pin);
				}
				else {
					LPC_PINCON->PINMODE9 |= (3<<2*pin);
				}
			break;
			
			default : while(1); // با اين کار نشون ميديم که خطايي رخ داده
		}
	}
}

/*
Example : Port2 Pin17 = 217  ----> pin = 217
*/
void digitalWrite( unsigned char pin, unsigned char status ) {

	if( pin<=31 ) { // PORT0
		pin -= 0;
		if(status)	LPC_GPIO0->FIOSET = (1<<pin);
		else 				LPC_GPIO0->FIOCLR = (1<<pin);
	}
	else if( pin>=32  && pin<=63  ) {	// PORT1
		pin -= 32;
		if(status)	LPC_GPIO1->FIOSET = (1<<pin);
		else 				LPC_GPIO1->FIOCLR = (1<<pin);
	}
	else if( pin>=64  && pin<=95  ) {	// PORT2
		pin -= 64;
		if(status)	LPC_GPIO2->FIOSET = (1<<pin);
		else 				LPC_GPIO2->FIOCLR = (1<<pin);
	}
	else if( pin>=96  && pin<=127 ) {	// PORT3
		pin -= 96;
		if(status)	LPC_GPIO3->FIOSET = (1<<pin);
		else 				LPC_GPIO3->FIOCLR = (1<<pin);
	}
	else if( pin>=128 && pin<=159 ) {	// PORT4
		pin -= 128;
		if(status)	LPC_GPIO4->FIOSET = (1<<pin);
		else 				LPC_GPIO4->FIOCLR = (1<<pin);
	}
}
/*
Example : Port2 Pin17 = 217  ----> pin = 217

return : 
0 : LOW
1 : HIGH
2 : EROR
*/
char digitalRead( unsigned char pin ) {

	if( pin<=31 ) { // PORT0
		pin -= 0;
		return ( LPC_GPIO0->FIOPIN & (1<<pin) ) >> pin;
	}
	else if( pin>=32  && pin<=63  ) {	// PORT1
		pin -= 32;
		return ( LPC_GPIO1->FIOPIN & (1<<pin) ) >> pin;
	}
	else if( pin>=64  && pin<=95  ) {	// PORT2
		pin -= 64;
		return ( LPC_GPIO2->FIOPIN & (1<<pin) ) >> pin;
	}
	else if( pin>=96  && pin<=127 ) {	// PORT3
		pin -= 96;
		return ( LPC_GPIO3->FIOPIN & (1<<pin) ) >> pin;
	}
	else if( pin>=128 && pin<=159 ) {	// PORT4
		pin -= 128;
		return ( LPC_GPIO4->FIOPIN & (1<<pin) ) >> pin;
	}

	return 2; // Error
}

void pinFunction( uint8_t v_pinNumber_u8, uint8_t v_pinFunction_u8 ) {

	uint8_t v_portNumber_u8;
	uint32_t *ptr_PINCON;

	v_portNumber_u8 = (v_pinNumber_u8>>5);
	v_pinNumber_u8  = v_pinNumber_u8 & 0x1f;  //lower 5-bits contains the bit number of a 32bit port

	v_portNumber_u8 = v_portNumber_u8 * 2;
	if( v_pinNumber_u8 >= 16 )
	{
		v_portNumber_u8++; 
		v_pinNumber_u8 = v_pinNumber_u8-16;
	}

	v_pinNumber_u8 = v_pinNumber_u8 * 2;

	ptr_PINCON = ((uint32_t *)&LPC_PINCON->PINSEL0  + v_portNumber_u8);

	*(uint32_t *)(ptr_PINCON) &= ~(0x03UL << v_pinNumber_u8);
	*(uint32_t *)(ptr_PINCON) |= (((uint32_t)v_pinFunction_u8) << v_pinNumber_u8);
}
