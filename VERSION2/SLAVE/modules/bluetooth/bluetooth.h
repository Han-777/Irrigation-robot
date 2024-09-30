#ifndef _BLUETOOTH_H
#define _BLUETOOTH_H

#include "robot_def.h"
#include "main.h"
#pragma pack(1) // 压缩结构体,取消字节对齐,下面的数据都可能被传输

typedef struct
{
    Drought_Info_e drought_buff[18];
} BLUETOOTH_data_t;

BLUETOOTH_data_t *Bluetooth_Init(UART_HandleTypeDef *bluetooth_usart_handle);
#pragma pack() // 开启字节对齐,结束前面的#pragma pack(1)

#endif