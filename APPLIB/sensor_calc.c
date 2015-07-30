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

U8 SlopeX_Direction;		// X�� ���⼾�� ��(0) / ��(1) ����
U8 SlopeY_Direction;		// Y�� ���⼾�� ��(0) / ��(1) ����
U8 Light_OnOff = 0;			// Light ���°� On = 1  / Off = 0

//------------------------------------------------------------------------------
//                      	===== �µ������� ��� =====
//------------------------------------------------------------------------------
U16 Calculate_Temperature(U16 SensorTemperature)
{
     U16 Temperature;
     
     Temperature = ((SensorTemperature - 124) / 8);
          
     return Temperature;	// ����(��)
}

//------------------------------------------------------------------------------
//                      	===== �����ļ����� ��� =====
//------------------------------------------------------------------------------
U8 Calculate_Lux(U16 SensorLux)
{
     char Lux;
     
     if(SensorLux >= 600)					// ���
     {
          Lux = 3;
     	Light_OnOff = 0;					// Light OFF
     }
     else if(SensorLux < 600 &&  SensorLux > 100)	// �߰�
     {
      	Lux = 2;
     	Light_OnOff = 0;					// Light OFF
     }
     else if(SensorLux <= 100)				// ��Ӵ�
     {
         	Lux = 1;
     	Light_OnOff = 1;					// Light ON
     }
     else 
     {
         	Lux = 0;
     	Light_OnOff = 0;					// Light OFF
     }

     return 	Lux;		// LUX(��������)
}

//------------------------------------------------------------------------------
//                      	===== ���������� ��� =====
//------------------------------------------------------------------------------
U16 Calculate_Humidity(U16 SensorHumidity)
{
     U16 Humidity;
     
     Humidity = ((SensorHumidity * 33) / 100);
     
     return Humidity; 	// ����(�ۼ�Ʈ) 
}
/*
//------------------------------------------------------------------------------
//                      	===== ���⼾���� ���(��ȣ�Ǻ�) =====
//------------------------------------------------------------------------------
U16 Get_Minus_Sign(U16 Packet)
{
	return Packet >> 15; 
}
*/

//------------------------------------------------------------------------------
//                      	===== ���⼾���� ��� =====
//------------------------------------------------------------------------------
U16 Calculate_Slope(U8 Direction, U16 SensorSlope, U16 Correction)
{
     // Direction �� ���� ������ ������ ���� X / Y �� ����Ѵ�. (�߰�����)  
     // Correction(������) = X: 406 , Y:410 (���� Ư���� ���Ͱ� �������� �ʿ�)
     // (+����) /  (-������)
     
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
     return Slope_Unsign_Value; 		// ����
}

//------------------------------------------------------------------------------
//                      	===== PSD������ ��� =====
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
     
     return PSD_Distance;	// ��Ƽ����
}

//------------------------------------------------------------------------------
//                      	===== �����ļ����� ��� =====
//------------------------------------------------------------------------------
U16 Calculate_UltraSonic(U8 SensorUltraSonic, U8 Temperature)
{
     U16 UltraSonic;
     
     UltraSonic = (((SensorUltraSonic * 0.000064)*((331 * 0.6 * Temperature) * 100)) / 2);
	
     return UltraSonic;	// ��Ƽ����
}

//------------------------------------------------------------------------------
//                      	===== ���������� ��� =====
//------------------------------------------------------------------------------
U16 Calculate_Direction(U16 SensorDirection)
{
     U16 Direction;
     
     Direction = (SensorDirection / 1.56);
     
    	return Direction;	// ����(�ð����) 
}


  

