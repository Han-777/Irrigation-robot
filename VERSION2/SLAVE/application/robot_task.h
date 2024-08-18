/* 注意该文件应只用于任务初始化,只能被robot.c包含*/
#pragma once

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "usart.h"
#include "cmsis_os.h"

#include "robot.h"
#include "daemon.h"
// #include "buzzer.h"
#include <memory.h>
#include "robot_queue.h"
// osThreadId insTaskHandle;
osThreadId initTaskHandle;
osThreadId robotTaskHandle;
osThreadId motorTaskHandle;
osThreadId daemonTaskHandle;
osThreadId waterTaskHandle;
// osThreadId uiTaskHandle;
/*      中断处理任务       */
osThreadId lidarTaskHandle;
// osThreadId gyroTaskHandle;
// osThreadId isrTaskHandle;

// void StartINSTASK(void const *argument);
// void RobotInitTASK(void const *argument); // 用于陀螺仪以及蓝牙数据处理,此任务完成之后可以激活其他任务
void StartInitTASK(void const *argument); // 用于陀螺仪以及蓝牙数据处理,此任务完成之后可以激活其他任务
void RobotInitTASK();
void StartMOTORTASK(void const *argument);
void StartDAEMONTASK(void const *argument);
void StartROBOTTASK(void const *argument);
void StartWaterTASK(void const *argument);

void StartLidarTask(void const *argument);
// void StartGyroTask(void const *argument);
// void StartISRTASK(void const *argument);

/**
 * @brief 初始化机器人任务,所有持续运行的任务都在这里初始化
 *
 */
void OSTaskInit()
{
#define ROBOTSTART
#ifdef ROBOTSTART
    // 创建队列

    // osThreadDef(gyrotask, StartGyroTask, osPriorityHigh, 0, 256);
    // gyroTaskHandle = osThreadCreate(osThread(gyrotask), NULL);

    // osThreadDef(isrtask, StartISRTASK, osPriorityHigh, 0, 256);
    // isrTaskHandle = osThreadCreate(osThread(isrtask), NULL);
// osThreadDef(uitask, StartUITASK, osPriorityNormal, 0, 512);
// uiTaskHandle = osThreadCreate(osThread(uitask), NULL);
#else
    osThreadDef(inittask, StartInitTASK, osPriorityNormal, 0, 128);
    initTaskHandle = osThreadCreate(osThread(inittask), NULL);
#endif
}

/**
 * @brief 机器人初始化任务,用于确认机器人满足初始化条件并激活其他任务
 *      初始化条件(可添加):
 *      1. gyro
 *      2. bluetooth接收到干旱信息
//  */
// __attribute__((noreturn)) void StartInitTASK(void const *argument)
// {
//     static float robot_init_dt;
//     static float robot_start;
//     // 初始化标志位
//     static uint8_t gyro_Init_flag = 0;
//     static uint8_t bluetooth_Init_flag = 0;
//     // 模块数据
//     static GYRO_data_t *gyro_data;
//     gyro_data = Gyro_Init(&huart5); // (待测:)这里的初始化只是判断是否稳定,应该不会影响后面的重新初始化判断吧
//     for (;;)
//     {
//         robot_start = DWT_GetTimeline_ms();
//         RobotInitTASK();
//         robot_init_dt = DWT_GetTimeline_ms() - robot_start;
//         if (robot_init_dt >= 1) // 任务超时判断(暂时没用)
//         {
//         }
//         GYRO_buff_to_data();
//         if (fabs(gyro_data->last_Pitch - gyro_data->Pitch) < 2 && fabs(gyro_data->last_Yaw - gyro_data->Yaw) < 2 && fabs(gyro_data->last_Roll - gyro_data->Roll) < 2) // 陀螺仪初始化完成判断
//         {
//             gyro_Init_flag = 1;
//         }
//         if (bluetooth_Init_flag == 0)
//         {
//             bluetooth_Init_flag = 1;
//         }
//         if (gyro_Init_flag && bluetooth_Init_flag)
//         {
// #ifndef ROBOTSTART
// #define ROBOTSTART
//             OSTaskInit();
// #endif
//             vTaskDelete(initTaskHandle);
//         }
//     }
// }

__attribute__((noreturn)) void StartMOTORTASK(void const *argument)
{
    static float motor_dt;
    static float motor_start;
    for (;;)
    {
        motor_start = DWT_GetTimeline_ms();
        MotorControlTask();
        motor_dt = DWT_GetTimeline_ms() - motor_start;
        if (motor_dt > 1)
        {
            // LOGERROR("[freeRTOS] MOTOR Task is being DELAY! dt = [%f]", &motor_dt);
        }
        osDelay(1);
    }
}

__attribute__((noreturn)) void StartDAEMONTASK(void const *argument)
{
    static float daemon_dt;
    static float daemon_start;
    // BuzzerInit();
    // LOGINFO("[freeRTOS] Daemon Task Start");
    for (;;)
    {
        // 100Hz
        daemon_start = DWT_GetTimeline_ms();
        DaemonTask();
        // BuzzerTask();
        daemon_dt = DWT_GetTimeline_ms() - daemon_start;
        if (daemon_dt > 10)
        {
            // LOGERROR("[freeRTOS] Daemon Task is being DELAY! dt = [%f]", &daemon_dt);
        }
        osDelay(10);
    }
}

__attribute__((noreturn)) void StartROBOTTASK(void const *argument)
{
    // static float robot_dt;
    // static float robot_start;
    // LOGINFO("[freeRTOS] ROBOT core Task Start");
    // 200Hz-500Hz,若有额外的控制任务如平衡步兵可能需要提升至1kHz
    for (;;)
    {
        // robot_start = DWT_GetTimeline_ms();
        // GYRO_buff_to_data();
        RobotTask();
        // robot_dt = DWT_GetTimeline_ms() - robot_start;
        // if (robot_dt > 5)
        // {
        // LOGERROR("[freeRTOS] ROBOT core Task is being DELAY! dt = [%f]", &robot_dt);
        // }
        osDelay(5);
    }
}

__attribute__((noreturn)) void StartWaterTASK(void const *argument)
{
    for (;;)
    {
        WaterTask();
        osDelay(5); // 即使没有任何UI需要刷新,也挂起一次,防止卡在UITask中无法切换
    }
}

void RobotInitTASK() {}