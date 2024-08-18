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
        USARTSend(mp3_instance, slight, DROUGHT_BUFF_LEN, USART_TRANSFER_DMA);
        break;
    case GENERAL:
        USARTSend(mp3_instance, general, DROUGHT_BUFF_LEN, USART_TRANSFER_DMA);
        break;
    case SERIOUS:
        USARTSend(mp3_instance, serious, DROUGHT_BUFF_LEN, USART_TRANSFER_DMA);
        break;
    default:
        break;
    }
}
