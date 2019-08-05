#ifndef _ADC_H
#define _ADC_H
#include"sys.h"



void ADC_init();
u16 Get_Adc1(u8 ch);
u16 Get_Adc2(u8 ch);
u16 Get_Adc1_Average(u8 ch,u8 num);
u16 Get_Adc2_Average(u8 ch,u8 num);
u16 Get_Voltage_ADC1(u8 ch,u8 num);
u16 Get_Voltage_ADC2(u8 ch,u8 num);

#endif




