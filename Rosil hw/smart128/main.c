
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>
 
#define sbi(PORTX , BitX)   PORTX |=  (1 << BitX)   
#define cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)

void Main_Init(void);
void Uart_Putch0(unsigned char PutData);
void Uart_Putch1(unsigned char PutData);
void Uart_U16Bit_PutNum(unsigned int NumData);
void Uart_U16Bit_PutNumBL(unsigned int Numdata);
unsigned int Read_ADC(unsigned char ADC_Input);
void Uart_Init(unsigned char com,unsigned long Uart_Baud);

int rx_8535;
int rx_blue;
int adc_num;
int Dis;
int Angle;
int Humid;
int Lux;
int T;

ISR(USART0_RX_vect)
{
	rx_8535 = UDR0;
//	Uart_U16Bit_PutNum(rx_8535);
	Uart_U16Bit_PutNumBL(rx_8535);	//send to bluetooth
//	Uart_Putch1(rx_8535);
	_delay_ms(500);
}

ISR(USART1_RX_vect)
{

	rx_blue = UDR1;
	//Uart_U16Bit_PutNumBL(rx_blue);
	if(rx_blue=='1') adc_num=1;
	else if(rx_blue=='2') adc_num=2;
	else if(rx_blue=='3') adc_num=3;
	else if(rx_blue=='4') adc_num=4;
	else if(rx_blue=='5') adc_num=5;
	else if(rx_blue=='6') adc_num=6;
	else if(rx_blue=='7') adc_num=7;
	else if(rx_blue=='8') adc_num=8;
	else if(rx_blue=='9') adc_num=9;
	_delay_ms(100);

}


int main(void)
{
	Main_Init();
	
	int i = 0;

	
	while(1)
	{	
//	char abc = 1;
//	Uart_U16Bit_PutNumBL(3333);
		_delay_ms(1000);
		if(adc_num==1)	//csd
		{
			for(i=0;i<5;i++)
			{
				Uart_Putch0(1);		//send to 8535
				_delay_ms(1000);
			}adc_num=0;
		}
		else if(adc_num==2)	//LM35	
		{
			for(i=0;i<5;i++)
			{
				Uart_Putch0(2);	//send to 8535
				_delay_ms(1000);
			}adc_num=0;
		}
		else if(adc_num==3)	//the
		{
			for(i=0;i<5;i++)
			{
				Uart_Putch0(3);	//send to 8535
				_delay_ms(1000);
			}adc_num=0;
		}
		else if(adc_num==4) //PSD
		{
			for(i=0;i<5;i++)
			{
				
				Read_ADC(0); 
				Dis = (( (11.65/(( ADC/204.8) - 0.147 )) - 0.42 ) * 10)-4;  //scale factor
				Uart_U16Bit_PutNum(Dis);
			//	Uart_U16Bit_PutNumBL(Dis);
			//	Uart_Putch1(Dis);
				_delay_ms(1000);
			}adc_num=0;
		}
		else if(adc_num==5) //알콜
		{
			for(i=0;i<5;i++)
			{
				Read_ADC(1);	
				Uart_U16Bit_PutNumBL(ADC);
				_delay_ms(1000);
			}adc_num=0;
		}
		else if(adc_num==6) //FLEXABLE
		{
			for(i=0;i<5;i++)
			{
				Read_ADC(2);	
				Angle = ((ADC/1024 * 5 )-(5/4))*216;		//scale factor
				Uart_U16Bit_PutNumBL(ADC);
				
				_delay_ms(1000);
			}adc_num=0;
		}
		else if(adc_num==7)	//소음센서
		{
			for(i=0;i<5;i++)
			{	
				Read_ADC(3);
				Uart_U16Bit_PutNumBL(ADC);
				_delay_ms(1000);
			}adc_num=0;
		}
		else if(adc_num==8)	//습도센서
		{
			for(i=0;i<5;i++)
			{	
				Read_ADC(4);
				Humid = ((ADC*5/1024)-0.5)*50-50;	//scale factor
				Uart_U16Bit_PutNumBL(Humid);
				_delay_ms(1000);
			}adc_num=0;
		}
		else if(adc_num==9)	//프리즘광센서
		{
			for(i=0;i<5;i++)
			{	
			
				Lux = ((10230/Read_ADC(5))*4.7)-47;		//scale factor
	  		    T=(2500/Lux);
	    		T= T*pow(T,0.25);	//t의 0.25승
				
				Uart_U16Bit_PutNumBL(T);
				_delay_ms(1000);
			}adc_num=0;
		}

	}
	
	return 0;
	
}

void Main_Init(void)                        //전체 세팅 
{
	sbi(SREG,7);           					//모든 인터럽트 비활성화
//////////////////////////////////////////////UART 세팅
	Uart_Init(0,9600);			//bluetooth uart enable
	Uart_Init(1,9600);			//computer uart enable
//////////////////////////////////////////////ADC 세팅

	ADMUX = 0x00;							//ADC 초기화
	ADCSRA = 0x87;							//ADC Enable, 분주비=128
	cbi(DDRF,0);							//ADC0 핀 입력으로 설정
	sbi(SREG,7);							//모든 인터럽트 활성화
}

void Uart_Putch0(unsigned char PutData)      //시리얼로부터 1바이트값을 보내는 함수
{
	while(!( UCSR0A & (1<<UDRE0)));         //데이터가 빌때까지 기다렷다가 데이터가차면 아웃
	UDR0 = PutData;							//데이터를 전송한다.
}					
				
void Uart_Putch1(unsigned char PutData)      //시리얼로부터 1바이트값을 보내는 함수
{
	while(!( UCSR1A & (1<<UDRE1)));         //데이터가 빌때까지 기다렷다가 데이터가차면 아웃
	UDR1 = PutData;							//데이터를 전송한다.
}	
		
void Uart_U16Bit_PutNum(unsigned int NumData)      //각 자리수를 10진수로 변형해서 출력
{
	unsigned int TempData;
	TempData = (NumData/10000);            // 10000 자리출력
	Uart_Putch1( TempData+48 );
	TempData = ( NumData%10000)/1000;      // 1000  자리출력
	Uart_Putch1( TempData+48 );
	TempData = ( NumData%1000)/100;		   // 100   자리출력
	Uart_Putch1( TempData+48 );
	TempData = ( NumData%100)/10;		   // 10    자리출력
	Uart_Putch1( TempData+48 );
	TempData = ( NumData%10);			   // 1     자리출력
	Uart_Putch1( TempData+48 );
}
void Uart_U16Bit_PutNumBL(unsigned int Numdata)
{
	unsigned char TempData;

	TempData = ( Numdata/1000);      // 1000  자리출력
	Uart_Putch1( TempData+48 );
	TempData = ( Numdata%1000)/100;		   // 100   자리출력
	Uart_Putch1( TempData+48 );
	TempData = ( Numdata%100)/10;		   // 10    자리출력
	Uart_Putch1( TempData+48);
	TempData = ( Numdata%10);			   // 1     자리출력
	Uart_Putch1( TempData+48);
	_delay_ms(10);
}
unsigned int Read_ADC(unsigned char ADC_Input)		
{
	ADMUX = ADC_Input;					//사용자 설정 (ADC값 입력)
	ADCSRA |= 0x40;						//ADC START Conversion
	while( ( ADCSRA & 0x10) == 0) ;     //ADC interrupt flag check
	return ADC;							//ADC값 반환
}

void Uart_Init(unsigned char com,unsigned long Uart_Baud) 
{	
	unsigned long Temp_UBRR;
	Temp_UBRR = 16000000/(16L * Uart_Baud) - 1;
	
	
    //---------------------------- UART0 초기화 --------------------------------
	if( com==0 )                           	
	{
		           // 통신속도 설정
		UBRR0H =(Temp_UBRR >> 8);              // Baud set
		UBRR0L =(Temp_UBRR & 0x00FF);
		
		UCSR0A = (0<<RXC0) | (1<<UDRE0);  // nothing in recieve buffer & transmission buffer  
		UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0) ;  //recieve & transmission enable ,   
		UCSR0C = (3<<UCSZ00);		//8bit transfer 
		cbi(DDRE,0); 	//RXD input
		sbi(DDRE,1);	//TXD output
		
	}
	
    //---------------------------- UART1 초기화 --------------------------------
	else if( com==1 )
	{
		              
		UBRR1H = (Temp_UBRR >> 8);              // Baud set
		UBRR1L = (Temp_UBRR & 0x00FF);
		  
		UCSR1A = (0<<RXC1) | (1<<UDRE1);	//nothing in recieve buffer & transmission buffer
		UCSR1B = (1<<RXEN1) | (1<<TXEN1) | (1<<RXCIE1);	//recieve & transmission enable
		UCSR1C = (3<<UCSZ10);			//8bit transfer
		cbi(DDRD,2);  	//RXD input
		sbi(DDRD,3);	//TXD output
		
	}
}
