#ifndef __LIDAR_H
#define __LIDAR_H
#include "sys.h"
#include "dma.h"
// #define lidar_left (uint16_t)(Inf.information[0])
// #define Strength (uint16_t)(Inf.information[1])
// #define Temp (uint16_t)(Inf.information[2])

// typedef union
// {
// 	char data[10];
// 	uint16_t information[5];
// }Union_Inf;

// extern Union_Inf Inf;
// extern char Inf_DMA_ready;
typedef enum
{
    left_lidar,
    right_lidar
} lidarIndexEnum;
/*===============public===================*/
// extern uint16_t lidar_right;
// extern uint16_t lidar_left;
void lidar_Init(lidarIndexEnum lidar_idx);
// void Inf_Init(u32 bound);
// void TIM10_Int_Init(u16 arr,u16 psc);

#endif
