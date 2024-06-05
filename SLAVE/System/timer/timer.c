#include "timer.h"
/* calculate
Freq = CK_PSC / (PSC + 1) / (ARR + 1) 
Duty = CCR / (ARR + 1)
Reso = 1 / (ARR + 1)

72MHz / 720 / 2000 = 50
*/

/**
 * @brief  4 servo timer initialization
 * 1: 2: 3: 4:
 * @param  arr: auto reload register
 * @param  psc: prescaler
 * @retval None
 */
void TIM3_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	TIM_TimeBaseStructure.TIM_Period = arr;					// auto reload register
	TIM_TimeBaseStructure.TIM_Prescaler = psc;				// prescaler
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // clock division
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1; // TIMx_CNT<TIMx_CCR1Ê±ÓÐÐ§ (when count up mode)
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 0; // duty cycle
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;

	/* enable channel 1 */
	TIM_OC1Init(TIM3, &TIM_OCInitStruct);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	/* enable channel 2 */
	TIM_OC2Init(TIM3, &TIM_OCInitStruct);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	/* enable channel 3 */
	TIM_OC3Init(TIM3, &TIM_OCInitStruct);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	/* enable channel 4 */
	TIM_OC4Init(TIM3, &TIM_OCInitStruct);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM3, ENABLE); 
	TIM_Cmd(TIM3, ENABLE);				
}

/**
 * @brief
 * 1: 2: 3: 4:
 * @param  arr: auto reload register
 * @param  psc: prescaler
 * @retval None
 */

void TIM2_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = arr;					// auto reload register
	TIM_TimeBaseStructure.TIM_Prescaler = psc;				// prescaler
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // clock division
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM2, ENABLE);
}

//void TIM2_IRQHandler()
//{
//	static char times = 0;
//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
//	{
////			Send_data(&Sending_data);
//		if(times%5==0)
//		{
//			Pid_Calculate(pidobject);
//			PWM_Calculate(pidobject);
//		}
//		times++;
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		
//	}
//}
// void PWM_Init(void)
// {
// 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

// 	GPIO_InitTypeDef GPIO_InitStructure;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);

// 	TIM_InternalClockConfig(TIM2);

// 	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
// 	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
// 	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
// 	TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;		//ARR
// 	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;		//PSC
// 	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
// 	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

// 	TIM_OCInitTypeDef TIM_OCInitStructure;
// 	TIM_OCStructInit(&TIM_OCInitStructure);
// 	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
// 	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
// 	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
// 	TIM_OC2Init(TIM2, &TIM_OCInitStructure);

// 	TIM_Cmd(TIM2, ENABLE);
// }

// void PWM_SetCompare2(uint16_t Compare)
// {
// 	TIM_SetCompare2(TIM2, Compare);
// }
