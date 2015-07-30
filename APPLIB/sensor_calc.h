/*==============================================================================
 *
 *   Calculation Funtion Module
 *
 *        File Name   		: sensor_calc.h
 *        Version        	: 1.0
 *        Date           	: 2006.02.08
 *        Author         	: Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       	: ATmega128(16MHz)
 *        Modified       	: 2006.02.08 By P.Y.S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
==============================================================================*/

#ifndef __CALCULATION_H
#define __CALCULATION_H

#define X 0
#define Y 1

//------------------------------------------------------------------------------
//                      	===== Funtion Prototype =====
//------------------------------------------------------------------------------

U16	Calculate_Temperature(U16 SensorTemperature);
U8 	Calculate_Lux(U16 SensorLux);
U16 	Calculate_Humidity(U16 SensorHumidity);
U16 	Calculate_Slope(U8 Direction, U16 SensorSlope, U16 Correction);
U16 	Calculate_Psd(U16 SensorPsd);
U16 	Calculate_UltraSonic(U8 SensorUltraSonic, U8 Temperature);
U16 	Calculate_Direction(U16 SensorDirection);



#endif
