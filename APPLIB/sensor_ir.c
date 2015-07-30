/*==============================================================================
 *
 *   IR_Sensor Module
 *
 *        File Name   		: sensor_ir.c
 *        Version        	: 1.2
 *        Date           	: 2005.12.11
 *        Author         	: Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       	: ATmega128(16MHz)
 *        Modified       	: 2006.02.03 By P.Y.S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
==============================================================================*/

#include <iom128.h>
#include "../define.h"
#include "../delay.h"
#include "IR_Sensor.h"

//------------------------------------------------------------------------------
//					===== IR_Sensor ÃÊ±âÈ­ ¼³Á¤ =====
//------------------------------------------------------------------------------
void IR_Sensor_Init(void)
{
     IR_OUTPUT_SETUP();       //PORTB ¹ß±¤ºÎ
     IR_INPUT_SETUP();        //PORTF ¼ö±¤ºÎ
}

//------------------------------------------------------------------------------
//					===== IR_Sensor ÀÚµ¿OnOff =====
//------------------------------------------------------------------------------
void IR_Sensor_OnOff(void)
{
          PORTB |= 0xFF;       //¹ß±¤ON
          Delay_us(10);
          PORTB &= 0x00;       //¹ß±¤OFF
          Delay_us(10);
}

