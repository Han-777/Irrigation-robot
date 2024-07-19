#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "MPU6050.h"

void TIM3_Init(u16 arr, u16 psc);
void TIM2_Init(u16 arr, u16 psc);
extern float Pitch,Roll,Yaw;

#endif
