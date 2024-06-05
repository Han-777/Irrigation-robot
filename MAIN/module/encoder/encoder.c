#include "encoder.h"
#include "oled.h"
#include "gray.h"
/*******
先检测编码器AB相位置
左右两边相差一个负号就可以，前后同号
*******/
int vec[2] = {0};

void Encoder_TIM_Init_All(void)
{
	Encoder1_TIM_Init();//Left
	Encoder2_TIM_Init();//Right
}

/**********************
编码器
速度读取函数
入口参数：定时器
Para: ENCODER1_TIM(left) | ENCODER2_TIM(Rignt)
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


void TIM7_IRQHandler(void){
	if(TIM_GetFlagStatus(TIM7, TIM_FLAG_Update) == SET){
		// static int i = 0;
		vec[0] = (u16)Read_Speed(ENCODER1_TIM);
		vec[1] = (u16)Read_Speed(ENCODER2_TIM);
		OLED_ShowNum(1, 9, vec[0], 5);
		OLED_ShowNum(2, 9, vec[1], 5);
//		OLED_ShowNum(3, 1, PE_Left, 5);
//		OLED_ShowNum(4, 1, PE_Right, 5);
		OLED_ShowNum(4, 1, (u16)Get_Count(), 5);
		// i++;
	}
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
}