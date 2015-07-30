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
//					===== SPI 서비스루틴 =====
//------------------------------------------------------------------------------
#pragma vector=SPI_STC_vect
__interrupt void SPI_ISR( void ) 
{
	Disable_ISR();           // 전체인터럽트 사용금지         
	/*
	switch(SPDR)             // 슬레이브 수신값 저장(순서상 한칸뒤로)
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
	Enable_ISR();             // 전체인터럽트 사용허가
}


//------------------------------------------------------------------------------ 
//                 		===== SPI 초기화 =====
//------------------------------------------------------------------------------
void Init_SPI(U8 MasterSlave)
{
	if( MasterSlave == MASTER )
	{
		SPCR = 0x50;        // SPE, Mastar Mode, SPI Mode0, Sck=fosc/4 
		SS00_Master();     	// /SS00 출력
		SS01_Master();     	// /SS01 출력
		SCK_Master();       // SCK 출력
		MOSI_Master();      // MOSI 출력
		MISO_Master();      // MISO 입력
	}
    
	else if( MasterSlave == SLAVE )
	{
		SPCR = 0xC0;   		// SPIE, SPE, Slave Mode, SPI Mode0, Sck=fosc/4
		SS00_Slave(); 		// /SS00 입력
		//SS01_Slave(); 	// /SS00 입력
		SCK_Slave();   		// SCK 입력
		MOSI_Slave();  		// MOSI 입력
		MISO_Slave();  		// MISO 출력
	}
    
    else
    {}
     
} 


//------------------------------------------------------------------------------ 
//                       ===== SPI 송수신 =====
//------------------------------------------------------------------------------
U8 SPI_TxRx(U8 Data)
{	// SS_Low();
	SPDR = Data;             	// Data 송신
	while(!(SPSR & (1<<SPIF)));	// 송신 확인
	Delay_us(100);				// 시간 지연
	// SS_High();
	return SPDR;           		// 수신 받은 데이터 반환
}

