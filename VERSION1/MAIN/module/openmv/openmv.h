#ifndef _OPENMV_H
#define _OPENMV_H

#include "sys.h"
typedef enum
{
    MILD_DROUGHT = 0x01, // ��΢�ɺ�
    GENERL_DROUGHT,      // һ��ɺ�
    SEVERE_DROUGHT,      // ���ظɺ�
    INFO_DROUGHT         // for drought_buffer (!D)
} colorIdx;
extern u8 cx, cy, color, z;

int get_OpenMV(void);

#endif