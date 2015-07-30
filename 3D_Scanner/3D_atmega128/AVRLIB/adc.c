/*==============================================================================
 *
 *   Analog Digital Convertor Module
 *
 *   File Name   	: adc.c
 *   Version        	: 1.0
 *   Date           	: 2013.10.29
 *	 Modified       	: 2013.10.29 By Park, Jin-Ho
 *	 Author         	: Park, Jin-Ho  (27th)
 *	 MPU_Type       	: ATmega128(16MHz)
 *	 Compiler		: WINAVR use AVRstudio 4.18
 *	 Copyright(c) ROLAB, Kwangwoon University.
 *   All Rights Reserved.
 *
==============================================================================*/

#include <avr/io.h>
#include "../define.h"
#include "adc.h"




U16 Read_ADC( U08 ADC_Input )		//ONLY ONCE SENSING  NO SEQUENTIAL.
{
	ADMUX |= ADC_Input;					//사용자 설정 (ADC값 입력)
	
	ADCSRA |= 0x40;						//ADC START Conversion
	
	while( ( ADCSRA & 0x10 ) == 0 ) ;     //ADC interrupt flag check
	{
		cbi( ADCSRA, ADEN );			//ADC OFF   NOT SURE ? SBI DDER IS BETTER?
		return ADC;							//ADC값 반환  RETURN MAKES DONE?
	}
}

U16 Read_ADC_NOSTOP( U08 ADC_Input )		
{
	ADMUX |= ADC_Input;					//사용자 설정 (ADC값 입력)
	
	ADCSRA |= 0x40;						//ADC START Conversion
	
	while( ( ADCSRA & 0x10 ) == 0 ) ;     //ADC interrupt flag check
	{			
		return ADC;							//ADC값 반환  RETURN MAKES DONE?
	}
}

U16 ADC_Average( U08 Channel, U08 number )		//Average ADC
{
	U16 value = 0;
	U16 temp[number];

	for(U08 cnt=0; cnt<number; cnt++)
	{
		temp[cnt] = Read_ADC(Channel);
		value += temp[cnt];
	}
	value /= number;
	
	return value;
}

//------------------------------------------------------------------------------
//					===== ADC 초기화 설정 =====
//------------------------------------------------------------------------------
void Init_ADC(void)
{
	DDRF = 0x00; 			   //ADC포트 입력 설정

	ADMUX = 0x40;
	ADCSRA = 0x00;			   ////AVCC단자로 입력전압 사용 및 레지스터 초기화 

	sbi( ADCSRA, ADPS0 );
	sbi( ADCSRA, ADPS1 );
	sbi( ADCSRA, ADPS2 );		//프리스케일러 128분주

	//sbi( ADCSRA, ADFR );			// 프리러닝 모드
	sbi( ADCSRA, ADEN );		   	// ADC 인에이블
	//sbi( ADCSRA, ADIE );			// ADC interrupt enable
	//ADMUX = 1;

	//sbi( ADCSRA, ADSC );
}


