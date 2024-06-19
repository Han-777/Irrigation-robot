#ifndef __PHOTOELECTRIC__H
#define __PHOTOELECTRIC__H

#include "sys.h"
void photoelectric_Control(void);

#define PE_LEFT GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_10)
#define PE_RIGHT GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_11)

#endif
