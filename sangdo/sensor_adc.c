/*==============================================================================
 *
 *   Sensor_Sensor Module
 *
 *        File Name      : sensor_adc.c
 *        Version        : 1.4
 *        Date           : 2006.05.31
 *        Author         : Eun Hye Kim (ROLAB 21th, Kwangwoon University)
 *        MPU_Type       : ATmega128(16MHz)
 *        Modified       : 2006.12.25 By P.Y.S
 *        Copyright(c) ROLAB. All Rights Reserved.
 *
==============================================================================*/
#include "main.h"
#include "define.h"
#include "sensor_adc.h"

U16 Read_ADC(U8 ADC_Input)
{
     ADMUX 		= 	ADC_Input;		// 사용자설정 -> adc값 입력
     ADCSRA		|=	0x40; 			// ADC START Conversion
     while( (ADCSRA & 0x10) == 0 );	// adc interrupt flag check
     ADCSRA		|=	0x10;			// adc interrupt flag clear
     return 	ADC;          		// adc 값 반환
}

void Init_Sensor_ADC(void)
{
    ADMUX = 0x00;
	ADCSRA	=  0x87;		// adc enable, 분주=128
}


