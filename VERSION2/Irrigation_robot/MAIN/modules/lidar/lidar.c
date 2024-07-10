#include "lidar.h"
#include "bsp_usart.h"
#include "daemon.h"
#include <string.h>

#define LIDAR_FRAME_SIZE 9 // lidar receive buffer size

static LD_data_t *ld_data;
// static USARTInstance *ld_instance[2] = {NULL};
static DaemonInstance *ld_daemon_instance;
static USARTInstance *lld_instance; // left lidar
static USARTInstance *rld_instance; // right lidar
/**
 * @brief lidar data parses
 * 内部判断usart_instance给左右lidar赋值
 * @param ld_buff 接收buffer
 */
static uint16_t ld_buff_to_data(const uint8_t *ld_buff)
{
    // for (uint8_t idx = 0; idx < LIDAR_FRAME_SIZE - 10; idx++)
    // {
    //     if ((ld_buff[idx] == 0x59) && (ld_buff[idx + 1] == 0x59))
    //     {
    //         uint8_t checksum = 0;
    //         for (uint8_t i = 0; i < 8; i++)
    //         {
    //             checksum += ld_buff[i];
    //         }
    //         if (checksum == ld_buff[8])
    //         {
    //             return (uint16_t)(ld_buff[3] << 8 | ld_buff[2]);
    //         }
    //     }
    // }
    // return 0; // 协议错误

    if ((ld_buff[0] == 0x59) && (ld_buff[1] == 0x59))
    {
        uint8_t checksum = 0;
        for (uint8_t i = 0; i < 8; i++)
        {
            checksum += ld_buff[i];
        }
        if (checksum == ld_buff[8])
        {
            return (uint16_t)(ld_buff[3] << 8 | ld_buff[2]);
        }
    }
    return 0; // 协议错误
}

/**
 * @brief ld_buff_to_data,用于注册到bsp_usart的回调函数中
 *
 * @note huart2: the address of left lidar usart handle
 *       huart4: the address of right lidar usart handle
 */
static void LDRxCallback(UART_HandleTypeDef *huart) // 串口接收回调_
{
    DaemonReload(ld_daemon_instance); // 先喂狗
    if (huart == &huart2)
    {
        ld_data->lld_distance = ld_buff_to_data(lld_instance->recv_buff); // 进行协议解析
    }
    else if (huart == &huart4)
    {
        ld_data->rld_distance = ld_buff_to_data(rld_instance->recv_buff);
    }
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
        memset(ld_data->lld_distance, 0, sizeof(ld_data->lld_distance)); // 清空数据
        USARTServiceInit(lld_instance);                                  // 尝试重新启动接收
        // LOGWARNING("[lidar] left lidar lost");
    }
    else
    {
        memset(ld_data->rld_distance, 0, sizeof(ld_data->rld_distance)); // 清空数据
        USARTServiceInit(rld_instance);                                  // 尝试重新启动接收
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
