#include "encoder.h"
#include "gray.h"
/*******
�ȼ�������AB��λ��
�����������һ�����žͿ��ԣ�ǰ��ͬ��
*******/

void Encoder_TIM_Init_All(void)
{
	Encoder1_TIM_Init();//Left
	Encoder2_TIM_Init();//Right
}

/**********************
������
�ٶȶ�ȡ����
��ڲ�������ʱ��
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


