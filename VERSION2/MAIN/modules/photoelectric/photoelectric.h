#ifndef __PHOTOELECTRIC__H
#define __PHOTOELECTRIC__H

#include "main.h"
#include <stdint.h>

typedef enum
{
    LEFT_PE_FLAG = 0b01,
    RIGHT_PE_FLAG = 0b10
} PE_FLAG_e;
static void PECallback(uint16_t pin_handle);

void PE_Init(uint16_t pe_pin_handle);

#endif
