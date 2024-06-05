#include "motor.h"

void Motor_Init(void)
{
	MOTOR_GPIO_Init();
	// freq (18k ~ 60k) = 84M / arr(50) / psc(84)
	// 最小脉冲宽度： 2us
	TIM4_PWM_Init(100 - 1, 42 - 1); // 84M / 84 / 50 = 20k
//	TIM4_PWM_Init(4200 - 1, 1 - 1); // 84M / 84 / 50 = 20k

}

float Abs(float m)
{
	float M;
	if (m >= 0)
	{
		M = m;
	}
	if (m < 0)
	{
		M = -m;
	}
	return M;
}

float Max(float m, float n)
{
	if (m >= n)
	{
		return m;
	}
	else if (m <= n)
	{
		return n;
	}
}

float Min(float m, float n)
{
	if (m <= n)
	{
		return m;
	}
	else if (m >= n)
	{
		return n;
	}
}

void Limit(int PWM_Max, int PWM_Min, int *PWM_OUt_L, int *PWM_OUt_R)
{
	int PWM_Max_Limit = 85; // 电机转到最小的PWM
	int PWM_Min_Limit = -85;
	if (*PWM_OUt_L >= PWM_Max)
	{
		*PWM_OUt_L = PWM_Max;
	}
	if (*PWM_OUt_L < PWM_Min)
	{
		*PWM_OUt_L = PWM_Min;
	}
	if (*PWM_OUt_R >= PWM_Max)
	{
		*PWM_OUt_R = PWM_Max;
	}
	if (*PWM_OUt_R < PWM_Min)
	{
		*PWM_OUt_R = PWM_Min;
	}
	//	if((*PWM_OUt_L)>=0&&(*PWM_OUt_L)<=PWM_Max_Limit)
	//	{
	//		*PWM_OUt_L=PWM_Max_Limit;
	//	}
	//	if((*PWM_OUt_R)>=0&&(*PWM_OUt_R)<=PWM_Max_Limit)
	//	{
	//		*PWM_OUt_R=PWM_Max_Limit;
	//	}
	//	if((*PWM_OUt_L)<0&&(*PWM_OUt_L)>=PWM_Min_Limit)
	//	{
	//		*PWM_OUt_L=PWM_Min_Limit;
	//	}
	//	if((*PWM_OUt_R)<0&&(*PWM_OUt_R)>=PWM_Min_Limit)
	//	{
	//		*PWM_OUt_R=PWM_Min_Limit;
	//	}
}

 void Car_Load(int L, int R)
 {
 	if (L > 0)
 	{
 		LIN1 = 1, LIN2 = 0; // 正转
 	}
 	if (L <= 0)
 	{
 		LIN1 = 0, LIN2 = 1; // 反转
 	}
 	if (R > 0)
 	{
 		RIN1 = 1, RIN2 = 0;
 	}
 	if (R <= 0)
 	{
 		RIN1 = 0, RIN2 = 1;
 	}
 	// TIM_SetCompare2(TIM4,Abs(L));//左轮
 	// TIM_SetCompare1(TIM4,Abs(R));//右轮
 	// MOTORL_COMPARE(Abs(L));
 	// MOTORR_COMPARE(Abs(R));
 	PWML = Abs(L);
 	PWMR = Abs(R);
 }

void Car_stop(void)
{
	LIN1=0;
	LIN2=0;
	TIM_SetCompare1(TIM4, 0);
	RIN1=0;
	RIN2=0;
	TIM_SetCompare2(TIM4, 0);
}
void Turn_Left_90_Angles(void)
{
	Car_Load(35, -35);
	delay_ms(100);
}
void Turn_Right_90_Angles(void)
{
	Car_Load(-35, 35);
	delay_ms(100);
}

// void Protect(void)  // ?
//{
//	if(((-Read_Speed(ENCODER2_TIM))<0)&&((Read_Speed(ENCODER1_TIM))<0))
////	if((Abs(-Read_Speed(3))>=105)&&(Abs(Read_Speed(2))>=105)&&set==1)
//		{
//			TIM7_Close();
////			EXTI_10_11_Close();
//			Car_stop();
//			LED1=0;
//			LED2=0;
//			delay_ms(100);
////			EXTInterruppt_Mode();
////			NVIC_Configuration();
//			TIM7_Int_Init(1000-1,840-1);//10ms进入一次中断
////			k=0;
//		}
//}