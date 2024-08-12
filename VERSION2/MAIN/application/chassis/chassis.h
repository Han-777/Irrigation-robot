#ifndef CHASSIS_H
#define CHASSIS_H

#include "stdint.h"
#include "controller.h"
// typedef struct
// {
//     /*   parameters add reality    */
//     // 目标角
//     float target_yaw;
//     float target_roll;
//     uint8_t cross_cnt; // 用于目标角度计算

// } chassis_gyro_data_t;

typedef struct
{
    /*   parameters add reality    */
    PIDInstance angle_instance;
    // 目标角
    float target_yaw;
} chassis_gyro_data_t;

/**
 * @brief 底盘应用初始化,请在开启rtos之前调用(目前会被RobotInit()调用)
 *
 */
void ChassisInit();

/**
 * @brief 底盘应用任务,放入实时系统以一定频率运行
 *
 */
void ChassisTask();
#include "gyro.h"

extern chassis_gyro_data_t chassis_gyro_ctrl_data;
extern GYRO_data_t *gyro_data;
#endif // CHASSIS_H