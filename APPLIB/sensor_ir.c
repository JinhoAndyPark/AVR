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
//					===== IR_Sensor �ʱ�ȭ ���� =====
//------------------------------------------------------------------------------
void IR_Sensor_Init(void)
{
     IR_OUTPUT_SETUP();       //PORTB �߱���
     IR_INPUT_SETUP();        //PORTF ������
}

//------------------------------------------------------------------------------
//					===== IR_Sensor �ڵ�OnOff =====
//------------------------------------------------------------------------------
void IR_Sensor_OnOff(void)
{
          PORTB |= 0xFF;       //�߱�ON
          Delay_us(10);
          PORTB &= 0x00;       //�߱�OFF
          Delay_us(10);
}

