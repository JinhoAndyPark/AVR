#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char state=0;		//now state
unsigned int temp=0;		//Rx data
unsigned long TCNT_val=0;	//for setting Fulse

SIGNAL(TIMER1_OVF_vect)		//TINT vector
{
	TCNT1 = TCNT_val;
	PORTB =~ PORTB;			//PINB01 toggle
}

unsigned char RX(void)
{
	if(temp =='1')	TCNT_val=59286;		//setting period 100ms
	else if(temp=='2') TCNT_val=34286;	//setting period 500ms
	else if(temp=='3') TCNT_val=3036;	//setting period 1s
	else TCNT_val=65535;				//none input

	while((UCSRA & 0x80) ==0);			//waiting recieve data

	temp=UDR;
	
}

/*This Function for monitoring*/
unsigned char TX(unsigned int i)
{
	while((UCSRA & 0x20) ==0);

	UDR = i;
}

int main(void)
{
	DDRB=0x01;
	PORTB=0x01;

	TCCR1B = 0x04;	//256
	TCNT1 = 65535;	// 
	TIMSK = 0x04;	//using Time1 16bit timer

	UCSRA = 0x00;	
	UCSRB = 0x18;	
	UCSRC = 0x06;

	UBRRH = 0x00;
	UBRRL = 103;	//9600 baud rate

	DDRD=0x02;		//Rx:Input, Tx:Output

	SREG = 0x80;

	while(1)
	{

		//RX();		//recieve data from computer

		TX('1');	//return data to computer


	}
	return 0;
}
