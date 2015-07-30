/*==============================================================================
 *
 *   Input/Output Module
 *
 *        File Name   		: Io.c
 *        Version        	: 1.1
 *        Date           	: 2005.12.16
 *        Author         	: Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       	: ATmega128(16MHz)
 *        Modified       	: 2006.02.03 By P.Y.S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
==============================================================================*/

#include <iom128.h>
#include "../define.h"
#include "io.h"

//------------------------------------------------------------------------------
//               			===== 초기화_입출력 =====
//------------------------------------------------------------------------------
void Init_IO(void)
{
	//-------------- 개별셋팅
    /*  
    PORTA=0x00;
    PORTB=0x00;
    PORTC=0x00;
    PORTD=0x00;
    PORTE=0x00;
    PORTF=0x00;
    PORTG=0x00;
    
    
	DDRA=0x00;
	DDRB=0x00;
	DDRC=0x00;
   	DDRD=0x00;
	DDRE=0x00;
	DDRF=0x00;
	DDRG=0x00;    
	*/    
    
    //-------------- 세부셋팅
    /*
    PORTA = (1<<PA7)|(1<<PA6)|(1<<PA5)|(1<<PA4)|(1<<PA3)|(1<<PA2)|(1<<PA1)|(1<<PA0);
    
    PORTB = (1<<PB7)|(1<<PB6)|(1<<PB5)|(1<<PB4)|(1<<PB3)|(1<<PB2)|(1<<PB1)|(1<<PB0);
    
    PORTC = (1<<PC7)|(1<<PC6)|(1<<PC5)|(1<<PC4)|(1<<PC3)|(1<<PC2)|(1<<PC1)|(1<<PC0);
    
    PORTD = (1<<PD7)|(1<<PD6)|(1<<PD5)|(1<<PD4)|(1<<PD3)|(1<<PD2)|(1<<PD1)|(1<<PD0);
    
    PORTE = (1<<PE7)|(1<<PE6)|(1<<PE5)|(1<<PE4)|(1<<PE3)|(1<<PE2)|(1<<PE1)|(1<<PE0);
    
    PORTF = (1<<PF7)|(1<<PF6)|(1<<PF5)|(1<<PF4)|(1<<PF3)|(1<<PF2)|(1<<PF1)|(1<<PF0);
    
    PORTG = 						   (1<<PG4)|(1<<PG3)|(1<<PG2)|(1<<PG1)|(1<<PG0);
    
    
	DDRA = (1<<DDA7)|(1<<DDA6)|(1<<DDA5)|(1<<DDA4)|(1<<DDA3)|(1<<DDA2)|(1<<DDA1)|(1<<DDA0);
	
    DDRB = (1<<DDB7)|(1<<DDB6)|(1<<DDB5)|(1<<DDB4)|(1<<DDB3)|(1<<DDB2)|(1<<DDB1)|(1<<DDB0);
    
    DDRC = (1<<DDC7)|(1<<DDC6)|(1<<DDC5)|(1<<DDC4)|(1<<DDC3)|(1<<DDC2)|(1<<DDC1)|(1<<DDC0);
    
    DDRD = (1<<DDD7)|(1<<DDD6)|(1<<DDD5)|(1<<DDD4)|(1<<DDD3)|(1<<DDD2)|(1<<DDD1)|(1<<DDD0);
    
    DDRE = (1<<DDE7)|(1<<DDE6)|(1<<DDE5)|(1<<DDE4)|(1<<DDE3)|(1<<DDE2)|(1<<DDE1)|(1<<DDE0);
    
    DDRF = (1<<DDF7)|(1<<DDF6)|(1<<DDF5)|(1<<DDF4)|(1<<DDF3)|(1<<DDF2)|(1<<DDF1)|(1<<DDF0);
    
    DDRG = 								 (1<<DDG4)|(1<<DDG3)|(1<<DDG2)|(1<<DDG1)|(1<<DDG0);
    */
    

}
