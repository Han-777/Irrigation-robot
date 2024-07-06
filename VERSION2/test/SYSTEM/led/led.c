#include "led.h"
void LED_Init(void)
{
	
	LL_GPIO_InitTypeDef GPIO_InitStruct;
	
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF|LL_AHB1_GRP1_PERIPH_GPIOG);
	
	GPIO_InitStruct.Mode=LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.OutputType=LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pin=LL_GPIO_PIN_9|LL_GPIO_PIN_10;
	GPIO_InitStruct.Pull=LL_GPIO_PULL_NO;
	GPIO_InitStruct.Speed=LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	
	GPIO_InitStruct.Mode=LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.OutputType=LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pin=LL_GPIO_PIN_6;
	GPIO_InitStruct.Pull=LL_GPIO_PULL_NO;
	GPIO_InitStruct.Speed=LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOG, &GPIO_InitStruct);
	
	LL_GPIO_SetOutputPin(GPIOG, LL_GPIO_PIN_6);
	LL_GPIO_SetOutputPin(GPIOF, LL_GPIO_PIN_9|LL_GPIO_PIN_10);
}