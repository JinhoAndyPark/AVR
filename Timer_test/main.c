#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char state=0;		//now state
unsigned int temp=0;		//Rx data
unsigned long OCR_val=0;	//for setting Fulse


SIGNAL(TIMER0_OVF_vect)		//TINT vector
{
	TCNT0 =55; //200=255-55
}

SIGNAL(INT0_vect)
{
	if(
}

unsigned char RX(void)
{
	if(temp =='1')	OCR_val=235;	//55~255 10% 
	else if(temp=='2') OCR_val=155;	//50%
	else if(temp=='3') OCR_val=75;	//90%
	else OCR_val=0;				//none input

	OCR0=OCR_val;///2)*-4;

	while((UCSRA & 0x80) ==0);			//waiting recieve data

	temp=UDR;
	
}

//This Function for monitoring
unsigned char TX(unsigned int i)
{
	while((UCSRA & 0x20) ==0);

	UDR = i;
}

int main(void)
{
	DDRB=0xFF;//0b00001011;
	//DDRC=0b00000000;
	DDRD=0xFB;//0b10000000;

	PORTB=0x02;//0b00000000;
	PORTD=0x00;

	TCCR0 = 0x7d;//0b01101101;
	//TCCR2 = 0b00000000;
	OCR0=OCR_val;///2)*-5)-1;
	//TCNT0=55;
	/*
	TCCR1B = 0x04;	//256
	TCNT1 = 65535;	//
	*/ 
	TIMSK = 0x01;	//using Time1 16bit timer

	MCUCR = 0x05;
	GICR = 0x80;

	UCSRA = 0x00;	
	UCSRB = 0x18;	
	UCSRC = 0x06;

	UBRRH = 0x00;
	UBRRL = 103;	//9600 baud rate

	//DDRD=0x02;		//Rx:Input, Tx:Output

	SREG = 0x80;

	while(1)
	{

		RX();		//recieve data from computer

		TX(temp);	//return data to computer


	}
	return 0;
}
