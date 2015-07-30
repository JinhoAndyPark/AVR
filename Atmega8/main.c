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
	DDRC = 0x00; 			   //ADC��Ʈ �Է� ����

	ADMUX = 0x40;
	cbi(ADMUX, ADLAR);
	ADCSRA = 0x00;			   ////AVCC���ڷ� �Է����� ��� �� �������� �ʱ�ȭ 

	sbi( ADCSRA, ADPS0 );
	sbi( ADCSRA, ADPS1 );
	sbi( ADCSRA, ADPS2 );		//001���������Ϸ� 2����

	//sbi( ADCSRA, ADFR );			// �������� ���
	sbi( ADCSRA, ADEN );		   	// ADC �ο��̺�
	//sbi( ADCSRA, ADIE );			// ADC interrupt enable
	//ADMUX = 1;

	//sbi( ADCSRA, ADSC );
}

void Uart_Init(void)
{
	
    //---------------------------- UART �ʱ�ȭ --------------------------------
		cbi(SREG,7);
	
			
		UCSRA = (0<<RXC) | (1<<UDRE);		// ����,�۽� ���º�Ʈ �ʱ�ȭ
        UCSRB = (1<<RXEN) | (1<<TXEN) | (1<<RXCIE) ;  		// �������ͷ�Ʈ,����,�۽� ��� Ȱ��ȭ
		UCSRC = (1<<UCSZ1) | (1<<UCSZ0) | 0x80;					// START 1��Ʈ/DATA 8��Ʈ/STOP 1��Ʈ
		
		cbi( DDRD, 0 );                         // RXD �� �Է����� ����
		sbi( DDRD, 1 );                         // TXD �� ������� ����

		UBRRH = 0;
		UBRRL = 51; //1MHZ:9600:6  8MHZ:9600:51 5.76:8	// Uart 9600 in 8Mhz

		sbi(SREG,7);
}

unsigned int Read_ADC( unsigned char ADC_Input )		//ONLY ONCE SENSING  NO SEQUENTIAL.
{
	ADMUX |= ADC_Input;					//����� ���� (ADC�� �Է�)
	
	ADCSRA |= 0x40;						//ADC START Conversion
	
	while( ( ADCSRA & 0x10 ) == 0 ) ;     //ADC interrupt flag check
	{
		//cbi( ADCSRA, ADEN );			//ADC OFF   NOT SURE ? SBI DDER IS BETTER?
		return ADC;							//ADC�� ��ȯ  RETURN MAKES DONE?
	}
}

unsigned int Read_ADC_NOSTOP( unsigned char ADC_Input )		
{
	ADMUX |= ADC_Input;					//����� ���� (ADC�� �Է�)
	
	ADCSRA |= 0x40;						//ADC START Conversion
	
	while( ( ADCSRA & 0x10 ) == 0 ) ;     //ADC interrupt flag check
	{			
		return ADC;							//ADC�� ��ȯ  RETURN MAKES DONE?
	}
}

void Uart_Putch(unsigned int PutData)
{

			while(!( UCSRA & (1<<UDRE)) );    // �۽Ű��ɽ������� ���
			UDR = PutData;                     // �����͸� �����Ѵ�
		
}

void Uart_U16Bit_PutNum(unsigned int NumData)
{
	unsigned int TempData;

	TempData = NumData/10000;
	Uart_Putch(TempData+48);      // 10000 	�ڸ� ������ ���
	
	TempData = (NumData%10000)/1000;
	Uart_Putch(TempData+48);      // 1000 	�ڸ� ������ ���
	
	TempData = (NumData%1000)/100;
	Uart_Putch(TempData+48);      // 100  	�ڸ� ������ ���
	
	TempData = (NumData%100)/10;
	Uart_Putch(TempData+48);      // 10   	�ڸ� ������ ���
	
	TempData =  NumData%10;
	Uart_Putch(TempData+48);      // 1   	�ڸ� ������ ���
}

