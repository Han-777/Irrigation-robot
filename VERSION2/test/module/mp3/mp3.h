#ifndef __MP3_H
#define __MP3_H

#include "sys.h"
#include "openmv.h"

#define BuadRate_9600 104

#define TX_PIN LL_GPIO_PIN_6
#define RX_PIN LL_GPIO_PIN_15
#define TX_PORT GPIOD
#define TX_DATA_H() LL_GPIO_SetOutputPin(TX_PORT, TX_PIN)   // 高电平
#define TX_DATA_L() LL_GPIO_ResetOutputPin(TX_PORT, TX_PIN) // 低电平

void VirtualTx_Config(void);
void VirtualCOM_ByteSend(uint8_t Data);
void VirtualCOM_StringSend(u8 *str);
void MP3_broadcast(colorIdx mess);

#endif
