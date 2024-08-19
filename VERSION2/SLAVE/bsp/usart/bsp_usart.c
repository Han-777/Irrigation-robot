/**
 * @file bsp_usart.c
 * @author Han-777
 * @brief  串口bsp层的实现
 * @version beta
 * @date 2024-07-06
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "bsp_usart.h"
#include "stdlib.h"
#include "memory.h"

/*============for virtual usart====================*/
#include "bsp_dwt.h"

/* usart service instance, modules' info would be recoreded here using USARTRegister() */
/* usart服务实例,所有注册了usart的模块信息会被保存在这里 */
static uint8_t usart_instance_idx = 0;
static USARTInstance *usart_instance[DEVICE_USART_CNT] = {NULL};

// 内存处理
#define MY_SECTION_SIZE_LIMIT 2 * 1024 // 2KB(for memory protection unit), ram size
__attribute__((section(".my_section"))) static uint8_t my_section[MY_SECTION_SIZE_LIMIT];
static size_t my_section_offset = 0;
void *my_malloc(size_t size)
{
    if (my_section_offset + size > MY_SECTION_SIZE_LIMIT)
        while (1)
            ;
    void *ptr = &my_section[my_section_offset];
    my_section_offset += size;
    return ptr;
}

/**
 * @brief 启动串口服务,会在每个实例注册之后自动启用接收,当前实现为DMA接收,后续可能添加IT和BLOCKING接收
 *
 * @todo 串口服务会在每个实例注册之后自动启用接收,当前实现为DMA接收,后续可能添加IT和BLOCKING接收
 *       可能还要将此函数修改为extern,使得module可以控制串口的启停
 *
 * @param _instance instance owned by module,模块拥有的串口实例
 */
void USARTServiceInit(USARTInstance *_instance)
{
    // HAL_UARTEx_ReceiveToIdle_IT(_instance->usart_handle, _instance->recv_buff, _instance->recv_buff_size); // 后面再尝试，目前全部用dma

    HAL_UARTEx_ReceiveToIdle_DMA(_instance->usart_handle, _instance->recv_buff, _instance->recv_buff_size);
    // 关闭dma half transfer中断防止两次进入HAL_UARTEx_RxEventCallback()
    // 这是HAL库的一个设计失误,发生DMA传输完成/半完成以及串口IDLE中断都会触发HAL_UARTEx_RxEventCallback()
    // 我们只希望处理第一种和第三种情况,因此直接关闭DMA半传输中断
    __HAL_DMA_DISABLE_IT(_instance->usart_handle->hdmarx, DMA_IT_HT);
}

USARTInstance *USARTRegister(USART_Init_Config_s *init_config)
{
    if (usart_instance_idx > DEVICE_USART_CNT) // 超过最大实例数
        while (1)
            ;
    for (uint8_t i = 0; i < usart_instance_idx; i++)
    {
        if (usart_instance[i]->usart_handle == init_config->usart_handle)
            while (1)
                // LOGERROR("[bsp_usart]: USART instance %d is already registered!\n", i);
                ;
    }
    USARTInstance *instance = (USARTInstance *)my_malloc(sizeof(USARTInstance));
    memset(instance, 0, sizeof(USARTInstance));

    instance->usart_handle = init_config->usart_handle;
    instance->recv_buff_size = init_config->recv_buff_size;
    instance->module_callback = init_config->module_callback;
    instance->recv_buff = (uint8_t *)my_malloc(init_config->recv_buff_size);

    usart_instance[usart_instance_idx++] = instance;
    USARTServiceInit(instance);
    return instance;
}
// double buffer regisitor

/* @todo 当前仅进行了形式上的封装,后续要进一步考虑是否将module的行为与bsp完全分离 */
void USARTSend(USARTInstance *_instance, uint8_t *send_buf, uint16_t send_size, USART_TRANSFER_MODE mode)
{
    switch (mode)
    {
    case USART_TRANSFER_BLOCKING:
        HAL_UART_Transmit(_instance->usart_handle, send_buf, send_size, 100);
        break;
    case USART_TRANSFER_IT:
        HAL_UART_Transmit_IT(_instance->usart_handle, send_buf, send_size);
        break;
    case USART_TRANSFER_DMA:
        HAL_UART_Transmit_DMA(_instance->usart_handle, send_buf, send_size);
        break;
    default:
        while (1)
            ; // illegal mode! check your code context! 检查定义instance的代码上下文,可能出现指针越界
        break;
    }
}

/* 串口发送时,gstate会被设为BUSY_TX */
uint8_t USARTIsReady(USARTInstance *_instance)
{
    if (_instance->usart_handle->gState | HAL_UART_STATE_BUSY_TX)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/**
 * @brief 每次dma/idle中断发生时，都会调用此函数.对于每个uart实例会调用对应的回调进行进一步的处理
 *        例如:视觉协议解析/遥控器解析/裁判系统解析
 *
 * @note  通过__HAL_DMA_DISABLE_IT(huart->hdmarx,DMA_IT_HT)关闭dma half transfer中断防止两次进入HAL_UARTEx_RxEventCallback()
 *        这是HAL库的一个设计失误,发生DMA传输完成/半完成以及串口IDLE中断都会触发HAL_UARTEx_RxEventCallback()
 *        我们只希望处理，因此直接关闭DMA半传输中断第一种和第三种情况
 *
 * @param huart 发生中断的串口
 * @param Size 此次接收到的总数居量,暂时没用
 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    for (uint8_t i = 0; i < usart_instance_idx; ++i)
    {
        if (huart == usart_instance[i]->usart_handle)
        {
            if (usart_instance[i]->module_callback != NULL)
            {
                // SCB_CleanInvalidateDCache(); // the easiest way with lowest efficiency
                // SCB_InvalidateDCache(); // [cache<-sram]稍微高一些(SCB_CleanDCache[cache->sram])
                // SCB_InvalidateDCache_by_Addr((uint32_t *)usart_instance[i]->recv_buff, (usart_instance[i]->recv_buff_size + 31) / 32); // 前面加1是因为HAL库);
                usart_instance[i]->module_callback(huart, Size);
                memset(usart_instance[i]->recv_buff, 0, Size); // 接收结束后清空buffer,对于变长数据是必要的
            }
            HAL_UARTEx_ReceiveToIdle_DMA(usart_instance[i]->usart_handle, usart_instance[i]->recv_buff, usart_instance[i]->recv_buff_size);
            // HAL_UARTEx_Receiv eToIdle_IT(usart_instance[i]->usart_handle, usart_instance[i]->recv_buff, usart_instance[i]->recv_buff_size);
            __HAL_DMA_DISABLE_IT(usart_instance[i]->usart_handle->hdmarx, DMA_IT_HT);
            return; // break the loop
        }
    }
}

/**
 * @brief 当串口发送/接收出现错误时,会调用此函数,此时这个函数要做的就是重新启动接收
 *
 * @note  最常见的错误:奇偶校验/溢出/帧错误
 *
 * @param huart 发生错误的串口
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    for (uint8_t i = 0; i < usart_instance_idx; ++i)
    {
        if (huart == usart_instance[i]->usart_handle)
        {
            uint32_t error = HAL_UART_GetError(huart);
            if (error & HAL_UART_ERROR_ORE)
            {
                // 溢出错误，可能需要清空接收缓冲区
                __HAL_UART_CLEAR_OREFLAG(huart);
                memset(usart_instance[i]->recv_buff, 0, usart_instance[i]->recv_buff_size);
            }

            if (error & HAL_UART_ERROR_FE)
            {
                // 帧错误，可能需要重新同步
                HAL_UART_AbortReceive(huart);
            }

            if (error & HAL_UART_ERROR_NE || error & HAL_UART_ERROR_PE)
            {
                // 噪声错误或奇偶校验错误，可能需要调整波特率或校验设置
                // 这里仅记录，实际调整需要更复杂的逻辑
            }

            // HAL_UARTEx_ReceiveToIdle_IT(usart_instance[i]->usart_handle, usart_instance[i]->recv_buff, usart_instance[i]->recv_buff_size);
            HAL_UARTEx_ReceiveToIdle_DMA(usart_instance[i]->usart_handle, usart_instance[i]->recv_buff, usart_instance[i]->recv_buff_size);
            __HAL_DMA_DISABLE_IT(usart_instance[i]->usart_handle->hdmarx, DMA_IT_HT);
            return;
        }
    }
}

/*================================VIRTUAL USART==================================*/
static uint8_t virtual_instance_idx = 0;

/**
 * @brief Virtual usart register
 *
 */
VIRTUALInstance *VIRTUAL_USARTRegister(VIRTUAL_Init_Config_s *init_config)
{
    if (virtual_instance_idx > DEVICE_VIRTUAL_CNT)
        while (1)
            ;
    VIRTUALInstance *instance = (VIRTUALInstance *)malloc(sizeof(VIRTUALInstance));
    memset(instance, 0, sizeof(VIRTUALInstance));

    instance->tx_pin = init_config->tx_pin;
    instance->rx_pin = init_config->rx_pin;
    instance->tx_port = init_config->tx_port;
    instance->rx_port = init_config->rx_port;
    instance->recv_buff_size = init_config->recv_buff_size;
    instance->recv_buff = (uint8_t *)malloc(init_config->recv_buff_size);
    instance->trans_baud = init_config->trans_baud;

    virtual_instance_idx++;
    return instance;
}

/* @todo 在实现freertos之后补充delay_us的实现 */
void VirtualCOM_ByteSend(VIRTUALInstance *instance, uint8_t data)
{
    uint8_t i;
    HAL_GPIO_WritePin(instance->tx_port, instance->tx_pin, GPIO_PIN_RESET); // 发送起始位
    // delay_us(instance->trans_baud); // after freertos
    for (i = 0; i < 8; i++) // 发送8位数据位
    {
        if (data & 0x01)
            HAL_GPIO_WritePin(instance->tx_port, instance->tx_pin, GPIO_PIN_SET); // 1
        else
            HAL_GPIO_WritePin(instance->tx_port, instance->tx_pin, GPIO_PIN_RESET); // 0
        data >>= 1;
        DWT_Delay_us(instance->trans_baud);
        // delay_us(instance->trans_baud); // after freertos
    }
    HAL_GPIO_WritePin(instance->tx_port, instance->tx_pin, GPIO_PIN_SET); // 发送结束位
    DWT_Delay_us(instance->trans_baud);
    // delay_us(instance->trans_baud); // after freertos
}

void VirtualCOM_SendArr(VIRTUALInstance *instance, uint8_t *arr, size_t arr_len)
{
    for (size_t i = 0; i < arr_len; i++)
    {
        VirtualCOM_ByteSend(instance, arr[i]);
    }
}