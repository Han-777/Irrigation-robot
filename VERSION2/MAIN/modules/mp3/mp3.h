#ifndef __MP3_H
#define __MP3_H

#include <stdint.h>
#include "main.h"
#include "robot_def.h"

void MP3_Init(UART_HandleTypeDef *mp3_usart_handle);

void MP3_broadcast(Drought_Info_e info);

// void MP3_Init(void);

// void MP3_broadcast(Drought_Info_e info);

#endif
