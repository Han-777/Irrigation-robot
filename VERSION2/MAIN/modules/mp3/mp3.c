#include "mp3.h"
#include "bsp_usart.h"

#define DROUGHT_BUFF_LEN 8
static USARTInstance *mp3_instance;
static uint8_t slight[DROUGHT_BUFF_LEN] = {0x7E, 0x04, 0x45, 0x00, 0x01, 0xEF, 0x0D, 0x0A};  // 轻微干旱
static uint8_t general[DROUGHT_BUFF_LEN] = {0x7E, 0x04, 0x45, 0x00, 0x02, 0xEF, 0x0D, 0x0A}; // 一般干旱
static uint8_t serious[DROUGHT_BUFF_LEN] = {0x7E, 0x04, 0x45, 0x00, 0x03, 0xEF, 0x0D, 0x0A}; // 严重干旱

void MP3_Init(UART_HandleTypeDef *mp3_usart_handle)
{
    USART_Init_Config_s conf;
    conf.module_callback = NULL; // 不需要接收
    conf.recv_buff_size = 0;
    conf.usart_handle = mp3_usart_handle;
    mp3_instance = USARTRegister(&conf);
    return;
}
// 语音播报
void MP3_broadcast(Drought_Info_e info)
{
    switch (info)
    {
    case SLIGHT:
        USARTSend(mp3_instance, slight, DROUGHT_BUFF_LEN, USART_TRANSFER_IT);
        break;
    case GENERAL:
        USARTSend(mp3_instance, general, DROUGHT_BUFF_LEN, USART_TRANSFER_IT);
        break;
    case SERIOUS:
        USARTSend(mp3_instance, serious, DROUGHT_BUFF_LEN, USART_TRANSFER_IT);
        break;
    default:
        break;
    }
}

// #include "mp3.h"
// #include "bsp_usart.h"

// #define DROUGHT_BUFF_LEN 8
// static VIRTUALInstance *mp3_instance;
// uint8_t slight[DROUGHT_BUFF_LEN] = {0x7E, 0x04, 0x45, 0x00, 0x01, 0xEF, 0x0D, 0x0A};  // 轻微干旱
// uint8_t general[DROUGHT_BUFF_LEN] = {0x7E, 0x04, 0x45, 0x00, 0x02, 0xEF, 0x0D, 0x0A}; // 一般干旱
// uint8_t serious[DROUGHT_BUFF_LEN] = {0x7E, 0x04, 0x45, 0x00, 0x03, 0xEF, 0x0D, 0x0A}; // 严重干旱

// void MP3_Init(void)
// {
//     VIRTUAL_Init_Config_s conf;
//     conf.tx_pin = MP3_VIRTUAL_UART_TX_Pin;
//     conf.tx_port = MP3_VIRTUAL_UART_TX_GPIO_Port;
//     conf.rx_pin = MP3_VIRTUAL_UART_RX_Pin;
//     conf.rx_port = MP3_VIRTUAL_UART_RX_GPIO_Port;
//     conf.recv_buff_size = 0;
//     conf.trans_baud = VIRTUAL_BAUDRATE_9600;

//     mp3_instance = VIRTUAL_USARTRegister(&conf);
// }
// // 语音播报
// void MP3_broadcast(Drought_Info_e info)
// {
//     if (info == SLIGHT)
//     {
//         VirtualCOM_SendArr(mp3_instance, slight, DROUGHT_BUFF_LEN);
//     }
//     else if (info == GENERAL)
//     {
//         VirtualCOM_SendArr(mp3_instance, general, DROUGHT_BUFF_LEN);
//     }
//     else if (info == SERIOUS)
//     {
//         VirtualCOM_SendArr(mp3_instance, serious, DROUGHT_BUFF_LEN);
//     }
//     else
//     {
//         VirtualCOM_SendArr(mp3_instance, slight, DROUGHT_BUFF_LEN);
//     }
// }
