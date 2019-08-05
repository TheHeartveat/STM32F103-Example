#include"usart.h"
#include"stm32f10x.h"
#include "delay.h"


//void USART_init(unsigned int BitRate)
//{
//	
//	GPIO_InitTypeDef GPIO_InitStruct;
//	USART_InitTypeDef USART_InitStruct;
//	NVIC_InitTypeDef  NVIC_InitStruct;
//	
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);    //开启GPIOA时钟
//	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);		//开启串口1时钟
//	
//	
//	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;        //复用推挽输出
//	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
//	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStruct);          
//	
//	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;      //浮空输入
//	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
//	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStruct);
//	
//	
//	USART_InitStruct.USART_BaudRate=BitRate;        //设置波特率
//	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;     //设置硬件流
//	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;      //USART接收和发送
//	USART_InitStruct.USART_Parity=USART_Parity_No;         //奇偶校验
//	USART_InitStruct.USART_StopBits=USART_StopBits_1;       //停止位
//	USART_InitStruct.USART_WordLength=USART_WordLength_8b;  //8个字节长度
//	USART_Init(USART1, &USART_InitStruct);
//	
//	USART_Cmd(USART1, ENABLE);       //使能串口1
//	
//	USART_ITConfig(USART1, USART_IT_RXNE,ENABLE);    //开启接收中断请求
//	
//	
//	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;        //中断通道   注：在stm32f10x.h里
//	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;         //开不开启中断通道
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;   //设置抢占优先级，0~3
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;     //设置子优先级
//	NVIC_Init(&NVIC_InitStruct);
//}
//void USART1_IRQHandler()      //中断服务函数，在启动文件里找
//{
//if(USART_GetITStatus(USART1,USART_IT_RXNE))   //判断USART1标志
//{
//	
//}
//}


