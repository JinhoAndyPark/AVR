/*==============================================================================
 *
 *   SPI Communication Module
 *
 *        File Name      : spi.h
 *        Version        : 1.2
 *        Date           : 2006.01.20
 *        Author         : Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       : ATmega128(16MHz)
 *        Modified       : 2006.07.04 By P.Y.S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
==============================================================================*/

#ifndef __SPI_H
#define __SPI_H

#define MASTER	0
#define SLAVE	1

/*
 * PORTE 7 : /SS01
 * PORTB 0 : /SS00    
 * PORTB 1 : SCK    
 * PORTB 2 : MOSI   
 * PORTB 3 : MISO   
 */

#define   SS00_Master()	sbi(DDRB, 0);      	// SCL ������� ����
#define   SS00_Slave() 	cbi(DDRB, 0);       // SCL �Է����� ����

#define   SS01_Master()	sbi(DDRE, 7);       // SCL ������� ����
#define   SS01_Slave() 	cbi(DDRE, 7);       // SCL �Է����� ����

#define   SCK_Master() 	sbi(DDRB, 1);    	// SCK ������� ����
#define   SCK_Slave() 	cbi(DDRB, 1);    	// SCK �Է����� ����

#define   MOSI_Master()	sbi(DDRB, 2);		// MOSI ������� ����
#define   MOSI_Slave() 	cbi(DDRB, 2);		// MOSI �Է����� ����

#define   MISO_Master()	cbi(DDRB, 3);		// MISO �Է����� ����
#define   MISO_Slave() 	sbi(DDRB, 3);		// MISO ������� ����

#define   SS00_High()	sbi(PORTB, 0);     	// SS00 High ���
#define   SS00_Low()	cbi(PORTB, 0);    	// SS00 Low  ���

#define   SS01_High()  	sbi(PORTE, 7);     	// SS01 High ���
#define   SS01_Low()   	cbi(PORTE, 7);     	// SS01 Low  ���


//------------------------------------------------------------------------------
//                       ===== Funtion Prototype =====
//------------------------------------------------------------------------------

void Init_SPI(U8 MasterSlave);
U8 SPI_TxRx(U8 Data);

#endif
