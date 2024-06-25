#include "tim.h"
#include "gyro.h"
/**************************************************************************
		TIM2-TIM5��ͨ�ã�,TIM12-14(ͨ��), TIM6, 7��������:APB1 42MHz, APBԤ��ƵΪ1:42MHz, ��Ϊ1: 84MHz
		TIM1,8���߼���,9,10,11��ͨ�ã�: APB2 84MHz, ��Ƶ��Ϊ1: 168Hz
***************************************************************************/

/**************************************************************************
							TIM 7
**************************************************************************/

// ��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
// Ft=84M��ʱ������Ƶ��,��λ:Mhz
void TIM7_Init(u16 arr, u16 psc)
{
	//	// gyro init
	//	if (!gyro_init_flag)
	//	{
	//		GYRO_Init();
	//		// PE_EXTI_Init();
	//	}

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStructure);

	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM7, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; // ��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;		 // �����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIMM7_Open(void)
{
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM7, ENABLE);
}
void TIM7_Close(void)
{
	// TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	// NVIC_InitTypeDef NVIC_InitStructure;

	// RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, DISABLE);

	TIM_ITConfig(TIM7, TIM_IT_Update, DISABLE);
	TIM_Cmd(TIM7, DISABLE);

	// NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; // ��ռ���ȼ�1
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;		 // �����ȼ�3
	// NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	// NVIC_Init(&NVIC_InitStructure);
}

// void TIM7_IRQHandler(void)
// {
// 	if (TIM_GetITStatus(TIM7,TIM_IT_Update)==SET)
// 	{

// 	}
// 	TIM_ClearITPendingBit(TIM7,TIM_IT_Update);

// }

/**************************************************************************
							Motor PWM TIM4
**************************************************************************/
void TIM4_PWM_Init(u32 arr, u32 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_AHB1PeriphClockCmd(MOTORL_PWM_PIN_CLK, ENABLE); // GPIO
	// RCC_AHB1PeriphClockCmd(MOTORR_PWM_PIN_CLK, ENABLE);

	RCC_APB1PeriphClockCmd(MOTORL_PWM_TIM_CLK, ENABLE); // TIM4
	// RCC_APB1PeriphClockCmd(MOTORR_PWM_TIM_CLK, ENABLE);

	GPIO_PinAFConfig(MOTORL_PWM_PORT, MOTORL_PWM_SOURCE, MOTORL_PWM_AF);
	GPIO_PinAFConfig(MOTORR_PWM_PORT, MOTORR_PWM_SOURCE, MOTORR_PWM_AF);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_InitStruct.GPIO_Pin = MOTORL_PWM_PIN | MOTORR_PWM_PIN;
	GPIO_Init(MOTORL_PWM_PORT, &GPIO_InitStruct);
	// GPIO_Init(MOTORR_PWM_PORT, &GPIO_InitStruct);

	TIM_DeInit(MOTORL_PWM_TIM);
	TIM_DeInit(MOTORR_PWM_TIM);
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; // ���벶��ķ�Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; // �ظ�����(�߼���ʱ��)
	TIM_TimeBaseInit(MOTORL_PWM_TIM, &TIM_TimeBaseInitStructure);
	TIM_TimeBaseInit(MOTORR_PWM_TIM, &TIM_TimeBaseInitStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 0;

	MOTORL_PWM_OC_INIT(&TIM_OCInitStructure);
	MOTORR_PWM_OC_INIT(&TIM_OCInitStructure);
	MOTORL_PWM_OC_PRELOAD_CFIG();
	MOTORR_PWM_OC_PRELOAD_CFIG(); // preload, only write in but it will not work without ARRP

	TIM_ARRPreloadConfig(MOTORL_PWM_TIM, ENABLE); // shadow risistor, ��һ����ͬ������
	TIM_ARRPreloadConfig(MOTORR_PWM_TIM, ENABLE);

	TIM_Cmd(MOTORL_PWM_TIM, ENABLE);
	TIM_Cmd(MOTORR_PWM_TIM, ENABLE);
}

/**************************************************************************
			Encoder1 TIM2 (left)  /  Encoder TIM3 (right)
**************************************************************************/
void Encoder1_TIM_Init(void) // Left
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	//	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(ENCODER1_PIN_CLK, ENABLE); // ����ʱ��
	RCC_APB1PeriphClockCmd(ENCODER1_TIM_CLK, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = ENCODER1_PIN_1 | ENCODER1_PIN_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(ENCODER1_PORT_1, &GPIO_InitStruct);

	GPIO_PinAFConfig(ENCODER1_PORT_1, ENCODER1_SOURCE_1, ENCODER1_AF);
	GPIO_PinAFConfig(ENCODER1_PORT_2, ENCODER1_SOURCE_2, ENCODER1_AF);

	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct); // ��ʼ����ʱ����
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 65536 - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 1 - 1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_ICFilter = 0x10;
	TIM_ICInit(ENCODER1_TIM, &TIM_ICInitStruct);

	TIM_EncoderInterfaceConfig(ENCODER1_TIM, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); // ���ñ�����ģʽ

	TIM_SetCounter(ENCODER1_TIM, 0); // ���㶨ʱ������ֵ
	TIM_ClearFlag(ENCODER1_TIM, TIM_FLAG_Update);
	TIM_ITConfig(ENCODER1_TIM, TIM_IT_Update, ENABLE); // ������������жϱ�־λ
	TIM_Cmd(ENCODER1_TIM, ENABLE);					   // ������ʱ��
}

void Encoder2_TIM_Init(void) // Right
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	//	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(ENCODER2_PIN_CLK, ENABLE); // ����ʱ��
	RCC_APB1PeriphClockCmd(ENCODER2_TIM_CLK, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = ENCODER2_PIN_1 | ENCODER2_PIN_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(ENCODER2_PORT_1, &GPIO_InitStruct);

	GPIO_PinAFConfig(ENCODER2_PORT_1, ENCODER2_SOURCE_1, ENCODER2_AF);
	GPIO_PinAFConfig(ENCODER2_PORT_2, ENCODER2_SOURCE_2, ENCODER2_AF);

	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct); // ��ʼ����ʱ����
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 65536 - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 1 - 1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_ICFilter = 0x10;
	TIM_ICInit(ENCODER2_TIM, &TIM_ICInitStruct);

	TIM_EncoderInterfaceConfig(ENCODER2_TIM, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); // ���ñ�����ģʽ

	TIM_SetCounter(ENCODER2_TIM, 0); // ���㶨ʱ������ֵ
	TIM_ClearFlag(ENCODER2_TIM, TIM_FLAG_Update);
	TIM_ITConfig(ENCODER2_TIM, TIM_IT_Update, ENABLE); // ������������жϱ�־λ
	TIM_Cmd(ENCODER2_TIM, ENABLE);					   // ������ʱ��
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(ENCODER1_TIM, TIM_IT_Update) != 0)
	{
		TIM_ClearITPendingBit(ENCODER1_TIM, TIM_IT_Update);
	}
}

void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(ENCODER2_TIM, TIM_IT_Update) != 0)
	{
		TIM_ClearITPendingBit(ENCODER2_TIM, TIM_IT_Update);
	}
}

/**************************************************************************
							Servo TIM13 / TIM4
**************************************************************************/
void Servo_Pitch_PWM_Init(u32 arr, int psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	// APB2 168MHZ
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource8, GPIO_AF_TIM13);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;		   // GPIOFC
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	   // ���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // �ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	   // ���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	   // ����
	GPIO_Init(GPIOF, &GPIO_InitStructure);			   // ��ʼ��PA6

	TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;				// ��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period = arr - 1;					// �Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInit(TIM13, &TIM_TimeBaseStructure); // ��ʼ����ʱ��

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;			  // ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1,TIMx_CNT<TMX_CCR1��ʱͨ��Ϊ��Ч��ƽ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // �Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	  // �������:TIM����Ƚϼ��Ե�,�͵�ƽ��Ч
	TIM_OC1Init(TIM13, &TIM_OCInitStructure);					  // ����Tָ���Ĳ�����ʼ������TIM1 4OC1
	TIM_OC1PreloadConfig(TIM13, TIM_OCPreload_Enable);			  // ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ��� !!!!!!!!!!!!!!!!!!!!!

	TIM_ARRPreloadConfig(TIM13, ENABLE); // ARPEʹ��
	TIM_Cmd(TIM13, ENABLE);				 // ʹ��TIM3
}

void Servo_Yaw_PWM_Init(u32 arr, int psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE); // 84M
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM14); // GPIOA6����Ϊ��ʱ��3

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;		   // GPIOFC
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	   // ���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // �ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	   // ���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	   // ����
	GPIO_Init(GPIOA, &GPIO_InitStructure);			   // ��ʼ��PA6

	TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;				// ��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period = arr - 1;					// �Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure); // ��ʼ����ʱ��3

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;			  // ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1,TIMx_CNT<TMX_CCR1��ʱͨ��Ϊ��Ч��ƽ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // �Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	  // �������:TIM����Ƚϼ��Ե�,�͵�ƽ��Ч
	TIM_OC1Init(TIM14, &TIM_OCInitStructure);					  // ����Tָ���Ĳ�����ʼ������TIM1 4OC1
	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);			  // ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ��� !!!!!!!!!!!!!!!!!!!!!

	TIM_ARRPreloadConfig(TIM14, ENABLE); // ARPEʹ��
	TIM_Cmd(TIM14, ENABLE);				 // ʹ��TIM3
}