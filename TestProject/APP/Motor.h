#ifndef _Motor_H
#define _Motor_H

//the motor interface is defined 
/*
Left:

ain1--PA0
ain2--PA1
PWM --PA2

Right
bin1--PA3
bin2--PA4
PWM --PA5

stby--PA6
*/

#include "system.h"

void InitGPIO_Motor(void);

void GO(void);

void Stop(void);

void Back(void);

void left(void);

void right(void);
#endif
