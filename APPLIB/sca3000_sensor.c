/*==============================================================================
 *
 *   (SCA3000-d01)Accelrmeter_Sensor Module
 *
 *        File Name      : sca3000_sensor.c
 *        Version        : 1.0
 *        Date           : 2008.07.25
 *        Author         : Hyun Jun Kim (ROLAB 23rd, SSM 18th)
 *        MPU_Type       : ATmega128(16MHz)
 *        Modified       : 2008.07.25 By k.h.j
 *        Copyright(c) ROLAB. All Rights Reserved.
 *
==============================================================================*/

//------------------------------------------------------------------------------
//                 			=== Include Headerfile ===
//------------------------------------------------------------------------------
#include <iom128.h>
#include "../define.h"
#include "sca3000_sensor.h"

//------------------------------------------------------------------------------
//                   		=== Variable Declaration ===
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
//                      	=== SPI Function ===
//------------------------------------------------------------------------------
void Init_sca3000(void)
{
    SPCR = 0x50;        // SPE, Mastar Mode, SPI Mode0, Sck=fosc/4 
    SS00_Master();     	// SS00 출력
	SCK_Master();       // SCK  출력
	MOSI_Master();      // MOSI 출력
	MISO_Master();      // MISO 입력
}


//Function taken in the 8-bit register address and returns 16-bit register value.
//Address : X-axis 0x05 , Y-axis 0x07 , Z-axis 0x09
void SCA3000_Read_16Bit(U8 Address)
{
    int result = 0;

    Address = Address << 2;         //RW bit is set to zero by shifting the bit.
                                    //pattern to left by 2
    SPI_SS_ON;                      //set CSB to zero
    SPDR = Address;                 //Write command to SPI bus
    
    while(!(SPSR & (1 << SPIF)));   //Wait until data has been sent 
    
    SPDR = 0x00;                    //Write dummy byte to line
                                    //in order to generate SPI clock for data read
    while(!(SPSR & (1 << SPIF)));   //Wait until data has been sent
    
    result = SPDR;                  //Get MSB of the result
    result = result << 8;           //Shift the MSB of the result to left by 8
        
    SPDR = 0x00;                    //Write dummy byte to line
                                    //in order to generate SPI clock for data read   
    while(!(SPSR & (1 << SPIF)));   //Wait until data has been sent

    result |= SPDR;                 //Get LSB of the result
    
    SPI_SS_OFF;                     //Set CSB to one

    return result;
}


//Read SCA3000 MODE register and return its value
void SCA3000_read_mode(void)
{
    int mode = 0;
    
    SPI_SS_ON;                      //set CSB to zero
    SPDR = SCA3000_MODE_REG_READ;   //Write command to SPI bus
    
    while(!(SPSR & (1 << SPIF)));   //Wait until data has been sent
    SPDR = 0x00;                    //Write dummy byte to line
                                    //in order to generate SPI clock for data read
    while(!(SPSR & (1 << SPIF)));   //Wait until data has been sent
    
    mode = SPDR;
    
    SPI_SS_OFF;                     //Set CSB to one
    return mode;    
}


//Set SCA3000 Free Fall detection ON
void SCA3000_Enable_FreeFall_Detection(void)
{
    int mode = 0;
    
    mode = SCA3000_read_mode();     //Read MODE register content, this
                                    //function is defined above
    mode = mode | SCA3000_FREEFALL; //Set FFD_EN bit to one,
                                    //enable free fall detection
    SPI_SS_ON;                      //set CSB to zero
    SPDR = SCA3000_MODE_REG_WRITE;  //Write command to SPI bus
    while(!(SPSR & (1 << SPIF)));   //Wait until data has been sent
        
    SPDR = mode;                    //Write new MODE register content to line
    while(!(SPSR & (1 << SPIF)));   //Wait until data has been sent
    
    SPI_SS_OFF;                     //Set CSB to one
}