/*==============================================================================
 *
 *   Analog Digital Convertor Module
 *
 *        File Name   		: adc.c
 *        Version        	: 1.0
 *        Date           	: 200.07.04
 *        Author         	: Kooksun Lee (ROLAB 20th, Kwangwoon University)
 *        MPU_Type       	: ATmega128(16MHz)
 *        Modified       	: 2006.07.04 By L.K.S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University.
 *        All Rights Reserved.
 *
==============================================================================*/

/*  === 참고사항 === 
Adc_Value = (측정하고자 하는 전압 * 분해능(avr에서는 1023) ) / 기준전압(5v) 
          : 원하는 전압을 찾아내는 공식이다

- Adc.h 의 FirstOfSensor, NumberOfSensor에 원하는 adc번호를 써주면 됩니다.
==============================================================================*/
#include "main.h"

void main()
{ 
  DDRA=0xff;
  while(1)
  {
  PORTA=0x01;
  }
  
}

/*
#include "../define.h"
#include "adc.h"


U16 Adc_Value ;      		// Adc 측정값
U8 Adc_Number ;     		// 측정하고자 하는 adc 번호
U8 Adc[NumberOfSensor+1];	// adc값이 배열로 저장된다.

//------------------------------------------------------------------------------
//					===== 배열 저장함수 =====
//------------------------------------------------------------------------------
void Save_Adc_Value( U8 Value,  U8 Number)
{
     Adc[Number] = Value; // ADC의 값을 배열로 저장한다. Adc[센서번호] = 센서값
}

//------------------------------------------------------------------------------
//					===== 변환 루틴 =====
//------------------------------------------------------------------------------
void Change_Mux(U8 Number)
{
    ADMUX = Number+1 ; 				// 다음 센서로 전환
    if (Number == NumberOfSensor) 	// 마지막 센서에 도착하면
    {
      ADMUX = FirstOfSensor; 		// 첫번째 센서로 전환하여 루프를 시작한다
    }
}

//------------------------------------------------------------------------------
//					===== ADC 서비스루틴 =====
//------------------------------------------------------------------------------
#pragma vector=ADC_vect
__interrupt void adc_isr( void )
{
     cbi(SREG,7);

     Adc_Value = ADC;       
     Adc_Number = ADMUX;   					// 센서의 값과 센서의 번호를 저장한다.

	 Save_Adc_Value(Adc_Value ,Adc_Number); // 센서의 값과 센서의 번호를 배열로 저장
     Change_Mux(Adc_Number);           		// 다음센서로 전환한다

     sbi(ADCSR, ADSC);                 		// A/D 컨버터 변환 시작 
     										// (단일변환 모드이므로)
     sbi(SREG,  7);
}


//------------------------------------------------------------------------------
//					===== ADC 초기화 설정 =====
//------------------------------------------------------------------------------
void Init_ADC(void)
{
//						1.사용할 단자 선택
     ADMUX = FirstOfSensor;       // 외부의 AREF 단자로 입력된 전압을 사용, ADC0단극성 입력
     
//                     	2. 비교기와 컨버터 중 선택
     sbi( ACSR,  ACD );           // 아날로그 비교기 사용 불가
     sbi( ADCSR, ADEN );          // 아날로그 디지털 컨버터 사용
     
//                    	3. 분주비 설정
     sbi(ADCSR, 2);               // A/D 클럭 분주비 설정 = > 16분주
     cbi(ADCSR, 1);               // A/D 클럭 분주비 설정
     cbi(ADCSR, 0);               // A/D 클럭 분주비 설정
     
//                   	4. 인터럽트 인에이블
     sbi( ADCSR, ADIE );          // ADC INTERRUPT ENABLE
     
//                     	5. 변환 시작
     cbi(ADCSR, ADFR);            // AD 컨버터 단일변환 모드
     sbi(ADCSR, ADSC);            // AD 컨버터 변환 시작

}

*/


