#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "sys.h"
/**************************************************************************
	������ƺ꣺һ·PWM��������������������������ͬ���Ҳ�����Ҳ��ͬ
**************************************************************************/
/*---------------------- MOTOR_MOVE--------------------*/

void Motor_Init(void);

// void Limit(int PWM_Max,int PWM_Min,int* PWM_OUt_L,int* PWM_OUt_R);
// float Abs(float m);
// float Max(float m,float n);
// float Min(float m,float n);
void Car_Load(int L, int R);
void Car_stop(void);
// void Turn_Left_90_Angles(void);
// void Turn_Right_90_Angles(void);
// void Protect(void);

#endif
