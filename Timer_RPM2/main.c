#include <avr/io.h>
#include <avr/interrupt.h>

typedef unsigned int U16;
typedef unsigned char U08;

unsigned char state=0;		//now state
unsigned int temp=0;		//Rx data
unsigned long OCR_val=0;	//for setting Fulse

unsigned int Encoder_CNT=0,Encoder_TMR=0,nTIME=0,nRPM=0;
unsigned char Read_flag=0;

unsigned char RX(void)
{
	if(temp =='1')	OCR_val=250;	//55~255 10% 
	else if(temp=='2') OCR_val=230;	//50%
	else if(temp=='3') OCR_val=210;	//90%
	else OCR_val=0;				//none input

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


void Uart_U16Bit_PutNum(U16 NumData)
{
	U16 TempData;

	TempData = NumData/10000;
	TX(TempData+48);      // 10000 	자리 무조건 출력
	
	TempData = (NumData%10000)/1000;
	TX(TempData+48);      // 1000 	자리 무조건 출력
	
	TempData = (NumData%1000)/100;
	TX(TempData+48);      // 100  	자리 무조건 출력
	
	TempData = (NumData%100)/10;
	TX(TempData+48);      // 10   	자리 무조건 출력
	
	TempData =  NumData%10;
	TX(TempData+48);      // 1   	자리 무조건 출력
}

SIGNAL(TIMER2_OVF_vect)	//0.000004s
{
	Encoder_TMR++;
}

SIGNAL(INT0_vect)	//ENCODER vector
{
	Encoder_CNT++;
	if(Encoder_CNT>=500)
	{
		Encoder_CNT = 0;
		nTIME = Encoder_TMR;
		//Encoder_TMR = 0;
		nTIME = (nTIME*256)+TCNT2;
		TCNT2=0; Encoder_TMR=0;
		nRPM = 15000000/nTIME;
		TX(' ');
		Uart_U16Bit_PutNum(nRPM);

	}
}



int main(void)
{
	DDRB=0xFF;//0b00001011;
	DDRD=0xFB;//0b10000000;

	PORTB=0x02;//0b00000000;
	PORTD=0x00;

	TCCR0 = 0x7d;//0b01101101;
	TCCR2 = 0x04;//0b00000000;
	OCR0=OCR_val;///2)*-5)-1;
	//TCNT0=55;
	
	//TCCR1B = 0x04;	//256
	//TCNT1 = 65535;	//
	 
	TIMSK = 0x41;	//using Time1 16bit timer

	MCUCR = 0x03;
	GICR = 0x40;

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
		TX(' ');


	}
	return 0;
}
