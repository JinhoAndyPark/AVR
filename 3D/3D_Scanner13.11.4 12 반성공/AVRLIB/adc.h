/*==============================================================================
 *
 *   Analog Digital Convertor Module
 *
 *        File Name   		: adc.h
 *        Version        	: 1.0
 *        Date           	: 2013.10.30
 *        Author         	: Park, Jin-Ho (ROLAB 27th, Kwangwoon University)
 *        MPU_Type       	: ATmega128(16MHz)
 *        Modified       	: 2013.10.30 By Park, Jin-Ho
 *        Copyright(c) ROLAB, Kwangwoon University.
 *        All Rights Reserved.
 *
==============================================================================*/
#ifndef __ADC_H
#define __ADC_H


//------------------------------------------------------------------------------
//                       ===== Funtion Prototype =====
//------------------------------------------------------------------------------
void Init_ADC(void); 						// ADC SETUP
U16 Read_ADC( U08 ADC_Input );
U16 ADC_Average( U08 Channel, U08 number );


#endif
