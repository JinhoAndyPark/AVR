#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

 
#define sbi(PORTX , BitX)   PORTX |=  (1 << BitX)   // ��Ʈ SET ��� ����
#define cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)   // ��Ʈ CLEAR ��� ����
 
void Main_Init(void);           // �ʱ�ȭ �Լ� ����

int main(void)
{      
    Main_Init();
		
    while(1)
    {
	PORTB=0x40;
	PORTB=0x20;
		/*
        OCR1A=0;        _delay_ms(1500); // 0%��Ƽ��
        OCR1A=250;       _delay_ms(1500); // 25%��Ƽ��
        OCR1A=500;      _delay_ms(1500); // 50%��Ƽ��
        OCR1A=750;      _delay_ms(1500); // 75%��Ƽ��
        OCR1A=1000;      _delay_ms(1500); // 100%��Ƽ��
		
        OCR1B=0;        _delay_ms(1500); // 0%��Ƽ��
        OCR1B=250;       _delay_ms(1500); // 25%��Ƽ��
        OCR1B=500;      _delay_ms(1500); // 50%��Ƽ��
        OCR1B=750;      _delay_ms(1500); // 75%��Ƽ��
        OCR1B=1000;      _delay_ms(1500); // 100%��Ƽ��
    */
	}
return 0;
}
void Main_Init(void)
{
    cbi(SREG,7);        // ��� ���ͷ�Ʈ ��Ȱ��ȭ

    DDRB    = 0xff;     // ��ƮB ������� ����
    //TCCR1A  = 0xA2;     // 1010 0010 ��� 14, 1,0 �񱳸�ġ0��� �����÷ο�1���
	//TCCR1B  = 0x1d;		// 0001 1101 (clkt=16000000/1024=15625Hz ) 64us
    //ICR1 = 1000;		// top ����
	//TCNT1=0;

//	sbi(SREG,7);         
			          
    
       /* TIMSK   = 0x03;     // COMP ���ͷ�Ʈ �ο��̺�
    sbi(SREG,7);      */  // ��� ���ͷ�Ʈ �ο��̺�
}
 
