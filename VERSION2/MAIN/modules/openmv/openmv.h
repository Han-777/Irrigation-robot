#ifndef _OPENMV_H
#define _OPENMV_H

#include "main.h"

typedef enum
{
    NONE = 0x00,
    GREEN = 0x01,
    BLUE = 0x02,
    RED = 0x03
} OPENMV_color_e;

typedef struct
{
    OPENMV_color_e color;
} OPENMV_data_t;

void Mv_Close(void);
void Mv_Open(void);
OPENMV_data_t *OPENMV_Init(UART_HandleTypeDef *openmv_usart_handle);

#endif