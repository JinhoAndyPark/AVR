

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>


#define 	sbi(PORTX , BitX)   PORTX |=  (1 << BitX)	// SET   BIT
#define 	cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)	// CLEAR BIT
#define     Firstpoint_SIG    1


void ADC_Init(void);
void Uart_Init(void);
unsigned int Read_ADC( unsigned char ADC_Input );
unsigned int Read_ADC_NOSTOP( unsigned char ADC_Input );
void Uart_Putch(unsigned int PutData);
void Uart_U16Bit_PutNum(unsigned int NumData);
void delay_us(unsigned char time_us);
void delay_ms(unsigned long time_ms);

unsigned int Dis;
unsigned int Read_RXC;

unsigned char Instruction;

ISR(USART_RXC_vect)
{
	Read_RXC = UDR; //Read UDR makes rxcflag 0
	
	//Uart_Putch(UDR);

//	if( Read_RXC == 1)		//from Sig_to8[0]
//	{	
	//	Uart_Putch(1);
		Instruction = 1;
	//}	
	//if( Read_RXC == 2 )	//from Sig_to8[1]
		
	//	Uart_Putch(99);
		//	while(1)
		//	{

			//	Read_ADC(0);
				//Dis = (( (11.65/(( ADC/204.8) - 0.147 )) - 0.42 ) * 10)-4;
				//if( Dis < 254 )	//cuz UDR0<255 in mega128 
			//	{
					//Uart_U16Bit_PutNum(Read_ADC(0));
				//	break;
			//	}
	   	//	}
	


}
int main(void)
{
	ADC_Init();
	Uart_Init();


	while(1)
	{		
	Read_ADC(0);
//	Uart_Putch(Read_ADC(0));
	Dis = (( (11.65/(( ADC/204.8) - 0.147 )) - 0.42 ) * 10)-4;
	Uart_U16Bit_PutNum(Dis);
	_delay_ms(1000);
//	Uart_Putch(10);
//	_delay_ms(2000);

	}
	return 0;
}

void ADC_Init(void)
{
	DDRC = 0x00; 			   //ADC포트 입력 설정

	ADMUX = 0x40;
	cbi(ADMUX, ADLAR);
	ADCSRA = 0x00;			   ////AVCC단자로 입력전압 사용 및 레지스터 초기화 




	sbi( ADCSRA, ADPS0 );
	sbi( ADCSRA, ADPS1 );
	sbi( ADCSRA, ADPS2 );		//프리스케일러 2분주  

	//sbi( ADCSRA, ADFR );			// 프리러닝 모드
	sbi( ADCSRA, ADEN );		   	// ADC 인에이블
	//sbi( ADCSRA, ADIE );			// ADC interrupt enable
	//ADMUX = 1;

	//sbi( ADCSRA, ADSC );
}

void Uart_Init(void)
{
	
    //---------------------------- UART 초기화 --------------------------------
		cbi(SREG,7);

		
		UCSRA = (0<<RXC) | (1<<UDRE);		// 수신,송신 상태비트 초기화
        UCSRB = (1<<RXEN) | (1<<TXEN) | (1<<RXCIE) | (0<<UCSZ0) ;  		// 수신인터럽트,수신,송신 기능 활성화
		UCSRC = (1<<UCSZ1) | (1<<UCSZ0) | 0x80;					// START 1비트/DATA 8비트/STOP 1비트
		
		cbi( DDRD, 0 );                         // RXD 핀 입력으로 설정
		sbi( DDRD, 1 );                         // TXD 핀 출력으로 설정

		UBRRH = 0;
		UBRRL = 51; //1MHZ:9600:6,48:12,24:25  8MHZ:9600:51 4800:103 2400:207 5.76:8	  16MHZ:9600:103

		sbi(SREG,7);
}

unsigned int Read_ADC( unsigned char ADC_Input )		//ONLY ONCE SENSING  NO SEQUENTIAL.
{
	//unsigned int data,dummy;
	ADMUX |= ADC_Input;					//사용자 설정 (ADC값 입력)
	
	ADCSRA |= 0x40;						//ADC START Conversion
	
	while( ( ADCSRA & 0x10 ) == 0 ) ;     //ADC interrupt flag check
	{
	//	cbi( ADCSRA, ADEN );			//ADC OFF   NOT SURE ? SBI DDER IS BETTER?
	//	data=ADCL;
	//	dummy = ADCH;
		return ADC;							//ADC값 반환  RETURN MAKES DONE?
		
	}
}

unsigned int Read_ADC_NOSTOP( unsigned char ADC_Input )		
{
	ADMUX |= ADC_Input;					//사용자 설정 (ADC값 입력)
	
	ADCSRA |= 0x40;						//ADC START Conversion
	
	while( ( ADCSRA & 0x10 ) == 0 ) ;     //ADC interrupt flag check
	{			
		return ADC;							//ADC값 반환  RETURN MAKES DONE?
	}
}

void Uart_Putch(unsigned int PutData)
{

			while(!( UCSRA & (1<<UDRE)) );    // 송신가능시점까지 대기
			UDR = PutData;                     // 데이터를 전송한다
		
}

void Uart_U16Bit_PutNum(unsigned int NumData)
{
	//NumData = 1024;
	unsigned int TempData;

	TempData = NumData/10000;
	Uart_Putch(TempData+48);		

	TempData = (NumData%10000)/1000;
	Uart_Putch(TempData+48);      // 1000 	자리 무조건 출력
	
	TempData = (NumData%1000)/100;
	Uart_Putch(TempData+48);      // 100  	자리 무조건 출력
	
	TempData = (NumData%100)/10;
	Uart_Putch(TempData+48);      // 10   	자리 무조건 출력
	
	TempData =  NumData%10;
	Uart_Putch(TempData+48);      // 1   	자리 무조건 출력


}

void delay_us(unsigned char time_us) // time delay(us)
{
	register unsigned int i;
	
	for(i = 0; i < time_us; i++) // 4 cycle +
	{
	asm volatile(" PUSH R0 "); // 2 cycle +		
	asm volatile(" POP R0 "); // 2 cycle    = 8cycle 1 us * 8 = 8us
	//asm volatile(" PUSH R0 "); // 2 cycle +
//	asm volatile(" POP R0 "); // 2 cycle = 12 cycle = 1.5 us for 8MHz  1cycle = 0.125 us
	}
	
	/*
	for(i = 0; i < time_us; i++) // 4 cycle +
	{
	asm volatile(" PUSH R0 "); // 2 cycle +		
	asm volatile(" POP R0 "); // 2 cycle +   
	asm volatile(" PUSH R0 "); // 2 cycle +
	asm volatile(" POP R0 "); // 2 cycle +
	asm volatile(" PUSH R0 "); // 2 cycle +		
	asm volatile(" POP R0 "); // 2 cycle = 16 cycle = 1 us for 16MHz  1cycle = 0.0625 us
	}*/
}

void delay_ms(unsigned long time_ms)       
{ 

    register unsigned int i;

    for(i = 0; i < time_ms; i++)

    { 
      delay_us(125); 	//0.001s

	//	delay_us(250);
	//	delay_us(250);
     //	delay_us(250);
	//	delay_us(250); //1ms
    }

}

