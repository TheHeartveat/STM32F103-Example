#ifndef __SPI_H
#define __SPI_H
#include "sys.h"

// SPI�����ٶ�����  
 				  
void SPI2_Init(void);			 //��ʼ��SPI��
void SPI2_SetSpeed(u8 SpeedSet); //����SPI�ٶ�   
u16 SPI2_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�
		 
#endif

