/*==============================================================================
 *
 *        cmps03 Module(I2c version)
 *
 *        File Name   		: sensor_cmps03.c
 *        Version        	: 1.0
 *        Date           	: 2006.07.13
 *        Author         	: Kooksun Lee (ROLAB 20th, Kwangwoon University)
 *        MPU_Type       	: ATmega128(16MHz)
 *        Modified       	: 2006.07.13 By L. K. S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University.
 *        All Rights Reserved.
 *
==============================================================================*/

#ifndef __SENSOR_CMPS03_H
#define __SENSOR_CMPS03_H

//------------------------------------------------------------------------------
//                       ===== Variables Set =====
//------------------------------------------------------------------------------

#define TWCR_CMD_MASK               0x0f
#define CMPSADDRESS                 0xc1

//------------------------------------------------------------------------------
//                       ===== Funtion Prototype =====
//------------------------------------------------------------------------------

void Init_Cmps03(void);
void Setup(void);
void Wate_Complete(void);
void Start_Condition(void);
void Master_Mode(void);
void Recieve_Data(void);
U16 Cmps_Data(void);


#endif
