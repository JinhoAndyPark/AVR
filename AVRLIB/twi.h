/*==============================================================================
 *
 *   Two Wire Serial Interface Module
 *
 *        File Name   		: Twi.h
 *        Version        	: 1.2
 *        Date           	: 2006.01.18
 *        Author         	: Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       	: ATmega128(16MHz)
 *        Modified       	: 2006.02.03 By P.Y.S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
==============================================================================*/

#ifndef __TWI_H
#define __TWI_H

// PORTD.0 : SCL / PORTD.1 : SDA

#define   SCL_Master()   sbi(DDRD, 0);     // SCL 출력으로 설정
#define   SCL_Slave()    cbi(DDRD, 0);     // SCL 입력으로 설정

#define   SDA_SET_WR()   sbi(DDRD, 1);     // SDA 출력으로 설정
#define   SDA_SET_RD()   cbi(DDRD, 1);     // SDA 입력으로 설정

#define   SDA_READ()     ( ( PIND & (1<<PIND1) ) & 0x01 );  // SDA값 확인 

#define   START_TWI()    sbi(PORTD, 1); sbi(PORTD, 0); Delay(20); cbi(PORTD, 1); Delay(2); cbi(PORTD, 0);
#define   END_TWI()      cbi(PORTD, 1); cbi(PORTD, 0); Delay(20); sbi(PORTD, 0); Delay(2); sbi(PORTD, 1);

#define   SCL_Pulse()    Delay(10); sbi(PORTD, 0); Delay(10); cbi(PORTD, 0);Delay(10);

//------------------------------------------------------------------------------
//                       ===== Funtion Prototype =====
//------------------------------------------------------------------------------

void Init_TWI(void);
void TWI_Write_Data(U8 Data);
U8 TWI_Read_Data(void);
U8 TWI_ACK(U8 Index);
void TWI_Write(U8 Address, U8 Data);
U8 TWI_Read(U8 Address);


#endif
