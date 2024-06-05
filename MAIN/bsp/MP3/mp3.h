#ifndef __VOICE_H
#define __VOICE_H

#include "sys.h"

#define BuadRate_9600 104

#define TX_PIN 		GPIO_Pin_6 
#define RX_PIN 		GPIO_Pin_15
#define TX_PORT   GPIOD
#define TX_DATA_H()  	GPIO_SetBits(TX_PORT, TX_PIN)     //高电平
#define TX_DATA_L()  	GPIO_ResetBits(TX_PORT,TX_PIN)    //低电平

void VirtualTx_Config(void);
void VirtualCOM_ByteSend(uint8_t Data);
void VirtualCOM_StringSend(u8 *str);
void MP3_broadcast(u8 mess);


#endif


