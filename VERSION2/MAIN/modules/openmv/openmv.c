#include "openmv.h"
#include "bsp_usart.h"
#include <string.h>
#include "daemon.h"

#define OPENMV_FRAME_SIZE 5
#define OPENMV_FRAME_HEAD 0x7EAA
#define OPENMV_FRAME_TAIL 0x7F55
static OPENMV_data_t *openmv_data;
static USARTInstance *openmv_instance; // left lidar

static void openmv_buff_to_data(uint16_t size)
{
    if (size == openmv_instance->recv_buff_size)
    {
        if ((openmv_instance->recv_buff[0] == (uint8_t)(OPENMV_FRAME_HEAD >> 8) && openmv_instance->recv_buff[1] == (uint8_t)(OPENMV_FRAME_HEAD & 0xFF)) &&
            (openmv_instance->recv_buff[OPENMV_FRAME_SIZE - 2] == (uint8_t)(OPENMV_FRAME_TAIL >> 8) && openmv_instance->recv_buff[OPENMV_FRAME_SIZE - 1] == (uint8_t)(OPENMV_FRAME_TAIL & 0xFF)))
        {
            memcpy(openmv_data, &openmv_instance->recv_buff[2], 1);
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
static void MVRxCallback(UART_HandleTypeDef *huart, uint16_t size) // 串口接收回调_
{
    openmv_buff_to_data(size);
}

/**
 * @brief
 * @note
 *
 */
static void MVLostCallback(void *id) // id is corresponding usart handle
{
    memset(openmv_instance, 0, sizeof(openmv_instance));
    USARTServiceInit(openmv_instance);
}

OPENMV_data_t *OPENMV_Init(UART_HandleTypeDef *openmv_usart_handle)
{
    USART_Init_Config_s conf;
    conf.module_callback = MVRxCallback;
    conf.usart_handle = openmv_usart_handle;
    conf.recv_buff_size = OPENMV_FRAME_SIZE;
    openmv_instance = USARTRegister(&conf);
    return openmv_data;
}
