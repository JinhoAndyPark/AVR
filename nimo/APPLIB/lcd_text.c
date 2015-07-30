#include <avr/io.h>			//ATmega128 I/O Header
#include <avr/interrupt.h>		//ATmega128 INTERRUPT Header
#include <util/delay.h>			//ATmega128 delay Function Header

#include "../define.h"
#include "lcd_text.h"


void Lcd_Init(void)
{
	
	LCD_PORT_SETUP();
	
	_delay_ms(50);

	Command(0x3C);
	_delay_us(40);
	Command(0x0F);
	_delay_us(40);
	Command(0x01);
	_delay_ms(2);
	Command(0x06);
}

void Command( U08 byte )
{
	_delay_ms(50);
	LCD_C_PORT = 0x00;
	_delay_us(1);
	LCD_C_PORT = 0x04;
	_delay_us(1);
	LCD_D_PORT = byte;
	LCD_C_PORT = 0x03; // 0000 0001
	_delay_ms(50);
	LCD_C_PORT = 0x00; // 0000 0000
}

void Data( U08 byte )
{
	LCD_C_PORT = 0x01;
	_delay_us(1);
	LCD_C_PORT = 0x05;
	_delay_us(1);
	LCD_D_PORT = byte;
	LCD_C_PORT = 0x01; // 0000 0101
	_delay_ms(50);
	LCD_C_PORT = 0x00; // 0000 0000
}

void Put_Lcd_Char( char Lcd_Data )
{ 
     Data( Lcd_Data ); 
     _delay_ms(50);
} 

void Put_Lcd_String( char *Lcd_Data) 
{ 
        while(*Lcd_Data != 0x00) 
        { 
                Put_Lcd_Char(*Lcd_Data); 
                ++Lcd_Data;
        } 
} 

void Display_Position( U08 line, U08 col ) 
{ 
     if( line == 0 ) 
     	Command( 0x80 + col );
     else 
          Command( 0xc0 + col ); 

} 

void Lcd_Put_Char_Xy( U08 line, U08 col, U08 Lcd_Data)
{
	Display_Position( line, col );
	Put_Lcd_Char( Lcd_Data );
}

void Lcd_Print_Xy( U08 line, U08 col, char *Lcd_Data)
{
	Display_Position( line, col );
	Put_Lcd_String( Lcd_Data );
}

void Lcd_Print_2Digit(U08 line, U08 col, U08 data)	//0~99
{
	U08 Temp;
	
	Temp = data / 10;
	Lcd_Put_Char_Xy(line, col, Temp+48);
	Temp = data % 10;
	Lcd_Put_Char_Xy(line, col+1, Temp+48);
}

void Lcd_Print_U16digit(U08 line, U08 col, U16 data)	//0~65535
{
	U08 Temp;
	
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

