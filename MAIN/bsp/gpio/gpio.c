#include "gpio.h"

/**************************************************************************
						电机控制初始化GPIO
**************************************************************************/
void MOTOR_GPIO_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd(LIN_GPIO_CLK, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	/*-------------------------LIN_GPIO_CONFIG--------------------------*/

	GPIO_InitStruct.GPIO_Pin = LIN1_GPIO_PIN | LIN2_GPIO_PIN | RIN1_GPIO_PIN | RIN2_GPIO_PIN;
	;
	GPIO_Init(LIN_GPIO_PORT, &GPIO_InitStruct);

	/*-------------------------RIN_GPIO_CONFIG--------------------------*/
	// RCC_AHB1PeriphClockCmd(RIN_GPIO_CLK, ENABLE);

	// GPIO_InitStruct.GPIO_Pin = RIN1_GPIO_PIN | RIN2_GPIO_PIN;
	// GPIO_Init(RIN_GPIO_PORT, &GPIO_InitStruct);
}

/**************************************************************************
						   光电初始化GPIO
**************************************************************************/
void photoelectricity_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOG, &GPIO_InitStruct);
}

/**************************************************************************
						   灰度初始化GPIO
**************************************************************************/

void gray_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOG | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_9 | GPIO_Pin_14;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOG, &GPIO_InitStruct); //

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct); //

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct); //

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOE, &GPIO_InitStruct); //

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_9;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct); //

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStruct); //
}

// //配置光电传感器
// GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3 ;
// GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
// GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
// GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
// GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
// GPIO_Init(GPIOD,&GPIO_InitStructure);
// //配置继电器PB12
// GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
// GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
// GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
// GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
// GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;   //高电平触发
// GPIO_Init(GPIOB,&GPIO_InitStructure);
// GPIO_ResetBits(GPIOB, GPIO_Pin_4);
// //配置继电器PF13
// GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
// GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
// GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
// GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
// GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;   //高电平触发
// GPIO_Init(GPIOB,&GPIO_InitStructure);
// GPIO_ResetBits(GPIOB, GPIO_Pin_12);

/**************************************************************************
						   Key初始化GPIO
**************************************************************************/
void Key_GPIO_Init()
{
	// c4 f11 f15 g1 e8 e13
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG, ENABLE);

	// col
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	// row
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_14;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/**************************************************************************
						   语音播报 初始化GPIO
**************************************************************************/

void voice_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOG,ENABLE);
	GPIO_InitStruct.GPIO_Pin=TX_PIN;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;	
	GPIO_Init(GPIOD,&GPIO_InitStruct);
	GPIO_SetBits(TX_PORT, TX_PIN);	
	
	GPIO_InitStruct.GPIO_Pin=RX_PIN;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;	
	GPIO_Init(GPIOG,&GPIO_InitStruct);
}

/**************************************************************************
				photoelectric 光电x3 初始化GPIO
**************************************************************************/

// 光电
void photoelectric_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOG,&GPIO_InitStruct);
}