#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define 	set(PORTX , BitX)   PORTX |=  (1 << BitX)
#define 	clr(PORTX , BitX)   PORTX &= ~(1 << BitX)

void UART_SETTING(void);
void Uart_Putch(unsigned char Com, unsigned char PutData);
void LCD_SETTING(void);
void LCD_CMD(unsigned char byte);
void LCD_DATA(unsigned char byte);
void Put_Lcd_Char(char Lcd_Data);
void Put_Lcd_String( char *Lcd_Data);
void Display_Position(unsigned char line, unsigned char col);
void Lcd_Put_Char_Xy(unsigned char line, unsigned char col, unsigned char Lcd_Data);
void Lcd_Print_Xy(unsigned char line, unsigned char col, char *Lcd_Data);

unsigned char Uart_Getch(unsigned char Com);

unsigned char data;

ISR(USART0_RX_vect)
{
		clr(SREG, 7);
		data = UDR0;
				
		if(data == 'A')		//조건1
		{
			PORTD = 0x00;

			clr(PORTB,0);
			set(PORTB,1);
			set(PORTB,2);

			Lcd_Print_Xy(0, 0, "   WARNING :    ");
			Lcd_Print_Xy(1, 0, "  Sense Sound   ");
			_delay_ms(5000);
			PORTD = 0xFF;
			set(PORTB,0);
		}

		else if(data == 'B')		//조건2
		{
			set(PORTB,0);
			clr(PORTB,1);
			set(PORTB,2);

			Lcd_Print_Xy(0, 0, " Stllable name  ");
			Lcd_Print_Xy(1, 0, "    NOW Do      ");
			_delay_ms(5000);
			set(PORTB,1);
		}

		else if(data == 'C')		//조건3
		{
			set(PORTB,0);
			set(PORTB,1);
			clr(PORTB,2);

			Lcd_Print_Xy(0, 0, " Stllable name  ");
			Lcd_Print_Xy(1, 0, "    NOW Re      ");
			_delay_ms(5000);
			set(PORTB,2);
		}
		set(SREG, 7);
}


int main(void)
{

	LCD_SETTING(); 		//Char LCD 초기화
	UART_SETTING();		//UART(BT) 초기화

	DDRD = 0xFF;		//진동모터 포트출력 선언
	PORTD = 0xFF;		//현재 모든 모터 ON

	DDRB = 0xFF;		//상태 LED 포트출력 선언 
	PORTB = 0xFF;		//초기상태 OFF

	set(SREG, 7);		//전체 인터럽트 활성화
	
	while(1)
	{
		Lcd_Print_Xy(0, 0, "  NOW DRIVING   ");
		Lcd_Print_Xy(1, 0, "                ");
	}
	return 0;
}

void UART_SETTING(void)
{
	unsigned int Temp_UBRR0;
	Temp_UBRR0 = 16000000L/(16L * 9600) - 1;   	// 통신 보레이트 계산식

	UBRR0H = (Temp_UBRR0 >> 8);              // 통신속도 설정 9600
	UBRR0L = (Temp_UBRR0 & 0x00FF);
		
	UCSR0A = (0<<RXC0)  | (1<<UDRE0);
    UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);  	
	UCSR0C = (3<<UCSZ00);
		
	clr( DDRE, 0 );
	set( DDRE, 1 );
}

void LCD_SETTING(void)
{
	
	DDRC = 0xFF; 
	DDRA = 0x07;

	_delay_ms(50);

	LCD_CMD(0x3C);	_delay_us(40);
	LCD_CMD(0x0F);	_delay_us(40);
	LCD_CMD(0x01);
	_delay_ms(2);
	LCD_CMD(0x06);
}

void LCD_CMD(unsigned char byte)
{
	_delay_ms(30);
	PORTA = 0x00;	_delay_us(1);
	PORTA = 0x04;	_delay_us(1);
	PORTC = byte;
	PORTA = 0x03;
	_delay_ms(30);
	PORTA = 0x00;
}

void LCD_DATA(unsigned char byte)
{
	PORTA = 0x01;	_delay_us(1);
	PORTA = 0x05;	_delay_us(1);
	PORTC = byte;
	PORTA = 0x01;
	_delay_ms(30);
	PORTA = 0x00;
}

void Put_Lcd_Char(char Lcd_Data)
{ 
     LCD_DATA(Lcd_Data);
     _delay_ms(20);
}

void Put_Lcd_String( char *Lcd_Data) 
{ 
	while(*Lcd_Data != 0x00) 
    { 
    	Put_Lcd_Char(*Lcd_Data); 
        ++Lcd_Data;
    } 
}

void Display_Position(unsigned char line, unsigned char col) 
{ 
     if( line == 0 ) 
     	LCD_CMD( 0x80 + col );
     else 
        LCD_CMD( 0xc0 + col ); 
}

void Lcd_Put_Char_Xy(unsigned char line, unsigned char col, unsigned char Lcd_Data)
{
	Display_Position( line, col );
	Put_Lcd_Char( Lcd_Data );
}

void Lcd_Print_Xy(unsigned char line, unsigned char col, char *Lcd_Data)
{
	Display_Position( line, col );
	Put_Lcd_String( Lcd_Data );
}


void Uart_Putch(unsigned char Com, unsigned char PutData)
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


