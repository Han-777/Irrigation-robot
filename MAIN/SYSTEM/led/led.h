#ifndef __LED__H
#define __LED__H
#include "sys.h"
#define LED1 PFout(9)
#define LED2 PFout(10)
#define BEEP PGout(6)
void LED_Init(void);
#endif
