#ifndef __ADC_H
#define __ADC_H


//------------------------------------------------------------------------------
//                       ===== Funtion Prototype =====
//------------------------------------------------------------------------------
void Init_ADC(void); 						// ADC SETUP
U16 ADC_Read( U08 Channel );
U16 ADC_Average( U08 Channel, U08 number );


#endif
