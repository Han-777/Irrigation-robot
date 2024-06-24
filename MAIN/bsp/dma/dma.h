#ifndef __DMA_H
#define __DMA_H

#include "sys.h"
#include "gyro.h"

#define UART5_RX_BUFFER_SIZE 256

#define GYRO_DMA_Channel DMA_Channel_4 // USART5
#define GRYO_DMA_Buf_Size 64
#define GYRO_DMA_Stream DMA1_Stream0

extern uint16_t lidar_right;
extern uint16_t lidar_left;

// void LCD_DMA_init(DMA_Stream_TypeDef *DMA_Streamx, u32 chx, u32 par, u32 mar, u16 ndtr);
// void OPS_DMA_init(DMA_Stream_TypeDef *DMA_Streamx, u32 chx, u32 par, u32 mar, u16 ndtr);

// void MYDMA_Enable(DMA_Stream_TypeDef *DMA_Streamx, u16 ndtr);

void GYRO_DMA_Config(void);
void USART2_DMA_Config(void);
void UART4_DMA_Config(void);

#endif