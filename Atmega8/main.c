#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>


#define 	sbi(PORTX , BitX)   PORTX |=  (1 << BitX)	// SET   BIT
#define 	cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)	// CLEAR BIT
#define     Firstpoint_SIG    1

typedef   signed  char    S08;
typedef unsigned  char    U08;
typedef   signed   int    S16;
typedef unsigned   int    U16;
typedef   signed  long    S32;
typedef unsigned  long    U32;

void ADC_Init(void);
void Uart_Init(void);
unsigned int Read_ADC( unsigned char ADC_Input );
unsigned int Read_ADC_NOSTOP( unsigned char ADC_Input );
void Uart_Putch(unsigned int PutData);
void Uart_U16Bit_PutNum(unsigned int NumData);


U16 Dis;
U08 Getch_USART;

U08 Instruction[3] = {0,0,0};
U08 SIG_To1[3] = {1,2,3};


ISR(USART_RXC_vect)
{

	Getch_USART = UDR; //Read UDR makes rxcflag 0


		switch( Getch_USART )
		{
		
			case 1:		//from Sig_to2[0] - sensing first point & laser on
			
			Instruction[0] = 1;
			sbi(PORTC,3);

			break;

			case 2:		//from Sig_to2[1] - sensing

			Read_ADC(0);
			Dis = (( (11.65/(( ADC/204.8) - 0.147 )) - 0.42 ) * 10)-4;
			Uart_Putch( Dis );

			break;
			
			case 3:

			cbi(PORTC,3); 	//from Sig_to2[2] - laser off

			break;

		}


}





int main(void)
{
	ADC_Init();
	Uart_Init();
	sbi(DDRC,3);
	


	while(1)
	{	
	
		_delay_ms(300);

		if( Instruction[0] == 1)
		{	
			Instruction[0] = 0;
			while(1)
			{	
				Read_ADC(0);
				Dis = (( (11.65/(( ADC/204.8) - 0.147 )) - 0.42 ) * 10)-4;
				if(Dis < 65)
				{
					Uart_Putch(SIG_To1[0]); ////SIG TO 1
					break;
				}
			}
		}
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
	sbi( ADCSRA, ADPS2 );		//001프리스케일러 2분주

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
        UCSRB = (1<<RXEN) | (1<<TXEN) | (1<<RXCIE) ;  		// 수신인터럽트,수신,송신 기능 활성화
		UCSRC = (1<<UCSZ1) | (1<<UCSZ0) | 0x80;					// START 1비트/DATA 8비트/STOP 1비트
		
		cbi( DDRD, 0 );                         // RXD 핀 입력으로 설정
		sbi( DDRD, 1 );                         // TXD 핀 출력으로 설정

		UBRRH = 0;
		UBRRL = 51; //1MHZ:9600:6  8MHZ:9600:51 5.76:8	// Uart 9600 in 8Mhz

		sbi(SREG,7);
}

unsigned int Read_ADC( unsigned char ADC_Input )		//ONLY ONCE SENSING  NO SEQUENTIAL.
{
	ADMUX |= ADC_Input;					//사용자 설정 (ADC값 입력)
	
	ADCSRA |= 0x40;						//ADC START Conversion
	
	while( ( ADCSRA & 0x10 ) == 0 ) ;     //ADC interrupt flag check
	{
		//cbi( ADCSRA, ADEN );			//ADC OFF   NOT SURE ? SBI DDER IS BETTER?
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
	unsigned int TempData;

	TempData = NumData/10000;
	Uart_Putch(TempData+48);      // 10000 	자리 무조건 출력
	
	TempData = (NumData%10000)/1000;
	Uart_Putch(TempData+48);      // 1000 	자리 무조건 출력
	
	TempData = (NumData%1000)/100;
	Uart_Putch(TempData+48);      // 100  	자리 무조건 출력
	
	TempData = (NumData%100)/10;
	Uart_Putch(TempData+48);      // 10   	자리 무조건 출력
	
	TempData =  NumData%10;
	Uart_Putch(TempData+48);      // 1   	자리 무조건 출력
}

