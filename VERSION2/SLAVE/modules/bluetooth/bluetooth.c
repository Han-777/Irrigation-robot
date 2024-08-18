#include "bluetooth.h"
#include "bsp_usart.h"
#include <string.h>
#include "daemon.h"

#define bluetooth_FRAME_SIZE 22
#define bluetooth_FRAME_HEAD 0x7EAA
#define bluetooth_FRAME_TAIL 0x7F55
static BLUETOOTH_data_t *bluetooth_data;
static USARTInstance *bluetooth_instance;

static void bluetooth_buff_to_data(uint16_t size)
{
    if (size == bluetooth_instance->recv_buff_size)
    {
        if ((bluetooth_instance->recv_buff[0] == (uint8_t)(bluetooth_FRAME_HEAD >> 8) && bluetooth_instance->recv_buff[1] == (uint8_t)(bluetooth_FRAME_HEAD & 0xFF)) &&
            (bluetooth_instance->recv_buff[bluetooth_FRAME_SIZE - 2] == (uint8_t)(bluetooth_FRAME_TAIL >> 8) && bluetooth_instance->recv_buff[bluetooth_FRAME_SIZE - 1] == (uint8_t)(bluetooth_FRAME_TAIL & 0xFF)))
        {
            memcpy(bluetooth_data, bluetooth_instance->recv_buff[2], 18);
            return;
        }
    }
}
/**
 * @brief ld_buff_to_data,用于注册到bsp_usart的回调函数中
 *
 * @note huart2: the address of left lidar usart handle
 *       huart4: the address of right lidar usart handle
 */
static void BTRxCallback(UART_HandleTypeDef *huart, uint16_t size) // 串口接收回调_
{
    bluetooth_buff_to_data(size);
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
    return bluetooth_data;
}
