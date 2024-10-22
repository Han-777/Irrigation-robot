/* 注意该文件应只用于任务初始化,只能被robot.c包含*/
#pragma once

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "usart.h"
#include "cmsis_os.h"

#include "robot.h"
#include "motor_task.h"
#include "daemon.h"
#include "lidar.h"
#include "gyro.h"
#include <memory.h>
#include "robot_queue.h"

osThreadId robotTaskHandle;
osThreadId motorTaskHandle;
osThreadId daemonTaskHandle;
osThreadId waterTaskHandle;
// osThreadId uiTaskHandle;
/*      中断处理任务       */
osThreadId lidarTaskHandle;
// osThreadId gyroTaskHandle;
// osThreadId isrTaskHandle;

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
    // 创建队列
    lidarQueue = xQueueCreate(10, sizeof(uint8_t) * (LIDAR_FRAME_SIZE + 1));
    // gyroQueue = xQueueCreate(10, sizeof(uint8_t) * GYRO_FRAME_SIZE);

    // osThreadDef(instask, StartINSTASK, osPriorityAboveNormal, 0, 1024);
    // insTaskHandle = osThreadCreate(osThread(instask), NULL); // 由于是阻塞读取传感器,为姿态解算设置较高优先级,确保以1khz的频率执行
    // // 后续修改为读取传感器数据准备好的中断处理,

    osThreadDef(motortask, StartMOTORTASK, osPriorityNormal, 0, 512);
    motorTaskHandle = osThreadCreate(osThread(motortask), NULL);

    osThreadDef(daemontask, StartDAEMONTASK, osPriorityNormal, 0, 128);
    daemonTaskHandle = osThreadCreate(osThread(daemontask), NULL);

    osThreadDef(robottask, StartROBOTTASK, osPriorityNormal, 0, 1500);
    robotTaskHandle = osThreadCreate(osThread(robottask), NULL);

    osThreadDef(watertask, StartWaterTASK, osPriorityNormal, 0, 1024);
    waterTaskHandle = osThreadCreate(osThread(watertask), NULL);

    osThreadDef(lidartask, StartLidarTask, osPriorityHigh, 0, 256);
    lidarTaskHandle = osThreadCreate(osThread(lidartask), NULL);
}

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
        osDelay(3);
    }
}

// static size_t heap_size = 0;
// UBaseType_t stackHighWaterMark;
__attribute__((noreturn)) void StartWaterTASK(void const *argument)
{
    for (;;)
    {
        WaterTask();
        // heap_size = xPortGetFreeHeapSize();
        // stackHighWaterMark = uxTaskGetStackHighWaterMark(waterTaskHandle); // 获取当前任务的栈使用情况
        osDelay(1); // 即使没有任何UI需要刷新,也挂起一次,防止卡在UITask中无法切换
    }
}

/**
 * @brief
 *
 * @note 经过测试,激光雷达的时候最好在chassis task suspend 时候再进行,后续需要加上浇水标志位调用vTaskResume此函数的代码
 * chassis task 和 lidar task一次只能有一个运行,除非找到更好的办法
 */
__attribute__((noreturn)) void StartLidarTask(void const *argument)
{
    uint8_t buffer[LIDAR_FRAME_SIZE + 1];
    for (;;)
    {
        if (xQueueReceive(lidarQueue, &buffer, portMAX_DELAY) == pdPASS)
        {
            // vTaskSuspendAll();    // 禁用调度器
            // taskENTER_CRITICAL(); // 禁用中断
            lidar_data_handle(buffer);
            // taskEXIT_CRITICAL(); // 启用中断
            // xTaskResumeAll();    // 启用调度器
        }
        // osDelay(2); // 增加延时
    }
}

void RobotInitTASK() {}