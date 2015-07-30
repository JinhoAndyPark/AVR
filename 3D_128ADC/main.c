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

void Init_ADC(void);
U16 Read_ADC( U08 ADC_Input );
U16 Read_ADC_NOSTOP( U08 ADC_Input );
void Init_Uart(U08 Com, U32 Uart_Baud);
void Uart_Putch(U08 Com, U08 PutData);
void Uart_U16Bit_PutNum(U08 Com, U16 NumData);

U16 Dis;
U08 Getch_USART;

U08 Instruction[3] = {0,0,0};
U08 SIG_To1[3] = {1,2,3};


ISR(USART0_RX_vect)
{
	Getch_USART = UDR0; //Read UDR makes rxcflag 0

//	Uart_Putch( 0,Getch_USART );
		switch( Getch_USART )
		{
		
			case 1:		//from Sig_to2[0]
			
			Instruction[0] = 1;
			
			break;

			case 2:		//from Sig_to2[1]

			Read_ADC(0);
			Dis = (( (11.65/(( ADC/204.8) - 0.147 )) - 0.42 ) * 10)-4;
			//Uart_U16Bit_PutNum(0,Dis);
			Uart_Putch( 0,Dis );

			break;
		}
		/*
	if( Getch_USART == 1)		//from Sig_to2[0]
	{	
//		Uart_Putch( 0,Getch_USART );
		Instruction[0] = 1;
	}	
	else if( Getch_USART == 1 )	//from Si_to2[1]
	{	
		Read_ADC(0);
		Dis = (( (11.65/(( ADC/204.8) - 0.147 )) - 0.42 ) * 10)-4;
		Uart_U16Bit_PutNum(0,Dis);
	}
*/
//	}

}

int main(void)
{
	Init_ADC();
	Init_Uart(0,9600);
	

	while(1)
	{
	//	Uart_Putch(0,2);
		_delay_ms(500);

		if( Instruction[0] == 1)
		{	
			Instruction[0] = 0;
			while(1)
			{	
				//Uart_Putch(0,1);
				
				Read_ADC(0);
				Dis = (( (11.65/(( ADC/204.8) - 0.147 )) - 0.42 ) * 10)-4;
				if(Dis < 65)
				{
					Uart_Putch(0,SIG_To1[0]); ////SIG TO 1
					break;
				}
			}
		}
		
	}
	return 0;
}



void Init_ADC(void)
{
	DDRF = 0x00; 			   //ADC포트 입력 설정

	ADMUX = 0x40;
	ADCSRA = 0x00;			   ////AVCC단자로 입력전압 사용 및 레지스터 초기화 

	sbi( ADCSRA, ADPS0 );
	sbi( ADCSRA, ADPS1 );
	sbi( ADCSRA, ADPS2 );		//프리스케일러 128분주

	//sbi( ADCSRA, ADFR );			// 프리러닝 모드
	sbi( ADCSRA, ADEN );		   	// ADC 인에이블
	//sbi( ADCSRA, ADIE );			// ADC interrupt enable
	//ADMUX = 1;

	//sbi( ADCSRA, ADSC );
}

U16 Read_ADC( U08 ADC_Input )		//ONLY ONCE SENSING  NO SEQUENTIAL.
{
	ADMUX |= ADC_Input;					//사용자 설정 (ADC값 입력)
	
	ADCSRA |= 0x40;						//ADC START Conversion
	
	while( ( ADCSRA & 0x10 ) == 0 ) ;     //ADC interrupt flag check
	{
	//	cbi( ADCSRA, ADEN );			//ADC OFF   NOT SURE ? SBI DDER IS BETTER?
		return ADC;							//ADC값 반환  RETURN MAKES DONE?
	}
}

U16 Read_ADC_NOSTOP( U08 ADC_Input )		
{
	ADMUX |= ADC_Input;					//사용자 설정 (ADC값 입력)
	
	ADCSRA |= 0x40;						//ADC START Conversion
	
	while( ( ADCSRA & 0x10 ) == 0 ) ;     //ADC interrupt flag check
	{			
		return ADC;							//ADC값 반환  RETURN MAKES DONE?
	}
}



void Init_Uart(U08 Com, U32 Uart_Baud)
{
	U16 Temp_UBRR;

	Temp_UBRR = 16000000L/(16L * Uart_Baud) - 1;   	// 통신 보레이트 계산식
													// U2X = 0 일때 (일반모드)
	
    //---------------------------- UART0 초기화 --------------------------------
	if( Com == 0 )                           	
	{
		UBRR0H = (Temp_UBRR >> 8);              // 통신속도 설정
		UBRR0L = (Temp_UBRR & 0x00FF);
		
		UCSR0A = (0<<RXC0)  | (1<<UDRE0);		// 수신,송신 상태비트 초기화
        UCSR0B = (1<<RXEN0) | (1<<TXEN0);  		// 수신,송신 기능 활성화
		UCSR0C = (3<<UCSZ00);				// START 1비트/DATA 8비트/STOP 1비트
		
		cbi( DDRE, 0 );                         // RXD0 핀 입력으로 설정
		sbi( DDRE, 1 );                         // TXD0 핀 출력으로 설정
		
	//	#ifdef UART0_RX_INT_ENABLE			// UART0_RX_INT_ENABLE 설정시만
			UCSR0B |=  (1<<RXCIE0);	             	// 수신인터럽트0 활성화
			sbi(SREG,7);
	//	#endif
	}
	
    //---------------------------- UART1 초기화 --------------------------------
	if( Com == 1)
	{
		UBRR1H = (Temp_UBRR >> 8);              // 통신속도 설정
		UBRR1L = (Temp_UBRR & 0x00FF);

		UCSR1A = (0<<RXC1)  | (1<<UDRE1); 	// 수신,송신 상태비트 초기화
		UCSR1B = (1<<RXEN1) | (1<<TXEN1);    	// 수신,송신 기능 활성화
		UCSR1C = (3<<UCSZ10);                   // START 1비트/DATA 8비트/STOP 1비트
		
		cbi( DDRD, 2 );                         // RXD1 핀 입력으로 설정
		sbi( DDRD, 3 );                         // TXD1 핀 출력으로 설정
		
	//	#ifdef UART1_RX_INT_ENABLE			// UART1_RX_INT_ENABLE 설정시만
			UCSR1B |=  (1<<RXCIE1);              	// 수신인터럽트1 활성화
			sbi(SREG,7);
	//	#endif
	}

}
void Uart_Putch(U08 Com, U08 PutData)
{
	switch(Com)
	{
		case 0:
			while(!( UCSR0A & (1<<UDRE0)) );    // 송신가능시점까지 대기
			UDR0 = PutData;                     // 데이터를 전송한다
			break;
		
		case 1:
			while(!( UCSR1A & (1<<UDRE1)) );    // 송신가능시점까지 대기
			UDR1 = PutData;                     // 데이터를 전송한다
			break;
	}
}

void Uart_U16Bit_PutNum(U08 Com, U16 NumData)
{
	U16 TempData;

	TempData = NumData/10000;
	Uart_Putch(Com, TempData+48);      // 10000 	자리 무조건 출력
	
	TempData = (NumData%10000)/1000;
	Uart_Putch(Com, TempData+48);      // 1000 	자리 무조건 출력
	
	TempData = (NumData%1000)/100;
	Uart_Putch(Com, TempData+48);      // 100  	자리 무조건 출력
	
	TempData = (NumData%100)/10;
	Uart_Putch(Com, TempData+48);      // 10   	자리 무조건 출력
	
	TempData =  NumData%10;
	Uart_Putch(Com, TempData+48);      // 1   	자리 무조건 출력
}

