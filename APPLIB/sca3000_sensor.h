/*==============================================================================
 *
 *   (SCA3000-d01)Accelrmeter_Sensor Module
 *
 *        File Name      : sca3000_sensor.h
 *        Version        : 1.0
 *        Date           : 2008.07.25
 *        Author         : Hyun Jun Kim (ROLAB 23rd, SSM 18th)
 *        MPU_Type       : ATmega128(16MHz)
 *        Modified       : 2008.07.25 By k.h.j
 *        Copyright(c) ROLAB. All Rights Reserved.
 *
==============================================================================*/
#ifndef __SCA3000_H
#define __SCA3000_H

#define   SS00_Master()	    sbi(DDRB, 0);      	// SCL 출력으로 설정
#define   SS01_Master()	    sbi(DDRE, 7);       // SCL 출력으로 설정
#define   SCK_Master() 	    sbi(DDRB, 1);    	// SCK 출력으로 설정
#define   MOSI_Master()	    sbi(DDRB, 2);		// MOSI 출력으로 설정
#define   MISO_Master()	    cbi(DDRB, 3);		// MISO 입력으로 설정

#define   SS00_High()	    sbi(PORTB, 0);     	// SS00 High 출력
#define   SS00_Low()	    cbi(PORTB, 0);    	// SS00 Low  출력

#define   SS01_High()  	    sbi(PORTE, 7);     	// SS01 High 출력
#define   SS01_Low()   	    cbi(PORTE, 7);     	// SS01 Low  출력

#define   SPI_CSB                   0x01        //SPI CSB
#define   SPI_PORT                  PORTB       //SPI PORT
#define   SCA3000_MODE_REG_READ     (0x14*4)    //calculate address to MODE register read
#define   SCA3000_MODE_REG_WRITE    (0x14*4+1*2)//calculate address to MODE register write
#define   SCA3000_FREEFALL          0x10        //FFD_EN bit is bit nro: 4
                                                //binary: 0001 0000 == 0x10 

//------------------------------------------------------------------------------
//                       ===== Funtion Prototype =====
//------------------------------------------------------------------------------
void Init_sca3000(void);
void SCA3000_Read_16Bit(U8 Address);
void SCA3000_read_mode(void);
void SCA3000_Enable_FreeFall_Detection(void);

#endif