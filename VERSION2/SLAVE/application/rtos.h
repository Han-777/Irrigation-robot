// 用于freertos下的延时实现

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

// 创建一个二值信号量
SemaphoreHandle_t xSemaphore = NULL;

void vSetupDelaySemaphore(void) {
    // 初始化二值信号量
    xSemaphore = xSemaphoreCreateBinary();
    if (xSemaphore == NULL) {
        // 处理错误，信号量创建失败
    }
    // 初始状态为未给予，即任务将在这个信号量上阻塞
    xSemaphoreTake(xSemaphore, portMAX_DELAY);
}

void vDelayFunction(TickType_t xTicksToDelay) {
    // 将信号量重置为未给予状态，任务将在这个信号量上阻塞
    xSemaphoreTake(xSemaphore, portMAX_DELAY);
    // 延迟指定的时间
    xSemaphoreGive(xSemaphore); // 给予信号量，解除任务阻塞
}

void vTaskFunction(void *pvParameters) {
    // 调用初始化函数创建信号量
    vSetupDelaySemaphore();

    for (;;) {
        // 任务的工作代码...

        // 调用延时函数，实现延时效果
        vDelayFunction(pdMS_TO_TICKS(1000)); // 延时1000毫秒

        // 任务的工作代码...
    }
}

