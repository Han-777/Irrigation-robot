#ifndef __USRATX_H
#define __USRATX_H

#include "sys.h"

/**************************************************************************
						Bluetooth 初始化 USART1
**************************************************************************/

void Bluetooth_USART_Init(u32 bound);
void Bluetooth_USART_Close(void);

/**************************************************************************
						TFmini_Left 初始化 USART2
**************************************************************************/

void TFmini_right_USART_Init(uint32_t bound, FunctionalState state);
void TFmini_right_USART_Close(void);

/**************************************************************************
						   OPENMV初始化 USART3
**************************************************************************/

void OpenMV_USART_Init(u32 bound);
void OpenMV_USART_Close(void);

/**************************************************************************
						TFmini_Right 初始化 USART4
**************************************************************************/

void TFmini_left_USART_Init(uint32_t bound, FunctionalState state);
void TFmini_left_USART_Close(void);

/**************************************************************************
						   陀螺仪初始化 USART5
**************************************************************************/

void gyro_USART_Init(uint32_t bound);
void gyro_USART_Close(void);

// /**************************************************************************
// 						   初始化 USART6
// **************************************************************************/

// void gyro_USART_Init(uint32_t bound);
// void gyro_USART_Close(void);

#endif
