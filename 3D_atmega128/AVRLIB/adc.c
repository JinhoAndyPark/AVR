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
	ADMUX |= ADC_Input;					//����� ���� (ADC�� �Է�)
	
	ADCSRA |= 0x40;						//ADC START Conversion
	
	while( ( ADCSRA & 0x10 ) == 0 ) ;     //ADC interrupt flag check
	{
		cbi( ADCSRA, ADEN );			//ADC OFF   NOT SURE ? SBI DDER IS BETTER?
		return ADC;							//ADC�� ��ȯ  RETURN MAKES DONE?
	}
}

U16 Read_ADC_NOSTOP( U08 ADC_Input )		
{
	ADMUX |= ADC_Input;					//����� ���� (ADC�� �Է�)
	
	ADCSRA |= 0x40;						//ADC START Conversion
	
	while( ( ADCSRA & 0x10 ) == 0 ) ;     //ADC interrupt flag check
	{			
		return ADC;							//ADC�� ��ȯ  RETURN MAKES DONE?
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
//					===== ADC �ʱ�ȭ ���� =====
//------------------------------------------------------------------------------
void Init_ADC(void)
{
	DDRF = 0x00; 			   //ADC��Ʈ �Է� ����

	ADMUX = 0x40;
	ADCSRA = 0x00;			   ////AVCC���ڷ� �Է����� ��� �� �������� �ʱ�ȭ 

	sbi( ADCSRA, ADPS0 );
	sbi( ADCSRA, ADPS1 );
	sbi( ADCSRA, ADPS2 );		//���������Ϸ� 128����

	//sbi( ADCSRA, ADFR );			// �������� ���
	sbi( ADCSRA, ADEN );		   	// ADC �ο��̺�
	//sbi( ADCSRA, ADIE );			// ADC interrupt enable
	//ADMUX = 1;

	//sbi( ADCSRA, ADSC );
}


