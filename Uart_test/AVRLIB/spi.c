/*==============================================================================
 *
 *   SPI Communication Module
 *
 *        File Name      : spi.c
 *        Version        : 1.2
 *        Date           : 2006.01.20
 *        Author         : Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       : ATmega128(16MHz)
 *        Modified       : 2006.07.04 By P.Y.S
 *        Copyright(c) ROLAB. All Rights Reserved.
 *
==============================================================================*/

#include <iom128.h>
#include "../define.h"
#include "../delay.h"
#include "spi.h"

//------------------------------------------------------------------------------
//					===== SPI ���񽺷�ƾ =====
//------------------------------------------------------------------------------
#pragma vector=SPI_STC_vect
__interrupt void SPI_ISR( void ) 
{
	Disable_ISR();           // ��ü���ͷ�Ʈ ������         
	/*
	switch(SPDR)             // �����̺� ���Ű� ����(������ ��ĭ�ڷ�)
	{
		case 0x80: SPDR = Sensor_L[0];
		   break;
		case 0x81: SPDR = Sensor_H[1];
		   break;
		case 0x82: SPDR = Sensor_L[1];
		   break;
		case 0x83: SPDR = Sensor_H[2];
		   break;
		case 0x84: SPDR = Sensor_L[2];
		   break;
		case 0x85: SPDR = Sensor_H[3];
		   break;
		case 0x86: SPDR = Sensor_L[3];
		   break;
		case 0x87: SPDR = Sensor_H[4];
		   break;
		case 0x88: SPDR = Sensor_L[4];
		   break;
		case 0x89: SPDR = Sensor_H[0];
		   break;
		case 0x8A: SPDR = Sensor_L[0];
		   break;
		case 0x8B: SPDR = Sensor_H[1];
		   break;
		case 0x8C: SPDR = Sensor_L[1];
		   break;
		case 0x8D: SPDR = Sensor_H[2];
		   break;
		case 0x8E: SPDR = Sensor_L[2];
		   break;
		case 0x8F: SPDR = Sensor_H[0];
		   break;
		default:   SPDR = 0xff;  
	}
	*/
	Enable_ISR();             // ��ü���ͷ�Ʈ ����㰡
}


//------------------------------------------------------------------------------ 
//                 		===== SPI �ʱ�ȭ =====
//------------------------------------------------------------------------------
void Init_SPI(U8 MasterSlave)
{
	if( MasterSlave == MASTER )
	{
		SPCR = 0x50;        // SPE, Mastar Mode, SPI Mode0, Sck=fosc/4 
		SS00_Master();     	// /SS00 ���
		SS01_Master();     	// /SS01 ���
		SCK_Master();       // SCK ���
		MOSI_Master();      // MOSI ���
		MISO_Master();      // MISO �Է�
	}
    
	else if( MasterSlave == SLAVE )
	{
		SPCR = 0xC0;   		// SPIE, SPE, Slave Mode, SPI Mode0, Sck=fosc/4
		SS00_Slave(); 		// /SS00 �Է�
		//SS01_Slave(); 	// /SS00 �Է�
		SCK_Slave();   		// SCK �Է�
		MOSI_Slave();  		// MOSI �Է�
		MISO_Slave();  		// MISO ���
	}
    
    else
    {}
     
} 


//------------------------------------------------------------------------------ 
//                       ===== SPI �ۼ��� =====
//------------------------------------------------------------------------------
U8 SPI_TxRx(U8 Data)
{	// SS_Low();
	SPDR = Data;             	// Data �۽�
	while(!(SPSR & (1<<SPIF)));	// �۽� Ȯ��
	Delay_us(100);				// �ð� ����
	// SS_High();
	return SPDR;           		// ���� ���� ������ ��ȯ
}

