#ifndef _Bluetooth_H
#define _Bluetooth_H
/*
Circuit connection mode
use USART1

STM32     HC-05
PA09 TX   RX
PB10 RX   TX

VCC 5V    5V
GND       GND
*/

#include "system.h"

void InitBluetooth(void);

#endif
