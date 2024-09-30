#include "usart_comm.h"
#include "bsp_usart.h"
#include "robot_def.h"
#include <string.h>

#define Comm_Frame_Size 19
#define FRAME_HEAD 0xAA
static Drought_Info_e drought_info[18];
static USARTInstance *comm_instance;

// 直接做数据处理
static void USART_Comm_Rx_Callback(void)
{
    if (comm_instance->recv_buff[0] == FRAME_HEAD)
    {
        memcpy(drought_info, &comm_instance->recv_buff[1], 18);
    }
}

/*** @brief: D区：0xAA, drought_info || 0xAA, water_cnt + 1 */
void USART_Comm_Sned(uint8_t water_cnt, Drought_Info_e D_Drought_Info)
{
    uint8_t info = 0;
    if (water_cnt > 18) // D region
        info = D_Drought_Info;
    else
        info = water_cnt;
    uint8_t send_buff[2] = {0xAA, info};
    UARTSend(comm_instance, send_buff, 2, USART_TRANSFER_IT);
}

static void Drought_Info_e *UART_Comm_Init(UART_HandleTypeDef *comm_uart_handle)
{
    USART_Init_Config_s usart_config;
    usart_config.module_callback = USART_Comm_Rx_Callback;
    usart_config.usart_handle = comm_uart_handle;
    usart_config.recv_buff_size = Comm_Frame_Size;
    comm_instance = USARTRegister(&usart_config);
    return drought_info;
}