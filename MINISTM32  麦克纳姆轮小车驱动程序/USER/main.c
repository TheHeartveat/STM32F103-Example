#include "led.h"
#include "delay.h"
#include "sys.h"
#include"Stepmotor.h"
#include "stm32f10x_usart.h"
#include "24l01.h"
#include "lcd.h"
#include "usart.h"	

 int main(void)
 {
	 NRF_DAT NRF24L01_dat;
	u8 RX_temp=0,i,speed=0;
	delay_init();	    	 //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	NRF24L01_Init();

	 while(NRF24L01_Check())
	 {
//				PAout(8)=1;
//			delay_ms(500);
//			PAout(8)=0;
//			delay_ms(100);
	 }
	 NRF24L01_RX_Mode();		  
		while(1)
		{	  		    		    				 
			
	if(NRF24L01_RxPacket((u8*)&NRF24L01_dat)==0)//一旦接收到信息,则显示出来.
			{

			}
			if(NRF24L01_dat.RX_Temp==1)for(i=0;i<14;i++)GO_Ahead(4); 
			if(NRF24L01_dat.RX_Temp==2)for(i=0;i<14;i++)Back(4);
			if(NRF24L01_dat.RX_Temp==3)for(i=0;i<14;i++)Left(4); 
			if(NRF24L01_dat.RX_Temp==4)for(i=0;i<14;i++)Right(4); 
			if(NRF24L01_dat.RX_Temp==5)for(i=0;i<14;i++)Turn_L(4); 
			if(NRF24L01_dat.RX_Temp==6)for(i=0;i<14;i++)Turn_R(4); 
			if(NRF24L01_dat.RX_Temp==10)stop();
			
		 
		}
		

 }

