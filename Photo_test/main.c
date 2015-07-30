
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define sbi(PORTX , BitX)   PORTX |=  (1 << BitX)   
#define cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)

void main_init(void);
unsigned int Read_ADC(unsigned char ADC_Input);
void Uart_Init(unsigned char com,unsigned long Uart_Baud);
void Uart_Putch(unsigned char Com, unsigned char PutData);
void Uart_U16Bit_PutNum(unsigned int NumData);


ISR(INT0_vect)
{	
	PORTC=0xff;
	_delay_ms(10);
}



//------------------------------------------------------------------------------
//     					===== main =====
//------------------------------------------------------------------------------
int main(void)
{
	unsigned int Dis=0 ;

	main_init();
	
	sbi(SREG,7);
	sbi(EIMSK,INT0);  
	sbi(EIMSK,INT1);  
	EICRA = 0x0A; 
	
	DDRD=0x00;
	DDRC=0xff;   
	
	
	PORTC=0x00;	

	while(1)
	{   
	Read_ADC(2);
	_delay_ms(100);
	Dis = ( (11.65/((ADC/204.8) - 0.147) ) - 0.42 ) * 10;
	Uart_U16Bit_PutNum(Dis);

	PORTC=0x00;
	}



	return 0;
}
//------------------------------------------------------------------------------
//     					===== main_init =====  					
//------------------------------------------------------------------------------
void main_init(void)
{
	cbi(SREG,7);				//all interrupt disable

	//ADC
	ADMUX = 0x40;							//ADC 초기화
	ADCSRA = 0x87;							//ADC Enable, 분주비=128
	cbi(DDRF,1);							//ADC1 핀 입력으로 설정
	sbi(SREG,7);							//모든 인터럽트 활성화

	//USART 
	Uart_Init(1,9600);			// uart enable
 
	
	sbi(SREG,7);
	
}


unsigned int Read_ADC(unsigned char ADC_Input)		
{	
	ADMUX |= ADC_Input;					//사용자 설정 (ADC값 입력)
	ADCSRA |= 0x40;						//ADC START Conversion
	while( ( ADCSRA & 0x10) == 0) ;     //ADC interrupt flag check
	return ADC;							//ADC값 반환
}



//------------------------------------------------------------------------------
//     				===== Uart_Init =====
//             		: Initial set what num & speed 
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
//     				===== Uart_Putch =====
//------------------------------------------------------------------------------
void Uart_Putch(unsigned char Com, unsigned char PutData)
{
	switch(Com)
	{
		case 0:
			while(!( UCSR0A & (1<<UDRE0)) );    // wait until the point of trasmission available
			UDR0 = PutData;                     // trasfer data
			break;
		
		case 1:
			while(!( UCSR1A & (1<<UDRE1)) );    // wait until the point of trasmission available
			UDR1 = PutData;                     // trasfer data
			break;
	}
}


//------------------------------------------------------------------------------
//     				===== decimal print in ASC =====  					
//------------------------------------------------------------------------------
void Uart_U16Bit_PutNum(unsigned int NumData)
{
	unsigned int TempData;

	TempData = NumData/10000;
	Uart_Putch(0,TempData+48);					// 10000's place print
	TempData = (NumData%10000)/1000;
	Uart_Putch(0,TempData+48);					// 1000's place print
	TempData = (NumData%1000)/100;
	Uart_Putch(0,TempData+48);					// 100's place print
	TempData = (NumData%100)/10;
	Uart_Putch(0,TempData+48);					// 10's place print
	TempData = (NumData%10);			
	Uart_Putch(0,TempData+48);					// 1's place print 
						
	TempData = NumData/10000;
	Uart_Putch(1,TempData+48);					// 10000's place print
	TempData = (NumData%10000)/1000;
	Uart_Putch(1,TempData+48);					// 1000's place print
	TempData = (NumData%1000)/100;
	Uart_Putch(1,TempData+48);					// 100's place print
	TempData = (NumData%100)/10;
	Uart_Putch(1,TempData+48);					// 10's place print
	TempData = (NumData%10);			
	Uart_Putch(1,TempData+48);					// 1's place print 
}
