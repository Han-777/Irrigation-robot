#ifndef __GD__H
#define __GD__H

#include "sys.h"
void GuanDian_Init(void);
void GuanDian_Control(void);
#define Left GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10)
#define Right GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_11)
#endif
