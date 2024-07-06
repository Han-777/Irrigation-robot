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
#define OUT0 LL_GPIO_IsInputPinSet(GPIOG, LL_GPIO_PIN_14)
#define OUT1 LL_GPIO_IsInputPinSet(GPIOE, LL_GPIO_PIN_5) // 0为�?�到白线
#define OUT2 LL_GPIO_IsInputPinSet(GPIOE, LL_GPIO_PIN_6) //
#define OUT3 LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_0)
#define OUT4 LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_7)
#define OUT5 LL_GPIO_IsInputPinSet(GPIOG, LL_GPIO_PIN_9) //
#define OUT6 LL_GPIO_IsInputPinSet(GPIOD, LL_GPIO_PIN_4)

/**************
 * right grayscale *
 ***************/
#define OUT7 LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_15) // 0为�?�到白线
#define OUT8 LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_5)  //
#define OUT9 LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_6)
#define OUT10 LL_GPIO_IsInputPinSet(GPIOG, LL_GPIO_PIN_7)
#define OUT11 LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_9) //
#define OUT12 LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_8) // 0为�?�到白线
#define OUT13 LL_GPIO_IsInputPinSet(GPIOD, LL_GPIO_PIN_7) //

int get_gray_cnt(void);
int get_cross_flag(void);

#endif
