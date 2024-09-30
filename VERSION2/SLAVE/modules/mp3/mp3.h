#ifndef __MP3_H
#define __MP3_H

#include <stdint.h>
#include "main.h"
#include "robot_def.h"
// typedef enum
// {
//     SLIGHT = 0x01,
//     GENERAL = 0x02, // Corrected typo from "GENERAl" to "GENERAL"
//     SERIOUS = 0x03,
// } MP3_broadcast_e;

void MP3_Init(UART_HandleTypeDef *mp3_usart_handle);

void MP3_broadcast(Drought_Info_e info);

#endif
