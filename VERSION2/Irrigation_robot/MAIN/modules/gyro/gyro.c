#include "gyro.h"
#include "bsp_usart.h"
#include "daemon.h"
#include <string.h>

#define GYRO_FRAME_SIZE 64 // gyro receive buffer size

static GYRO_data_t gyro_data;
static DaemonInstance *GYRO_daemon_instance;
static USARTInstance *gyro_instance;

/**
 * @brief gyro data parses
 *
 * @param GYRO_buff 接收buffer
 */
static uint16_t GYRO_buff_to_data(const uint8_t *GYRO_buff)
{
    if ((GYRO_buff[0] == 0x59) && (GYRO_buff[1] == 0x59))
    {
        uint8_t checksum = 0;
        for (uint8_t i = 0; i < 8; i++)
        {
            checksum += GYRO_buff[i];
        }
        if (checksum == GYRO_buff[8])
        {
            return (uint16_t)(GYRO_buff[3] << 8 | GYRO_buff[2]);
        }
    }
}

/**
 * @brief GYRO_buff_to_data,用于注册到bsp_usart的回调函数中
 *
 * @note huart2: the address of left lidar usart handle
 *       huart4: the address of right lidar usart handle
 */
static void GYRORxCallback(UART_HandleTypeDef *huart) // 串口接收回调_
{
    DaemonReload(GYRO_daemon_instance); // 先喂狗
    GYRO_buff_to_data(gyro_instance->rx_buff);
}

/**
 * @brief 雷达离线的回调函数,注册到守护进程中,串口掉线时调用
 * @note huart2: the address of left lidar usart handle
 *       huart4: the address of right lidar usart handle
 */
static void GYROLostCallback(void *id) // id is corresponding usart handle
{
    if (id == &huart2) // left lidar handle
    {
        memset(GYRO_data.lGYRO_distance, 0, sizeof(GYRO_data.lGYRO_distance)); // 清空数据
        USARTServiceInit(lGYRO_instance);                                      // 尝试重新启动接收
        LOGWARNING("[lidar] right lidar lost");
    }
    else
    {
        memset(GYRO_data.rGYRO_distance, 0, sizeof(GYRO_data.rGYRO_distance)); // 清空数据
        USARTServiceInit(rGYRO_instance);                                      // 尝试重新启动接收
        LOGWARNING("[lidar] left lidar lost");
    }
}

GYRO_data_t *Lidar_Init(UART_HandleTypeDef *GYRO_usart_handle)
{
    USART_Init_Config_s conf;
    conf.module_callback = GYRORxCallback;
    conf.usart_handle = GYRO_usart_handle;
    conf.recv_buff_size = LIDAR_FRAME_SIZE;
    if (GYRO_usart_handle == &huart2) // left lidar handle
    {
        lGYRO_instance = USARTRegister(&conf);
    }
    else if (GYRO_usart_handle == &huart4) // right lidar handle
    {
        rGYRO_instance = USARTRegister(&conf);
    }

    Daemon_Init_Config_s daemon_conf = {
        .reload_count = 2, // 看门狗待了解_ 20ms没收到消息  输出频率默认为100Hz->10ms
        .callback = GYROLostCallback,
        .owner_id = GYRO_usart_handle,
    };
    GYRO_daemon_instance = DaemonRegister(&daemon_conf);
}

/**
 * @brief transfer data from hexadecimaml to floating-point values
 * 实现16进制的can数据转换成浮点型数据
 */
float DATA_Trans(u8 Data_1, u8 Data_2, u8 Data_3, u8 Data_4)
{
    long long transition_32;
    float tmp = 0;
    int sign = 0;
    int exponent = 0;
    float mantissa = 0;
    transition_32 = 0;
    transition_32 |= Data_4 << 24;
    transition_32 |= Data_3 << 16;
    transition_32 |= Data_2 << 8;
    transition_32 |= Data_1;
    sign = (transition_32 & 0x80000000) ? -1 : 1; // 符号位
    // 先右移操作，再按位与计算，出来结果是30到23位对应的e
    exponent = ((transition_32 >> 23) & 0xff) - 127;
    // 将22~0转化为10进制，得到对应的x系数
    mantissa = 1 + ((float)(transition_32 & 0x7fffff) / 0x7fffff);
    tmp = sign * mantissa * pow(2, exponent);
    return tmp;
}

long long timestamp(u8 Data_1, u8 Data_2, u8 Data_3, u8 Data_4)
{
    u32 transition_32;
    transition_32 = 0;
    transition_32 |= Data_4 << 24;
    transition_32 |= Data_3 << 16;
    transition_32 |= Data_2 << 8;
    transition_32 |= Data_1;
    return transition_32;
}