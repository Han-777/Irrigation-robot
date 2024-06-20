#ifndef __GRAY_H__
#define __GRAY_H__
/*--------------------------------------------------------------*/
#include "sys.h"
#include "gyro.h"
extern int cross_cnt;
// OUT1 -> OUT12 from left to right
/**************
 * left grayscale *
 ***************/
#define OUT0 GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_14)
#define OUT1 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5) // 0为�?�到白线
#define OUT2 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6) //
#define OUT3 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0)
#define OUT4 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)
#define OUT5 GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9) //
#define OUT6 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4)

/**************
 * right grayscale *
 ***************/
#define OUT7 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) // 0为�?�到白线
#define OUT8 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)  //
#define OUT9 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)
#define OUT10 GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_7)
#define OUT11 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9) //
#define OUT12 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) // 0为�?�到白线
#define OUT13 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7) //

int get_gray_cnt(void);
int get_cross_flag(void);

#endif
