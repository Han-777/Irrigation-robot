/**
 * @file lidar.h
 * @author DJI 2016
 * @author modified by neozng
 * @brief  遥控器模块定义头文件
 * @version beta
 * @date 2022-11-01
 *
 * @copyright Copyright (c) 2016 DJI corp
 * @copyright Copyright (c) 2022 HNU YueLu EC all rights reserved
 *
 */
#ifndef LIDAR_H
#define LIDAR_H

#include <stdint.h>
#include "main.h"
#include "usart.h"

typedef struct
{
    uint16_t lld_distance;
    uint16_t rld_distance;
} LD_data_t;

#endif