#include "dma.h"
#include "stm32f4xx.h"

void GYRO_DMA_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

	DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(GYRO_DMA_Stream);

	while (DMA_GetCmdStatus(GYRO_DMA_Stream) != DISABLE)
	{
	} // 等待DMA可配置
	// 配置DMA1 Stream0 Channel4用于UART5 RX
	// DMA_DeInit(DMA1_Stream0);
	// DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	// DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART5->DR;
	// DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)UART5_Buffer;
	// DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	// DMA_InitStructure.DMA_BufferSize = UART5_BUFFER_SIZE;
	// DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	// DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	// DMA_InitStructure.DMA_PeripheralDataAlignment = DMA_PeripheralDataAlignment_Byte;
	// DMA_InitStructure.DMA_MemoryDataAlignment = DMA_MemoryDataAlignment_Byte;
	// DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	// DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	// DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMODE_Disable;
	// DMA_Init(DMA1_Stream0, &DMA_InitStructure);

	// // 使能DMA1 Stream0
	// DMA_Cmd(DMA1_Stream0, ENABLE);

	// // 使能UART5 DMA接收
	// USART_DMACmd(UART5, USART_DMAReq_Rx, ENABLE);

	/* 配置 DMA Stream */
//	DMA_InitStructure.DMA_Channel = GYRO_DMA_Channel;						// 通道选择
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;		// DMA外设地址
//	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&OPS_data.data[2];	// DMA 存储器0地址
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;					// 外设到储存器
//	DMA_InitStructure.DMA_BufferSize = GRYO_DMA_Buf_Size;					// 数据传输量
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		// 外设非增量模式
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					// 存储器增量模式
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // 外设数据长度:8位
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			// 存储器数据长度:8位
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							// 使用连续模式
//	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;					// 优先级
//	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
//	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
//	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;			// 存储器突发单次传输
//	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; // 外设突发单次传输
//	DMA_Init(OPS_DMA_Stream, &DMA_InitStructure);						// 初始化DMA Stream

//	USART_DMACmd(OPS_UART, USART_DMAReq_Rx, DISABLE); // 对帧成功时再启动
//	DMA_Cmd(OPS_DMA_Stream, DISABLE);
}
void MYDMA_Enable(DMA_Stream_TypeDef *DMA_Streamx, u16 ndtr)
{

	DMA_Cmd(DMA_Streamx, DISABLE); // 关闭DMA传输

	while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE)
	{
	} // 确保DMA可以被设置

	DMA_SetCurrDataCounter(DMA_Streamx, ndtr); // 数据传输量

	DMA_Cmd(DMA_Streamx, ENABLE); // 开启DMA传输
}

// void UART5_IRQHandler(void)
// {
//     if(USART_GetITStatus(UART5, USART_IT_IDLE) != RESET)
//     {
//         // 清除IDLE中断标志
//         USART_ReceiveData(UART5);

//         // 停止DMA传输
//         DMA_Cmd(DMA1_Stream0, DISABLE);

//         // 计算接收到的数据长度
//         uint16_t rx_len = sizeof(Fd_data) - DMA_GetCurrDataCounter(DMA1_Stream0);

//         // 处理接收到的数据
//         ProcessReceivedData(rx_len);

//         // 清除DMA标志位
//         DMA_ClearFlag(DMA1_Stream0, DMA_FLAG_TCIF0 | DMA_FLAG_HTIF0 | DMA_FLAG_TEIF0 | DMA_FLAG_DMEIF0 | DMA_FLAG_FEIF0);

//         // 重新设置DMA传输数量
//         DMA_SetCurrDataCounter(DMA1_Stream0, sizeof(Fd_data));

//         // 重新启动DMA传输
//         DMA_Cmd(DMA1_Stream0, ENABLE);
//     }
// }

// void ProcessReceivedData(uint16_t rx_len)
// {
//     static u8 last_rsnum = 0;
//     static u8 rsimu_flag = 0;
//     static u8 rsacc_flag = 0;

//     for(uint16_t i = 0; i < rx_len; i++)
//     {
//         u8 Usart_Receive = Fd_data[i];

//         if (((last_rsnum == FRAME_END) && (Usart_Receive == FRAME_HEAD)) || i > 0)
//         {
//             if ((Fd_data[1] == TYPE_IMU) && (Fd_data[2] == IMU_LEN))
//                 rsimu_flag = 1;
//             if ((Fd_data[1] == TYPE_AHRS) && (Fd_data[2] == AHRS_LEN))
//                 rsacc_flag = 1;
//         }

//         last_rsnum = Usart_Receive;

//         if (rsimu_flag == 1 && i == IMU_RS - 1)
//         {
//             rsimu_flag = 0;
//             rs_imutype = 1;
//             if (Fd_data[IMU_RS - 1] == FRAME_END)
//                 memcpy(Fd_rsimu, Fd_data, IMU_RS);
//         }

//         if (rsacc_flag == 1 && i == AHRS_RS - 1)
//         {
//             rsacc_flag = 0;
//             rs_ahrstype = 1;
//             if (Fd_data[AHRS_RS - 1] == FRAME_END)
//                 memcpy(Fd_rsahrs, Fd_data, AHRS_RS);
//         }
//     }
// }

// void UART5_Init(uint32_t bound)
// {
//     // ... (保留原有的GPIO和UART配置代码)

//     // 配置DMA
//     DMA_InitTypeDef DMA_InitStructure;
//     RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

//     DMA_DeInit(DMA1_Stream0);
//     DMA_InitStructure.DMA_Channel = DMA_Channel_4;
//     DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART5->DR;
//     DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Fd_data;
//     DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
//     DMA_InitStructure.DMA_BufferSize = sizeof(Fd_data);
//     DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//     DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//     DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//     DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
//     DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
//     DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//     DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
//     DMA_Init(DMA1_Stream0, &DMA_InitStructure);

//     // 使能DMA
//     DMA_Cmd(DMA1_Stream0, ENABLE);

//     // 使能UART5 DMA接收
//     USART_DMACmd(UART5, USART_DMAReq_Rx, ENABLE);

//     // 使能UART5空闲中断
//     USART_ITConfig(UART5, USART_IT_IDLE, ENABLE);

//     // ... (保留原有的NVIC配置代码)
// }