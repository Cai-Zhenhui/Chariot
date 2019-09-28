#include "SysTick.h"
#include "Motor.h"
//#include "Sensor_inf.h"
#include "usart.h"
#include "SteeringEngine.h"
//#include "hwjs.h"

void delay_s(int a){
	int i=0;
	for(i=0;i<a;++i){
		delay_ms(1000);
	}
}
void InitALL()
{
	//Initialize all the configurations here
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	InitGPIO_Motor();
	//InfraredSensor_Init();
	//InitGPIO_SteeringEngine();
	TIM3_CH1_PWM_Init(200,7199);
	
	
	//Hwjs_Init();
	//USART1_Init(9600);//9600 will error
}	

int main()
{
	//unsigned char flag_start=0;
	u16 i=0;
	InitALL();//Initialize all the configurations
	
	while(1)
	{
		for(i=5;i<15;++i){
			TIM2->CCR1=i;
			TIM2->CCR2=i;
			TIM2->CCR3=i;
			TIM2->CCR4=i;
			delay_ms(500);
		}
		//delay_s(3);
		
	}
	
	
	
	return 0;
}
