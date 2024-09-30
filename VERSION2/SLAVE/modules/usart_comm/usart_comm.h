#ifndef USART_COMM__H
#define USART_COMM_H

#include <stdint.h>
#include "main.h"

/* ------------------------- Internal Data ----------------------------------- */
void USART_Comm_Sned(uint8_t water_cnt, Drought_Info_e D_Drought_Info);

Drought_Info_e *UART_Comm_Init(UART_HandleTypeDef *comm_uart_handle);
#endif