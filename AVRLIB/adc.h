/*==============================================================================
 *
 *   Analog Digital Convertor Module
 *
 *        File Name   		: adc.h
 *        Version        	: 1.0
 *        Date           	: 200.07.04
 *        Author         	: Kooksun Lee (ROLAB 20th, Kwangwoon University)
 *        MPU_Type       	: ATmega128(16MHz)
 *        Modified       	: 2006.07.04 By L.K.S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University.
 *        All Rights Reserved.
 *
==============================================================================*/
#ifndef __ADC_H
#define __ADC_H

#define NumberOfSensor 0x03 // ADC3
#define FirstOfSensor  0x00	// ADC0 -> ADC0에서 ADC3까지 사용한다.     
							// 사용 예시 :(0x05,0x03 ->ADC3에서 ADC5까지 사용한다)

//------------------------------------------------------------------------------
//                       ===== Funtion Prototype =====
//------------------------------------------------------------------------------
void Init_Adc(void); 						// ADC SETUP
void Save_Adc_Value( U8 Value,  U8 Number); // ADC값과 번호를 배열로 저장한다
void Change_Mux(U8 Adc_Number); 			// MUX 변환 루틴

#endif
