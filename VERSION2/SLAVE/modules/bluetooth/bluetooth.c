#include "bluetooth.h"
#include "bsp_usart.h"
#include <string.h>
#include "daemon.h"

#define BLUETOOTH_FRAME_SZIE 28
#define BLUETOOTH_FRAME_HEAD 0x2C2D
#define BLUETOOTH_FRAME_TAIL 0x5B5A
static uint8_t bluetooth_data[BLUETOOTH_FRAME_SZIE];
static USARTInstance *bluetooth_instance;

// static void bluetooth_buff_to_data(void)
// {
//     if (bluetooth_instance->recv_buff[0] == (BLUETOOTH_FRAME_HEAD >> 8) && bluetooth_instance->recv_buff[1] == (BLUETOOTH_FRAME_HEAD & 0x00ff) && bluetooth_instance->recv_buff[BLUETOOTH_FRAME_SZIE - 2] == (BLUETOOTH_FRAME_TAIL >> 8) && bluetooth_instance->recv_buff[BLUETOOTH_FRAME_SZIE - 1] == (BLUETOOTH_FRAME_TAIL & 0x00ff))
//     {
//         memcpy(bluetooth_data, bluetooth_instance->recv_buff + sizeof(BLUETOOTH_FRAME_HEAD) * 8, BLUETOOTH_FRAME_SZIE - sizeof(BLUETOOTH_FRAME_HEAD) - sizeof(BLUETOOTH_FRAME_TAIL)); // 去除头尾
//         return;
//     }
// }

// /**
//  * @brief ld_buff_to_data,用于注册到bsp_usart的回调函数中
//  *
//  * @note
//  *
//  */
// static void MVRxCallback(UART_HandleTypeDef *huart, uint16_t Size) // 串口接收回调_
// {
//     bluetooth_buff_to_data();
// }

// /**
//  * @brief
//  * @note
//  *
//  */
// static void MVLostCallback(void *id) // id is corresponding usart handle
// {
//     memset(bluetooth_instance, 0, sizeof(bluetooth_instance));
//     USARTServiceInit(bluetooth_instance);
// }

// BLUETOOTH_data_t *BLUETOOTH_Init(UART_HandleTypeDef *bluetooth_usart_handle)
// {
//     USART_Init_Config_s conf;
//     conf.module_callback = MVRxCallback;
//     conf.usart_handle = bluetooth_usart_handle;
//     conf.recv_buff_size = BLUETOOTH_FRAME_SZIE;
//     bluetooth_instance = USARTRegister(&conf);

//     return bluetooth_data;
// }

// bluetooth_data *Bluetooth_Init(UART_HandleTypeDef *bluetooth_usart_handle)
// {

// }