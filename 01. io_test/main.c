#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	int switch1;
	unsigned char led = 0;

	DDRC=0xff; 
    DDRD=0x00;
	while(1)
	{
		switch1=(PIND&(1<<PIND0));
	    
		if(switch1==0)
		{
			if(led == 0)
			{
				led = 0x01;
			}
			else if(led == 0x80)
			{
				led = 0x01;
			}
			else 
			{
				led = led << 1;
			}
		}
		else
		{
			led=0;
		}
		PORTC = led;
		_delay_ms(300);		
	} 
	return 0;
}
