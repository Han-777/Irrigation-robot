#ifndef __RUN_H
#define __RUN_H

#include "stm32f4xx.h" // Device header
#include "chassis.h"
#include "openmv.h"
#include "exti.h"
#include "sys.h"
#include "arm.h"
#include "lidar.h"
typedef enum
{
	A,
	B,
	C,
	D,
	home
} regionEnum;
#define RUN_SPEED 20

// extern u8 color_Index;
extern int region_finish_flag, cross_cnt, plant_cnt;
extern regionEnum region;
int get_region(void);
void Run(void);

#endif
