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
    osThreadDef(robottask, StartROBOTTASK, osPriorityNormal, 0, 1024);
    robotTaskHandle = osThreadCreate(osThread(robottask), NULL);

    osThreadDef(watertask, StartWaterTASK, osPriorityNormal, 0, 1024);
    waterTaskHandle = osThreadCreate(osThread(watertask), NULL);
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
        osDelay(1); // 即使没有任何UI需要刷新,也挂起一次,防止卡在UITask中无法切换
    }
}

void RobotInitTASK() {}