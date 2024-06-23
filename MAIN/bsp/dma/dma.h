#include "stm32f4xx.h"
#include "sys.h"

void LCD_DMA_init(DMA_Stream_TypeDef *DMA_Streamx,u32 chx,u32 par,u32 mar,u16 ndtr);
void OPS_DMA_init(DMA_Stream_TypeDef *DMA_Streamx,u32 chx,u32 par,u32 mar,u16 ndtr);

void MYDMA_Enable(DMA_Stream_TypeDef *DMA_Streamx,u16 ndtr);
