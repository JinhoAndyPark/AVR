/*==============================================================================
 *
 *   EEPROM Control Module
 *
 *     	File Name   	: eeprom.c
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
#include <iom128.h>
#include "../define.h"
#include "eeprom.h"

//------------------------------------------------------------------------------
//     				===== EEPROM_Write =====
//             		:사용자가 지정된 주소의 eeprom에 지정한 데이타를 저장한다.
//------------------------------------------------------------------------------
void EEPROM_Write(U16 Address, U08 Data)
{
	while(EECR & (1<<EEWE))	;			//	Wait for completion of previous write
	
	EEAR = Address;						// Set up address and data registers
	EEDR = Data;

	EECR |= (1<<EEMWE);					// Write logical one to EEMWE 	
	EECR |= (1<<EEWE);					// Start eeprom write by setting EEWE
}


//------------------------------------------------------------------------------
//     				===== EEPROM_Read =====
//             		:사용자가 지정된 주소의 데이타를 읽어봐 반환한다.
//------------------------------------------------------------------------------
U08 EEPROM_Read(U16 Address)
{
	
	while(EECR & (1<<EEWE));			// Wait for completion of previous write
	
	EEAR = Address;						// Set up address register
	
	EECR |= (1<<EERE);					// Start eeprom read by writing EERE
	
	return EEDR;						// Return data from data register
}
