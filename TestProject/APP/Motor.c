#include "Motor.h"

void InitGPIO_Motor()
{
	
	GPIO_InitTypeDef GPIO_InitStructure;//
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=(GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);//Init 0-7
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//set the output mode to push-pull output
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//set the port speed to 50MHz
	GPIO_Init(GPIOA,&GPIO_InitStructure); //initialize
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
	//GPIO_SetBits(GPIOA,GPIO_Pin_6);//STBY set 1
}

void GO(void)
{
	//10 10
	GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);//A0 A1 A3 A4 set 0
	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_2);// A1  A4 set 1
}


void Stop(void)
{
	//0000
	GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);//A0 A1 A3 A4 set 0
}

void Back(void)
{
	//01 01
	GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);//A0 A1 A3 A4 set 0
	GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_3);// A1  A4 set 1
}
void left(void)
{
	//0110
	GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);//A0 A1 A3 A4 set 0
	GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2);// A1  A4 set 1
}

void right(void)
{
	//1001
	GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);//A0 A1 A3 A4 set 0
	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_3);// A1  A4 set 1
}
