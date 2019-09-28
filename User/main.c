#include "SysTick.h"
#include "Motor.h"

#include "Sensor_inf.h"
#include "SteeringGear.h"

void InitALL()
{
	//Initialize all the configurations here
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	PWM_Init(7199,0);
	
	SteeringGearInit();
}	

void delay_s(int a){
	int i=0;
	for(i=0;i<a;++i){
		delay_ms(1000);
	}
}


int main()
{
	int speed=40;
	int speedback=20;
	int pwm=40;
	InitALL();//Initialize all the configurations
	
	
	delay_s(5);
	while(1)
	{
		
		if((SFL==1)&&(SFR==1)){
			Go(speed);
		}else if((SFL==1)&&(SFR==0)){
			TurnLeft(speed,pwm);
		}else if((SFL==0)&&(SFR==1)){
			TurnRight(speed,pwm);
		}else if(((SFL==0)&&(SFR==0))){
			Go(20);
			delay_ms(200);
			if((SLL==1||SLR==1)){
				;//Vertical left
				while(1){
					if((SLL==1)&&(SLR==1)){
						VerticalL(speed);
					}
					else if((SLL==1)&&(SLR==0)){
						VerticalLLeft(speed,pwm);
					}
					else if((SLL==0)&&(SLR==1)){
						VerticalLRight(speed,pwm);
					}
					else{
						Back(speedback);
					}
				}
			}
			else if((SRL==1)||(SRR==1)){
				;//Vertical right
				while(1){
					if((SRL==1)&&(SRR==1)){
						VerticalR(speed);
					}
					else if((SRL==1)&&(SRR==0)){
						VerticalRLeft(speed,pwm);
					}
					else if((SRL==0)&&(SRR==1)){
						VerticalRRight(speed,pwm);
					}
					else{
						Back(speedback);
					}
				}
			}
			else {
				Back(speedback);
			}
		}
		
		/*
		if ((SRL == 1) && (SRR == 1)) {
			VerticalR(speed);
		}
		else if ((SRL == 1) && (SRR == 0)) {
			VerticalRLeft(speed, 25);
		}
		else if ((SRL == 0) && (SRR == 1)) {
			VerticalRRight(speed, 25);
		}
		else {
			Stop();
		}*/
		
		/*
		TIM_SetCompare1(TIM3,190);
		delay_s(1);
		TIM_SetCompare1(TIM3,185);
		delay_s(1);*/
	}
	return 0;
}
