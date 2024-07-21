#ifndef __MP3_H
#define __MP3_H

#include "main.h"
#include <stdint.h>

typedef enum
{
    SLIGHT,
    GENERAl,
    SERIOUS
} MP3_broadcast_type;
void MP3_Init(void);

void MP3_broadcast(MP3_broadcast_type info);
#endif
