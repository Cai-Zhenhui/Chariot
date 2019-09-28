#ifndef _SteeringEngine_H
#define _SteeringEngine_H

#include "system.h"
#include "SysTick.h"

void TIM3_CH1_PWM_Init(u16 per,u16 psc);
void InitGPIO_SteeringEngine(void);
void set_stervo_angle(int angle);
#endif
