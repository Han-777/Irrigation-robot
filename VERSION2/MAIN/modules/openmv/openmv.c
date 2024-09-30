#include "openmv.h"
#include "bsp_usart.h"
#include <string.h>
#include "daemon.h"

#define OPENMV_FRAME_SIZE 20
#define OPENMV_FRAME_HEAD 0x7EAA
#define OPENMV_FRAME_TAIL 0xBB55
static OPENMV_data_t *openmv_data;
static USARTInstance *openmv_instance; // left lidar

void Mv_Close(void)
{
    // HAL_UART_Abort_IT(&huart3);
    HAL_UART_AbortReceive_IT(openmv_instance->usart_handle);

    // 清空接收缓冲区
    memset(openmv_instance->recv_buff, 0, openmv_instance->recv_buff_size);
}

void Mv_Open(void)
{
    // HAL_UART_Receive_IT(&huart3, openmv_instance->recv_buff, openmv_instance->recv_buff_size);
    // 启动 UART 接收
    HAL_UARTEx_ReceiveToIdle_DMA(openmv_instance->usart_handle, openmv_instance->recv_buff, openmv_instance->recv_buff_size);

    // 关闭 DMA 半传输中断
    __HAL_DMA_DISABLE_IT(openmv_instance->usart_handle->hdmarx, DMA_IT_HT);
}

static void openmv_buff_to_data(uint16_t size)
{
    for (int i = 0; i < OPENMV_FRAME_SIZE - 5; ++i)
    {
        if ((openmv_instance->recv_buff[i] == (uint8_t)(OPENMV_FRAME_HEAD >> 8) && openmv_instance->recv_buff[i + 1] == (uint8_t)(OPENMV_FRAME_HEAD & 0xFF)) && (openmv_instance->recv_buff[i + 3] == (uint8_t)(OPENMV_FRAME_TAIL >> 8) && openmv_instance->recv_buff[i + 4] == (uint8_t)(OPENMV_FRAME_TAIL & 0xFF)))
        {
            openmv_data->color = openmv_instance->recv_buff[i + 2];
            // memcpy(bluetoothata->drought_buff, &bluetooth_instance->recv_buff[i + 2], 18);
            // for (int i = 0; i < 18; ++i)
            // {
            //     bluetooth_data->drought_buff[i] = bluetooth_instance->recv_buff[i + 2];
            // }
            return;
        }
    }

    // if ((openmv_instance->recv_buff[0] == (uint8_t)(OPENMV_FRAME_HEAD >> 8) && openmv_instance->recv_buff[1] == (uint8_t)(OPENMV_FRAME_HEAD & 0xFF)) &&
    //     (openmv_instance->recv_buff[OPENMV_FRAME_SIZE - 2] == (uint8_t)(OPENMV_FRAME_TAIL >> 8) && openmv_instance->recv_buff[OPENMV_FRAME_SIZE - 1] == (uint8_t)(OPENMV_FRAME_TAIL & 0xFF)))
    // {
    //     // memcpy(openmv_data, &openmv_instance->recv_buff[2], 1);
    //     openmv_data->color = openmv_instance->recv_buff[2];
    //     return;
    // }
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
    // memset(openmv_instance, 0, sizeof(openmv_instance));
    USARTServiceInit(openmv_instance);
}

OPENMV_data_t *OPENMV_Init(UART_HandleTypeDef *openmv_usart_handle)
{
    USART_Init_Config_s conf;
    conf.module_callback = MVRxCallback;
    conf.usart_handle = openmv_usart_handle;
    conf.recv_buff_size = OPENMV_FRAME_SIZE;
    openmv_instance = USARTRegister(&conf);
    openmv_data->color = NONE;
    return openmv_data;
}
