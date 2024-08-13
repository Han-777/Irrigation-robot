#ifndef __GRAY_H__
#define __GRAY_H__

#include "main.h"

/*** @note later it should be put to application layer*/
/*--------------------------------------------------------------*/
// OUT1 -> OUT12 from left to right

/**************
 * left grayscale *
 ***************/
#define OUT0 HAL_GPIO_ReadPin(GRAY0_GPIO_GPIO_Port, GRAY0_GPIO_Pin)
#define OUT1 HAL_GPIO_ReadPin(GRAY1_GPIO_GPIO_Port, GRAY1_GPIO_Pin)
#define OUT2 HAL_GPIO_ReadPin(GRAY2_GPIO_GPIO_Port, GRAY2_GPIO_Pin)
#define OUT3 HAL_GPIO_ReadPin(GRAY3_GPIO_GPIO_Port, GRAY3_GPIO_Pin)
#define OUT4 HAL_GPIO_ReadPin(GRAY4_GPIO_GPIO_Port, GRAY4_GPIO_Pin)
#define OUT5 HAL_GPIO_ReadPin(GRAY5_GPIO_GPIO_Port, GRAY5_GPIO_Pin)
#define OUT6 HAL_GPIO_ReadPin(GRAY6_GPIO_GPIO_Port, GRAY6_GPIO_Pin)

/**************
 * right grayscale *
 ***************/
#define OUT7 HAL_GPIO_ReadPin(GRAY7_GPIO_GPIO_Port, GRAY7_GPIO_Pin)
#define OUT8 HAL_GPIO_ReadPin(GRAY8_GPIO_GPIO_Port, GRAY8_GPIO_Pin)
#define OUT9 HAL_GPIO_ReadPin(GRAY9_GPIO_GPIO_Port, GRAY9_GPIO_Pin)
#define OUT10 HAL_GPIO_ReadPin(GRAY10_GPIO_GPIO_Port, GRAY10_GPIO_Pin)
#define OUT11 HAL_GPIO_ReadPin(GRAY11_GPIO_GPIO_Port, GRAY11_GPIO_Pin)
#define OUT12 HAL_GPIO_ReadPin(GRAY12_GPIO_GPIO_Port, GRAY12_GPIO_Pin)
#define OUT13 HAL_GPIO_ReadPin(GRAY13_GPIO_GPIO_Port, GRAY13_GPIO_Pin)

uint8_t get_gray_cnt(void);

#endif
