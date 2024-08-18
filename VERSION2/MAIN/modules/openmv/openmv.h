#ifndef _OPENMV_H
#define _OPENMV_H

#include "main.h"

typedef enum
{
    REDLAND = 0x01,
    GREENLAND = 0x02,
    BLUELAND = 0x03
} OPENMV_color_e;

typedef struct
{
    OPENMV_color_e color;
} OPENMV_data_t;

OPENMV_data_t *OPENMV_Init(UART_HandleTypeDef *openmv_usart_handle);

#endif