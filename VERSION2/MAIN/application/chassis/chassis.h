#ifndef CHASSIS_H
#define CHASSIS_H

#include "stdint.h"
#include "controller.h"

typedef struct
{
    // 上电角
    float ori_yaw;
    float ori_pitch;
    float ori_roll;
    uint8_t init_flag; // 每次开启陀螺仪任务时候设置

    float target_yaw;
    float cal_yaw; // 经过转换后的参考值
} GYRO_Ctrl_Data_t;
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

#endif // CHASSIS_H