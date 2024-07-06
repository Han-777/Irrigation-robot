#ifndef __PHOTOELECTRIC__H
#define __PHOTOELECTRIC__H

#include "sys.h"
// void photoelectric_Control(void);

#define PE_LEFT LL_GPIO_IsInputPinSet(GPIOG, LL_GPIO_PIN_10)
#define PE_RIGHT LL_GPIO_IsInputPinSet(GPIOG, LL_GPIO_PIN_11)
#define PE_NOZZLE LL_GPIO_IsInputPinSet(GPIOD, LL_GPIO_PIN_3) // // ÅçÍ·¹âµç

#endif
