#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include<math.h>

#define sbi(PORTX , BitX)   PORTX |=  (1 << BitX)   
#define cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)

int rx_data;
unsigned char adcNum;
double T;
double Val;

void Uart_Putch(int data)
{
   while((UCSRA & 0x20) != 0x20);
   UDR = data;
}


ISR(USART_RX_vect)
{	
	rx_data=UDR;

	adcNum=rx_data;
//	Uart_Putch(adcNum);
//	_delay_ms(500);
}

unsigned int read_adc(unsigned char pin)
{
   ADMUX = pin;
   ADCSRA |= (1<<ADSC);
   while(ADCSRA & (1<<ADIF) == 0)
   ADCSRA |=(1<<ADIF);
   return ADCW;
}



void Uart_U16Bit_PutNum(unsigned int NumData)      //각 자리수를 10진수로 변형해서 출력
{
	unsigned int TempData;
	TempData = (NumData/10000);            // 10000 자리출력
	Uart_Putch( TempData+48 );
	TempData = ( NumData%10000)/1000;      // 1000  자리출력
	Uart_Putch( TempData+48 );
	TempData = ( NumData%1000)/100;		   // 100   자리출력
	Uart_Putch( TempData+48 );
	TempData = ( NumData%100)/10;		   // 10    자리출력
	Uart_Putch( TempData+48 );
	TempData = ( NumData%10);			   // 1     자리출력
	Uart_Putch( TempData+48 );
}

int main(void)
{
   ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //ADC EN, 128분주
   SREG |= 0x80;
   
   UCSRA = 0;
   UCSRB = 0x98;   //tx,rx en 	Rx interrupt enable
   UCSRC = 0x06;   //8bit, no parity

   UBRRH = 0;
   UBRRL = 103;//9600  16; //57.6k
	
	DDRA=0x00;	//adc in
	cbi(DDRD,0); //RX in
	sbi(DDRD,1); //TX out
	DDRC=0xff;	//led out
	PORTC=0x00;
   int i=0;
   while(1)
   {

		if(adcNum==1)//CDS
		{
		for(i=0;i<3;i++)
		{
				Val = ((10230/read_adc(1))*4.7)-47;		//scale factor
	  		    T=(2500/Val);
	    		T= T*pow(T,0.25);	//t의 0.25승
				Uart_Putch(T);		//send to 128
				_delay_ms(1000);
			}adcNum=0;
		}
		else if(adcNum==2)//LM35
		{
			for(i=0;i<3;i++)
			{
				T = (int)(read_adc(2)*0.1222);	//scale factor
				Uart_Putch(T);	//send to 128
				_delay_ms(1000);
			}adcNum=0;
		}
		else if(adcNum==3)//Therimister
		{
			for(i=0;i<3;i++)
			{
				Val = read_adc(3);
			
	   			 T = (1 / (log(((1023/Val)*4.7)-4.7)/3800 + 1/298.15)) - 273.15;	//scale factor
				Uart_Putch(T);	//send to 128
				_delay_ms(1000);
			}adcNum=0;
		}
	
   }
   return 0;
}
