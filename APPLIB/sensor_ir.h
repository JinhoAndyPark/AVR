/*==============================================================================
 *
 *   IR_Sensor Module
 *
 *        File Name   		: sensor_ir.h
 *        Version        	: 1.2
 *        Date           	: 2005.12.11
 *        Author         	: Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       	: ATmega128(16MHz)
 *        Modified       	: 2006.02.03 By P.Y.S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
==============================================================================*/

#ifndef __IR_SENSOR_H
#define __IR_SENSOR_H

#define   IR_OUTPUT_SETUP()        DDRB = 0xFF;   PORTB = 0x00;
#define   IR_INPUT_SETUP()         DDRF = 0x00;   PORTF = 0x00;

//------------------------------------------------------------------------------
//                       ===== Funtion Prototype =====
//------------------------------------------------------------------------------
void IR_Sensor_Init(void);
void IR_Sensor_OnOff(void);

#endif

