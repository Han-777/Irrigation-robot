#ifndef __ENCODER__H
#define __ENCODER__H

#include "sys.h"

// Para: ENCODER1_TIM(left) | ENCODER2_TIM(Rignt)
extern int vec[2];
void Encoder_TIM_Init_All(void);
int Read_Speed(TIM_TypeDef* TIMx);

#endif
