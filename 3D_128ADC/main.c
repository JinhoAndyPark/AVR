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
	DDRF = 0x00; 			   //ADC��Ʈ �Է� ����

	ADMUX = 0x40;
	ADCSRA = 0x00;			   ////AVCC���ڷ� �Է����� ��� �� �������� �ʱ�ȭ 

	sbi( ADCSRA, ADPS0 );
	sbi( ADCSRA, ADPS1 );
	sbi( ADCSRA, ADPS2 );		//���������Ϸ� 128����

	//sbi( ADCSRA, ADFR );			// �������� ���
	sbi( ADCSRA, ADEN );		   	// ADC �ο��̺�
	//sbi( ADCSRA, ADIE );			// ADC interrupt enable
	//ADMUX = 1;

	//sbi( ADCSRA, ADSC );
}

U16 Read_ADC( U08 ADC_Input )		//ONLY ONCE SENSING  NO SEQUENTIAL.
{
	ADMUX |= ADC_Input;					//����� ���� (ADC�� �Է�)
	
	ADCSRA |= 0x40;						//ADC START Conversion
	
	while( ( ADCSRA & 0x10 ) == 0 ) ;     //ADC interrupt flag check
	{
	//	cbi( ADCSRA, ADEN );			//ADC OFF   NOT SURE ? SBI DDER IS BETTER?
		return ADC;							//ADC�� ��ȯ  RETURN MAKES DONE?
	}
}

U16 Read_ADC_NOSTOP( U08 ADC_Input )		
{
	ADMUX |= ADC_Input;					//����� ���� (ADC�� �Է�)
	
	ADCSRA |= 0x40;						//ADC START Conversion
	
	while( ( ADCSRA & 0x10 ) == 0 ) ;     //ADC interrupt flag check
	{			
		return ADC;							//ADC�� ��ȯ  RETURN MAKES DONE?
	}
}



void Init_Uart(U08 Com, U32 Uart_Baud)
{
	U16 Temp_UBRR;

	Temp_UBRR = 16000000L/(16L * Uart_Baud) - 1;   	// ��� ������Ʈ ����
													// U2X = 0 �϶� (�Ϲݸ��)
	
    //---------------------------- UART0 �ʱ�ȭ --------------------------------
	if( Com == 0 )                           	
	{
		UBRR0H = (Temp_UBRR >> 8);              // ��żӵ� ����
		UBRR0L = (Temp_UBRR & 0x00FF);
		
		UCSR0A = (0<<RXC0)  | (1<<UDRE0);		// ����,�۽� ���º�Ʈ �ʱ�ȭ
        UCSR0B = (1<<RXEN0) | (1<<TXEN0);  		// ����,�۽� ��� Ȱ��ȭ
		UCSR0C = (3<<UCSZ00);				// START 1��Ʈ/DATA 8��Ʈ/STOP 1��Ʈ
		
		cbi( DDRE, 0 );                         // RXD0 �� �Է����� ����
		sbi( DDRE, 1 );                         // TXD0 �� ������� ����
		
	//	#ifdef UART0_RX_INT_ENABLE			// UART0_RX_INT_ENABLE �����ø�
			UCSR0B |=  (1<<RXCIE0);	             	// �������ͷ�Ʈ0 Ȱ��ȭ
			sbi(SREG,7);
	//	#endif
	}
	
    //---------------------------- UART1 �ʱ�ȭ --------------------------------
	if( Com == 1)
	{
		UBRR1H = (Temp_UBRR >> 8);              // ��żӵ� ����
		UBRR1L = (Temp_UBRR & 0x00FF);

		UCSR1A = (0<<RXC1)  | (1<<UDRE1); 	// ����,�۽� ���º�Ʈ �ʱ�ȭ
		UCSR1B = (1<<RXEN1) | (1<<TXEN1);    	// ����,�۽� ��� Ȱ��ȭ
		UCSR1C = (3<<UCSZ10);                   // START 1��Ʈ/DATA 8��Ʈ/STOP 1��Ʈ
		
		cbi( DDRD, 2 );                         // RXD1 �� �Է����� ����
		sbi( DDRD, 3 );                         // TXD1 �� ������� ����
		
	//	#ifdef UART1_RX_INT_ENABLE			// UART1_RX_INT_ENABLE �����ø�
			UCSR1B |=  (1<<RXCIE1);              	// �������ͷ�Ʈ1 Ȱ��ȭ
			sbi(SREG,7);
	//	#endif
	}

}
void Uart_Putch(U08 Com, U08 PutData)
{
	switch(Com)
	{
		case 0:
			while(!( UCSR0A & (1<<UDRE0)) );    // �۽Ű��ɽ������� ���
			UDR0 = PutData;                     // �����͸� �����Ѵ�
			break;
		
		case 1:
			while(!( UCSR1A & (1<<UDRE1)) );    // �۽Ű��ɽ������� ���
			UDR1 = PutData;                     // �����͸� �����Ѵ�
			break;
	}
}

void Uart_U16Bit_PutNum(U08 Com, U16 NumData)
{
	U16 TempData;

	TempData = NumData/10000;
	Uart_Putch(Com, TempData+48);      // 10000 	�ڸ� ������ ���
	
	TempData = (NumData%10000)/1000;
	Uart_Putch(Com, TempData+48);      // 1000 	�ڸ� ������ ���
	
	TempData = (NumData%1000)/100;
	Uart_Putch(Com, TempData+48);      // 100  	�ڸ� ������ ���
	
	TempData = (NumData%100)/10;
	Uart_Putch(Com, TempData+48);      // 10   	�ڸ� ������ ���
	
	TempData =  NumData%10;
	Uart_Putch(Com, TempData+48);      // 1   	�ڸ� ������ ���
}

