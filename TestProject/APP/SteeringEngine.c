#include "SteeringEngine.h"
void GPIOInit(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=(GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOC,GPIO_Pin_6|GPIO_Pin_8|GPIO_Pin_10);
	GPIO_ResetBits(GPIOC,GPIO_Pin_7|GPIO_Pin_9|GPIO_Pin_11);
}
void TIM3_CH1_PWM_Init(u16 per,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//GPIOInit();
	
	/* ����ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	/*  ����GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin=(GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//�����������
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);//�ı�ָ���ܽŵ�ӳ��	
	
	TIM_TimeBaseInitStructure.TIM_Period=per;   //�Զ�װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //��Ƶϵ�� 16bit 1-65536
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�������ϼ���ģʽ
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);	
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//?
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC1Init(TIM2,&TIM_OCInitStructure); //����Ƚ�ͨ��1��ʼ��
	TIM_OC2Init(TIM2,&TIM_OCInitStructure);
	TIM_OC3Init(TIM2,&TIM_OCInitStructure);
	TIM_OC4Init(TIM2,&TIM_OCInitStructure);
	
	TIM_CtrlPWMOutputs(TIM2,ENABLE);
	//TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable); //ʹ��TIMx�� CCR1 �ϵ�Ԥװ�ؼĴ���
	TIM_ARRPreloadConfig(TIM2,ENABLE);//ʹ��Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM2,ENABLE); //ʹ�ܶ�ʱ��
		
}

void set_stervo_angle(int angle)
{
	TIM1 -> CCR1 =500+ angle *11.11f;
}
