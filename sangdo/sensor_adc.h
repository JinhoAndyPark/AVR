/*==============================================================================
 *
 *   Psd_Sensor Module
 *
 *        File Name      : Psd_Adc_Lib.h
 *        Version        : 1.3
 *        Date           : 2006.05.31
 *        Author         : Eun Hye Kim (ROLAB 21th, Kwangwoon University)
 *        MPU_Type       : ATmega128(16MHz)
 *        Modified       : 2006.05.31 By k.e.h
 *        Copyright(c) ROLAB. All Rights Reserved.
 *
==============================================================================*/
#ifndef __SENSOR_ADC_H
#define __SENSOR_ADC_H

U16 Read_ADC(U8 ADC_Input);
void Init_Sensor_ADC(void);

#endif

