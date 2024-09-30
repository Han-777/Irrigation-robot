#ifndef BSP_USART_H
#define BSP_USART_H

#include <stdint.h>
// #include "main.h"
#include "usart.h"

#define DEVICE_USART_CNT 5     // C板至多分配3个串口
#define USART_RXBUFF_LIMIT 256 // 如果协议需要更大的buff,请修改这里

// USART handle
// 模块回调函数,用于解析协议
typedef void (*usart_module_callback)(UART_HandleTypeDef *huart, uint16_t Size);

/* 发送模式枚举 */
typedef enum
{
    USART_TRANSFER_NONE = 0,
    USART_TRANSFER_BLOCKING,
    USART_TRANSFER_IT,
    USART_TRANSFER_DMA,
} USART_TRANSFER_MODE;

// 串口实例结构体,每个module都要包含一个实例.
// 由于串口是独占的点对点通信,所以不需要考虑多个module同时使用一个串口的情况,因此不用加入id;当然也可以选择加入,这样在bsp层可以访问到module的其他信息
typedef struct // relate to usart module, which contains information about the data receiving process
{
    uint8_t *recv_buff;                    // 预先定义的最大buff大小,如果太小请修改USART_RXBUFF_LIMIT
    size_t recv_buff_size;                 // 模块接收一包数据的大小
    UART_HandleTypeDef *usart_handle;      // 实例对应的usart_handle
    usart_module_callback module_callback; // 解析收到的数据的回调函数
} USARTInstance;

// // 使用双缓冲机制的串口实例结构体
// typedef struct // relate to usart module, which contains information about the data receiving process
// {
// #ifdef USART_
//     uint8_t recv_buff[2][USART_RXBUFF_LIMIT]; // 双缓冲的buff
//     uint8_t recv_buff_size;                   // 模块接收一包数据的大小
//     uint8_t recv_buff_index;                  // 记录当前读取的buff index
//     UART_HandleTypeDef *usart_handle;         // 实例对应的usart_handle
//     usart_module_callback module_callback;    // 解析收到的数据的回调函数
// } USARTInstance_doubleBuffer;

/* usart 初始化配置结构体 */
typedef struct
{
    uint8_t recv_buff_size;                // 模块接收一包数据的大小
    UART_HandleTypeDef *usart_handle;      // 实例对应的usart_handle
    usart_module_callback module_callback; // 解析收到的数据的回调函数
} USART_Init_Config_s;

/**
 * @brief 注册一个串口实例,返回一个串口实例指针
 *
 * @param init_config 传入串口初始化结构体
 */
USARTInstance *USARTRegister(USART_Init_Config_s *init_config);

/**
 * @brief 启动串口服务,需要传入一个usart实例.一般用于lost callback的情况(使用串口的模块daemon)
 *
 * @param _instance
 */
void USARTServiceInit(USARTInstance *_instance);

/**
 * @brief 通过调用该函数可以发送一帧数据,需要传入一个usart实例,发送buff以及这一帧的长度
 * @note 在短时间内连续调用此接口,若采用IT/DMA会导致上一次的发送未完成而新的发送取消.
 * @note 若希望连续使用DMA/IT进行发送,请配合USARTIsReady()使用,或自行为你的module实现一个发送队列和任务.
 * @todo 是否考虑为USARTInstance增加发送队列以进行连续发送?
 *
 * @param _instance 串口实例
 * @param send_buf 待发送数据的buffer
 * @param send_size how many bytes to send
 */
void USARTSend(USARTInstance *_instance, uint8_t *send_buf, uint16_t send_size, USART_TRANSFER_MODE mode);

/**
 * @brief 判断串口是否准备好,用于连续或异步的IT/DMA发送
 *
 * @param _instance 要判断的串口实例
 * @return uint8_t ready 1, busy 0
 */
uint8_t USARTIsReady(USARTInstance *_instance);

/*=======================tab=========VIRTUAL USART==================================*/
#define DEVICE_VIRTUAL_CNT 1
#define VIRTUAL_USART_RXBUFF_LIMIT 16
// one bit delay time for the imitation of baud rate (in us)
#define VIRTUAL_BAUDRATE_9600 104 // 1 / 9600 * 10 ^ 6
#define VIRTUAL_BAUDRATE_115200 9 // 1 / 115200 * 10 ^ 6
// void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)

// 串口实例结构体,每个module都要包含一个实例.
// 由于串口是独占的点对点通信,所以不需要考虑多个module同时使用一个串口的情况,因此不用加入id;当然也可以选择加入,这样在bsp层可以访问到module的其他信息
typedef struct // relate to usart module, which contains information about the data receiving process
{
    GPIO_TypeDef *tx_port;
    GPIO_TypeDef *rx_port;
    uint16_t tx_pin;
    uint16_t rx_pin;
    size_t recv_buff_size; // 模块接收一包数据的大小
    uint8_t *recv_buff;    // 预先定义的最大buff大小,如果太小请修改USART_RXBUFF_LIMIT
    uint16_t trans_baud;   // virtual trans baud
} VIRTUALInstance;

/* usart 初始化配置结构体 */
typedef struct
{
    GPIO_TypeDef *tx_port;
    GPIO_TypeDef *rx_port;
    uint16_t tx_pin;
    uint16_t rx_pin;
    size_t recv_buff_size; // 模块接收一包数据的大小
    uint16_t trans_baud;   // virtual trans baud
} VIRTUAL_Init_Config_s;

/**
 * @brief 注册一个串口实例,返回一个串口实例指针
 *
 * @param init_config 传入串口初始化结构体
 */
VIRTUALInstance *VIRTUAL_USARTRegister(VIRTUAL_Init_Config_s *init_config);

/* @todo 在实现freertos之后补充delay_us的实现 */
void VirtualCOM_ByteSend(VIRTUALInstance *instance, uint8_t data);
void VirtualCOM_SendArr(VIRTUALInstance *instance, uint8_t *arr, size_t arr_len);

#endif
