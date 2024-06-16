#ifndef __ENCODER__H
#define __ENCODER__H

#include "sys.h"

#define LEFT_ENCODER ENCODER1_TIM
#define RIGHT_ENCODER ENCODER2_TIM
// Para: ENCODER1_TIM(left) | ENCODER2_TIM(Rignt)
void Encoder_TIM_Init_All(void);
int Read_Speed(TIM_TypeDef *TIMx);

#endif
