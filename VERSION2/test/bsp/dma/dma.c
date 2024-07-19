#include "dma.h"
#include "legacy.h"
#include "ll_includes.h"
#include "stm32f4xx_hal_conf.h"

uint8_t UART5_RX_Buffer_A[UART5_RX_BUFFER_SIZE];
uint8_t UART5_RX_Buffer_B[UART5_RX_BUFFER_SIZE];
volatile uint8_t *current_buffer;
volatile uint8_t *processing_buffer;

void GYRO_DMA_Config(void)
{
	LL_DMA_InitTypeDef DMA_InitStructure;
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

	DMA_DeInit(GYRO_DMA_Stream);
	while (DMA_GetCmdStatus(GYRO_DMA_Stream) != DISABLE)
	{
	}

	DMA_InitStructure.Channel = GYRO_DMA_Channel;						// 通道选择
	DMA_InitStructure.PeriphOrM2MSrcAddress = (uint32_t)&UART5->DR;		// 外设地址
	DMA_InitStructure.MemoryOrM2MDstAddress = (uint32_t)UART5_RX_Buffer_A;	// 内存地址
	DMA_InitStructure.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;					// 传输方向
	DMA_InitStructure.NbData = UART5_RX_BUFFER_SIZE;				// 传输大小
	DMA_InitStructure.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;		// 外设地址不增加
	DMA_InitStructure.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;					// 内存地址自增
	DMA_InitStructure.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE; // 外设数据宽度
	DMA_InitStructure.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;			// 内存数据宽度
	DMA_InitStructure.Mode = LL_DMA_MODE_CIRCULAR;							// 循环模式
	DMA_InitStructure.Priority = LL_DMA_PRIORITY_HIGH;						// 优先级高
	DMA_InitStructure.FIFOMode = LL_DMA_FIFOMODE_DISABLE;					// 禁用FIFO
	DMA_InitStructure.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_FULL;
	DMA_InitStructure.MemBurst = LL_DMA_MBURST_SINGLE; // 单次传输
	DMA_InitStructure.PeriphBurst = LL_DMA_PBURST_SINGLE;

	LL_DMA_SetCurrentTargetMem(DMA1, LL_DMA_STREAM_0, LL_DMA_CURRENTTARGETMEM0);
	LL_DMA_SetMemory1Address(DMA1, LL_DMA_STREAM_0, (uint32_t)UART5_RX_Buffer_B);
	LL_DMA_EnableDoubleBufferMode(DMA1, LL_DMA_STREAM_0);
	LL_DMA_Init(DMA1, LL_DMA_STREAM_0, &DMA_InitStructure);

	// 配置DMA中断
	LL_DMA_EnableIT_HT(DMA1, LL_DMA_STREAM_0);

	// 使能DMA
	LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_0);

	// 配置NVIC
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// 使能UART5的DMA接收
	LL_USART_EnableDMAReq_RX(UART5);
}

void ProcessDMAData(uint8_t *buffer, uint16_t size)
{
	static u8 Count = 0;
	static u8 last_rsnum = 0;
	static u8 rsimu_flag = 0; // 接收开始标志位
	static u8 rsacc_flag = 0;
	u8 Usart_Receive;

	RS485_RX_RE = 0;
	RS485_RX_DE = 0;
	ttl_receive = 1;

	// 处理接收到的数据
	for (uint16_t i = 0; i < size; i++)
	{
		Usart_Receive = buffer[i];
		Fd_data[Count] = Usart_Receive;

		if (((last_rsnum == FRAME_END) && (Usart_Receive == FRAME_HEAD)) || Count > 0)
		{
			Count++;
			if ((Fd_data[1] == TYPE_IMU) && (Fd_data[2] == IMU_LEN))
				rsimu_flag = 1;
			if ((Fd_data[1] == TYPE_AHRS) && (Fd_data[2] == AHRS_LEN))
				rsacc_flag = 1;
		}
		else
			Count = 0;

		last_rsnum = Usart_Receive;

		// 接收完整后进入
		if (rsimu_flag == 1 && Count == IMU_RS)
		{
			Count = 0;
			rsimu_flag = 0;
			rs_imutype = 1; // imu data available flag
			if (Fd_data[IMU_RS - 1] == FRAME_END)
				memcpy(Fd_rsimu, Fd_data, sizeof(Fd_data));
		}
		if (rsacc_flag == 1 && Count == AHRS_RS)
		{
			Count = 0;
			rsacc_flag = 0;
			rs_ahrstype = 1; // ahrs data available flag
			if (Fd_data[AHRS_RS - 1] == FRAME_END)
				memcpy(Fd_rsahrs, Fd_data, sizeof(Fd_data));
		}
	}
}

void DMA1_Stream0_IRQHandler(void)
{
	if ((LL_DMA_IsEnabledIT_TC(DMA1, LL_DMA_STREAM_0) && LL_DMA_IsActiveFlag_TC0(DMA1)) != RESET)
	{
		LL_DMA_ClearFlag_TC0(DMA1);

		// 切换缓冲区
		if (LL_DMA_GetCurrentTargetMem(DMA1, LL_DMA_STREAM_0) == 0)
		{
			processing_buffer = UART5_RX_Buffer_A;
			current_buffer = UART5_RX_Buffer_B;
		}
		else
		{
			processing_buffer = UART5_RX_Buffer_B;
			current_buffer = UART5_RX_Buffer_A;
		}

		// 处理接收到的数据
		ProcessDMAData(processing_buffer, UART5_RX_BUFFER_SIZE);

		// 重新启动DMA传输
		LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_0, UART5_RX_BUFFER_SIZE);
		LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_0);
	}

	if ((LL_DMA_IsEnabledIT_HT(DMA1, LL_DMA_STREAM_0) && LL_DMA_IsActiveFlag_HT0(DMA1)) != RESET)
	{
		LL_DMA_ClearFlag_HT0(DMA1);
		// 半传输中断处理逻辑（可选）
	}
}

void UART5_IRQHandler(void)
{

	// 检查过载错误
	if (LL_USART_IsActiveFlag_ORE(UART5) != RESET)
	{
		LL_USART_ClearFlag_ORE(UART5);
		// 清除过载错误标志
		LL_USART_ReceiveData9(UART5); // 读取SR和DR
	}

	if (((LL_USART_IsEnabledIT_IDLE(UART5))&& (LL_USART_IsActiveFlag_IDLE(UART5))) != RESET)
	{
		// 清除IDLE标志
		LL_USART_ReceiveData9(UART5);

		// 停止DMA传输
		LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_0);

		// 获取接收到的数据长度
		uint16_t recv_size = UART5_RX_BUFFER_SIZE - DMA_GetCurrDataCounter(GYRO_DMA_Stream);

		// 处理接收到的数据
		ProcessDMAData(current_buffer, recv_size);

		// 清除DMA标志位
		LL_DMA_ClearFlag_FE0(DMA1);

		// 重新设置DMA传输数量
		DMA_SetCurrDataCounter(GYRO_DMA_Stream, UART5_RX_BUFFER_SIZE);

		// 重新启动DMA传输
		DMA_Cmd(GYRO_DMA_Stream, ENABLE);
	}
}

/*====================USART2_DMA==========================*/
//#define USART2_RX_BUFFER_SIZE 128
//uint8_t USART2_RX_Buffer[USART2_RX_BUFFER_SIZE];
//volatile uint16_t USART2_RX_Count = 0;

//u8 rx_data_right[9];
//uint16_t lidar_right = 0;

//u8 uart_state = 0;
//u8 uart_index = 0;

//// void ProcessUARTData(uint8_t *rx_buffer, uint16_t rx_count, u8 *rx_data, uint16_t *dist)
//// {
//// 	static u8 count = 0;
//// 	static u8 i = 0;
//// 	u8 j = 0;
//// 	uint16_t Dist = 0;

//// 	for (uint16_t k = 0; k < rx_count; k++)
//// 	{
//// 		u8 Res = rx_buffer[k];
//// 		switch (count)
//// 		{
//// 		case 0:
//// 		case 1:
//// 			if (Res == 0x59)
//// 			{
//// 				count++;
//// 				rx_data[i] = Res;
//// 				i++;
//// 			}
//// 			else
//// 			{
//// 				count = 0;
//// 				i = 0;
//// 			}
//// 			break;
//// 		case 2:
//// 			rx_data[i] = Res;
//// 			i++;
//// 			if (i == 8)
//// 				count++;
//// 			break;
//// 		case 3:
//// 			for (j = 0; j < 8; j++)
//// 			{
//// 				rx_data[8] += rx_data[j];
//// 			}
//// 			if (rx_data[8] == Res)
//// 			{
//// 				Dist = ((uint16_t)(rx_data[3] << 8) | rx_data[2]);
//// 				if (Dist > 100)
//// 				{
//// 					Dist = 100;
//// 				}
//// 			}
//// 			*dist = Dist;
//// 			count = 0;
//// 			i = 0;
//// 			rx_data[8] = 0;
//// 			break;
//// 		}
//// 	}
//// }

//void ProcessUARTData(uint8_t *rx_buffer, uint16_t rx_count, u8 *rx_data, uint16_t *dist, u8 *state, u8 *index)
//{
//	uint16_t Dist = 0;
//	u8 checksum = 0;

//	for (uint16_t k = 0; k < rx_count; k++)
//	{
//		u8 Res = rx_buffer[k];

//		switch (*state)
//		{
//		case 0:
//			if (Res == 0x59)
//			{
//				rx_data[0] = Res;
//				*state = 1;
//				*index = 1;
//			}
//			break;

//		case 1:
//			if (Res == 0x59)
//			{
//				rx_data[1] = Res;
//				*state = 2;
//				*index = 2;
//			}
//			else
//			{
//				*state = 0;
//			}
//			break;

//		case 2:
//			rx_data[*index] = Res;
//			(*index)++;
//			if (*index == 8)
//			{
//				*state = 3;
//			}
//			break;

//		case 3:
//			checksum = rx_data[0] + rx_data[1] + rx_data[2] + rx_data[3] +
//					   rx_data[4] + rx_data[5] + rx_data[6] + rx_data[7];
//			if (checksum == Res)
//			{
//				Dist = ((uint16_t)rx_data[3] << 8) | rx_data[2];
//				*dist = (Dist > 100) ? 100 : Dist;
//			}
//			*state = 0;
//			*index = 0;
//			break;
//		}
//	}
//}

//void DMA1_Stream5_IRQHandler(void)
//{
//	if (DMA_GetITStatus(DMA1_Stream5, DMA_IT_TEIF5) != RESET)
//	{
//		DMA_ClearITPendingBit(DMA1_Stream5, DMA_IT_TEIF5);
//		// 处理传输错误
//	}

//	if (DMA_GetITStatus(DMA1_Stream5, DMA_IT_TCIF5) != RESET)
//	{
//		DMA_ClearITPendingBit(DMA1_Stream5, DMA_IT_TCIF5);

//		// 停止DMA传输
//		DMA_Cmd(DMA1_Stream5, DISABLE);

//		// 获取接收到的数据长度
//		USART2_RX_Count = USART2_RX_BUFFER_SIZE - DMA_GetCurrDataCounter(DMA1_Stream5);

//		// 处理接收到的数据

//		ProcessUARTData(USART2_RX_Buffer, USART2_RX_Count, rx_data_right, &lidar_right, &uart_state, &uart_index);

//		// 重新设置DMA传输数量
//		DMA_SetCurrDataCounter(DMA1_Stream5, USART2_RX_BUFFER_SIZE);

//		// 重新启动DMA传输
//		DMA_Cmd(DMA1_Stream5, ENABLE);
//	}
//}

//void USART2_IRQHandler(void)
//{
//	if (USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)
//	{
//		USART_ClearFlag(USART2, USART_FLAG_ORE);
//		USART_ReceiveData(USART2);
//	}

//	if (USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
//	{
//		USART_ReceiveData(USART2);
//	}
//}

//void USART2_DMA_Config(void)
//{
//	DMA_InitTypeDef DMA_InitStructure;

//	// 使能DMA1时钟
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

//	// DMA通道配置
//	DMA_DeInit(DMA1_Stream5);
//	while (DMA_GetCmdStatus(DMA1_Stream5) != DISABLE)
//	{
//	}

//	DMA_InitStructure.DMA_Channel = DMA_Channel_4;							// 通道选择
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;		// 外设地址
//	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)USART2_RX_Buffer;		// 内存地址
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;					// 传输方向
//	DMA_InitStructure.DMA_BufferSize = USART2_RX_BUFFER_SIZE;				// 传输大小
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		// 外设地址不增加
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					// 内存地址自增
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // 外设数据宽度
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			// 内存数据宽度
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							// 循环模式
//	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						// 优先级
//	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;					// 禁用FIFO
//	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
//	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;			// 单次传输
//	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; // 单次传输

//	DMA_Init(DMA1_Stream5, &DMA_InitStructure);

//	// 配置DMA中断
//	DMA_ITConfig(DMA1_Stream5, DMA_IT_TC | DMA_IT_TE, ENABLE);

//	// 使能DMA
//	DMA_Cmd(DMA1_Stream5, ENABLE);

//	// 配置NVIC
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream5_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

//	USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);
//}
///*====================UART4_DMA==========================*/
//#define UART4_RX_BUFFER_SIZE 128
//uint8_t UART4_RX_Buffer[UART4_RX_BUFFER_SIZE];
//volatile uint16_t UART4_RX_Count = 0;

//u8 rx_data_left[9];
//uint16_t lidar_left = 0;

//void DMA1_Stream2_IRQHandler(void)
//{
//	if (DMA_GetITStatus(DMA1_Stream2, DMA_IT_TEIF2) != RESET)
//	{
//		DMA_ClearITPendingBit(DMA1_Stream2, DMA_IT_TEIF2);
//		// 处理传输错误
//	}

//	if (DMA_GetITStatus(DMA1_Stream2, DMA_IT_TCIF2) != RESET)
//	{
//		DMA_ClearITPendingBit(DMA1_Stream2, DMA_IT_TCIF2);

//		// 停止DMA传输
//		DMA_Cmd(DMA1_Stream2, DISABLE);

//		// 获取接收到的数据长度
//		UART4_RX_Count = UART4_RX_BUFFER_SIZE - DMA_GetCurrDataCounter(DMA1_Stream2);

//		// 处理接收到的数据
//		// ProcessUARTData(UART4_RX_Buffer, UART4_RX_Count, rx_data_left, &lidar_left);
//		ProcessUARTData(UART4_RX_Buffer, UART4_RX_Count, rx_data_left, &lidar_left, &uart_state, &uart_index);

//		// 重新设置DMA传输数量
//		DMA_SetCurrDataCounter(DMA1_Stream2, UART4_RX_BUFFER_SIZE);

//		// 重新启动DMA传输
//		DMA_Cmd(DMA1_Stream2, ENABLE);
//	}
//}

//void UART4_IRQHandler(void)
//{
//	if (USART_GetFlagStatus(UART4, USART_FLAG_ORE) != RESET)
//	{
//		USART_ClearFlag(UART4, USART_FLAG_ORE);
//		USART_ReceiveData(UART4);
//	}

//	if (USART_GetITStatus(UART4, USART_IT_IDLE) != RESET)
//	{
//		USART_ReceiveData(UART4);
//	}
//}

//void UART4_DMA_Config(void)
//{
//	DMA_InitTypeDef DMA_InitStructure;

//	// 使能DMA1时钟
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

//	// DMA通道配置
//	DMA_DeInit(DMA1_Stream2);
//	while (DMA_GetCmdStatus(DMA1_Stream2) != DISABLE)
//	{
//	}

//	DMA_InitStructure.DMA_Channel = DMA_Channel_4;							// 通道选择
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART4->DR;		// 外设地址
//	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)UART4_RX_Buffer;		// 内存地址
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;					// 传输方向
//	DMA_InitStructure.DMA_BufferSize = UART4_RX_BUFFER_SIZE;				// 传输大小
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		// 外设地址不增加
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					// 内存地址自增
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // 外设数据宽度
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			// 内存数据宽度
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							// 循环模式
//	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						// 优先级
//	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;					// 禁用FIFO
//	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
//	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;			// 单次传输
//	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; // 单次传输

//	DMA_Init(DMA1_Stream2, &DMA_InitStructure);

//	// 配置DMA中断
//	DMA_ITConfig(DMA1_Stream2, DMA_IT_TC | DMA_IT_TE, ENABLE);

//	// 使能DMA
//	DMA_Cmd(DMA1_Stream2, ENABLE);

//	// 配置NVIC
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream2_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

//	USART_DMACmd(UART4, USART_DMAReq_Rx, ENABLE);
//}