#include "bluetooth.h"
#include "bsp_usart.h"
#include <string.h>
#include "daemon.h"

#define bluetooth_FRAME_SIZE 100
#define bluetooth_FRAME_HEAD 0x7EAA
#define bluetooth_FRAME_TAIL 0x7F55
static BLUETOOTH_data_t *bluetooth_data;
static USARTInstance *bluetooth_instance;
void bluetooth_buff_to_data(void)
{
    for (int i = 0; i < bluetooth_FRAME_SIZE - 22; ++i)
    {
        if (bluetooth_instance->recv_buff[i] == 0x7E && bluetooth_instance->recv_buff[i + 1] == 0xAA && bluetooth_instance->recv_buff[i + 20] == 0x7F && bluetooth_instance->recv_buff[i + 21] == 0x55)
        {
            for (size_t j = 0; j < 18; ++j)
            {
                bluetooth_data->drought_buff[j] = bluetooth_instance->recv_buff[i + 2 + j];
            }
        }
        // if ((bluetooth_instance->recv_buff[i] == (uint8_t)(bluetooth_FRAME_HEAD >> 8) && bluetooth_instance->recv_buff[i + 1] == (uint8_t)(bluetooth_FRAME_HEAD & 0xFF)) && (bluetooth_instance->recv_buff[i + 20] == (uint8_t)(bluetooth_FRAME_TAIL >> 8) && bluetooth_instance->recv_buff[i + 21] == (uint8_t)(bluetooth_FRAME_TAIL & 0xFF)))
        // {
        //     memcpy(bluetooth_data->drought_buff, &bluetooth_instance->recv_buff[i + 2], 18);
        //     // for (int i = 0; i < 18; ++i)
        //     // {
        //     //     bluetooth_data->drought_buff[i] = bluetooth_instance->recv_buff[i + 2];
        //     // }
        //     // return;
        // }
    }
    // if ((bluetooth_instance->recv_buff[0] == (uint8_t)(bluetooth_FRAME_HEAD >> 8) && bluetooth_instance->recv_buff[1] == (uint8_t)(bluetooth_FRAME_HEAD & 0xFF)) &&
    //     (bluetooth_instance->recv_buff[bluetooth_FRAME_SIZE - 2] == (uint8_t)(bluetooth_FRAME_TAIL >> 8) && bluetooth_instance->recv_buff[bluetooth_FRAME_SIZE - 1] == (uint8_t)(bluetooth_FRAME_TAIL & 0xFF)))
    // {
    //     memcpy(bluetooth_data->drought_buff, &bluetooth_instance->recv_buff[2], 18);
    //     // for (int i = 0; i < 18; ++i)
    //     // {
    //     //     bluetooth_data->drought_buff[i] = bluetooth_instance->recv_buff[i + 2];
    //     // }
    //     return;
    // }
}
/**
 * @brief ld_buff_to_data,用于注册到bsp_usart的回调函数中
 *
 * @note huart2: the address of left lidar usart handle
 *       huart4: the address of right lidar usart handle
 */
static void BTRxCallback(UART_HandleTypeDef *huart, uint16_t size) // 串口接收回调_
{
    bluetooth_buff_to_data();
}

/**
 * @brief
 * @note
 *
 */
static void MVLostCallback(void *id) // id is corresponding usart handle
{
    memset(bluetooth_instance, 0, sizeof(bluetooth_instance));
    USARTServiceInit(bluetooth_instance);
}

BLUETOOTH_data_t *Bluetooth_Init(UART_HandleTypeDef *bluetooth_usart_handle)
{
    USART_Init_Config_s conf;
    conf.module_callback = BTRxCallback;
    conf.usart_handle = bluetooth_usart_handle;
    conf.recv_buff_size = bluetooth_FRAME_SIZE;
    bluetooth_instance = USARTRegister(&conf);

    memset(bluetooth_data->drought_buff, 0, sizeof(BLUETOOTH_data_t));
    return bluetooth_data;
}
