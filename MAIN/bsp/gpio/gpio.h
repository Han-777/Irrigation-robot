#ifndef	__GPIO_H__
#define __GPIO_H__

#include "sys.h"
/**************************************************************************
	������ƺ꣺һ·PWM��������������������������ͬ���Ҳ�����Ҳ��ͬ
**************************************************************************/
void MOTOR_GPIO_Init(void);

//  direction macro
#define LIN1   PFout(6)  // Left 
#define LIN2   PFout(7)  
#define RIN1   PFout(11)  // Right
#define RIN2   PFout(5)  

#define LIN1_GPIO_PIN       	GPIO_Pin_6 
#define LIN2_GPIO_PIN   		GPIO_Pin_7
#define LIN_GPIO_PORT  			GPIOF
#define LIN_GPIO_CLK 			RCC_AHB1Periph_GPIOF

#define RIN1_GPIO_PIN       	GPIO_Pin_11 // F5
#define RIN2_GPIO_PIN   		GPIO_Pin_5 //
#define RIN_GPIO_PORT  			GPIOF
// #define RIN2_GPIO_PORT  		GPIOF
#define RIN_GPIO_CLK 			RCC_AHB1Periph_GPIOF

/**************************************************************************
						   ����ʼ��GPIO
**************************************************************************/
void photoelectricity_GPIO_Init(void);

#define PE_Left   			GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10)
#define PE_Right   			GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_11)

/**************************************************************************
						   �Ҷȳ�ʼ��GPIO
**************************************************************************/
void gray_GPIO_Init(void);

/**************************************************************************
						   Key��ʼ��GPIO
**************************************************************************/
void Key_GPIO_Init();

#define ROW_SET1 GPIO_SetBits(GPIOF,GPIO_Pin_4)
#define ROW_SET2 GPIO_SetBits(GPIOD,GPIO_Pin_9)
#define ROW_SET3 GPIO_SetBits(GPIOD,GPIO_Pin_14)

#define ROW_RESET1 GPIO_ResetBits(GPIOF,GPIO_Pin_4)
#define ROW_RESET2 GPIO_ResetBits(GPIOD,GPIO_Pin_9)
#define ROW_RESET3 GPIO_ResetBits(GPIOD,GPIO_Pin_14)

#define COL_SCAN1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)
#define COL_SCAN2 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_0)
#define COL_SCAN3 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_2)


/**************************************************************************
						   �������� ��ʼ��GPIO
**************************************************************************/
#define TX_PIN 		GPIO_Pin_6 
#define RX_PIN 		GPIO_Pin_15
#define TX_PORT   GPIOD
#define TX_DATA_H()  	GPIO_SetBits(TX_PORT, TX_PIN)     //�ߵ�ƽ
#define TX_DATA_L()  	GPIO_ResetBits(TX_PORT,TX_PIN)    //�͵�ƽ

void voice_Config(void);

/**************************************************************************
				photoelectric ���x3 ��ʼ��GPIO
**************************************************************************/
void photoelectric_GPIO_Init(void);

#endif
	