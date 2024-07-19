#ifndef __IIC_H
#define __IIC_H

#include "sys.h"

void OLED_I2C_Init(void);
void OLED_I2C_Start(void);
void OLED_I2C_Stop(void);
void OLED_I2C_SendByte(uint8_t Byte);

#endif
    