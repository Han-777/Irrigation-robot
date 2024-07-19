#include "exti.h"
#include "run.h"

/*///////////////////////////////////////////////////////////////////////////////
�ⲿ�ж������������Ҳ�Ĺ�紫����
///////////////////////////////////////////////////////////////////////////////*/
/*****
4��25�¼�
******/
// int R_r = 0;	// �����ж��������������Ƿ�Ҫ��ˮ,��
// int L_l = 0;	// �����ж��������������Ƿ�Ҫ��ˮ����
// int Flag_L = 0; // �����ж���������󼤹���Ժ�����̧�Ƕ�
// int Flag_R = 0;
int left_water_flag = 0, right_water_flag = 0; // water start flag

//////////////////////////
// void PE_EXTI_Init(void) // for cross_cnt = 2/4/6
// {
// 	static u8 temp_water_cnt = 0;
// 	NVIC_InitTypeDef NVIC_InitStructure;
// 	EXTI_InitTypeDef EXTI_InitStructure;

// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); // ʹ��SYSCFGʱ��,���õ��ⲿ�ж�ʱһ��Ҫ�õ�

// 	photoelectric_GPIO_Init();

// 	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource10);
// 	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource11);
// 	EXTI_DeInit();

// 	if (water_finish()) // D��ǰ, ��ˮ���������PEȫ��
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
// 		if (water_finish_structure.right_water_finish) // �Ҳཽˮ������ֻ����߹��
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
// 		if (water_finish_structure.left_water_finish) // ��ཽˮ���Ҳ���
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
// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; // ��ռ���ȼ�0
// 	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;		 // �����ȼ�2
// 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				 // ʹ���ⲿ�ж�ͨ��
// 	NVIC_Init(&NVIC_InitStructure);								 // ����
// }
void PE_EXTI_Open(void)
{
	LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_10);
	LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_11);
	EXTI->IMR |= (LL_EXTI_LINE_10 | LL_EXTI_LINE_11); // ʹ��EXTI10��EXTI11�ж�
}
void PE_EXTI_Init(void) // for cross_cnt = 2/4/6
{
	// static u8 temp_water_cnt = 0;
	NVIC_InitTypeDef NVIC_InitStructure;
	LL_EXTI_InitTypeDef EXTI_InitStructure;

	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG); // ʹ��SYSCFGʱ��,���õ��ⲿ�ж�ʱһ��Ҫ�õ�

	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTG, LL_SYSCFG_EXTI_LINE10);
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTG, LL_SYSCFG_EXTI_LINE11);
	LL_EXTI_DeInit();

	// temp_water_cnt = 0;
	// left_water_flag = 0;
	// right_water_flag = 0;
	EXTI_InitStructure.Line_0_31 = LL_EXTI_LINE_10 | LL_EXTI_LINE_11;
	EXTI_InitStructure.Mode = LL_EXTI_MODE_IT;
	EXTI_InitStructure.Trigger = LL_EXTI_TRIGGER_FALLING;
	EXTI_InitStructure.LineCommand = ENABLE;
	LL_EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; // ��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;		 // �����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				 // ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);								 // ����
}

void PE_EXTI_Close(void)
{
	// NVIC_InitTypeDef NVIC_InitStructure;
	// EXTI_InitTypeDef EXTI_InitStructure;

	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, DISABLE);
	// SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource10);
	// SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource11);
	// EXTI_DeInit();

	// EXTI_InitStructure.EXTI_Line = EXTI_Line10 | EXTI_Line11;
	// EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	// EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	// EXTI_InitStructure.EXTI_LineCmd = DISABLE;
	// EXTI_Init(&EXTI_InitStructure);

	// NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; // ��ռ���ȼ�0
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;		 // �����ȼ�2
	// NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;			 // ʹ���ⲿ�ж�ͨ��
	// NVIC_Init(&NVIC_InitStructure);								 // ����
	LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_10);
	LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_11);
	EXTI->IMR &= ~(LL_EXTI_LINE_10 | LL_EXTI_LINE_11); // ʧ��EXTI10��EXTI11�ж�
}

/**
 * @brief  ���ж������ˮ��־λ
 *
 * A/B������Գƣ�A����B����
 * C/D�����಻�Գƣ����߶�Ҫ��
 * @param    None
 * @return   None
 */
void EXTI15_10_IRQHandler(void)
{
	if ((LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_11) == SET) || (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_10) == SET))
	{
		if (region == A) // A
		{
			if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_10) == SET) // left hand side
			{
				movement_stop();
				left_water_flag = 1;
				right_water_flag = 1;
			}
		}
		else if (region == B) // B
		{
			if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_11) == SET) // right hand side
			{
				// TIM7_Close();
				movement_stop();
				left_water_flag = 1;
				right_water_flag = 1;
			}
		}
		else if ((region == C || region == D)) // C / D
		{
			if ((LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_11) == SET) && (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_10) == SET))
			{
				movement_stop();
				left_water_flag = 1;
				right_water_flag = 1;
			}
			else if ((LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_11) == SET) && (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_10) == RESET))
			{
				movement_stop();
				right_water_flag = 1;
			}
			else if ((LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_11) == RESET) && (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_10) == SET))
			{
				movement_stop();
				left_water_flag = 1;
			}
		}
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_10);
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_11);
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
//			k++; // k����Ϊ0��1��ֵ
//			N_Flag++;
//			delay_ms(1000);
//		}
//		else
//		{
//			// �ᵼ�´Ӹտ�ʼ����һ������֮�����������
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
/********����һ************/

/*
1.������ȫ�ԳƵĹ���ͬһ����Ƭ��io�ڶ�ȡ��ƽ
2.ֻ��Ҫһ���ⲿ�жϣ�����һ�߽Ӵ������趼�ᴥ���ж�
3.���ڹ�����Ϸ���������ȫ�ԳƵĹ��1��2
4.�����жϺ��жϣ�������1����������߽�ˮ��2���������ұߣ���������������ͬʱ
�����1��2Ҳ�����ò��ģ����棬�����ӿ��Խ���������⣩
���⣺
1.����������߶�ͬʱ��⵽ʱ�����⣬�������ֻ��һ�߼�⵽������һ��û�м�⵽ʱ�᲻������ж�
*/
/*����һ

*/
/*********������****************/
/*
1.������ȫ�ԳƵĹ��ֱ���ӵ�Ƭ����һ��io�ڶ�ȡ��ƽ
2.������߻��費�Գ���û������
3.������߻���Գƣ�Ҳ�ͷ���һһ�������Ϸ�����һ�����1��2
4.��������ȼ��ߣ���������жϣ����1��⵽������߽�ˮ��2��⵽���ұߣ�����⵽�򶼽�ˮ

*/