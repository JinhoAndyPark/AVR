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
#define FirstOfSensor  0x00	// ADC0 -> ADC0���� ADC3���� ����Ѵ�.     
							// ��� ���� :(0x05,0x03 ->ADC3���� ADC5���� ����Ѵ�)

//------------------------------------------------------------------------------
//                       ===== Funtion Prototype =====
//------------------------------------------------------------------------------
void Init_Adc(void); 						// ADC SETUP
void Save_Adc_Value( U8 Value,  U8 Number); // ADC���� ��ȣ�� �迭�� �����Ѵ�
void Change_Mux(U8 Adc_Number); 			// MUX ��ȯ ��ƾ

#endif
