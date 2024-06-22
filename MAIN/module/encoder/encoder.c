#include "encoder.h"
#include "gray.h"
/*******
先检测编码器AB相位置
左右两边相差一个负号就可以，前后同号
*******/

void Encoder_TIM_Init_All(void)
{
	Encoder1_TIM_Init();//Left
	Encoder2_TIM_Init();//Right
}

/**********************
编码器
速度读取函数
入口参数：定时器
Para: ENCODER1_TIM(right) | ENCODER2_TIM(left)
**********************/
int Read_Speed(TIM_TypeDef* TIMx)
{
	int encoderCount;
	if (TIMx == ENCODER1_TIM)
	{
		encoderCount = ENCODER1_CNT;
		ENCODER1_TIM->CNT = 0;
		return encoderCount;
	}
	else if (TIMx == ENCODER2_TIM)
	{
		encoderCount = ENCODER2_CNT;
		ENCODER2_TIM->CNT = 0;
		return encoderCount;
	}
	else 
	{
		return 0;
	}
}


