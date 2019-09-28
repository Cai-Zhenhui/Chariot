#ifndef _Usart_H
#define _Usart_H
/*
Circuit connection mode
use USART1

STM32     HC-05
PA09 TX   RX
PA10 RX   TX

VCC 5V    5V
GND       GND
*/

#include "system.h"
extern uint16_t r;// the function USART_ReceiveData() returns a value of type uint16_t
extern u16 value[4];
void USART1_Init(u32 bound);

#endif
