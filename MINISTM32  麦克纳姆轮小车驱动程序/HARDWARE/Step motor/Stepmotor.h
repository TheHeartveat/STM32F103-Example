#ifndef _STEPMOTOR_H
#define _STEPMOTOR_H
#include"stm32f10x.h"






void GO_Ahead(u8 i);
void Back(u8 i);
void Left(u8 i);
void Right(u8 i);
void Turn_L(u8 i);
void Turn_R(u8 i);
void stop();
#endif

