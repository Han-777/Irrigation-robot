#include "tim.h"
#include "gyro.h"
/**************************************************************************
		TIM2-TIM5（通用）,TIM12-14(通用), TIM6, 7（基本）:APB1 42MHz, APB预分频为1:42MHz, 不为1: 84MHz
		TIM1,8（高级）,9,10,11（通用）: APB2 84MHz, 分频不为1: 168Hz
***************************************************************************/

/**************************************************************************
							TIM 7
**************************************************************************/

// 定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
// Ft=84M定时器工作频率,单位:Mhz
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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; // 抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;		 // 子优先级3
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
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; // 抢占优先级1
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;		 // 子优先级3
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
	TIM_TimeBaseInitStructure.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1; // 输入捕获的分频
	TIM_TimeBaseInitStructure.CounterMode = LL_TIM_COUNTERMODE_UP;
	TIM_TimeBaseInitStructure.Autoreload = arr;
	TIM_TimeBaseInitStructure.Prescaler = psc;
	TIM_TimeBaseInitStructure.RepetitionCounter = 0; // 重复次数(高级定时器)
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

	LL_TIM_EnableARRPreload(MOTORL_PWM_TIM); // shadow risistor, 下一周期同步更新
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

	LL_AHB1_GRP1_EnableClock(ENCODER1_PIN_CLK); // 开启时钟
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

	LL_TIM_StructInit(&TIM_TimeBaseInitStruct); // 初始化定时器。
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
	LL_TIM_IC_SetPolarity(ENCODER1_TIM, LL_TIM_CHANNEL_CH2, LL_TIM_IC_POLARITY_RISING); // 配置编码器模式

	LL_TIM_SetCounter(ENCODER1_TIM, 0); // 清零定时器计数值
	LL_TIM_ClearFlag_UPDATE(ENCODER1_TIM);
	LL_TIM_EnableIT_UPDATE(ENCODER1_TIM); // 配置溢出更新中断标志位
	LL_TIM_EnableCounter(ENCODER1_TIM);					   // 开启定时器
}

void Encoder2_TIM_Init(void) // Right
{
	LL_GPIO_InitTypeDef GPIO_InitStruct;
	LL_TIM_InitTypeDef TIM_TimeBaseInitStruct;
	LL_TIM_IC_InitTypeDef TIM_ICInitStruct;
	//	NVIC_InitTypeDef NVIC_InitStructure;

	LL_AHB1_GRP1_EnableClock(ENCODER2_PIN_CLK); // 开启时钟
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

	LL_TIM_StructInit(&TIM_TimeBaseInitStruct); // 初始化定时器。
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
	LL_TIM_IC_SetPolarity(ENCODER2_TIM, LL_TIM_CHANNEL_CH2, LL_TIM_IC_POLARITY_RISING); // 配置编码器模式

	LL_TIM_SetCounter(ENCODER2_TIM, 0); // 清零定时器计数值
	LL_TIM_ClearFlag_UPDATE(ENCODER2_TIM);
	LL_TIM_EnableIT_UPDATE(ENCODER2_TIM); // 配置溢出更新中断标志位
	LL_TIM_EnableCounter(ENCODER2_TIM);					   // 开启定时器
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
	GPIO_InitStructure.Mode = LL_GPIO_MODE_ALTERNATE;	   // 复用功能
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH; // 速度100MHz
	GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;	   // 推挽复用输出
	GPIO_InitStructure.Pull = LL_GPIO_PULL_UP;	   // 上拉
	GPIO_InitStructure.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOF, &GPIO_InitStructure);			   // 初始化PA6

	TIM_TimeBaseStructure.Prescaler = psc - 1;				// 定时器分频
	TIM_TimeBaseStructure.CounterMode = LL_TIM_COUNTERMODE_UP; // 向上计数模式
	TIM_TimeBaseStructure.Autoreload = arr - 1;					// 自动重装载值
	TIM_TimeBaseStructure.ClockDivision = 0;
	LL_TIM_Init(TIM13, &TIM_TimeBaseStructure); // 初始化定时器

	TIM_OCInitStructure.OCMode = LL_TIM_OCMODE_PWM1;			  // 选择定时器模式:TIM脉冲宽度调制模式1,TIMx_CNT<TMX_CCR1是时通道为有效电平
	TIM_OCInitStructure.OCState = LL_TIM_OCSTATE_ENABLE; // 比较输出使能
	TIM_OCInitStructure.OCPolarity = LL_TIM_OCPOLARITY_HIGH;	  // 输出极性:TIM输出比较极性低,低电平有效
	LL_TIM_OC_Init(TIM13, LL_TIM_CHANNEL_CH1, &TIM_OCInitStructure);					  // 根据T指定的参数初始化外设TIM1 4OC1
	LL_TIM_OC_EnablePreload(TIM13, LL_TIM_CHANNEL_CH1);			  // 使能TIM3在CCR1上的预装载寄存器 !!!!!!!!!!!!!!!!!!!!!

	LL_TIM_EnableARRPreload(TIM13); // ARPE使能
	LL_TIM_EnableCounter(TIM13);				 // 使能TIM3
}

void Servo_Yaw_PWM_Init(u32 arr, int psc)
{
	LL_GPIO_InitTypeDef GPIO_InitStructure;
	LL_TIM_InitTypeDef TIM_TimeBaseStructure;
	LL_TIM_OC_InitTypeDef TIM_OCInitStructure;

	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM14); // 84M
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_7, LL_GPIO_AF_9); // GPIOA6复用为定时器3

	GPIO_InitStructure.Pin = LL_GPIO_PIN_7;		   // GPIOFC
	GPIO_InitStructure.Mode = LL_GPIO_MODE_ALTERNATE;	   // 复用功能
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH; // 速度100MHz
	GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;	   // 推挽复用输出
	GPIO_InitStructure.Pull = LL_GPIO_PULL_UP;	   // 上拉
	GPIO_InitStructure.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOA, &GPIO_InitStructure);			   // 初始化PA6

	TIM_TimeBaseStructure.Prescaler = psc - 1;				// 定时器分频
	TIM_TimeBaseStructure.CounterMode = LL_TIM_COUNTERMODE_UP; // 向上计数模式
	TIM_TimeBaseStructure.Autoreload = arr - 1;					// 自动重装载值
	TIM_TimeBaseStructure.ClockDivision = 0;
	LL_TIM_Init(TIM14, &TIM_TimeBaseStructure); // 初始化定时器3

	TIM_OCInitStructure.OCMode = LL_TIM_OCMODE_PWM1;			  // 选择定时器模式:TIM脉冲宽度调制模式1,TIMx_CNT<TMX_CCR1是时通道为有效电平
	TIM_OCInitStructure.OCState = LL_TIM_OCSTATE_ENABLE; // 比较输出使能
	TIM_OCInitStructure.OCPolarity = LL_TIM_OCPOLARITY_HIGH;	  // 输出极性:TIM输出比较极性低,低电平有效
	LL_TIM_OC_Init(TIM14, LL_TIM_CHANNEL_CH1, &TIM_OCInitStructure);					  // 根据T指定的参数初始化外设TIM1 4OC1
	LL_TIM_OC_EnablePreload(TIM14, LL_TIM_CHANNEL_CH1);			  // 使能TIM3在CCR1上的预装载寄存器 !!!!!!!!!!!!!!!!!!!!!

	LL_TIM_EnableARRPreload(TIM14); // ARPE使能
	LL_TIM_EnableCounter(TIM14);				 // 使能TIM3
}