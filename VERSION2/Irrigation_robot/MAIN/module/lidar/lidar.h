/**
 * @file lidar.h
 * @author Han-777
 * @brief  TF-mini模块定义头文件
 * @version beta
 * @date 2024-07-07
 *
 */
#ifndef LIDAR_H
#define LIDAR_H

#include <stdint.h>
#include "main.h"

typedef struct
{
    uint16_t lld_distance;
    uint16_t rld_distance;
} LD_data_t;

#endif