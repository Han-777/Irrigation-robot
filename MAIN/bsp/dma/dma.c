#include "dma.h"
#include "stm32f4xx.h"

uint8_t UART5_RX_Buffer_A[UART5_RX_BUFFER_SIZE];
uint8_t UART5_RX_Buffer_B[UART5_RX_BUFFER_SIZE];
volatile uint8_t *current_buffer;
volatile uint8_t *processing_buffer;

void GYRO_DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

	DMA_DeInit(GYRO_DMA_Stream);
	while (DMA_GetCmdStatus(GYRO_DMA_Stream) != DISABLE)
	{
	}

	DMA_InitStructure.DMA_Channel = GYRO_DMA_Channel;						// 通道选择
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART5->DR;		// 外设地址
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)UART5_RX_Buffer_A;	// 内存地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;					// 传输方向
	DMA_InitStructure.DMA_BufferSize = UART5_RX_BUFFER_SIZE;				// 传输大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		// 外设地址不增加
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					// 内存地址自增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // 外设数据宽度
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			// 内存数据宽度
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							// 循环模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						// 优先级高
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;					// 禁用FIFO
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; // 单次传输
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

	DMA_DoubleBufferModeConfig(DMA1_Stream0, (uint32_t)UART5_RX_Buffer_B, DMA_Memory_0);
	DMA_DoubleBufferModeCmd(DMA1_Stream0, ENABLE);
	DMA_Init(DMA1_Stream0, &DMA_InitStructure);

	// 配置DMA中断
	DMA_ITConfig(DMA1_Stream0, DMA_IT_TC | DMA_IT_HT, ENABLE);

	// 使能DMA
	DMA_Cmd(DMA1_Stream0, ENABLE);

	// 配置NVIC
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// 使能UART5的DMA接收
	USART_DMACmd(UART5, USART_DMAReq_Rx, ENABLE);
}

// void DMA1_Stream0_IRQHandler(void)
// {
// 	static u8 Count = 0;
// 	static u8 last_rsnum = 0;
// 	static u8 rsimu_flag = 0; // 接收开始标志位
// 	static u8 rsacc_flag = 0;
// 	u8 Usart_Receive;

// 	if (DMA_GetITStatus(DMA1_Stream0, DMA_IT_TCIF0) != RESET)
// 	{
// 		DMA_ClearITPendingBit(DMA1_Stream0, DMA_IT_TCIF0);

// 		// 切换缓冲区
// 		if (DMA_GetCurrentMemoryTarget(DMA1_Stream0) == 0)
// 		{
// 			processing_buffer = UART5_RX_Buffer_A;
// 			current_buffer = UART5_RX_Buffer_B;
// 		}
// 		else
// 		{
// 			processing_buffer = UART5_RX_Buffer_B;
// 			current_buffer = UART5_RX_Buffer_A;
// 		}

// 		RS485_RX_RE = 0;
// 		RS485_RX_DE = 0;
// 		ttl_receive = 1;

// 		// 处理接收到的数据
// 		for (uint16_t i = 0; i < UART5_RX_BUFFER_SIZE; i++)
// 		{
// 			Usart_Receive = processing_buffer[i];
// 			Fd_data[Count] = Usart_Receive;

// 			if (((last_rsnum == FRAME_END) && (Usart_Receive == FRAME_HEAD)) || Count > 0)
// 			{
// 				Count++;
// 				if ((Fd_data[1] == TYPE_IMU) && (Fd_data[2] == IMU_LEN))
// 					rsimu_flag = 1;
// 				if ((Fd_data[1] == TYPE_AHRS) && (Fd_data[2] == AHRS_LEN))
// 					rsacc_flag = 1;
// 			}
// 			else
// 				Count = 0;

// 			last_rsnum = Usart_Receive;

// 			// 接收完整后进入
// 			if (rsimu_flag == 1 && Count == IMU_RS)
// 			{
// 				Count = 0;
// 				rsimu_flag = 0;
// 				rs_imutype = 1; // imu data available flag
// 				if (Fd_data[IMU_RS - 1] == FRAME_END)
// 					memcpy(Fd_rsimu, Fd_data, sizeof(Fd_data));
// 			}
// 			if (rsacc_flag == 1 && Count == AHRS_RS)
// 			{
// 				Count = 0;
// 				rsacc_flag = 0;
// 				rs_ahrstype = 1; // ahrs data available flag
// 				if (Fd_data[AHRS_RS - 1] == FRAME_END)
// 					memcpy(Fd_rsahrs, Fd_data, sizeof(Fd_data));
// 			}
// 		}

// 		// 重新启动DMA传输
// 		DMA_SetCurrDataCounter(DMA1_Stream0, UART5_RX_BUFFER_SIZE);
// 		DMA_Cmd(DMA1_Stream0, ENABLE);
// 	}

// 	if (DMA_GetITStatus(DMA1_Stream0, DMA_IT_HTIF0) != RESET)
// 	{
// 		DMA_ClearITPendingBit(DMA1_Stream0, DMA_IT_HTIF0);
// 		// 半传输中断处理逻辑（可选）
// 	}
// }

// void UART5_IRQHandler(void)
// {
// 	// 检查过载错误
// 	if (USART_GetFlagStatus(USARTx, USART_FLAG_ORE) != RESET)
// 	{
// 		// 清除过载错误标志
// 		USART_ReceiveData(USARTx); // 读取SR和DR
// 	}

// 	/*
// 	当使用DMA接收数据时，DMA会自动将接收到的数据从USART数据寄存器传输到内存缓冲区。此时，USART的接收中断（RXNE）通常不会触发，因为数据传输是由DMA处理的。

// 	为了检测一帧数据的结束，通常会启用USART的空闲中断（IDLE）。当USART接收到一帧数据并且接收线空闲时，会触发空闲中断。在空闲中断中，可以处理接收到的数据并重新启动DMA。

// 	*/
// 	if (USART_GetITStatus(UART5, USART_IT_IDLE) != RESET)
// 	{
// 		// 清除IDLE中断标志
// 		USART_ClearITPendingBit(UART5, USART_IT_IDLE);

// 		// 获取接收到的数据长度
// 		uint16_t rxCount = UART5_RX_BUFFER_SIZE - DMA_GetCurrDataCounter(DMA1_Stream0);

// 		// 确定当前使用的缓冲区
// 		uint8_t *currentBuffer = (DMA_GetCurrentMemoryTarget(DMA1_Stream0) == 0) ? UART5_RX_Buffer_B : UART5_RX_Buffer_A;

// 		// 处理接收到的数据
// 		ProcessReceivedData(currentBuffer, rxCount);
// 	}
// }

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
	if (DMA_GetITStatus(DMA1_Stream0, DMA_IT_TCIF0) != RESET)
	{
		DMA_ClearITPendingBit(DMA1_Stream0, DMA_IT_TCIF0);

		// 切换缓冲区
		if (DMA_GetCurrentMemoryTarget(DMA1_Stream0) == 0)
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
		DMA_SetCurrDataCounter(DMA1_Stream0, UART5_RX_BUFFER_SIZE);
		DMA_Cmd(DMA1_Stream0, ENABLE);
	}

	if (DMA_GetITStatus(DMA1_Stream0, DMA_IT_HTIF0) != RESET)
	{
		DMA_ClearITPendingBit(DMA1_Stream0, DMA_IT_HTIF0);
		// 半传输中断处理逻辑（可选）
	}
}

void UART5_IRQHandler(void)
{

	// 检查过载错误
	if (USART_GetFlagStatus(UART5, USART_FLAG_ORE) != RESET)
	{
		// 清除过载错误标志
		USART_ReceiveData(UART5); // 读取SR和DR
	}

	if (USART_GetITStatus(UART5, USART_IT_IDLE) != RESET)
	{
		// 清除IDLE标志
		USART_ReceiveData(UART5);

		// 停止DMA传输
		DMA_Cmd(DMA1_Stream0, DISABLE);

		// 获取接收到的数据长度
		uint16_t recv_size = UART5_RX_BUFFER_SIZE - DMA_GetCurrDataCounter(GYRO_DMA_Stream);

		// 处理接收到的数据
		ProcessDMAData(current_buffer, recv_size);

		// 清除DMA标志位
		DMA_ClearFlag(DMA1_Stream0, DMA_FLAG_TCIF0 | DMA_FLAG_HTIF0 | DMA_FLAG_TEIF0 | DMA_FLAG_DMEIF0 | DMA_FLAG_FEIF0);

		// 重新设置DMA传输数量
		DMA_SetCurrDataCounter(GYRO_DMA_Stream, UART5_RX_BUFFER_SIZE);

		// 重新启动DMA传输
		DMA_Cmd(GYRO_DMA_Stream, ENABLE);
	}
}
