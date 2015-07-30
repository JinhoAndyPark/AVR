#include "main.h"

#define stbit	0xFF
#define edbit	0xEE



unsigned char Get_data;
unsigned char RXbuf[30];
unsigned char PKflag, PKcnt;

unsigned char PK_mode, PK_temp, PK_humi, PK_tgtemp, PK_tghumi, PK_time;

unsigned int scancnt;

unsigned char MODE_flag, SENSOR_flag, START_flag, TEMPUP_flag, TEMPDW_flag, HUMIUP_flag, HUMIDW_flag, TIMEUP_flag, TIMEDW_flag;
unsigned char KEY_MODE_flag, KEY_SENSOR_flag, KEY_START_flag, KEY_TEMPUP_flag, KEY_TEMPDW_flag, KEY_HUMIUP_flag, KEY_HUMIDW_flag, KEY_TIMEUP_flag, KEY_TIMEDW_flag;

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 131;
	scancnt++;
	if(scancnt >= 100)
	{
		scancnt = 0;
		KEYSCAN();
	}
}

ISR(USART0_RX_vect)
{
	Disable_ISR();
	Get_data = UDR0;

	if(PKflag == 1)
	{
		if((Get_data == edbit) && (PKcnt == 6))
		{
			PKflag = 0;
			PKcnt = 0;
			PK_mode = RXbuf[0];
			PK_temp = RXbuf[1];
			PK_humi = RXbuf[2];
			PK_tgtemp = RXbuf[3];
			PK_tghumi = RXbuf[4];
			PK_time = RXbuf[5];
		}
		else
		{
			RXbuf[PKcnt] = Get_data;
			PKcnt++;
		}
	}
	
	if((Get_data == stbit) && (PKflag == 0))	
	{
		PKflag = 1;	
	}

	Enable_ISR();
}

void main(void)
{
	Init_main();

	while(1)
	{
		if(PK_mode == 1)	Lcd_Print_Xy(0,0,"MODE: Auto ");
		else				Lcd_Print_Xy(0,0,"MODE: Manu ");
		Lcd_Print_Num(0, 12, PK_time);
		
		Lcd_Print_Num(1, 0, PK_temp);
		Lcd_Print_Xy(1,2,"/");
		Lcd_Print_Num(1, 3, PK_tgtemp);
		Lcd_Print_Xy(1,5,"  ");
		Lcd_Print_Num(1, 7, PK_humi);
		Lcd_Print_Xy(1,9,"/");
		Lcd_Print_Num(1, 10, PK_tghumi);

		_delay_ms(300);
		
	}
}

void Init_main(void)
{
	Disable_ISR();
	
	Lcd_Init();
	Timer0_Init();
	Init_Uart(9600);

	//sbi(DDRE,3);
	//sbi(DDRE,4);

	//cbi(DDRG, 0);

	//Lcd_Print_Xy(0,0, "test");

	DDRB = 0x00;
	DDRG = 0x00;

	Enable_ISR();
}

void Lcd_Init(void)
{
	
	DDRC = 0xff; 
	DDRA = 0x07;
	
	_delay_ms(50);

	Command(0x3C);
	_delay_us(40);
	Command(0x0F);
	_delay_us(40);
	Command(0x01);
	_delay_ms(2);
	Command(0x06);
}

void Command(unsigned char byte)
{
	_delay_ms(30);
	PORTA = 0x00;
	_delay_us(1);
	PORTA = 0x04;
	_delay_us(1);
	PORTC = byte;
	PORTA = 0x03;
	_delay_ms(30);
	PORTA = 0x00;
}

void Data(unsigned char byte)
{
	PORTA = 0x01;
	_delay_us(1);
	PORTA = 0x05;
	_delay_us(1);
	PORTC = byte;
	PORTA = 0x01;
	_delay_ms(30);
	PORTA = 0x00;
}

void Put_Lcd_Char(char Lcd_Data)
{ 
     Data(Lcd_Data); 
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
     	Command( 0x80 + col );
     else 
        Command( 0xc0 + col ); 
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

void Lcd_Print_Num(unsigned char line, unsigned char col, unsigned char data)
{
	unsigned char Temp;
	
	Temp = data / 10;
	Lcd_Put_Char_Xy(line, col, Temp+48);
	Temp = data % 10;
	Lcd_Put_Char_Xy(line, col+1, Temp+48);
}

void Lcd_Print_U16digit(unsigned char line, unsigned char col, unsigned int data)	//0~65535
{
	unsigned char Temp;
	
	Temp = data / 10000;
	Lcd_Put_Char_Xy(line, col, Temp+48);
	Temp = (data % 10000) / 1000;
	Lcd_Put_Char_Xy(line, col+1, Temp+48);
	Temp = (data % 1000) / 100;
	Lcd_Put_Char_Xy(line, col+2, Temp+48);
	Temp = (data % 100) / 10;
	Lcd_Put_Char_Xy(line, col+3, Temp+48);
	Temp = data % 10;
	Lcd_Put_Char_Xy(line, col+4, Temp+48);
}

void Timer0_Init(void)

{                
	sbi( TIMSK, TOIE0 ); 
	TCNT0 = 0;	
		
	TCCR0 = ( 0 << CS00 ) | ( 1 << CS01 ) | ( 1 << CS02 );	
}

void Init_Uart(unsigned int want_Baud)
{
	unsigned int Temp_UBRR;

	Temp_UBRR = 16000000L/(16L * want_Baud) - 1;   

	UBRR0H = (Temp_UBRR >> 8);     
	UBRR0L = (Temp_UBRR & 0x00FF);
		
	UCSR0A = (0<<RXC0)  | (1<<UDRE0);	
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);  		
	UCSR0C = (3<<UCSZ00);			
		
	cbi( DDRE, 0 );                      
	sbi( DDRE, 1 );                       
	
	UCSR0B |=  (1<<RXCIE0);	             
}

void Uart_Putch(unsigned char PutData)
{
	while(!( UCSR0A & (1<<UDRE0)) ); 
	UDR0 = PutData;            
}

void KEYSCAN(void)
{
	if((PINB & (1 << 0)) == 0)
	{
		if(KEY_MODE_flag == 1)
		{
			Uart_Putch('A');
			KEY_MODE_flag = 0;
		}
	}

	else if((PINB & (1 << 1)) == 0)
	{
		if(KEY_SENSOR_flag == 1)
		{
			Uart_Putch('B');
			KEY_SENSOR_flag = 0;
		}
	}

	else if((PINB & (1 << 2)) == 0)
	{
		if(KEY_START_flag == 1)
		{
			Uart_Putch('C');
			KEY_START_flag = 0;
		}
	}

	else if((PINB & (1 << 3)) == 0)
	{
		if(KEY_TEMPUP_flag == 1)
		{
			Uart_Putch('D');
			KEY_TEMPUP_flag = 0;
		}
	}

	else if((PINB & (1 << 4)) == 0)
	{
		if(KEY_TEMPDW_flag == 1)
		{
			Uart_Putch('E');
			KEY_TEMPDW_flag = 0;
		}
	}

	else if((PINB & (1 << 5)) == 0)
	{
		if(KEY_HUMIUP_flag == 1)
		{
			Uart_Putch('F');
			KEY_HUMIUP_flag = 0;
		}
	}

	else if((PINB & (1 << 6)) == 0)
	{
		if(KEY_HUMIDW_flag == 1)
		{
			Uart_Putch('G');
			KEY_HUMIDW_flag = 0;
		}
	}

	else if((PING & (1 << 3)) == 0)
	{
		if(KEY_TIMEUP_flag == 1)
		{
			Uart_Putch('H');
			KEY_TIMEUP_flag = 0;
		}
	}

	else if((PING & (1 << 4)) == 0)
	{
		if(KEY_TIMEDW_flag == 1)
		{
			Uart_Putch('I');
			KEY_TIMEDW_flag = 0;
		}
	}

	else
	{
		KEY_MODE_flag = 1;
		KEY_SENSOR_flag = 1;
		KEY_START_flag = 1;
		KEY_TEMPUP_flag = 1;
		KEY_TEMPDW_flag = 1;
		KEY_HUMIUP_flag = 1;
		KEY_HUMIDW_flag = 1;
		KEY_TIMEUP_flag = 1;
		KEY_TIMEDW_flag = 1;
	}
}