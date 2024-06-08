#ifndef __GPIO_H
#define __GPIO_H

#include "sys.h"

#define BuadRate_9600 104

void VirtualTx_Config(void);
void VirtualCOM_ByteSend(uint8_t Data);
void VirtualCOM_StringSend(u8 *str);
void MP3_broadcast(u8 mess);


#endif


