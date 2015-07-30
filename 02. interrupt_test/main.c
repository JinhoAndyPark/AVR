#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define sbi(PORTX,BitX) PORTX |= (1<<BitX) //비트 SET 명령 정의
#define cbi(PORTX,BitX) PORTX &= ~(1<<BitX) //비트 CLEAR 명령 정의


int num=0;


ISR(INT0_vect)
{	
	num=1;
}

ISR(INT1_vect)
{	
	
	num=2;
}



int main(void)
{	
	sbi(SREG,7);
	sbi(EIMSK,INT0);  
	sbi(EIMSK,INT1);  
	EICRA = 0x0A; 

	DDRC=0xff;   
	
	
	PORTC=0x00;
	while(1)
	{
	
		if(num==1)
		{	
			if(PORTC==0x00)
			PORTC=1;
			else if(PORTC==0x80)
			PORTC=1;
			else
			PORTC<<1;
		}
		if(num==2)
		{
			if(PORTC==0x80)
			PORTC=40;
			else if(PORTC==0)
			PORTC=80;
			else
			PORTC>>1;
		}
	}
return 0;
}
