#ifndef __RUN_H
#define __RUN_H

#include "legacy.h"
#include "ll_includes.h"
#include "stm32f4xx_hal_conf.h"
#include "chassis.h"
#include "openmv.h"
#include "exti.h"
#include "sys.h"
#include "arm.h"
#include "lidar.h"
#include "bluetooth.h"
typedef enum
{
	A,
	B,
	C,
	D,
	home
} regionEnum;
#define RUN_SPEED 30
// typedef struct
// {
// };

// extern u8 color_Index;
extern int region_finish_flag, cross_cnt, plant_cnt;
extern regionEnum region;
int get_region(void);
void Run(void);

extern int C_lidar_error;

#endif
