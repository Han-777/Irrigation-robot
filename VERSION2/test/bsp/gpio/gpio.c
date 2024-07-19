#include "gpio.h"

/**************************************************************************
						鐢垫満鎺у埗鍒濓�??锟藉寲GPIO
**************************************************************************/
void MOTOR_GPIO_Init(void)
{

	LL_GPIO_InitTypeDef GPIO_InitStruct;

	LL_AHB1_GRP1_EnableClock(LIN_GPIO_CLK);

	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	/*-------------------------LIN_GPIO_CONFIG--------------------------*/

	GPIO_InitStruct.Pin = LIN1_GPIO_PIN | LIN2_GPIO_PIN | RIN1_GPIO_PIN | RIN2_GPIO_PIN;
	;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(LIN_GPIO_PORT, &GPIO_InitStruct);

	/*-------------------------RIN_GPIO_CONFIG--------------------------*/
	// RCC_AHB1PeriphClockCmd(RIN_GPIO_CLK, ENABLE);

	// GPIO_InitStruct.GPIO_Pin = RIN1_GPIO_PIN | RIN2_GPIO_PIN;
	// GPIO_Init(RIN_GPIO_PORT, &GPIO_InitStruct);
}

/**************************************************************************
						   鍏�?�數鍒濓�??锟藉寲GPIO
**************************************************************************/
void photoelectricity_GPIO_Init(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct;
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOG);
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pin = LL_GPIO_PIN_10 | LL_GPIO_PIN_11;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}

/**************************************************************************
						   鐏板害鍒濓拷?锟藉寲GPIO
**************************************************************************/

void gray_GPIO_Init(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct;

	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC | LL_AHB1_GRP1_PERIPH_GPIOD | LL_AHB1_GRP1_PERIPH_GPIOG | LL_AHB1_GRP1_PERIPH_GPIOB | LL_AHB1_GRP1_PERIPH_GPIOA | LL_AHB1_GRP1_PERIPH_GPIOE);

	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pin = LL_GPIO_PIN_7 | LL_GPIO_PIN_9 | LL_GPIO_PIN_14;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOG, &GPIO_InitStruct); //

	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pin = LL_GPIO_PIN_8 | LL_GPIO_PIN_15;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct); //

	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pin = LL_GPIO_PIN_5 | LL_GPIO_PIN_6 | LL_GPIO_PIN_7;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct); //

	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pin = LL_GPIO_PIN_5 | LL_GPIO_PIN_6;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOE, &GPIO_InitStruct); //

	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pin = LL_GPIO_PIN_0 | LL_GPIO_PIN_9;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOC, &GPIO_InitStruct); //

	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pin = LL_GPIO_PIN_4 | LL_GPIO_PIN_7;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOD, &GPIO_InitStruct); //
}

// //閰嶇疆鍏夌數浼犳劅锟�??
// GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3 ;
// GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
// GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
// GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
// GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
// GPIO_Init(GPIOD,&GPIO_InitStructure);
// //閰嶇疆缁х數鍣≒B12
// GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
// GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
// GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
// GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
// GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;   //楂�?�數骞宠Е锟�?
// GPIO_Init(GPIOB,&GPIO_InitStructure);
// GPIO_ResetBits(GPIOB, GPIO_Pin_4);
// //閰嶇疆缁х數鍣≒F13
// GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
// GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
// GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
// GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
// GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;   //楂�?�數骞宠Е锟�?
// GPIO_Init(GPIOB,&GPIO_InitStructure);
// GPIO_ResetBits(GPIOB, GPIO_Pin_12);

/**************************************************************************
						   Key鍒濓�??锟藉寲GPIO
**************************************************************************/
void Key_GPIO_Init()
{
	// c4 f11 f15 g1 e8 e13
	LL_GPIO_InitTypeDef GPIO_InitStructure;
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC | LL_AHB1_GRP1_PERIPH_GPIOE | LL_AHB1_GRP1_PERIPH_GPIOF | LL_AHB1_GRP1_PERIPH_GPIOG);

	// col
	GPIO_InitStructure.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull = LL_GPIO_PULL_DOWN;
	GPIO_InitStructure.Pin = LL_GPIO_PIN_15;
	GPIO_InitStructure.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.Pin = LL_GPIO_PIN_0 | LL_GPIO_PIN_2;
	GPIO_InitStructure.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOF, &GPIO_InitStructure);

	// row
	GPIO_InitStructure.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pin = LL_GPIO_PIN_4;
	GPIO_InitStructure.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_InitStructure.Pin = LL_GPIO_PIN_9 | LL_GPIO_PIN_14;
	GPIO_InitStructure.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/**************************************************************************
						   锟�?闊虫挱锟�?? 鍒濓�??锟藉寲GPIO
**************************************************************************/

void voice_Config(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct;
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD | LL_AHB1_GRP1_PERIPH_GPIOG);
	GPIO_InitStruct.Pin = TX_PIN;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	LL_GPIO_SetOutputPin(TX_PORT, TX_PIN);

	GPIO_InitStruct.Pin = RX_PIN;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}

/**************************************************************************
				photoelectric 鍏�?�數x3 鍒濓�??锟藉寲GPIO
**************************************************************************/

// 鍏�?�數
void photoelectric_GPIO_Init(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct;
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD | LL_AHB1_GRP1_PERIPH_GPIOG);

	// GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	// GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	// GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
	// GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	// GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	// GPIO_Init(GPIOC,&GPIO_InitStruct);

	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	// GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	// GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	// GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_5|GPIO_Pin_6;
	// GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	// GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	// GPIO_Init(GPIOE,&GPIO_InitStruct);

	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pin = LL_GPIO_PIN_10 | LL_GPIO_PIN_11;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}

/**************************************************************************
								水泵GPIO
**************************************************************************/

void pump_GPIO_Init(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStructure;
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	GPIO_InitStructure.Pin = LL_GPIO_PIN_12;
	GPIO_InitStructure.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStructure.Pull = LL_GPIO_PULL_DOWN; // 楂�?�數骞宠Е鍙�
	GPIO_InitStructure.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_12);
}
