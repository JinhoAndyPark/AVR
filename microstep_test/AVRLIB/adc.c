/*==============================================================================
 *
 *   Analog Digital Convertor Module
 *
 *   File Name   	: adc.c
 *   Version        	: 1.0
 *   Date           	: 2012.12.26
 *	 Modified       	: 2012.12.26 By Kim, Hyun-Jun
 *	 Author         	: Kim, Hyun-Jun  (23rd)
 *	 MPU_Type       	: ATmega128(16MHz)
 *	 Compiler		: WINAVR use AVRstudio 4.18
 *	 Copyright(c) ROLAB, Kwangwoon University.
 *   All Rights Reserved.
 *
==============================================================================*/

#include <avr/io.h>
#include "../define.h"
#include "adc.h"




U16 ADC_Read( U08 Channel )
{
	U16 value = 0;

	ADMUX = Channel;
	
	sbi( ADCSRA, ADSC );		// ADC Conversion Start
	
	while( ADCSRA & ( 1 << ADSC ) ); 	// wait ADC conversion complete

	value = ADCL;
	value |= (U16)ADCH << 8;
	
	return value;

}

U16 ADC_Average( U08 Channel, U08 number )		//Average ADC
{
	U16 value = 0;
	U16 temp[number];

	for(U08 cnt=0; cnt<number; cnt++)
	{
		temp[cnt] = ADC_Read(Channel);
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

	ADMUX = 0x00;
	ADCSRA = 0x00;			   //�������� �ʱ�ȭ �� AREF���ڷ� �Է����� ���

	sbi( ADCSRA, ADPS0 );
	sbi( ADCSRA, ADPS1 );
	sbi( ADCSRA, ADPS2 );		//���������Ϸ� 128����

	//sbi( ADCSRA, ADFR );			// �������� ���
	sbi( ADCSRA, ADEN );		   	// ADC �ο��̺�

	ADMUX = 1;

	//sbi( ADCSRA, ADSC );
}

