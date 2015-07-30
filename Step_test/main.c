#include <avr/io.h>
#include <util/delay.h>

#define sbi(PORTX , BitX)   PORTX |=  (1 << BitX)   
#define cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)

int main(void)
{
	DDRA = 0xff;
	
	cbi(PORTA,3);	//2»ó
	sbi(PORTA,4);	//reset

	sbi(PORTA,1);
		
	sbi(PORTA,7);	////DIR 1=CLOCK 0=DISCLOCK
	
	

	while(1)
	{
		//sbi(PORTA,6);
		sbi(PORTA,5);
		_delay_us(1500);
	//	cbi(PORTA,6);
		cbi(PORTA,5);
	
	}

	return 0;
}
