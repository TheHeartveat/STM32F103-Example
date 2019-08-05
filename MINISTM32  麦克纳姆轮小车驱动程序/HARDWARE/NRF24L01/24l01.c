#include "24l01.h"
#include "delay.h"
#include "spi.h"


/*注：A和B单片机通过NRF24L01通信，A主机的发送和接收地址可不一样，
B主机的发送和接收地址可不一样 ，但A的发送地址和B的接收必须一致，
A的接收地址和B的发送地址必须一致，否则将不能通信 */  
const u8 TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //发送地址     发送方的地址和接收方的地址必须一致，否者将不能通信（可自定义地址）
const u8 RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //接收地址			接收方和发送方的地址必须一致（可自定义地址）


//初始化24L01的IO口

void NRF24L01_Init(void)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure; 
	
 	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE );	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
	GPIO_SetBits(GPIOC,GPIO_Pin_4);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU  ;   //上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);
	SPI1_Init();    		//初始化SPI
		
	SPI_Cmd(SPI1, DISABLE); // 
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//选择了串行时钟的稳态:时钟悬空低电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//数据捕获于第一个时钟沿
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;		//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	SPI_Init(SPI1, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器

	
	NRF24L01_CE=0; 	//使能24L01
	NRF24L01_CSN=1;	//SPI片选取消	 	
}
//检测24L01是否存在
//返回值:0，成功;1，失败	
u8 NRF24L01_Check(void)
{
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i;
	SPI1_SetSpeed(SPI_BaudRatePrescaler_8); //spi速度为9Mhz（24L01的最大SPI时钟为10Mhz）   	 
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);//写入5个字节的地址.	
	NRF24L01_Read_Buf(TX_ADDR,buf,5); //读出写入的地址  
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;//检测24L01错误	
	return 0;		 //检测到24L01
}	 	 
//SPI写寄存器
//reg:指定寄存器地址
//value:写入的值
u8 NRF24L01_Write_Reg(u8 reg,u8 value)
{
	u8 status=0;	
   	NRF24L01_CSN=0;                 //使能SPI传输   （SPI片选，低电平有效）
  	status =SPI1_ReadWriteByte(reg);//发送寄存器号  （选择写入的寄存器（地址））
  	SPI1_ReadWriteByte(value);      //写入寄存器的值  
  	NRF24L01_CSN=1;                 //禁止SPI传输	   
  	return(status);       			//返回状态值
}
//读取SPI寄存器值
//reg:要读的寄存器
u8 NRF24L01_Read_Reg(u8 reg)
{
	u8 reg_val=0;	    //存储寄存器的值
 	NRF24L01_CSN = 0;          //使能SPI传输		
  	SPI1_ReadWriteByte(reg);   //发送寄存器号     	（选择读取的寄存器（地址））
  	reg_val=SPI1_ReadWriteByte(0XFF);//读取寄存器内容   （0xFF：空指令，可随便定义，对读取没有影响）
  	NRF24L01_CSN = 1;          //禁止SPI传输		    
  	return(reg_val);           //返回状态值
}	
//把NRF24L01输出缓存寄存器中的数值读到缓存区（数组）中
//reg:寄存器(位置)	（读取的寄存器的地址）
//*pBuf:数据指针			
//len:数据长度         可用sizeof计算，例如：sizeof（a）,结果是变量a占用的字节数
//返回值,此次读到的状态寄存器值 
u8 NRF24L01_Read_Buf(u8 reg,u8 *pBuf,u8 len)
{
	u8 status,u8_ctr;	       //status：状态值
  	NRF24L01_CSN = 0;           //使能SPI传输
  	status=SPI1_ReadWriteByte(reg);//发送寄存器值(位置),并读取状态值   	   （选择读取的寄存器（地址））
 	for(u8_ctr=0;u8_ctr<len;u8_ctr++)pBuf[u8_ctr]=SPI1_ReadWriteByte(0XFF);//读出数据				（0xFF：空指令，可随便定义，对读取没有影响）
  	NRF24L01_CSN=1;       //关闭SPI传输
  	return status;        //返回读到的状态值
}
//把缓存区（数组）的数值写到NRF24L01的输入缓存寄存器中
//reg:寄存器(位置)			（写入的寄存器的地址）
//*pBuf:数据指针       
//len:数据长度					可用sizeof计算，例如：sizeof（a）,结果是变量a占用的字节数
//返回值,此次读到的状态寄存器值
u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
{
	u8 status,u8_ctr;	    
 	NRF24L01_CSN = 0;          //使能SPI传输
  	status = SPI1_ReadWriteByte(reg);//发送寄存器值(位置),并读取状态值
  	for(u8_ctr=0; u8_ctr<len; u8_ctr++)SPI1_ReadWriteByte(*pBuf++); //写入数据	 
  	NRF24L01_CSN = 1;       //关闭SPI传输
  	return status;          //返回读到的状态值
}				   
//启动NRF24L01发送数据，即发送一个数组的各个成员数值
//txbuf:待发送数据首地址  
//返回值:发送完成状况
u8 NRF24L01_TxPacket(u8 *txbuf)
{
	u8 sta=0;
 	SPI1_SetSpeed(SPI_BaudRatePrescaler_8);//spi速度为9Mhz（24L01的最大SPI时钟为10Mhz）   
	NRF24L01_CE=0;			//接收模式（关闭射频）
	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//写数据到TX BUF  32个字节		把txbuf指针指向的数组的各个成员的数值写到发送缓冲区（地址：WR_TX_PLOAD）内，TX_PLOAD_WIDTH个字节（32个）
 	NRF24L01_CE=1;//发送模式（开启射频）	   
	while(NRF24L01_IRQ!=0);//等待发送完成  等待NRF24L01产生中断（中断是低电平），无论是发送数据还是接收数据，数据接收或发送完毕NRF24L01的IRQ就会被拉低
	sta=NRF24L01_Read_Reg(STATUS);  //读取状态寄存器的值	   STATUS：状态寄存器的地址   sta：存储状态寄存器的值
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //清除TX_DS或MAX_RT中断标志   清除状态寄存器
	if(sta&MAX_TX)//达到最大重发次数   sta&MAX_TX为真，也就是sta==MAX_TX，执行该if语句
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);//清除TX FIFO寄存器    清除发送寄存器
		return MAX_TX; 
	}
	if(sta&TX_OK)//发送完成     
	{
		return TX_OK;
	}
	return 0xff;//其他原因发送失败
}
//启动NRF24L01接收数据，存入缓存区内
//txbuf:待发送数据首地址		
//返回值:0，接收完成；其他，错误代码
u8 NRF24L01_RxPacket(u8 *rxbuf)
{
	u8 sta=0;
	NRF24L01_CE=1;//发送模式（开启射频）
  while(NRF24L01_IRQ!=0);	  //等待接收完成
	NRF24L01_CE=0;			//接收模式（关闭射频）
	SPI1_SetSpeed(SPI_BaudRatePrescaler_8); //spi速度为9Mhz（24L01的最大SPI时钟为10Mhz）  设置SPI通信传输的速度 
	sta=NRF24L01_Read_Reg(STATUS);  //读取状态寄存器的值    	     STATUS：状态寄存器的地址   sta：存储状态寄存器的值 
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //清除TX_DS或MAX_RT中断标志		 清除状态寄存器
	if(sta&RX_OK)//接收到数据       sta&RX_OK：即sta==RX_OK，执行该if语句
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//读取数据    RD_RX_PLOAD：读取的寄存器的地址 rxbuf：存入的数组的首地址  RX_PLOAD_WIDTH：接收的字节数   可用sizeof计算，例如：sizeof（a）,结果是变量a占用的字节数
		NRF24L01_Write_Reg(FLUSH_RX,0xff);//清除RX FIFO寄存器 
		return 0; 
	}	   
	return 1;//没收到任何数据
}					    
//该函数初始化NRF24L01到RX模式
//设置RX地址,写RX数据宽度,选择RF频道,波特率和LNA HCURR
//当CE变高后,即进入RX模式,并可以接收数据了		

//注：此时+和|（或），可通用，因为NRF_WRITE_REG高四位有效，加上的数 或者 或的数低四位有效
void NRF24L01_RX_Mode(void)
{
	NRF24L01_CE=0;	  
  	NRF24L01_Write_Buf(NRF_WRITE_REG|RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//写RX节点地址  NRF_WRITE_REG+RX_ADDR_P0：数据通道0接收地址 (u8*)RX_ADDRESS：接收地址，存在RX_ADDRESS数组内   RX_ADR_WIDTH：字节数（5个）
	  
  	NRF24L01_Write_Reg(NRF_WRITE_REG|EN_AA,0x01);    	//开启通道0的自动应答模式    NRF_WRITE_REG|EN_AA：自动应答操纵的寄存器的地址  0x01：开启相应位
  	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);	//开启通道0的接收模式       	 
  	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);	    	//设置RF通信频率   		  NRF_WRITE_REG+RF_CH：设置通信频率的寄存器的地址    发送通道和接收必须一致
  	NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//设置通道0的有效数据宽度    <=32bit	    
  	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);	//设置TX发射参数,0db增益,2Mbps,低噪声增益开启   发射功率、速度
  	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0f);		//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式   设置为接收模式，是否开启CRC校验等
  	NRF24L01_CE = 1; //CE为高,进入接收模式   开启射频
}						 
//该函数初始化NRF24L01到TX模式
//设置TX地址,写TX数据宽度,设置RX自动应答的地址,填充TX发送数据,选择RF频道,波特率和LNA HCURR
//PWR_UP,CRC使能
//当CE变高后,即进入RX模式,并可以接收数据了		   
//CE为高大于10us,则启动发送.	 
void NRF24L01_TX_Mode(void)
{														 
	NRF24L01_CE=0;	    
  	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);//写TX节点地址 
  	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); //设置TX节点地址,主要为了使能ACK	  

  	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);     //使能通道0的自动应答    
  	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01); //使能通道0的接收地址  
	NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);//设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次  最大重发次数，超过最大重发次数，对方还没收到数据，则放弃发送
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);       //设置RF通道为40     发送通道和接收必须一致
  	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e);    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断   设置为发送模式，是否开启CRC校验等
	NRF24L01_CE=1;//CE为高,10us后启动发送		开启射频
}










