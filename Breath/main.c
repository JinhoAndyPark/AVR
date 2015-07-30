#include <avr/io.h>
#include <util/delay.h>

///////////////////////////////////////
int main(void)
{
	DDRF=0xff;
	while(1)
	{
		PORTF = 0xff;
		asm volatile(" PUSH R0 "); //
	asm volatile(" POP R0 ");		// total 4cycle  result: 2mhz!!!!!
		PORTF = 0;
	
	}
	
	return 0;
}


/*
void delay_us(unsigned char time_us) // time delay(us)
{
	register unsigned int i;

	for(i = 0; i < time_us; i++) // 4 cycle +
	{
	asm volatile(" PUSH R0 "); // 2 cycle +		
	asm volatile(" POP R0 "); // 2 cycle    = 8cycle 1 us * 8 = 8us
	//asm volatile(" PUSH R0 "); // 2 cycle +
	//asm volatile(" POP R0 "); // 2 cycle = 12 cycle = 1.5 us for 8MHz  1cycle = 0.125 us
	}
}
*/
