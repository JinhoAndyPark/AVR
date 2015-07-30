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
//					===== ADC 초기화 설정 =====
//------------------------------------------------------------------------------
void Init_ADC(void)
{
	DDRF = 0x00; 			   //ADC포트 입력 설정

	ADMUX = 0x00;
	ADCSRA = 0x00;			   //레지스터 초기화 및 AREF단자로 입력전압 사용

	sbi( ADCSRA, ADPS0 );
	sbi( ADCSRA, ADPS1 );
	sbi( ADCSRA, ADPS2 );		//프리스케일러 128분주

	cbi( ADCSRA, ADFR );			// 프리러닝 모드
	sbi( ADCSRA, ADEN );		   	// ADC 인에이블

	ADMUX = 1;

	sbi( ADCSRA, ADSC );
}


