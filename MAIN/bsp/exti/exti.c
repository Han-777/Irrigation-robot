#include "exti.h"
/*///////////////////////////////////////////////////////////////////////////////
�ⲿ�ж������������Ҳ�Ĺ�紫����
///////////////////////////////////////////////////////////////////////////////*/
/*****
4��25�¼�
******/
void EXTInterruppt_Mode(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); // ʹ��SYSCFGʱ��,���õ��ⲿ�ж�ʱһ��Ҫ�õ�

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource10); // ���
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource11); // ���
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
	// ���
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; // ��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;		 // �����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				 // ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);								 // ����
																 // ��
}
void NVIC_Configuration_Close(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, DISABLE); // ʹ��SYSCFGʱ��,���õ��ⲿ�ж�ʱһ��Ҫ�õ�

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

	// ���
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; // ��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;		 // �����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;			 // ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);								 // ����
																 // ��
}
//////////////////////////
void EXTIX_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); // ʹ��SYSCFGʱ��,���õ��ⲿ�ж�ʱһ��Ҫ�õ�

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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; // ��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;		 // �����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				 // ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);								 // ����
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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; // ��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;		 // �����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;			 // ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);								 // ����
}

// int Flower_Count=0;//��һ�໨����
int R_r = 0;	// �����ж��������������Ƿ�Ҫ��ˮ,��
int L_l = 0;	// �����ж��������������Ƿ�Ҫ��ˮ����
int Flag_L = 0; // �����ж���������󼤹���Ժ�����̧�Ƕ�
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
//			k++;//k����Ϊ0��1��ֵ
//			N_Flag++;
//			delay_ms(1000);
//		}
//		else
//		{
//			//�ᵼ�´Ӹտ�ʼ����һ������֮�����������
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
