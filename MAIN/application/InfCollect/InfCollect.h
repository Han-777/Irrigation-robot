#ifndef __INFCOLLECT_H
#define __INFCOLLECT_H	 
#include "sys.h"

//#define Dist_left (uint16_t)(Inf.information[0])
//#define Strength (uint16_t)(Inf.information[1])
//#define Temp (uint16_t)(Inf.information[2])


typedef union
{
	char data[10];
	uint16_t information[5]; 
}Union_Inf;


extern Union_Inf Inf;
extern char Inf_DMA_ready;
extern uint16_t Dist_right;
extern uint16_t Dist_left;

void Inf_Init(u32 bound);
void Inf_UART5_Init(u32 bound);
void TIM10_Int_Init(u16 arr,u16 psc);

void USART3_IRQHandler(void);
void USART2_IRQHandler(void);
void USART6_IRQHandler(void);
void TFmini_right_init(uint32_t bound);
void TFmini_left_init(uint32_t bound);
void TFmini_right_init_close(uint32_t bound);
void TFmini_left_init_close(uint32_t bound);
#endif
