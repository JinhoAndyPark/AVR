/*==============================================================================
 *
 *   EEPROM Control Module
 *
 *     	File Name   	: eeprom.h
 *    	Version        	: 1.0
 *    	Date           	: 2007.01.09
 *		Modified       	: 2007.01.09 By Pyo, Yoon-Seok
 *		Author         	: Pyo, Yoon-Seok  (ROBIT 1st, Kwangwoon University)
 *		MPU_Type       	: ATmega128(16MHz)
 *		Compiler		: IAR Eebedded Workbench 4.1
 *		Copyright(c) 2007 ROBIT, Kwangwoon University.
 *    	All Rights Reserved.
 *		
 *      ※ ATmega128 Datasheet의 Code Example을 그대로 이용하였다.
==============================================================================*/

#ifndef __EEPROM_H
#define __EEPROM_H

//------------------------------------------------------------------------------
//                      	===== Funtion Prototype =====
//------------------------------------------------------------------------------

void EEPROM_Write(U16 Address, U08 Data);		// EEPROM_Write DATA
U08 EEPROM_Read(U16 Address);					// EEPROM_read  DATA

#endif
