#include "lidar.h"
#include "bsp_usart.h"
#include "daemon.h"
#include <string.h>

static LD_data_t *ld_data;
static DaemonInstance *ld_daemon_instance;
static USARTInstance *lld_instance; // left lidar
static USARTInstance *rld_instance; // right lidar

void Lidar_Close(void)
{
    // HAL_UART_Abort_IT(&huart2);
    // HAL_UART_Abort_IT(&huart4);
    // 中止当前的 UART 接收操作
    HAL_UART_AbortReceive_IT(lld_instance->usart_handle);
    // HAL_UART_AbortReceive_IT(rld_instance->usart_handle);

    // 清空接收缓冲区
    memset(lld_instance->recv_buff, 0, lld_instance->recv_buff_size);
    // memset(rld_instance->recv_buff, 0, rld_instance->recv_buff_size);
}

void Lidar_Open(void)
{
    // HAL_UART_Receive_IT(&huart2, lld_instance->recv_buff, lld_instance->recv_buff_size);
    // HAL_UART_Receive_IT(&huart4, rld_instance->recv_buff, rld_instance->recv_buff_size);
    // 启动 UART 接收
    HAL_UARTEx_ReceiveToIdle_DMA(lld_instance->usart_handle, lld_instance->recv_buff, lld_instance->recv_buff_size);
    HAL_UARTEx_ReceiveToIdle_DMA(rld_instance->usart_handle, rld_instance->recv_buff, rld_instance->recv_buff_size);

    // 关闭 DMA 半传输中断
    __HAL_DMA_DISABLE_IT(lld_instance->usart_handle->hdmarx, DMA_IT_HT);
    __HAL_DMA_DISABLE_IT(rld_instance->usart_handle->hdmarx, DMA_IT_HT);
}
#ifdef LIDAR_INFO_HANDLE_OUT

static uint8_t lidar_buff[LIDAR_FRAME_SIZE + 1]; // +1: for indentification of left and right

void lidar_data_handle(uint8_t *buffer)
{
    uint8_t temp = 0;
    if ((buffer[0] == 0x59) && (buffer[1] == 0x59))
    {
        uint8_t checksum = 0;
        for (uint8_t i = 0; i < 8; i++)
        {
            checksum += buffer[i];
        }
        if (checksum == buffer[8])
        {
            if (buffer[9] == 0) // left lidar
            {
                ld_data->lld_distance = (uint16_t)(buffer[3] << 8 | buffer[2]);
            }
            else if (buffer[9] == 1) // right lidar
            {
                ld_data->rld_distance = (uint16_t)(buffer[3] << 8 | buffer[2]);
            }
        }
    }
}
#else
/**
 * @brief lidar data parses
 * 内部判断usart_instance给左右lidar赋值
 * @param ld_buff 接收buffer
 */
static void ld_buff_to_data(UART_HandleTypeDef *huart, uint8_t *ld_buff)
{
    if ((ld_buff[0] == 0x59) && (ld_buff[1] == 0x59))
    {
        uint8_t checksum = 0;
        for (uint8_t i = 0; i < 8; i++)
        {
            checksum += ld_buff[i];
        }
        if (checksum == ld_buff[8])
        {
            if (huart == &huart2)
            {
                ld_data->lld_distance = (uint16_t)(ld_buff[3] << 8 | ld_buff[2]);
            }
            else if (huart == &huart4)
            {
                ld_data->rld_distance = (uint16_t)(ld_buff[3] << 8 | ld_buff[2]);
            }
        }
        return; // 协议错误
    }
}
#endif

/**
 * @brief ld_buff_to_data,用于注册到bsp_usart的回调函数中
 *
 * @note huart2: the address of left lidar usart handle
 *       huart4: the address of right lidar usart handle
 */
static void LDRxCallback(UART_HandleTypeDef *huart, uint16_t Size) // 串口接收回调_
{
    DaemonReload(ld_daemon_instance); // 先喂狗
#ifdef LIDAR_INFO_HANDLE_OUT
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    if (huart == &huart2)
    {
        memset(lidar_buff, 0, LIDAR_FRAME_SIZE + 1);
        memcpy(lidar_buff, lld_instance->recv_buff, Size);
        lidar_buff[Size] = 0; // 左激光雷达标识
        xQueueSendFromISR(lidarQueue, &lidar_buff, 0);
    }
    else if (huart == &huart4)
    {
        // memset(lidar_buff, 0, LIDAR_FRAME_SIZE + 1);
        memcpy(lidar_buff, rld_instance->recv_buff, Size);
        lidar_buff[Size] = 1; // 右激光雷达标识
        xQueueSendFromISR(lidarQueue, &lidar_buff, 0);
    }
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
#else
    if (huart == &huart2)
    {
        ld_buff_to_data(huart, lld_instance->recv_buff);
    }
    else if (huart == &huart4)
    {
        ld_buff_to_data(huart, rld_instance->recv_buff);
    }
#endif
}

/**
 * @brief 雷达离线的回调函数,注册到守护进程中,串口掉线时调用
 * @note huart2: the address of left lidar usart handle
 *       huart4: the address of right lidar usart handle
 */
static void LDLostCallback(void *id) // id is corresponding usart handle
{
    if (id == &huart2) // left lidar handle
    {
        // memset(ld_data->lld_distance, 0, sizeof(ld_data->lld_distance)); // 清空数据
        USARTServiceInit(lld_instance); // 尝试重新启动接收
        // LOGWARNING("[lidar] left lidar lost");
    }
    else
    {
        // memset(ld_data->rld_distance, 0, sizeof(ld_data->rld_distance)); // 清空数据
        USARTServiceInit(rld_instance); // 尝试重新启动接收
        // LOGWARNING("[lidar] right lidar lost");
    }
}

LD_data_t *Lidar_Init(UART_HandleTypeDef *ld_usart_handle)
{
    USART_Init_Config_s conf;
    conf.module_callback = LDRxCallback;
    conf.usart_handle = ld_usart_handle;
    conf.recv_buff_size = LIDAR_FRAME_SIZE;
    if (ld_usart_handle == &huart2) // left lidar handle
    {
        ld_data->lld_distance = 0;
        lld_instance = USARTRegister(&conf);
    }
    else if (ld_usart_handle == &huart4) // right lidar handle
    {
        ld_data->rld_distance = 0;
        rld_instance = USARTRegister(&conf);
    }

    Daemon_Init_Config_s daemon_conf = {
        .reload_count = 2, // 看门狗待了解_ 20ms没收到消息  输出频率默认为100Hz->10ms
        .callback = LDLostCallback,
        .owner_id = ld_usart_handle,
    };
    ld_daemon_instance = DaemonRegister(&daemon_conf);
    return ld_data;
}
