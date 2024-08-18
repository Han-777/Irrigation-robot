#ifndef _BLUETOOTH_H
#define _BLUETOOTH_H

#include "main.h"

typedef enum
{
    REDLAND = 0x01,
    GREENLAND = 0x02,
    BLUELAND = 0x03
} BLUETOOTH_color_e;

typedef struct
{
    BLUETOOTH_color_e drought_buff[18];
} BLUETOOTH_data_t;

BLUETOOTH_data_t *Bluetooth_Init(UART_HandleTypeDef *bluetooth_usart_handle);

#endif