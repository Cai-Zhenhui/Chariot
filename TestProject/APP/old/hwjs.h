#ifndef _hwjs_H
#define _hwjs_H

#include "system.h"



void Hwjs_Init(void);
u8 HW_jssj(void);

//定义全局变量

extern unsigned char IRcord[4];//用来存放分离后的四个字节的数据 其中数据码 在IRcord[2]中
//extern unsigned char IRdata[32];//用存储32位红外数据
extern unsigned char IRok;

#endif
