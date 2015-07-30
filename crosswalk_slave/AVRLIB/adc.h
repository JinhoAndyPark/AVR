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


//------------------------------------------------------------------------------
//                       ===== Funtion Prototype =====
//------------------------------------------------------------------------------
void Init_ADC(void); 						// ADC SETUP
U16 ADC_Read( U08 Channel );
U16 ADC_Average( U08 Channel, U08 number );


#endif
