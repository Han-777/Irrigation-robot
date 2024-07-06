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

	LL_TIM_InitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7);

	TIM_TimeBaseInitStructure.Autoreload = arr;
	TIM_TimeBaseInitStructure.Prescaler = psc;
	TIM_TimeBaseInitStructure.CounterMode = LL_TIM_COUNTERMODE_UP;
	TIM_TimeBaseInitStructure.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
	LL_TIM_Init(TIM7, &TIM_TimeBaseInitStructure);

	LL_TIM_EnableIT_UPDATE(TIM7);
	LL_TIM_EnableCounter(TIM7);

	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; // ��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;		 // �����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIMM7_Open(void)
{
	LL_TIM_EnableIT_UPDATE(TIM7);
	LL_TIM_EnableCounter(TIM7);
}
void TIM7_Close(void)
{
	// TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	// NVIC_InitTypeDef NVIC_InitStructure;

	// RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, DISABLE);

	LL_TIM_DisableIT_UPDATE(TIM7);
	LL_TIM_DisableCounter(TIM7);

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
	LL_GPIO_InitTypeDef GPIO_InitStruct;
	LL_TIM_InitTypeDef TIM_TimeBaseInitStructure;
	LL_TIM_OC_InitTypeDef TIM_OCInitStructure;

	LL_AHB1_GRP1_EnableClock(MOTORL_PWM_PIN_CLK); // GPIO
	// RCC_AHB1PeriphClockCmd(MOTORR_PWM_PIN_CLK, ENABLE);

	LL_APB1_GRP1_EnableClock(MOTORL_PWM_TIM_CLK); // TIM4
	// RCC_APB1PeriphClockCmd(MOTORR_PWM_TIM_CLK, ENABLE);

	GPIO_PinAFConfig(MOTORL_PWM_PORT, MOTORL_PWM_SOURCE, MOTORL_PWM_AF);
	GPIO_PinAFConfig(MOTORR_PWM_PORT, MOTORR_PWM_SOURCE, MOTORR_PWM_AF);

	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;

	GPIO_InitStruct.Pin = MOTORL_PWM_PIN | MOTORR_PWM_PIN;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(MOTORL_PWM_PORT, &GPIO_InitStruct);
	// GPIO_Init(MOTORR_PWM_PORT, &GPIO_InitStruct);

	LL_TIM_DeInit(MOTORL_PWM_TIM);
	LL_TIM_DeInit(MOTORR_PWM_TIM);
	TIM_TimeBaseInitStructure.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1; // ���벶��ķ�Ƶ
	TIM_TimeBaseInitStructure.CounterMode = LL_TIM_COUNTERMODE_UP;
	TIM_TimeBaseInitStructure.Autoreload = arr;
	TIM_TimeBaseInitStructure.Prescaler = psc;
	TIM_TimeBaseInitStructure.RepetitionCounter = 0; // �ظ�����(�߼���ʱ��)
	LL_TIM_Init(MOTORL_PWM_TIM, &TIM_TimeBaseInitStructure);
	LL_TIM_Init(MOTORR_PWM_TIM, &TIM_TimeBaseInitStructure);

	TIM_OCInitStructure.OCMode = LL_TIM_OCMODE_PWM1;
	TIM_OCInitStructure.OCState = LL_TIM_OCSTATE_ENABLE;
	TIM_OCInitStructure.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
	TIM_OCInitStructure.CompareValue = 0;

	MOTORL_PWM_OC_INIT(&TIM_OCInitStructure);
	MOTORR_PWM_OC_INIT(&TIM_OCInitStructure);
	MOTORL_PWM_OC_PRELOAD_CFIG();
	MOTORR_PWM_OC_PRELOAD_CFIG(); // preload, only write in but it will not work without ARRP

	LL_TIM_EnableARRPreload(MOTORL_PWM_TIM); // shadow risistor, ��һ����ͬ������
	LL_TIM_EnableARRPreload(MOTORR_PWM_TIM);

	LL_TIM_EnableCounter(MOTORL_PWM_TIM);
	LL_TIM_EnableCounter(MOTORR_PWM_TIM);
}

/**************************************************************************
			Encoder1 TIM2 (left)  /  Encoder TIM3 (right)
**************************************************************************/
void Encoder1_TIM_Init(void) // Left
{
	LL_GPIO_InitTypeDef GPIO_InitStruct;
	LL_TIM_InitTypeDef TIM_TimeBaseInitStruct;
	LL_TIM_IC_InitTypeDef TIM_ICInitStruct;
	//	NVIC_InitTypeDef NVIC_InitStructure;

	LL_AHB1_GRP1_EnableClock(ENCODER1_PIN_CLK); // ����ʱ��
	LL_APB1_GRP1_EnableClock(ENCODER1_TIM_CLK);

	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pin = ENCODER1_PIN_1 | ENCODER1_PIN_2;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(ENCODER1_PORT_1, &GPIO_InitStruct);

	GPIO_PinAFConfig(ENCODER1_PORT_1, ENCODER1_SOURCE_1, ENCODER1_AF);
	GPIO_PinAFConfig(ENCODER1_PORT_2, ENCODER1_SOURCE_2, ENCODER1_AF);

	LL_TIM_StructInit(&TIM_TimeBaseInitStruct); // ��ʼ����ʱ����
	TIM_TimeBaseInitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
	TIM_TimeBaseInitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
	TIM_TimeBaseInitStruct.Autoreload = 65536 - 1;
	TIM_TimeBaseInitStruct.Prescaler = 1 - 1;
	TIM_TimeBaseInitStruct.RepetitionCounter = 0;
	LL_TIM_Init(TIM2, &TIM_TimeBaseInitStruct);

	LL_TIM_IC_StructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.ICFilter = 0x10;
	LL_TIM_IC_Init(ENCODER1_TIM, LL_TIM_CHANNEL_CH1, &TIM_ICInitStruct);

	LL_TIM_SetEncoderMode(ENCODER1_TIM, LL_TIM_ENCODERMODE_X4_TI12);
	LL_TIM_IC_SetActiveInput(ENCODER1_TIM, LL_TIM_CHANNEL_CH1, LL_TIM_ACTIVEINPUT_DIRECTTI);
	LL_TIM_IC_SetActiveInput(ENCODER1_TIM, LL_TIM_CHANNEL_CH2, LL_TIM_ACTIVEINPUT_DIRECTTI);
	LL_TIM_IC_SetPolarity(ENCODER1_TIM, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_RISING);
	LL_TIM_IC_SetPolarity(ENCODER1_TIM, LL_TIM_CHANNEL_CH2, LL_TIM_IC_POLARITY_RISING); // ���ñ�����ģʽ

	LL_TIM_SetCounter(ENCODER1_TIM, 0); // ���㶨ʱ������ֵ
	LL_TIM_ClearFlag_UPDATE(ENCODER1_TIM);
	LL_TIM_EnableIT_UPDATE(ENCODER1_TIM); // ������������жϱ�־λ
	LL_TIM_EnableCounter(ENCODER1_TIM);					   // ������ʱ��
}

void Encoder2_TIM_Init(void) // Right
{
	LL_GPIO_InitTypeDef GPIO_InitStruct;
	LL_TIM_InitTypeDef TIM_TimeBaseInitStruct;
	LL_TIM_IC_InitTypeDef TIM_ICInitStruct;
	//	NVIC_InitTypeDef NVIC_InitStructure;

	LL_AHB1_GRP1_EnableClock(ENCODER2_PIN_CLK); // ����ʱ��
	LL_APB1_GRP1_EnableClock(ENCODER2_TIM_CLK);

	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pin = ENCODER2_PIN_1 | ENCODER2_PIN_2;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(ENCODER2_PORT_1, &GPIO_InitStruct);

	GPIO_PinAFConfig(ENCODER2_PORT_1, ENCODER2_SOURCE_1, ENCODER2_AF);
	GPIO_PinAFConfig(ENCODER2_PORT_2, ENCODER2_SOURCE_2, ENCODER2_AF);

	LL_TIM_StructInit(&TIM_TimeBaseInitStruct); // ��ʼ����ʱ����
	TIM_TimeBaseInitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
	TIM_TimeBaseInitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
	TIM_TimeBaseInitStruct.Autoreload = 65536 - 1;
	TIM_TimeBaseInitStruct.Prescaler = 1 - 1;
	TIM_TimeBaseInitStruct.RepetitionCounter = 0;
	LL_TIM_Init(TIM2, &TIM_TimeBaseInitStruct);

	LL_TIM_IC_StructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.ICFilter = 0x10;
	LL_TIM_IC_Init(ENCODER2_TIM, LL_TIM_CHANNEL_CH1, &TIM_ICInitStruct);

	LL_TIM_SetEncoderMode(ENCODER2_TIM, LL_TIM_ENCODERMODE_X4_TI12);
	LL_TIM_IC_SetActiveInput(ENCODER2_TIM, LL_TIM_CHANNEL_CH1, LL_TIM_ACTIVEINPUT_DIRECTTI);
	LL_TIM_IC_SetActiveInput(ENCODER2_TIM, LL_TIM_CHANNEL_CH2, LL_TIM_ACTIVEINPUT_DIRECTTI);
	LL_TIM_IC_SetPolarity(ENCODER2_TIM, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_RISING);
	LL_TIM_IC_SetPolarity(ENCODER2_TIM, LL_TIM_CHANNEL_CH2, LL_TIM_IC_POLARITY_RISING); // ���ñ�����ģʽ

	LL_TIM_SetCounter(ENCODER2_TIM, 0); // ���㶨ʱ������ֵ
	LL_TIM_ClearFlag_UPDATE(ENCODER2_TIM);
	LL_TIM_EnableIT_UPDATE(ENCODER2_TIM); // ������������жϱ�־λ
	LL_TIM_EnableCounter(ENCODER2_TIM);					   // ������ʱ��
}

void TIM2_IRQHandler(void)
{
	if ((LL_TIM_IsActiveFlag_UPDATE(ENCODER1_TIM) && LL_TIM_IsEnabledIT_UPDATE(ENCODER1_TIM)) != 0)
	{
		LL_TIM_ClearFlag_UPDATE(ENCODER1_TIM);
	}
}

void TIM3_IRQHandler(void)
{
	if ((LL_TIM_IsActiveFlag_UPDATE(ENCODER2_TIM) && LL_TIM_IsEnabledIT_UPDATE(ENCODER2_TIM)) != 0)
	{
		LL_TIM_ClearFlag_UPDATE(ENCODER2_TIM);
	}
}

/**************************************************************************
							Servo TIM13 / TIM4
**************************************************************************/
void Servo_Pitch_PWM_Init(u32 arr, int psc)
{
	LL_GPIO_InitTypeDef GPIO_InitStructure;
	LL_TIM_InitTypeDef TIM_TimeBaseStructure;
	LL_TIM_OC_InitTypeDef TIM_OCInitStructure;
	// APB2 168MHZ
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM13);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
	LL_GPIO_SetAFPin_8_15(GPIOF, LL_GPIO_PIN_8, LL_GPIO_AF_9);

	GPIO_InitStructure.Pin = LL_GPIO_PIN_8;		   // GPIOFC
	GPIO_InitStructure.Mode = LL_GPIO_MODE_ALTERNATE;	   // ���ù���
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH; // �ٶ�100MHz
	GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;	   // ���츴�����
	GPIO_InitStructure.Pull = LL_GPIO_PULL_UP;	   // ����
	GPIO_InitStructure.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOF, &GPIO_InitStructure);			   // ��ʼ��PA6

	TIM_TimeBaseStructure.Prescaler = psc - 1;				// ��ʱ����Ƶ
	TIM_TimeBaseStructure.CounterMode = LL_TIM_COUNTERMODE_UP; // ���ϼ���ģʽ
	TIM_TimeBaseStructure.Autoreload = arr - 1;					// �Զ���װ��ֵ
	TIM_TimeBaseStructure.ClockDivision = 0;
	LL_TIM_Init(TIM13, &TIM_TimeBaseStructure); // ��ʼ����ʱ��

	TIM_OCInitStructure.OCMode = LL_TIM_OCMODE_PWM1;			  // ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1,TIMx_CNT<TMX_CCR1��ʱͨ��Ϊ��Ч��ƽ
	TIM_OCInitStructure.OCState = LL_TIM_OCSTATE_ENABLE; // �Ƚ����ʹ��
	TIM_OCInitStructure.OCPolarity = LL_TIM_OCPOLARITY_HIGH;	  // �������:TIM����Ƚϼ��Ե�,�͵�ƽ��Ч
	LL_TIM_OC_Init(TIM13, LL_TIM_CHANNEL_CH1, &TIM_OCInitStructure);					  // ����Tָ���Ĳ�����ʼ������TIM1 4OC1
	LL_TIM_OC_EnablePreload(TIM13, LL_TIM_CHANNEL_CH1);			  // ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ��� !!!!!!!!!!!!!!!!!!!!!

	LL_TIM_EnableARRPreload(TIM13); // ARPEʹ��
	LL_TIM_EnableCounter(TIM13);				 // ʹ��TIM3
}

void Servo_Yaw_PWM_Init(u32 arr, int psc)
{
	LL_GPIO_InitTypeDef GPIO_InitStructure;
	LL_TIM_InitTypeDef TIM_TimeBaseStructure;
	LL_TIM_OC_InitTypeDef TIM_OCInitStructure;

	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM14); // 84M
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_7, LL_GPIO_AF_9); // GPIOA6����Ϊ��ʱ��3

	GPIO_InitStructure.Pin = LL_GPIO_PIN_7;		   // GPIOFC
	GPIO_InitStructure.Mode = LL_GPIO_MODE_ALTERNATE;	   // ���ù���
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH; // �ٶ�100MHz
	GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;	   // ���츴�����
	GPIO_InitStructure.Pull = LL_GPIO_PULL_UP;	   // ����
	GPIO_InitStructure.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOA, &GPIO_InitStructure);			   // ��ʼ��PA6

	TIM_TimeBaseStructure.Prescaler = psc - 1;				// ��ʱ����Ƶ
	TIM_TimeBaseStructure.CounterMode = LL_TIM_COUNTERMODE_UP; // ���ϼ���ģʽ
	TIM_TimeBaseStructure.Autoreload = arr - 1;					// �Զ���װ��ֵ
	TIM_TimeBaseStructure.ClockDivision = 0;
	LL_TIM_Init(TIM14, &TIM_TimeBaseStructure); // ��ʼ����ʱ��3

	TIM_OCInitStructure.OCMode = LL_TIM_OCMODE_PWM1;			  // ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1,TIMx_CNT<TMX_CCR1��ʱͨ��Ϊ��Ч��ƽ
	TIM_OCInitStructure.OCState = LL_TIM_OCSTATE_ENABLE; // �Ƚ����ʹ��
	TIM_OCInitStructure.OCPolarity = LL_TIM_OCPOLARITY_HIGH;	  // �������:TIM����Ƚϼ��Ե�,�͵�ƽ��Ч
	LL_TIM_OC_Init(TIM14, LL_TIM_CHANNEL_CH1, &TIM_OCInitStructure);					  // ����Tָ���Ĳ�����ʼ������TIM1 4OC1
	LL_TIM_OC_EnablePreload(TIM14, LL_TIM_CHANNEL_CH1);			  // ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ��� !!!!!!!!!!!!!!!!!!!!!

	LL_TIM_EnableARRPreload(TIM14); // ARPEʹ��
	LL_TIM_EnableCounter(TIM14);				 // ʹ��TIM3
}