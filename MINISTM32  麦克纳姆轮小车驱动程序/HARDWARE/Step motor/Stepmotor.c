#include"Stepmotor.h"
#include"sys.h"
#include "delay.h"
#include "24l01.h"





void stop()
{

						PBout(0)=0;
						PBout(1)=0;
						PBout(6)=0;
						PBout(7)=0;     //1号电机
						
						PBout(8)=0;
						PBout(9)=0;
						PBout(10)=0;
						PBout(11)=0;     //2号电机
						
						PBout(12)=0;
						PBout(13)=0;
						PBout(14)=0;
						PBout(15)=0;     //3号电机
						
						PCout(6)=0;
						PCout(7)=0;
						PCout(8)=0;
						PCout(9)=0;       //4号电机
}
void GO_Ahead(u8 i)
{
//	unsigned int i;
//	for(i=0;i<50;i++)
//	{
	          PBout(0)=1;
						PBout(1)=0;
						PBout(6)=0;
						PBout(7)=0;     //1号电机
						
						PBout(8)=1;
						PBout(9)=0;
						PBout(10)=0;
						PBout(11)=0;     //2号电机
						
						PBout(12)=1;
						PBout(13)=0;
						PBout(14)=0;
						PBout(15)=0;     //3号电机
						
						PCout(6)=1;
						PCout(7)=0;
						PCout(8)=0;
						PCout(9)=0;       //4号电机
						  delay_ms(i);//1
						
						PBout(0)=0;
						PBout(1)=0;
						PBout(6)=1;
						PBout(7)=0;      	//1号电机
						
						PBout(8)=0;
						PBout(9)=0;
						PBout(10)=1;
						PBout(11)=0;			 //2号电机
						
						PBout(12)=0;
						PBout(13)=0;
						PBout(14)=1;
						PBout(15)=0;			//3号电机
						
						PCout(6)=0;
						PCout(7)=0;
						PCout(8)=1;
						PCout(9)=0;				//4号电机
						 	  delay_ms(i);//2
						
						PBout(0)=0;
						PBout(1)=1;
						PBout(6)=0;
						PBout(7)=0;				//1号电机
						
						PBout(8)=0;
						PBout(9)=1;
						PBout(10)=0;
						PBout(11)=0;				//2号电机
						
						PBout(12)=0;
						PBout(13)=1;
						PBout(14)=0;
						PBout(15)=0;			//3号电机
						
						PCout(6)=0;
						PCout(7)=1;
						PCout(8)=0;
						PCout(9)=0;				//4号电机
							  delay_ms(i);//3
						
						PBout(0)=0;
						PBout(1)=0;
						PBout(6)=0;
						PBout(7)=1;				//1号电机
						
						PBout(8)=0;
						PBout(9)=0;
						PBout(10)=0;
						PBout(11)=1;				//2号电机
						
						PBout(12)=0;
						PBout(13)=0;
						PBout(14)=0;
						PBout(15)=1;			//3号电机
						
						PCout(6)=0;
						PCout(7)=0;
						PCout(8)=0;
						PCout(9)=1;				//4号电机
							  delay_ms(i);//4
				
}

void Back(u8 i)
{

	          PBout(0)=0;
						PBout(1)=0;
						PBout(6)=0;
						PBout(7)=1;				//1号电机
						
						PBout(8)=0;
						PBout(9)=0;
						PBout(10)=0;
						PBout(11)=1;				//2号电机
						
						PBout(12)=0;
						PBout(13)=0;
						PBout(14)=0;
						PBout(15)=1;			//3号电机
						
						PCout(6)=0;
						PCout(7)=0;
						PCout(8)=0;
						PCout(9)=1;				//4号电机
						 	  delay_ms(i);//4
						
						PBout(0)=0;
						PBout(1)=1;
						PBout(6)=0;
						PBout(7)=0;				//1号电机
						
						PBout(8)=0;
						PBout(9)=1;
						PBout(10)=0;
						PBout(11)=0;				//2号电机
						
						PBout(12)=0;
						PBout(13)=1;
						PBout(14)=0;
						PBout(15)=0;			//3号电机
						
						PCout(6)=0;
						PCout(7)=1;
						PCout(8)=0;
						PCout(9)=0;				//4号电机
							  delay_ms(i);//3
						
						PBout(0)=0;
						PBout(1)=0;
						PBout(6)=1;
						PBout(7)=0;      	//1号电机
						
						PBout(8)=0;
						PBout(9)=0;
						PBout(10)=1;
						PBout(11)=0;			 //2号电机
						
						PBout(12)=0;
						PBout(13)=0;
						PBout(14)=1;
						PBout(15)=0;			//3号电机
						
						PCout(6)=0;
						PCout(7)=0;
						PCout(8)=1;
						PCout(9)=0;				//4号电机
						 	  delay_ms(i);//2
						
						PBout(0)=1;
						PBout(1)=0;
						PBout(6)=0;
						PBout(7)=0;     //1号电机
						
						PBout(8)=1;
						PBout(9)=0;
						PBout(10)=0;
						PBout(11)=0;     //2号电机
						
						PBout(12)=1;
						PBout(13)=0;
						PBout(14)=0;
						PBout(15)=0;     //3号电机
						
						PCout(6)=1;
						PCout(7)=0;
						PCout(8)=0;
						PCout(9)=0;       //4号电机
						 	  delay_ms(i);//1
						
}
void Left(u8 i)
{

						PBout(0)=1;
						PBout(1)=0;
						PBout(6)=0;
						PBout(7)=0;     //1号电机
						
						PBout(8)=0;
						PBout(9)=0;
						PBout(10)=0;
						PBout(11)=1;				//2号电机
						
						PBout(12)=1;
						PBout(13)=0;
						PBout(14)=0;
						PBout(15)=0;     //3号电机
						
						PCout(6)=0;
						PCout(7)=0;
						PCout(8)=0;
						PCout(9)=1;       //4号电机
						 	  delay_ms(i);//1
						
						PBout(0)=0;
						PBout(1)=0;
						PBout(6)=1;
						PBout(7)=0;      	//1号电机
						
						PBout(8)=0;
						PBout(9)=1;
						PBout(10)=0;
						PBout(11)=0;				//2号电机
						
						PBout(12)=0;
						PBout(13)=0;
						PBout(14)=1;
						PBout(15)=0;			//3号电机
						
						PCout(6)=0;
						PCout(7)=1;
						PCout(8)=0;
						PCout(9)=0;				//4号电机
						 	  delay_ms(i);//2
						
						PBout(0)=0;
						PBout(1)=1;
						PBout(6)=0;
						PBout(7)=0;				//1号电机
						
						PBout(8)=0;
						PBout(9)=0;
						PBout(10)=1;
						PBout(11)=0;			 //2号电机
						
						PBout(12)=0;
						PBout(13)=1;
						PBout(14)=0;
						PBout(15)=0;			//3号电机
						
						PCout(6)=0;
						PCout(7)=0;
						PCout(8)=1;
						PCout(9)=0;				//4号电机
						 	  delay_ms(i);//3
						
						PBout(0)=0;
						PBout(1)=0;
						PBout(6)=0;
						PBout(7)=1;				//1号电机
						
						PBout(8)=1;
						PBout(9)=0;
						PBout(10)=0;
						PBout(11)=0;     //2号电机
						
						PBout(12)=0;
						PBout(13)=0;
						PBout(14)=0;
						PBout(15)=1;			//3号电机
						
						PCout(6)=1;
						PCout(7)=0;
						PCout(8)=0;
						PCout(9)=0;				//4号电机
						 	  delay_ms(i);//4
							
						
}
void Right(u8 i)
{
	
						PBout(0)=0;
						PBout(1)=0;
						PBout(6)=0;
						PBout(7)=1;     //1号电机
						
						PBout(8)=1;
						PBout(9)=0;
						PBout(10)=0;
						PBout(11)=0;     //2号电机
						
						PBout(12)=0;
						PBout(13)=0;
						PBout(14)=0;
						PBout(15)=1;     //3号电机
						
						PCout(6)=1;
						PCout(7)=0;
						PCout(8)=0;
						PCout(9)=0;       //4号电机
						 	  delay_ms(i);//1
						
						PBout(0)=0;
						PBout(1)=1;
						PBout(6)=0;
						PBout(7)=0;      	//1号电机
						
						PBout(8)=0;
						PBout(9)=0;
						PBout(10)=1;
						PBout(11)=0;			 //2号电机
						
						PBout(12)=0;
						PBout(13)=1;
						PBout(14)=0;
						PBout(15)=0;			//3号电机
						
						PCout(6)=0;
						PCout(7)=0;
						PCout(8)=1;
						PCout(9)=0;				//4号电机
						 	  delay_ms(i);//2
						
						PBout(0)=0;
						PBout(1)=0;
						PBout(6)=1;
						PBout(7)=0;				//1号电机
						
						PBout(8)=0;
						PBout(9)=1;
						PBout(10)=0;
						PBout(11)=0;				//2号电机
						
						PBout(12)=0;
						PBout(13)=0;
						PBout(14)=1;
						PBout(15)=0;			//3号电机
						
						PCout(6)=0;
						PCout(7)=1;
						PCout(8)=0;
						PCout(9)=0;				//4号电机
						  	  delay_ms(i);//3
						
						PBout(0)=1;
						PBout(1)=0;
						PBout(6)=0;
						PBout(7)=0;				//1号电机
						
						PBout(8)=0;
						PBout(9)=0;
						PBout(10)=0;
						PBout(11)=1;				//2号电机
						
						PBout(12)=1;
						PBout(13)=0;
						PBout(14)=0;
						PBout(15)=0;			//3号电机
						
						PCout(6)=0;
						PCout(7)=0;
						PCout(8)=0;
						PCout(9)=1;				//4号电机
						  	  delay_ms(i);//4
					
}
void Turn_R(u8 i)
{

						 PBout(0)=1;
						PBout(1)=0;
						PBout(6)=0;
						PBout(7)=0;     //1号电机
						
						PBout(8)=0;
						PBout(9)=0;
						PBout(10)=0;
						PBout(11)=1;     //2号电机
						
						PBout(12)=0;
						PBout(13)=0;
						PBout(14)=0;
						PBout(15)=1;     //3号电机
						
						PCout(6)=1;
						PCout(7)=0;
						PCout(8)=0;
						PCout(9)=0;       //4号电机
							  delay_ms(i);//1
						
						PBout(0)=0;
						PBout(1)=0;
						PBout(6)=1;
						PBout(7)=0;      	//1号电机
						
						PBout(8)=0;
						PBout(9)=1;
						PBout(10)=0;
						PBout(11)=0;			 //2号电机
						
						PBout(12)=0;
						PBout(13)=1;
						PBout(14)=0;
						PBout(15)=0;			//3号电机
						
						PCout(6)=0;
						PCout(7)=0;
						PCout(8)=1;
						PCout(9)=0;				//4号电机
						 	  delay_ms(i);//2
						
						PBout(0)=0;
						PBout(1)=1;
						PBout(6)=0;
						PBout(7)=0;				//1号电机
						
						PBout(8)=0;
						PBout(9)=0;
						PBout(10)=1;
						PBout(11)=0;				//2号电机
						
						PBout(12)=0;
						PBout(13)=0;
						PBout(14)=1;
						PBout(15)=0;			//3号电机
						
						PCout(6)=0;
						PCout(7)=1;
						PCout(8)=0;
						PCout(9)=0;				//4号电机
						 	  delay_ms(i);//3
						
						PBout(0)=0;
						PBout(1)=0;
						PBout(6)=0;
						PBout(7)=1;				//1号电机
						
						PBout(8)=1;
						PBout(9)=0;
						PBout(10)=0;
						PBout(11)=0;				//2号电机
						
						PBout(12)=1;
						PBout(13)=0;
						PBout(14)=0;
						PBout(15)=0;			//3号电机
						
						PCout(6)=0;
						PCout(7)=0;
						PCout(8)=0;
						PCout(9)=1;				//4号电机
							  delay_ms(i);//4
					
}
void Turn_L(u8 i)
{
	
				PBout(0)=0;
						PBout(1)=0;
						PBout(6)=0;
						PBout(7)=1;     //1号电机
						
						PBout(8)=1;
						PBout(9)=0;
						PBout(10)=0;
						PBout(11)=0;     //2号电机
						
						PBout(12)=1;
						PBout(13)=0;
						PBout(14)=0;
						PBout(15)=0;     //3号电机
						
						PCout(6)=0;
						PCout(7)=0;
						PCout(8)=0;
						PCout(9)=1;       //4号电机
						  delay_ms(i);//1
						
						PBout(0)=0;
						PBout(1)=1;
						PBout(6)=0;
						PBout(7)=0;      	//1号电机
						
						PBout(8)=0;
						PBout(9)=0;
						PBout(10)=1;
						PBout(11)=0;			 //2号电机
						
						PBout(12)=0;
						PBout(13)=0;
						PBout(14)=1;
						PBout(15)=0;			//3号电机
						
						PCout(6)=0;
						PCout(7)=1;
						PCout(8)=0;
						PCout(9)=0;				//4号电机
						 	  delay_ms(i);//2
						
						PBout(0)=0;
						PBout(1)=0;
						PBout(6)=1;
						PBout(7)=0;				//1号电机
						
						PBout(8)=0;
						PBout(9)=1;
						PBout(10)=0;
						PBout(11)=0;				//2号电机
						
						PBout(12)=0;
						PBout(13)=1;
						PBout(14)=0;
						PBout(15)=0;			//3号电机
						
						PCout(6)=0;
						PCout(7)=0;
						PCout(8)=1;
						PCout(9)=0;				//4号电机
							  delay_ms(i);//3
						
						PBout(0)=1;
						PBout(1)=0;
						PBout(6)=0;
						PBout(7)=0;				//1号电机
						
						PBout(8)=0;
						PBout(9)=0;
						PBout(10)=0;
						PBout(11)=1;				//2号电机
						
						PBout(12)=0;
						PBout(13)=0;
						PBout(14)=0;
						PBout(15)=1;			//3号电机
						
						PCout(6)=1;
						PCout(7)=0;
						PCout(8)=0;
						PCout(9)=0;				//4号电机
						 	  delay_ms(i);//4
							
						
}

