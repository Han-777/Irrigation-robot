#ifndef _OPENMV_H
#define _OPENMV_H

#include "sys.h"
typedef enum
{
    MILD_DROUGHT = 0x01, // 轻微干旱
    GENERL_DROUGHT,      // 一般干旱
    SEVERE_DROUGHT,      // 严重干旱
    INFO_DROUGHT         // for drought_buffer (!D)
} colorIdx;
extern u8 cx, cy, color, z;

int get_OpenMV(void);

#endif