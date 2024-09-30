#ifndef __WATER_H
#define __WATER_H
#include "main.h"
// 浇水
#define watering_Plant HAL_GPIO_WritePin(RELAY_GPIO_GPIO_Port, RELAY_GPIO_Pin, GPIO_PIN_SET)
#define stop_watering_Plant HAL_GPIO_WritePin(RELAY_GPIO_GPIO_Port, RELAY_GPIO_Pin, GPIO_PIN_RESET)

void WaterInit(void);
void WaterTask(void);

#endif