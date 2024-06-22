#include "exti.h"
#include "run.h"

/*///////////////////////////////////////////////////////////////////////////////
外部中断用来控制左右侧的光电传感器
///////////////////////////////////////////////////////////////////////////////*/
/*****
4月25新加
******/
int R_r = 0;	// 用来判断在主函数里面是否要浇水,右
int L_l = 0;	// 用来判断在主函数里面是否要浇水，左
int Flag_L = 0; // 用来判断是左边算左激光测试后舵机所抬角度
int Flag_R = 0;
int left_water_flag = 0, right_water_flag = 0; // water start flag

//////////////////////////
// void PE_EXTI_Init(void) // for cross_cnt = 2/4/6
// {
// 	static u8 temp_water_cnt = 0;
// 	NVIC_InitTypeDef NVIC_InitStructure;
// 	EXTI_InitTypeDef EXTI_InitStructure;

// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); // 使能SYSCFG时钟,在用到外部中断时一定要用到

// 	photoelectric_GPIO_Init();

// 	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource10);
// 	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource11);
// 	EXTI_DeInit();

// 	if (water_finish()) // D区前, 浇水计数两侧后PE全开
// 	{
// 		temp_water_cnt = 0;
// 		left_water_flag = 0;
// 		right_water_flag = 0;
// 		EXTI_InitStructure.EXTI_Line = EXTI_Line10 | EXTI_Line11;
// 		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
// 		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
// 		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
// 		EXTI_Init(&EXTI_InitStructure);
// 	}
// 	else
// 	{
// 		if (water_finish_structure.right_water_finish) // 右侧浇水结束后只开左边光电
// 		{
// 			++temp_water_cnt;
// 			right_water_flag = 0;
// 			water_finish_structure.right_water_finish = 0;
// 			EXTI_InitStructure.EXTI_Line = EXTI_Line10;
// 			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
// 			EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
// 			EXTI_InitStructure.EXTI_LineCmd = ENABLE;
// 			EXTI_Init(&EXTI_InitStructure);
// 		}
// 		if (water_finish_structure.left_water_finish) // 左侧浇水后开右侧光电
// 		{
// 			++temp_water_cnt;
// 			left_water_flag = 0;
// 			water_finish_structure.left_water_finish = 0;
// 			EXTI_InitStructure.EXTI_Line = EXTI_Line11;
// 			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
// 			EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
// 			EXTI_InitStructure.EXTI_LineCmd = ENABLE;
// 			EXTI_Init(&EXTI_InitStructure);
// 		}
// 	}

// 	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; // 抢占优先级0
// 	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;		 // 子优先级2
// 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				 // 使能外部中断通道
// 	NVIC_Init(&NVIC_InitStructure);								 // 配置
// }
void PE_EXTI_Init(void) // for cross_cnt = 2/4/6
{
	// static u8 temp_water_cnt = 0;
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); // 使能SYSCFG时钟,在用到外部中断时一定要用到

	photoelectric_GPIO_Init();

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource10);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource11);
	EXTI_DeInit();

	// temp_water_cnt = 0;
	// left_water_flag = 0;
	// right_water_flag = 0;
	EXTI_InitStructure.EXTI_Line = EXTI_Line10 | EXTI_Line11;
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

void PE_EXTI_Close(void)
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

/**
 * @brief  在中断里给浇水标志位
 *
 * A/B区两侧对称，A看左，B看右
 * C/D区两侧不对称，两边都要看
 * @param    None
 * @return   None
 */
void EXTI15_10_IRQHandler(void)
{
	if ((EXTI_GetITStatus(EXTI_Line11) == SET) || (EXTI_GetITStatus(EXTI_Line10) == SET))
	{
		if (region == A) // A
		{
			if (EXTI_GetITStatus(EXTI_Line10) == SET) // left hand side
			{
				//				delay_ms(50);
				TIM7_Close();
				Car_stop();
				// gyro_USART_Close();

				delay_ms(50);
				left_water_flag = 1;
				right_water_flag = 1;
				// EXTI_ClearITPendingBit(EXTI_Line10);
				// EXTI_ClearITPendingBit(EXTI_Line11);
				PE_EXTI_Close();
			}
		}
		else if (region == B) // B
		{
			if (EXTI_GetITStatus(EXTI_Line11) == SET) // right hand side
			{
				TIM7_Close();
				Car_stop();
				// gyro_USART_Close();
				delay_ms(50);
				left_water_flag = 1;
				right_water_flag = 1;
				// EXTI_ClearITPendingBit(EXTI_Line10);
				// EXTI_ClearITPendingBit(EXTI_Line11);
				PE_EXTI_Close();
			}
		}
		else if ((region == C || region == D)) // C / D
		{
			TIM7_Close();
			Car_stop();
			// gyro_USART_Close();
			delay_ms(50);
			if ((EXTI_GetITStatus(EXTI_Line11) == SET) && (EXTI_GetITStatus(EXTI_Line10) == SET))
			{
				left_water_flag = 1;
				right_water_flag = 1;
				// EXTI_ClearITPendingBit(EXTI_Line11);
				// EXTI_ClearITPendingBit(EXTI_Line10);
				PE_EXTI_Close();
			}
			else if ((EXTI_GetITStatus(EXTI_Line11) == SET) && (EXTI_GetITStatus(EXTI_Line10) == RESET))
			{
				right_water_flag = 1;
				// EXTI_ClearITPendingBit(EXTI_Line11);
				PE_EXTI_Close();
			}
			else if ((EXTI_GetITStatus(EXTI_Line11) == RESET) && (EXTI_GetITStatus(EXTI_Line10) == SET))
			{
				left_water_flag = 1;
				// EXTI_ClearITPendingBit(EXTI_Line10);
				PE_EXTI_Close();
			}
		}
		// else
		// {
		// 	EXTI_ClearITPendingBit(EXTI_Line10);
		// 	EXTI_ClearITPendingBit(EXTI_Line11);
		// 	//
		// }
		EXTI_ClearITPendingBit(EXTI_Line10);
		EXTI_ClearITPendingBit(EXTI_Line11);
		//			BEEP=1;
	}
	//	}
	//	LED2=1;
	//	LED1=0;

	// err++;
	// if (err >= 200)
	// {
	// 	delay_ms(300);
	// }
}

// void EXTI9_5_IRQHandler(void)
//{
//	if ((EXTI_GetITStatus(EXTI_Line5 | EXTI_Line6 | EXTI_Line7 | EXTI_Line8 | EXTI_Line9) == SET))
//	{
//		if (Flower_Count >= 50)
//		{
//			EXTI_ClearITPendingBit(EXTI_Line5 | EXTI_Line6 | EXTI_Line7 | EXTI_Line8 | EXTI_Line9);
//			TIM7_Close();
//			NVIC_Configuration_Close();
//			Car_stop();
//			k++; // k反复为0，1两值
//			N_Flag++;
//			delay_ms(1000);
//		}
//		else
//		{
//			// 会导致从刚开始到第一个花盆之间矫正不存在
//			EXTI_ClearITPendingBit(EXTI_Line5 | EXTI_Line6 | EXTI_Line7 | EXTI_Line8 | EXTI_Line9);
//			Car_Load(100, 100);
//			set = 1;
//			//			delay_ms(200);
//			//			set=1;
//		}
//	}
// }
// void EXTI9_5_IRQHandler(void)
//{
//	if ((EXTI_GetITStatus(EXTI_Line5 | EXTI_Line6 | EXTI_Line7 | EXTI_Line8 | EXTI_Line9) == SET))
//	{
//		EXTI_ClearITPendingBit(EXTI_Line5 | EXTI_Line6 | EXTI_Line7 | EXTI_Line8 | EXTI_Line9);
//	}
// }
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
