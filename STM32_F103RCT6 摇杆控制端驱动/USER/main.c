#include "stm32f10x_tim.h"
#include "pwm.h"
#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include"ADC.h"
#include"stm32f10x_adc.h"
#include"usart.h"
#include "spi.h"
#include "24l01.h"




 int main()
 {	
	 NRF_DAT NRF24l01_dat;
u8 speed=0;
	 	 u16 ADC2_temp=0,ADC1_temp=0;

		delay_init();	    	 //延时函数初始化	  
		OLED_Init();			//初始化OLED  
		OLED_Clear(); 
	  ADC_init();

			SPI2_Init();
		NRF24L01_Init(); 
 while(NRF24L01_Check())
 {
	 
	 OLED_ShowString(0,0,"NRF24L04 ERROR");
 }
 OLED_ShowString(0,0,"LOADING....");
 delay_ms(1000);
	OLED_Clear(); 	 
OLED_ShowString(0,0,"NRF24L04 OK");
  delay_ms(1000);
 OLED_Clear(); 	 
OLED_ShowString(0,0,"START WORKING!");
	delay_ms(2000);
 NRF24L01_TX_Mode();
		while(1)
		{		
		if(NRF24L01_TxPacket((u8*)&NRF24l01_dat,32)==TX_OK)    //(u8*)&NRF24l01_dat:&NRF24l01_dat：取NRF24l01_dat结构体的地址，（u8*）强制类型转化为u8类型的指针
					{
							OLED_ShowNum(90,4,NRF24l01_dat.TX_Temp,3,16);
						
					}

				ADC2_temp=Get_Adc2_Average(ADC_Channel_2,8);
			 ADC1_temp=Get_Adc1_Average(ADC_Channel_1,8);
									
									
									
			if(ADC1_temp/16>=180&ADC2_temp/16>124&ADC2_temp/16<129){NRF24l01_dat.TX_Temp=1; OLED_ShowString(0,4,"GO AHEAD");}//前进
			if(ADC1_temp/16<=70&ADC2_temp/16>124&ADC2_temp/16<129){NRF24l01_dat.TX_Temp=2;OLED_ShowString(0,4,"BACK");}//后退
			if(ADC2_temp/16>=190&ADC1_temp/16>124&ADC1_temp/16<129){NRF24l01_dat.TX_Temp=3; OLED_ShowString(0,4,"LEFT");}//左转
			if(ADC2_temp/16<=70&ADC1_temp/16>124&ADC1_temp/16<129){NRF24l01_dat.TX_Temp=4; OLED_ShowString(0,4,"RIGHT");}//右转
			if(ADC2_temp/16>=129&ADC1_temp/16>=140){NRF24l01_dat.TX_Temp=5; OLED_ShowString(0,4,"L TURN");}//左转圈
			if(ADC2_temp/16<=80&ADC1_temp/16>=190){NRF24l01_dat.TX_Temp=6;OLED_ShowString(0,4,"R TURN");}//右转圈
			if(ADC1_temp/16<140&ADC1_temp/16>100&ADC2_temp/16>100&ADC2_temp/16<140){NRF24l01_dat.TX_Temp=10;OLED_ShowString(0,4,"         ");}
			


//			TIM_SetCompare1(TIM1, b);
			
//			delay_ms(10);
		
		}	 
	
}

