/*==============================================================================
 *
 *   L298 Driver Module
 *
 *        File Name      : motor_dc.c
 *        Version        : 1.0
 *        Date           : 2006.06.08
 *        Author         : Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       : ATmega128(16MHz)
 * 		  Compiler		 : IAR Eebedded Workbench 4.1
 *        Modified       : 2006.06.08 By Yoonseok Pyo
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
==============================================================================*/
#include <iom128.h>
#include "../define.h"
#include "../delay.h"
#include "motor_dc.h"

//------------------------------------------------------------------------------
//    L298�� ����Ͽ���.
//		PORTB 0 : ����LEFT - 
//		PORTB 2 : ����LEFT +
//		PORTB 1 : ����RIGHT -
//		PORTB 3 : ����RIGHT +
//		0C1A	: ����LEFT �ӵ�(Ÿ�̸�1��� PWM0)	
//		0C1B	: ����LEFT �ӵ�(Ÿ�̸�1��� PWM1)
//------------------------------------------------------------------------------
void Init_L298(void)
{
    Init_Timer();
    DDRB = 0xff;
}

void Init_Timer(void)
{  
     sbi( TIMSK, 3 );
     sbi( TIMSK, 4 );

     TCCR1A = 0xA1;
     TCCR1B = 0x05;  
}

void Forward(void)	//����
{
	sbi(PORTB,0);
	cbi(PORTB,2);
    
	cbi(PORTB,1);
	sbi(PORTB,3);
    
	OCR1A = 120;
	OCR1B = 120;
	Delay_us(15000);	                                           	
}

void Back(void)		//����
{
	cbi(PORTB,0);
	sbi(PORTB,2);
    
	sbi(PORTB,1);
	cbi(PORTB,3);
    
	OCR1A = 120;
	OCR1B = 120;
	Delay_us(15000);
}

void Left(void)		//��ȸ��
{
	sbi(PORTB,0);
	cbi(PORTB,2);
    
	cbi(PORTB,1);
	sbi(PORTB,3);
    
	OCR1A = 120;
	OCR1B = 20;
	Delay_us(15000);
}

void Right(void)	//��ȸ��
{
	sbi(PORTB,0);
	cbi(PORTB,2);
    
	cbi(PORTB,1);
	sbi(PORTB,3);
    
	OCR1A = 20;
	OCR1B = 120;                	          	
	Delay_us(15000);
}


void Stop(void)		//����
{
	PORTB = 0x00;
	OCR1A = 0;
	OCR1B = 0;
}

