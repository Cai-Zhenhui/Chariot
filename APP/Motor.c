#include "Motor.h"
void Motor_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE); //ʹ��PB PC�˿�ʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB 
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
  GPIO_Init(GPIOC, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOC 
}
void PWM_Init(u16 arr,u16 psc)
{		 		
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	Motor_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);  //ʹ��GPIO����ʱ��ʹ��
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9; //TIM_CH1 //TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0;                            //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

  TIM_CtrlPWMOutputs(TIM8,ENABLE);	//MOE �����ʹ��	

	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��		
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH4Ԥװ��ʹ��	 
	
	TIM_ARRPreloadConfig(TIM8, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM8, ENABLE);  //ʹ��TIM
}

/*
v =(0,100)
*/
void Go(int v){
	ENLB=1;
	ENLF=0;
	ENRF=0;
	ENRB=1;
	
	PWMLB=7200-72*v;
	PWMLF=72*v;
	PWMRF=72*v;
	PWMRB=7200-72*v;
}

void Back(int v){
	ENLB=0;
	ENLF=1;
	ENRF=1;
	ENRB=0;
	
	PWMLB=72*v;
	PWMLF=7200-72*v;
	PWMRF=7200-72*v;
	PWMRB=72*v;
}

/*
pwm control left motor 
pwm =(0,100)
*/
void TurnLeft(int v, int pwm){
	ENLB=1;
	ENLF=0;
	ENRF=0;
	ENRB=1;
	
	PWMLB=7200-(int)(0.72*v*pwm);
	PWMLF=(int)(0.72*v*pwm);
	PWMRF=72*v;
	PWMRB=7200-72*v;
	
}

void TurnRight(int v, int pwm){
	ENLB=1;
	ENLF=0;
	ENRF=0;
	ENRB=1;
	
	PWMLB=7200-72*v;
	PWMLF=72*v;
	PWMRF=(int)(0.72*v*pwm);
	PWMRB=7200-(int)(0.72*v*pwm);
}

void Stop(void){
	ENLB=1;
	ENLF=0;
	ENRF=0;
	ENRB=1;
	
	PWMLB=7200;
	PWMLF=0;
	PWMRF=0;
	PWMRB=7200;
}

//
void VerticalR(int v){
	ENLB=0;//re
	ENLF=0;
	ENRF=1;//re
	ENRB=1;
	
	PWMLB=72*v;
	PWMLF=72*v;
	PWMRF=7200-72*v;
	PWMRB=7200-72*v;
}
void VerticalRRight(int v,int pwm){
	ENLB=0;//re
	ENLF=0;
	ENRF=1;//re
	ENRB=1;
	
	PWMLB=(int)(0.72*v*pwm);
	PWMLF=72*v;
	PWMRF=7200-72*v;
	PWMRB=7200-(int)(0.72*v*pwm);
}
void VerticalRLeft(int v,int pwm){
	ENLB=0;//re
	ENLF=0;
	ENRF=1;//re
	ENRB=1;
	
	PWMLB=72*v;
	PWMLF=(int)(0.72*v*pwm);
	PWMRF=7200-(int)(0.72*v*pwm);
	PWMRB=7200-72*v;
}

void VerticalL(int v){
	ENLB=1;
	ENLF=1;//re
	ENRF=0;
	ENRB=0;//re
	
	PWMLB=7200-72*v;
	PWMLF=7200-72*v;
	PWMRF=72*v;
	PWMRB=72*v;
}
void VerticalLRight(int v,int pwm){
	ENLB=1;
	ENLF=1;//re
	ENRF=0;
	ENRB=0;//re
	
	PWMLB=7200-72*v;
	PWMLF=7200-(int)(0.72*v*pwm);
	PWMRF=(int)(0.72*v*pwm);
	PWMRB=72*v;
}
void VerticalLLeft(int v,int pwm){
	ENLB=1;
	ENLF=1;//re
	ENRF=0;
	ENRB=0;//re
	
	PWMLB=7200-(int)(0.72*v*pwm);
	PWMLF=7200-72*v;
	PWMRF=72*v;
	PWMRB=(int)(0.72*v*pwm);
}

void test(int a,int b, int c,int d){
	PWMLB=a;
	PWMLF=b;
	PWMRF=c;
	PWMRB=d;
}
void test_en(int a,int b, int c,int d){
	ENLB=a;
	ENLF=b;
	ENRF=c;
	ENRB=d;
	//test(100,100,100,100);
}

