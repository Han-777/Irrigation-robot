#include "exti.h"
/*///////////////////////////////////////////////////////////////////////////////
外部中断用来控制左右侧的光电传感器
///////////////////////////////////////////////////////////////////////////////*/
/*****
4月25新加
******/
void EXTInterruppt_Mode(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); // 使能SYSCFG时钟,在用到外部中断时一定要用到

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource10); // 光电
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource11); // 光电
	EXTI_DeInit();

	gray_GPIO_Init();

	//	GuanDian_Init();
	EXTI_InitStructure.EXTI_Line = EXTI_Line10;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_Init(&EXTI_InitStructure);
}
void EXTI_NVIC_Configuration(void)
{
	EXTInterruppt_Mode();
	NVIC_InitTypeDef NVIC_InitStructure;
	// 光电
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; // 抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;		 // 子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				 // 使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);								 // 配置
																 // 线
}
void NVIC_Configuration_Close(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, DISABLE); // 使能SYSCFG时钟,在用到外部中断时一定要用到

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource10);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource11);
	EXTI_DeInit();

	//	Line_Init();
	//	GuanDian_Init();

	EXTI_InitStructure.EXTI_Line = EXTI_Line10;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
	EXTI_Init(&EXTI_InitStructure);

	// 光电
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; // 抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;		 // 子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;			 // 使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);								 // 配置
																 // 线
}
//////////////////////////
void EXTIX_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); // 使能SYSCFG时钟,在用到外部中断时一定要用到

	//	GuanDian_Init();

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource10);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource11);
	EXTI_DeInit();

	EXTI_InitStructure.EXTI_Line = EXTI_Line10;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; // 抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;		 // 子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				 // 使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);								 // 配置
}
void EXTI_10_11_Close(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, DISABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource10);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource11);
	EXTI_DeInit();

	EXTI_InitStructure.EXTI_Line = EXTI_Line10 | EXTI_Line11;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; // 抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;		 // 子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;			 // 使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);								 // 配置
}

// int Flower_Count=0;//计一侧花盆数
int R_r = 0;	// 用来判断在主函数里面是否要浇水,右
int L_l = 0;	// 用来判断在主函数里面是否要浇水，左
int Flag_L = 0; // 用来判断是左边算左激光测试后舵机所抬角度
int Flag_R = 0;
int err = 0;

// int N_Flag = 0;
// float NEW_Target_Yaw = 0;
// float target_Yaw = 0;
float Err_Set = 90;
// int k=-1;
int k = 0;
// void EXTI15_10_IRQHandler(void)
//{
//	Protect();
//	if ((EXTI_GetITStatus(EXTI_Line11) == SET) || (EXTI_GetITStatus(EXTI_Line10) == SET))
//	{
//		if (N_Flag == 0)
//		{
//			if (EXTI_GetITStatus(EXTI_Line10) == SET)
//			{
//				delay_ms(50);
//				TIM7_Close();
//				Car_stop();
//				delay_ms(50);
//				Flag_L = 1;
//				Flag_R = 1;
//				EXTI_ClearITPendingBit(EXTI_Line10);
//				EXTI_ClearITPendingBit(EXTI_Line11);
//				EXTI_10_11_Close();
//			}
//		}
//		else if (N_Flag == 2)
//		{
//			if (EXTI_GetITStatus(EXTI_Line11) == SET)
//			{
//				TIM7_Close();
//				Car_stop();
//				delay_ms(50);
//				Flag_L = 1;
//				Flag_R = 1;
//				EXTI_ClearITPendingBit(EXTI_Line10);
//				EXTI_ClearITPendingBit(EXTI_Line11);
//				EXTI_10_11_Close();
//			}
//		}
//		else if ((N_Flag >= 3 && N_Flag <= 7))
//		{

//			TIM7_Close();

//			Car_stop();
//			delay_ms(200);
//			if ((EXTI_GetITStatus(EXTI_Line11) == SET) && (EXTI_GetITStatus(EXTI_Line10) == SET))
//			{
//				Flag_R = 1;
//				Flag_L = 1;
//				EXTI_ClearITPendingBit(EXTI_Line11);
//				EXTI_ClearITPendingBit(EXTI_Line10);
//				EXTI_10_11_Close();
//			}
//			else if ((EXTI_GetITStatus(EXTI_Line11) == SET) && (EXTI_GetITStatus(EXTI_Line10) == RESET))
//			{
//				Flag_R = 1;
//				EXTI_ClearITPendingBit(EXTI_Line11);
//				EXTI_10_11_Close();
//			}
//			else if ((EXTI_GetITStatus(EXTI_Line11) == RESET) && (EXTI_GetITStatus(EXTI_Line10) == SET))
//			{
//				Flag_L = 1;
//				EXTI_ClearITPendingBit(EXTI_Line10);
//				EXTI_10_11_Close();
//			}
//		}
//		else
//		{
//			EXTI_ClearITPendingBit(EXTI_Line10);
//			EXTI_ClearITPendingBit(EXTI_Line11);
//			//
//		}
//		EXTI_ClearITPendingBit(EXTI_Line10);
//		EXTI_ClearITPendingBit(EXTI_Line11);
//		//			BEEP=1;
//	}
//	//	}
//	//	LED2=1;
//	//	LED1=0;

//	err++;
//	if (err >= 200)
//	{
//		delay_ms(300);
//	}
//}

// void EXTI9_5_IRQHandler(void)
//{
//	if((EXTI_GetITStatus(EXTI_Line5|EXTI_Line6|EXTI_Line7|EXTI_Line8|EXTI_Line9)==SET))
//	{
//		if(Flower_Count>=50)
//		{
//			EXTI_ClearITPendingBit(EXTI_Line5|EXTI_Line6|EXTI_Line7|EXTI_Line8|EXTI_Line9);
//			TIM7_Close();
//			NVIC_Configuration_Close();
//			Car_stop();
//			k++;//k反复为0，1两值
//			N_Flag++;
//			delay_ms(1000);
//		}
//		else
//		{
//			//会导致从刚开始到第一个花盆之间矫正不存在
//			EXTI_ClearITPendingBit(EXTI_Line5|EXTI_Line6|EXTI_Line7|EXTI_Line8|EXTI_Line9);
//			Car_Load(100,100);
//			set=1;
////			delay_ms(200);
////			set=1;
//		}
//	}
//}
// void EXTI9_5_IRQHandler(void)
//{
//	if((EXTI_GetITStatus(EXTI_Line5|EXTI_Line6|EXTI_Line7|EXTI_Line8|EXTI_Line9)==SET))
//	{
//		EXTI_ClearITPendingBit(EXTI_Line5|EXTI_Line6|EXTI_Line7|EXTI_Line8|EXTI_Line9);
//	}
//}
/********方案一************/

/*
1.两边完全对称的光电接同一个单片机io口读取电平
2.只需要一个外部中断，任意一边接触到花盆都会触发中断
3.再在光电正上方放两个完全对称的光电1，2
4.进入中断后判断，如果光电1触发到则左边浇水，2触发到则右边，都触发到则两边同时
（光电1，2也可以用测距模块代替，这样子可以解决边沿问题）
问题：
1.如果左右两边都同时检测到时无问题，但是如果只有一边检测到，另外一边没有检测到时会不会进入中断
*/
/*方案一

*/
/*********方案二****************/
/*
1.两边完全对称的光电分别各接单片机的一个io口读取电平
2.如果两边花盆不对称则没有问题
3.如果两边花盆对称，也和方案一一样在正上方各放一个光电1，2
4.以左边优先级高，如果进入中断，如果1检测到，则左边浇水，2检测到则右边，都检测到则都浇水

*/
