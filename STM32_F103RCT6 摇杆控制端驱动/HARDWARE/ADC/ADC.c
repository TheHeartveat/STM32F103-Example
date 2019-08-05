#include"ADC.h"
#include"stm32f10x.h"
#include"stm32f10x_adc.h"
#include"delay.h"
#include "oled.h"



void ADC_init()
{
	 GPIO_InitTypeDef GPIO_InitStruct;	
	 ADC_InitTypeDef  ADC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);		//��ADC1ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);		//��ADC1ʱ��
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AIN;			//GPIO����Ϊģ������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;					//ѡ��PA1
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;	//GPIO�ٶ�50MHZ
	GPIO_Init(GPIOA, &GPIO_InitStruct);						//��ʼ��GPIOA
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AIN;			//GPIO����Ϊģ������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;					//ѡ��PA1
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;	//GPIO�ٶ�50MHZ
	GPIO_Init(GPIOA, &GPIO_InitStruct);						//��ʼ��GPIOA
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);				//����Ϊ6��Ƶ
	ADC_DeInit(ADC1);													//��λADC1
	ADC_DeInit(ADC2);													//��λADC1
	
	
	ADC_InitStruct.ADC_ContinuousConvMode=DISABLE;								//�Ƿ�����ת������
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;              //��������Ϊ�Ҷ���
	ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;   //�ⲿ������ʽ����ʹ���ⲿ����
	ADC_InitStruct.ADC_Mode=ADC_Mode_Independent;         //ADCģʽ������ģʽ
	ADC_InitStruct.ADC_NbrOfChannel=1;									//ͨ������1
	ADC_InitStruct.ADC_ScanConvMode=DISABLE;           //������ɨ��
	ADC_Init(ADC1, &ADC_InitStruct);                //��ʼ��ADC1
	
	ADC_InitStruct.ADC_ContinuousConvMode=DISABLE;								//�Ƿ�����ת������
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;              //��������Ϊ�Ҷ���
	ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;   //�ⲿ������ʽ����ʹ���ⲿ����
	ADC_InitStruct.ADC_Mode=ADC_Mode_Independent;         //ADCģʽ������ģʽ
	ADC_InitStruct.ADC_NbrOfChannel=1;									//ͨ������1
	ADC_InitStruct.ADC_ScanConvMode=DISABLE;           //������ɨ��
	ADC_Init(ADC2, &ADC_InitStruct);                //��ʼ��ADC1
	
	ADC_Cmd(ADC1,ENABLE);														//ʹ��ADC1
	ADC_Cmd(ADC2,ENABLE);														//ʹ��ADC1
	
	
	ADC_ResetCalibration(ADC1);                  //ʹ�ܸ�λУ׼
	while(ADC_GetResetCalibrationStatus(ADC1));	 //�ȴ�У׼����
	ADC_StartCalibration(ADC1);                  //��ʼADCУ׼
	while(ADC_GetCalibrationStatus(ADC1));     //�ȴ�У׼����
	
	ADC_ResetCalibration(ADC2);                  //ʹ�ܸ�λУ׼
	while(ADC_GetResetCalibrationStatus(ADC2));	 //�ȴ�У׼����
	ADC_StartCalibration(ADC2);                  //��ʼADCУ׼
	while(ADC_GetCalibrationStatus(ADC2));     //�ȴ�У׼����
	
}
/*
���ܣ���ȡADCת��ֵ
ch:ͨ��
*/
u16 Get_Adc1(u8 ch)
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5  );    //���ù���ͨ����ADC1��ͨ�����������еڼ���ת����1��������ʱ��
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	while(ADC_GetSoftwareStartConvStatus(ADC1));
	
	return ADC_GetConversionValue(ADC1);
}

u16 Get_Adc2(u8 ch)
{
	ADC_RegularChannelConfig(ADC2, ch, 1, ADC_SampleTime_239Cycles5  );    //���ù���ͨ����ADC1��ͨ�����������еڼ���ת����1��������ʱ��
	
	ADC_SoftwareStartConvCmd(ADC2,ENABLE);
	while(ADC_GetSoftwareStartConvStatus(ADC2));
	
	return ADC_GetConversionValue(ADC2);
}

/*
���ܣ�ADCת��ֵƽ����
ch:ͨ��
nmu:ƽ��������
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
���ܣ���ADCת��ֵת��Ϊ��ѹ
ch:ͨ��
nmu:ƽ��������
*/
u16 Get_Voltage_ADC1(u8 ch,u8 num)
{
	u16 val;
	float voltage;
	
	val=Get_Adc1_Average(ch , num);
	voltage=(float)val*(3.3/4096);     //�ο���ѹ��3.3    12λADC
	
	return voltage*10000;  
}

u16 Get_Voltage_ADC2(u8 ch,u8 num)
{
	u16 val;
	float voltage;
	
	val=Get_Adc2_Average(ch , num);
	voltage=(float)val*(3.3/4096);     //�ο���ѹ��3.3    12λADC
	
	return voltage*1000;  
}




