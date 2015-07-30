
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define SET_BIT(PORTX , BitX)   PORTX |=  (1 << BitX)   
#define CLR_BIT(PORTX , BitX)   PORTX &= ~(1 << BitX)


//------------------------------------------------------------------------------
//                   		=== Function Declaration ===
//------------------------------------------------------------------------------
void Init_Main(void);
void Init_Timer0(void);
void Init_Uart0(void);
void Init_Uart1(void);
void Uart_Putch(unsigned char  Com, unsigned int PutData);
void Init_Ext_Interrupt5(void);
void Init_Ext_Interrupt7(void);
void Uart_U16Bit_PutNum(unsigned int Numdata);

//------------------------------------------------------------------------------
//                   		=== Variable Declaration ===
//------------------------------------------------------------------------------

volatile unsigned  int Sonic_val = 0, Sonic_cm = 0;


//------------------------------------------------------------------------------
//                   		=== Interrupt Service Routine ===
//------------------------------------------------------------------------------

ISR(TIMER0_OVF_vect)	// Sonic Trigger Pulse
{
	
		
	SET_BIT(PORTG,0),SET_BIT(PORTG,1);   //�����ʼ��� Ʈ����,���ʼ��� Ʈ����
	_delay_us(10);
	CLR_BIT(PORTG,0),CLR_BIT(PORTG,1); 
	
	TCNT0 = 0; 
	
}

ISR(INT5_vect)           //������ ���� ���� 
{	

	if(EICRB == 0x0c)		    //�����ʸ� RISING  �̸� (���ʵ� RISING�̸� DISABLE �̶�� ��������ħ)
	{
		
		TCNT0 = 0;			//ī��Ʈ �ʱ�ȭ
		EICRB=0x08; 		//�����ʸ� FALLING ����
		
	}
	else if(EICRB == 0x08)    //������ FALLING  ,���� RISING  �̸� 
	{
		
		TCCR0 = 0x00;			//off timer cnt
		Sonic_val = TCNT0;		//check cnt		
		Sonic_cm = (((Sonic_val * 64) * 34300)/2000000) +1;			//������ �Ÿ�����
		Uart_U16Bit_PutNum(Sonic_cm);

		_delay_ms(1000);
		
		EICRB=0xc0;    // ���ʸ�RISING, ���������̿�x 

		TCCR0 = ( 1 << CS00 ) | ( 1 << CS01 ) | ( 1 << CS02 );		//freescale : 1024 Ÿ�̸� ���� 
		TCNT0 = 56;                                                 //256-56=200   64us*200=��12.8ms
		
		CLR_BIT( EIMSK, INT5  );    // EXT_INT 4 DISABLE 
		SET_BIT( EIMSK, INT7  );    // EXT_INT 5 ENABLE
	}
}

ISR(INT7_vect)
{	
	if(EICRB==0xc0)		    //���ʸ� RISING EDGE �̸� 
	{	
		TCNT0 = 0;		//ī��Ʈ �ʱ�ȭ
		//Uart_Putch(1,7);
		EICRB=0x80;   // ���� FALLING SET 
		
	}
	
	else if(EICRB==0x80)    //���ʸ� FALLING
	{
		TCCR0 = 0x00;			//off timer cnt
		Sonic_val = TCNT0;		//check cnt

		Sonic_cm = (((Sonic_val * 64) * 34300)/2000000) +1;			//������ �Ÿ�����
		Uart_U16Bit_PutNum(Sonic_cm);

		_delay_ms(1000);

		EICRB=0x0c;    // �����ʸ� FALLING

		TCCR0 = ( 1 << CS00 ) | ( 1 << CS01 ) | ( 1 << CS02 );		//freescale : 1024
		TCNT0 = 56;                                                 //256-56=200   64us*200=��12.8ms 

		SET_BIT( EIMSK, INT5  );    // EXT_INT 4 ENABLE 
		CLR_BIT( EIMSK, INT7  );    // EXT_INT 5 DISABLE
	}
}

void main(void)
{ 
	Init_Main();		// init_device
	
	while(1)
	{		
	
	}
}


//------------------------------------------------------------------------------
//                       	=== Initialize Function ===
//------------------------------------------------------------------------------
void Init_Main(void)
{
	CLR_BIT(SREG, 7);           	// ��ü���ͷ�Ʈ ������

	Init_Timer0();				// �ʱ�ȭ_Ÿ�̸�2
    Init_Uart0();  				// �ʱ�ȭ_�ø������0
    Init_Uart1();				// �ʱ�ȭ_�ø������1 
    Init_Ext_Interrupt5();		// INT4 ��ȣ ���ͷ�Ʈ(�����ʼ���)
	Init_Ext_Interrupt7();		// INT5 ��ȣ ���ͷ�Ʈ(���ʼ���)

	SET_BIT(DDRG, 0);			// �����ʼ��� Ʈ������¼���
	SET_BIT(DDRG, 1);			// ���ʼ��� Ʈ���� ��¼���
	
	SET_BIT(SREG, 7);            //  ��ü ���ͷ�Ʈ Ȱ��ȭ 
}


void Init_Timer0(void)   
{   
	SET_BIT( TIMSK, TOIE0 );     //timer0 overflow interrupt able
	TCCR0 = ( 1 << CS00 ) | ( 1 << CS01 ) | ( 1 << CS02 );		//���ֺ� 1024 = 64us	
	TCNT0 = 56;					 // 256-56=200   64us*200=��12.8ms	
}


void Init_Uart0(void)		//ALRO UART0=bluetooth
{
	unsigned   int Temp_UBRR0;
	Temp_UBRR0 = 16000000L/(16L * 9600) - 1;   

	UBRR0H = (Temp_UBRR0 >> 8);        
	UBRR0L = (Temp_UBRR0 & 0x00FF);
		
	UCSR0A = (0<<RXC0)  | (1<<UDRE0);	
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);  		
	UCSR0C = (3<<UCSZ00);			
		
	CLR_BIT( DDRE, 0 );        
	SET_BIT( DDRE, 1 );          
}


void Init_Uart1(void)		//ALRO UART1=computer
{
	unsigned   int Temp_UBRR1;
	Temp_UBRR1 = 16000000L/(16L * 9600) - 1;  //(UBRR�� ���ϱ����) UBRR=��103
		
	UBRR1H = (Temp_UBRR1 >> 8);  	//0       
	UBRR1L = (Temp_UBRR1 & 0x00FF); //103  9600bps

	UCSR1A = (0<<RXC1)  | (1<<UDRE1);  //���Ź��� ���������, �۽Ź��� ���������
	UCSR1B = (1<<RXEN1) | (1<<TXEN1);  //���ź� ����,�۽ź� ���� Ȱ��ȭ
	UCSR1C = (3<<UCSZ10);  			   //���۵����� ��Ʈ�� 8��Ʈ            
	
	CLR_BIT( DDRD, 2 );  //���ź� �Է�����
	SET_BIT( DDRD, 3 );  //�۽ź� ������� 
	
}


void Uart_Putch(unsigned char  Com, unsigned int PutData)
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


void Uart_U16Bit_PutNum(unsigned int NumData)   // 10������ ���
{
	unsigned int TempData;
	TempData = NumData/10000;
	Uart_Putch(1,TempData+48);                  // 10000 �ڸ� ���
	TempData = (NumData%10000)/1000;
	Uart_Putch(1,TempData+48);					// 1000 �ڸ� ���
	TempData = (NumData%1000)/100;
	Uart_Putch(1,TempData+48);					// 100 �ڸ� ���
	TempData = (NumData%100)/10;
	Uart_Putch(1,TempData+48);					// 10 �ڸ� ���
	TempData = (NumData%10);			
	Uart_Putch(1,TempData+48);					// 1 �ڸ� ��� 
}


void Init_Ext_Interrupt5(void)  				//������ ���� ���ͷ�Ʈ 
{
	SET_BIT( EICRB, ISC51 );    // INT4 RISING EDGE ENABLE
	SET_BIT( EICRB, ISC50 );    // INT4 RISING EDGE ENABLE
	
	SET_BIT( EIMSK, INT5  );    // EXT_INT 4 ENABLE
	CLR_BIT( EIFR, INTF5 );     // INTERRUPT FLAG CLEAR	
	CLR_BIT( DDRE, 5 );  	    // ��ȣ �޾Ƶ���
	//SET_BIT( PORTE, 4 );		// Input Set, Pull-Up Setting?????????
}

void Init_Ext_Interrupt7(void)
{
	CLR_BIT( EICRB, ISC71 );    // 
	CLR_BIT( EICRB, ISC70 );    //�������� 00  
	
	CLR_BIT( EIMSK, INT7  );    // EXT_INT 5 DISABLE
	CLR_BIT( EIFR , INTF7 );    // INTERRUPT FLAG CLEAR
	CLR_BIT( DDRE, 7);			// ��ȣ �޾Ƶ���   
	//SET_BIT( PORTE, 5);			// Input Set, Pull-Up Setting?????????
}

