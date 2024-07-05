#ifndef _OPENMV_H
#define _OPENMV_H

#include "sys.h"

extern u8 cx,cy,color,z;

void OPENMV_usart_init(u32 bound);
int Openmv_gain();
void USART3_IRQHandler(void);
#endif