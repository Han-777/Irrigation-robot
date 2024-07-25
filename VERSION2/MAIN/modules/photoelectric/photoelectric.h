#ifndef __PHOTOELECTRIC__H
#define __PHOTOELECTRIC__H

#include "main.h"
#include <stdint.h>

typedef enum
{
    LEFT_PE_FLAG = 0b00000001,
    RIGHT_PE_FLAG = 0b00000010
} PE_FLAG_e;

uint8_t *PE_Init(uint16_t pe_pin_handle);

#endif
