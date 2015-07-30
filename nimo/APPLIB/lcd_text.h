#ifndef __Text_Lcd_H 
#define __Text_Lcd_H 

//Text Lcd 포트 정의
#define	LCD_D_PORT	PORTC // 데이타포트
#define	LCD_C_PORT	PORTA // 제어포트

#define	LCD_PORT_SETUP()	DDRC = 0xff; DDRA = 0x07;  //포트셋팅


//Text Lcd 명령어 셋팅
#define	FUNSET		0x38		//Function Set			0011 1000
#define	ENTMODE		0x06		//Entry Mode Set		0000 0110
#define	ALLCLR		0x01		//All Clear 			0000 0001
#define	DISPON		0x0e		//Display On			0000 1110


//------------------------------------------------------------------------------
//                       ===== Funtion Prototype =====
//------------------------------------------------------------------------------
void Lcd_Init(void);
void Command( U08 byte);
void Data( U08 byte);
void Put_Lcd_Char( char Lcd_Data );
void Put_Lcd_String( char *Lcd_Data);
void Display_Position( U08 line, U08 col );
void Lcd_Put_Char_Xy( U08 line, U08 col, U08 Lcd_Data);
void Lcd_Print_Xy( U08 line, U08 col, char *Lcd_Data);
void Lcd_Print_2Digit(U08 line, U08 col, U08 data);
void Lcd_Print_U16digit(U08 line, U08 col, U16 data);

#endif
