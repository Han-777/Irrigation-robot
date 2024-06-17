#ifndef __PHOTOELECTRIC__H
#define __PHOTOELECTRIC__H

#include "sys.h"
void photoelectric_Control(void);

#define Left GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_10)
#define Right GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_11)

#endif
