
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

 
#define sbi(PORTX , BitX)   PORTX |=  (1 << BitX)   
#define cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)

void Main_Init(void);
void Uart_Putch(unsigned char PutData);
void Uart_U16Bit_PutNum(unsigned int NumData);
unsigned int Read_ADC(unsigned char ADC_Input);



void main(void)
{
	Main_Init();

	while(1)
	{
		Uart_U16Bit_PutNum(Read_ADC(0b01000000));  //������ ���� ���� �����͸� ��ǻ�ͷ� �۽�
		_delay_ms(1000);
	}
}

void Main_Init(void)                        //��ü ���� 
{
//////////////////////////////////////////////UART ����

	cbi(SREG,7);           					//��� ���ͷ�Ʈ ��Ȱ��ȭ
	UBRR0H = 0; UBRR0L = 16;				//57600bps(16MHz)
	UCSR0A = (0<<RXC0)|(1<<UDRE0);			//����,�۽� ���º�Ʈ �ʱ�
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);			//����,�۽� ��� Ȱ��ȭ
	UCSR0C = (3<<UCSZ00);					//START  1��Ʈ DATA8��Ʈ
	cbi(DDRE,0);							//RXD1�� �Է����� ����
	sbi(DDRE,1);							//TXD1�� ������� ����

	                   



//////////////////////////////////////////////ADC ����

	ADMUX = 0x00;							//ADC �ʱ�ȭ
	ADCSRA = 0x87;							//ADC Enable, ���ֺ�=128
	cbi(DDRF,0);							//ADC0 �� �Է����� ����
	sbi(SREG,7);							//��� ���ͷ�Ʈ Ȱ��ȭ
}



void Uart_Putch(unsigned char PutData)      //�ø���κ��� 1����Ʈ���� ������ �Լ�
{
	while(!( UCSR0A & (1<<UDRE0)));         //�����Ͱ� �������� ��ٷǴٰ� �����Ͱ����� �ƿ�
	UDR0 = PutData;							//�����͸� �����Ѵ�.
}										



void Uart_U16Bit_PutNum(unsigned int NumData)      //�� �ڸ����� 10������ �����ؼ� ���
{
	unsigned int TempData;
	TempData = (NumData/10000);            // 10000 �ڸ����
	Uart_Putch( TempData+48 );
	TempData = ( NumData%10000)/1000;      // 1000  �ڸ����
	Uart_Putch( TempData+48 );
	TempData = ( NumData%1000)/100;		   // 100   �ڸ����
	Uart_Putch( TempData+48 );
	TempData = ( NumData%100)/10;		   // 10    �ڸ����
	Uart_Putch( TempData+48 );
	TempData = ( NumData%10);			   // 1     �ڸ����
	Uart_Putch( TempData+48 );
}




unsigned int Read_ADC(unsigned char ADC_Input)		
{
	ADMUX = ADC_Input;					//����� ���� (ADC�� �Է�)
	ADCSRA |= 0x40;						//ADC START Conversion
	while( ( ADCSRA & 0x10) == 0) ;     //ADC interrupt flag check
	return ADC;							//ADC�� ��ȯ
}
