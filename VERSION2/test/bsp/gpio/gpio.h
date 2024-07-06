#ifndef __GPIO_H__
#define __GPIO_H__

#include "sys.h"
/**************************************************************************
	������ƺ꣺һ·PWM��������������������������ͬ���Ҳ�����Ҳ��ͬ
**************************************************************************/
void MOTOR_GPIO_Init(void);

//  direction macro
#define LIN1 PFout(6) // Left
#define LIN2 PFout(7)
#define RIN1 PFout(11) // Right
#define RIN2 PFout(5)

#define LIN1_GPIO_PIN LL_GPIO_PIN_6
#define LIN2_GPIO_PIN LL_GPIO_PIN_7
#define LIN_GPIO_PORT GPIOF
#define LIN_GPIO_CLK LL_AHB1_GRP1_PERIPH_GPIOF

#define RIN1_GPIO_PIN LL_GPIO_PIN_11 // F5
#define RIN2_GPIO_PIN LL_GPIO_PIN_5  //
#define RIN_GPIO_PORT GPIOF
// #define RIN2_GPIO_PORT  		GPIOF
#define RIN_GPIO_CLK LL_AHB1_GRP1_PERIPH_GPIOF

/**************************************************************************
						   ����ʼ��GPIO
**************************************************************************/
void photoelectricity_GPIO_Init(void);

#define PE_Left LL_GPIO_IsInputPinSet(GPIOG, LL_GPIO_PIN_10)
#define PE_Right LL_GPIO_IsInputPinSet(GPIOG, LL_GPIO_PIN_11)

/**************************************************************************
						   �Ҷȳ�ʼ��GPIO
**************************************************************************/
void gray_GPIO_Init(void);

/**************************************************************************
						   Key��ʼ��GPIO
**************************************************************************/
void Key_GPIO_Init();

#define ROW_SET1 LL_GPIO_SetOutputPin(GPIOF, LL_GPIO_PIN_4)
#define ROW_SET2 LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_9)
#define ROW_SET3 LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_14)

#define ROW_RESET1 LL_GPIO_ResetOutputPin(GPIOF, LL_GPIO_PIN_4)
#define ROW_RESET2 LL_GPIO_ResetOutputPin(GPIOD, LL_GPIO_PIN_9)
#define ROW_RESET3 LL_GPIO_ResetOutputPin(GPIOD, LL_GPIO_PIN_14)

#define COL_SCAN1 LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_15)
#define COL_SCAN2 LL_GPIO_IsInputPinSet(GPIOF, LL_GPIO_PIN_0)
#define COL_SCAN3 LL_GPIO_IsInputPinSet(GPIOF, LL_GPIO_PIN_2)

/**************************************************************************
						   �������� ��ʼ��GPIO
**************************************************************************/
#define TX_PIN LL_GPIO_PIN_6
#define RX_PIN LL_GPIO_PIN_15
#define TX_PORT GPIOD
#define TX_DATA_H() LL_GPIO_SetOutputPin(TX_PORT, TX_PIN)	// �ߵ�ƽ
#define TX_DATA_L() LL_GPIO_ResetOutputPin(TX_PORT, TX_PIN) // �͵�ƽ

void voice_Config(void);

/**************************************************************************
				photoelectric ���x3 ��ʼ��GPIO
**************************************************************************/
void photoelectric_GPIO_Init(void);

/**************************************************************************
								ˮ��GPIO
**************************************************************************/
void pump_GPIO_Init(void);
#define close_pump LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_12)
#define open_pump LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_12)
#endif
