/*==============================================================================
 *
 *   Calculation Funtion Module
 *
 *        File Name   		: sensor_calc.c
 *        Version        	: 1.1
 *        Date           	: 2006.02.08
 *        Author         	: Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       	: ATmega128(16MHz)
 *        Modified       	: 2006.02.09 By P.Y.S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
==============================================================================*/

#include <iom128.h>
#include "../define.h"
#include "sensor_calc.h"


//------------------------------------------------------------------------------
//					===== Gloval Variable Number =====
//------------------------------------------------------------------------------

U8 SlopeX_Direction;		// X축 기울기센서 좌(0) / 우(1) 상태
U8 SlopeY_Direction;		// Y축 기울기센서 뒤(0) / 앞(1) 상태
U8 Light_OnOff = 0;			// Light 상태값 On = 1  / Off = 0

//------------------------------------------------------------------------------
//                      	===== 온도센서값 계산 =====
//------------------------------------------------------------------------------
U16 Calculate_Temperature(U16 SensorTemperature)
{
     U16 Temperature;
     
     Temperature = ((SensorTemperature - 124) / 8);
          
     return Temperature;	// 섭씨(도)
}

//------------------------------------------------------------------------------
//                      	===== 초음파센서값 계산 =====
//------------------------------------------------------------------------------
U8 Calculate_Lux(U16 SensorLux)
{
     char Lux;
     
     if(SensorLux >= 600)					// 밝다
     {
          Lux = 3;
     	Light_OnOff = 0;					// Light OFF
     }
     else if(SensorLux < 600 &&  SensorLux > 100)	// 중간
     {
      	Lux = 2;
     	Light_OnOff = 0;					// Light OFF
     }
     else if(SensorLux <= 100)				// 어둡다
     {
         	Lux = 1;
     	Light_OnOff = 1;					// Light ON
     }
     else 
     {
         	Lux = 0;
     	Light_OnOff = 0;					// Light OFF
     }

     return 	Lux;		// LUX(조도단위)
}

//------------------------------------------------------------------------------
//                      	===== 습도센서값 계산 =====
//------------------------------------------------------------------------------
U16 Calculate_Humidity(U16 SensorHumidity)
{
     U16 Humidity;
     
     Humidity = ((SensorHumidity * 33) / 100);
     
     return Humidity; 	// 습도(퍼센트) 
}
/*
//------------------------------------------------------------------------------
//                      	===== 기울기센서값 계산(부호판별) =====
//------------------------------------------------------------------------------
U16 Get_Minus_Sign(U16 Packet)
{
	return Packet >> 15; 
}
*/

//------------------------------------------------------------------------------
//                      	===== 기울기센서값 계산 =====
//------------------------------------------------------------------------------
U16 Calculate_Slope(U8 Direction, U16 SensorSlope, U16 Correction)
{
     // Direction 은 기울기 센서의 목적에 따라 X / Y 라 명명한다. (추가가능)  
     // Correction(보정값) = X: 406 , Y:410 (센서 특성상 센터값 보정값이 필요)
     // (+왼쪽) /  (-오른쪽)
     
     U16 Slope_Unsign_Value;
     
     switch (Direction)
     {
       case X:
		if(SensorSlope >= Correction)
		{
			SlopeX_Direction = 0;          
			Slope_Unsign_Value = ((SensorSlope - Correction) / 6);
		}
		else if(SensorSlope < Correction)
		{
			SlopeX_Direction = 1;
			Slope_Unsign_Value = ((Correction - SensorSlope) / 6);
		}
          
          break;
          
       case Y:
          if(SensorSlope >= Correction)
		{
			SlopeY_Direction = 0;          
			Slope_Unsign_Value = ((SensorSlope - Correction) / 6);
		}
		else if(SensorSlope < Correction)
		{
			SlopeY_Direction = 1;
			Slope_Unsign_Value = ((Correction - SensorSlope) / 6);
		}
          
          break;
     }
     return Slope_Unsign_Value; 		// 각도
}

//------------------------------------------------------------------------------
//                      	===== PSD센서값 계산 =====
//------------------------------------------------------------------------------
U16 Calculate_Psd(U16 SensorPsd)
{
     U8 PSD_Distance;
     
     if(SensorPsd <88)
     {
        	PSD_Distance = 155;
     }
     else
     {
          PSD_Distance = (88.2 / ( (SensorPsd / 204.8) + 0.1) ) - 15;
     }
     
     return PSD_Distance;	// 센티미터
}

//------------------------------------------------------------------------------
//                      	===== 초음파센서값 계산 =====
//------------------------------------------------------------------------------
U16 Calculate_UltraSonic(U8 SensorUltraSonic, U8 Temperature)
{
     U16 UltraSonic;
     
     UltraSonic = (((SensorUltraSonic * 0.000064)*((331 * 0.6 * Temperature) * 100)) / 2);
	
     return UltraSonic;	// 센티미터
}

//------------------------------------------------------------------------------
//                      	===== 방위센서값 계산 =====
//------------------------------------------------------------------------------
U16 Calculate_Direction(U16 SensorDirection)
{
     U16 Direction;
     
     Direction = (SensorDirection / 1.56);
     
    	return Direction;	// 각도(시계방향) 
}


  

