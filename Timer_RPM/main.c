#include <avr/io.h>
#include <avr/interrupt.h>
unsigned char state=0;		//now state
unsigned int temp=0,rpm=0;		//Rx data
unsigned long OCR_val=0;	//for setting Fulse
unsigned long count=0,time=0,time1rev=0;

void pr(unsigned int j);
unsigned char TX(unsigned int i);


SIGNAL(SIG_INTERRUPT0)
{
	count=count+1;
	if(count==500)
	{
		count=0;
		rpm=60/(1.048576*time+TCNT1*0.000016);
		TCNT1=0;

		time=0;


		TX(rpm/10000+48);			//10000자리 출력
		TX((rpm%10000)/1000+48);	//1000자리 출력
		TX((rpm%1000)/100+48);	//100자리 출력
		TX((rpm%100)/10+48);		//10자리 출력
		TX((rpm%10)+48);			//1자리 출력
		TX('	');
	}

}


SIGNAL(TIMER0_OVF_vect)		//TINT vector
{
	TCNT0 =55; //200=255-55
}

SIGNAL(TIMER1_OVF_vect)		//TINT vector
{

	time=time+1; 
	TCNT1=0;
	
}

unsigned char RX(void)
{
	if(temp =='1')	OCR_val=235;		//55~255 10% 
	else if(temp=='2') OCR_val=155;		//50%
	else if(temp=='3') OCR_val=75;		//90%
	else OCR_val=0;						//none input

	OCR0=OCR_val;

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
	DDRD=0xFB;//0b10000000;

	PORTB=0x02;//0b00000000;
	PORTD=0x00;

	TCCR0 = 0x7d;//0b01101101;
	OCR0=OCR_val;
	TCNT0=55;
	
	TCCR1B = 0x04;	//256
	TCNT1 = 0;	//
	
	TIMSK = 0x05;	//using Time1 16bit timer

	UCSRA = 0x00;	
	UCSRB = 0x18;	
	UCSRC = 0x06;

	UBRRH = 0x00;
	UBRRL = 103;	//9600 baud rate


    GICR=0x40;
    MCUCR = 0x02;

	SREG = 0x80;

	while(1)
	{

		RX();		//recieve data from computer

		TX(temp);	//return data to computer


	}
	return 0;
}
