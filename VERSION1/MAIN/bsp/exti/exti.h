#ifndef _EXTI__H
#define _EXTI__H

#include "sys.h"
// #include "photoelectric.h"
// #include "gray.h"
extern int left_water_flag, right_water_flag; // water start flag
void EXTIX_Init(void);                        // 外部中断初始化
void EXTI3_IRQHandler(void);
void EXTI_Line_Close(void);
void EXTI_Line_Init(void);
void EXTI2_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
int Get_N(void);
void EXTI_3_Disable(void);
void EXTI_3_Enable(void);
void EXTI_0_Disable(void);
void EXTI_0_Enable(void);
void EXTI_10_11_Close(void);

void EXTInterruppt_Mode(void);
void EXTI_NVIC_Configuration(void);
void NVIC_Configuration_Close(void);

void PE_EXTI_Init(void); // for cross_cnt = 2/4/6
void PE_EXTI_Close(void);
void PE_EXTI_Open(void);

#endif
