#include"ADC.h"
#include"stm32f10x.h"
#include"stm32f10x_adc.h"
#include"delay.h"
#include "oled.h"



void ADC_init()
{
	 GPIO_InitTypeDef GPIO_InitStruct;	
	 ADC_InitTypeDef  ADC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //打开GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);		//打开ADC1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);		//打开ADC1时钟
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AIN;			//GPIO设置为模拟输入
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;					//选中PA1
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;	//GPIO速度50MHZ
	GPIO_Init(GPIOA, &GPIO_InitStruct);						//初始化GPIOA
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AIN;			//GPIO设置为模拟输入
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;					//选中PA1
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;	//GPIO速度50MHZ
	GPIO_Init(GPIOA, &GPIO_InitStruct);						//初始化GPIOA
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);				//设置为6分频
	ADC_DeInit(ADC1);													//复位ADC1
	ADC_DeInit(ADC2);													//复位ADC1
	
	
	ADC_InitStruct.ADC_ContinuousConvMode=DISABLE;								//是否连续转换：否
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;              //设置数据为右对齐
	ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;   //外部触发方式：不使用外部触发
	ADC_InitStruct.ADC_Mode=ADC_Mode_Independent;         //ADC模式：独立模式
	ADC_InitStruct.ADC_NbrOfChannel=1;									//通道数：1
	ADC_InitStruct.ADC_ScanConvMode=DISABLE;           //不设置扫描
	ADC_Init(ADC1, &ADC_InitStruct);                //初始化ADC1
	
	ADC_InitStruct.ADC_ContinuousConvMode=DISABLE;								//是否连续转换：否
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;              //设置数据为右对齐
	ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;   //外部触发方式：不使用外部触发
	ADC_InitStruct.ADC_Mode=ADC_Mode_Independent;         //ADC模式：独立模式
	ADC_InitStruct.ADC_NbrOfChannel=1;									//通道数：1
	ADC_InitStruct.ADC_ScanConvMode=DISABLE;           //不设置扫描
	ADC_Init(ADC2, &ADC_InitStruct);                //初始化ADC1
	
	ADC_Cmd(ADC1,ENABLE);														//使能ADC1
	ADC_Cmd(ADC2,ENABLE);														//使能ADC1
	
	
	ADC_ResetCalibration(ADC1);                  //使能复位校准
	while(ADC_GetResetCalibrationStatus(ADC1));	 //等待校准结束
	ADC_StartCalibration(ADC1);                  //开始ADC校准
	while(ADC_GetCalibrationStatus(ADC1));     //等待校准结束
	
	ADC_ResetCalibration(ADC2);                  //使能复位校准
	while(ADC_GetResetCalibrationStatus(ADC2));	 //等待校准结束
	ADC_StartCalibration(ADC2);                  //开始ADC校准
	while(ADC_GetCalibrationStatus(ADC2));     //等待校准结束
	
}
/*
功能：获取ADC转换值
ch:通道
*/
u16 Get_Adc1(u8 ch)
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5  );    //配置规则通道：ADC1，通道，规则序列第几个转换（1），采样时间
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	while(ADC_GetSoftwareStartConvStatus(ADC1));
	
	return ADC_GetConversionValue(ADC1);
}

u16 Get_Adc2(u8 ch)
{
	ADC_RegularChannelConfig(ADC2, ch, 1, ADC_SampleTime_239Cycles5  );    //配置规则通道：ADC1，通道，规则序列第几个转换（1），采样时间
	
	ADC_SoftwareStartConvCmd(ADC2,ENABLE);
	while(ADC_GetSoftwareStartConvStatus(ADC2));
	
	return ADC_GetConversionValue(ADC2);
}

/*
功能：ADC转换值平均数
ch:通道
nmu:平均数除数
*/
u16 Get_Adc1_Average(u8 ch,u8 num)
{
	unsigned char i;
	u32 temp=0;
	for(i=0;i<num;i++)
	{
		temp+=Get_Adc1(ch);
		delay_ms(4);
	}
	return temp/num;
}
u16 Get_Adc2_Average(u8 ch,u8 num)
{
	unsigned char i;
	u32 temp=0;
	for(i=0;i<num;i++)
	{
		temp+=Get_Adc2(ch);
		delay_ms(4);
	}
	return temp/num;
}
/*
功能：将ADC转换值转化为电压
ch:通道
nmu:平均数除数
*/
u16 Get_Voltage_ADC1(u8 ch,u8 num)
{
	u16 val;
	float voltage;
	
	val=Get_Adc1_Average(ch , num);
	voltage=(float)val*(3.3/4096);     //参考电压：3.3    12位ADC
	
	return voltage*10000;  
}

u16 Get_Voltage_ADC2(u8 ch,u8 num)
{
	u16 val;
	float voltage;
	
	val=Get_Adc2_Average(ch , num);
	voltage=(float)val*(3.3/4096);     //参考电压：3.3    12位ADC
	
	return voltage*1000;  
}




