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

	DMA_InitStructure.DMA_Channel = GYRO_DMA_Channel;						// ͨ��ѡ��
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART5->DR;		// �����ַ
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)UART5_RX_Buffer_A;	// �ڴ��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;					// ���䷽��
	DMA_InitStructure.DMA_BufferSize = UART5_RX_BUFFER_SIZE;				// �����С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		// �����ַ������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					// �ڴ��ַ����
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // �������ݿ��
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			// �ڴ����ݿ��
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							// ѭ��ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						// ���ȼ���
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;					// ����FIFO
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; // ���δ���
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

	DMA_DoubleBufferModeConfig(DMA1_Stream0, (uint32_t)UART5_RX_Buffer_B, DMA_Memory_0);
	DMA_DoubleBufferModeCmd(DMA1_Stream0, ENABLE);
	DMA_Init(DMA1_Stream0, &DMA_InitStructure);

	// ����DMA�ж�
	DMA_ITConfig(DMA1_Stream0, DMA_IT_TC | DMA_IT_HT, ENABLE);

	// ʹ��DMA
	DMA_Cmd(DMA1_Stream0, ENABLE);

	// ����NVIC
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// ʹ��UART5��DMA����
	USART_DMACmd(UART5, USART_DMAReq_Rx, ENABLE);
}

void ProcessDMAData(uint8_t *buffer, uint16_t size)
{
	static u8 Count = 0;
	static u8 last_rsnum = 0;
	static u8 rsimu_flag = 0; // ���տ�ʼ��־λ
	static u8 rsacc_flag = 0;
	u8 Usart_Receive;

	RS485_RX_RE = 0;
	RS485_RX_DE = 0;
	ttl_receive = 1;

	// ������յ�������
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

		// �������������
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

		// �л�������
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

		// ������յ�������
		ProcessDMAData(processing_buffer, UART5_RX_BUFFER_SIZE);

		// ��������DMA����
		DMA_SetCurrDataCounter(DMA1_Stream0, UART5_RX_BUFFER_SIZE);
		DMA_Cmd(DMA1_Stream0, ENABLE);
	}

	if (DMA_GetITStatus(DMA1_Stream0, DMA_IT_HTIF0) != RESET)
	{
		DMA_ClearITPendingBit(DMA1_Stream0, DMA_IT_HTIF0);
		// �봫���жϴ����߼�����ѡ��
	}
}

void UART5_IRQHandler(void)
{

	// �����ش���
	if (USART_GetFlagStatus(UART5, USART_FLAG_ORE) != RESET)
	{
		USART_ClearFlag(UART5, USART_FLAG_ORE);
		// ������ش����־
		USART_ReceiveData(UART5); // ��ȡSR��DR
	}

	if (USART_GetITStatus(UART5, USART_IT_IDLE) != RESET)
	{
		// ���IDLE��־
		USART_ReceiveData(UART5);

		// ֹͣDMA����
		DMA_Cmd(DMA1_Stream0, DISABLE);

		// ��ȡ���յ������ݳ���
		uint16_t recv_size = UART5_RX_BUFFER_SIZE - DMA_GetCurrDataCounter(GYRO_DMA_Stream);

		// ������յ�������
		ProcessDMAData(current_buffer, recv_size);

		// ���DMA��־λ
		DMA_ClearFlag(DMA1_Stream0, DMA_FLAG_TCIF0 | DMA_FLAG_HTIF0 | DMA_FLAG_TEIF0 | DMA_FLAG_DMEIF0 | DMA_FLAG_FEIF0);

		// ��������DMA��������
		DMA_SetCurrDataCounter(GYRO_DMA_Stream, UART5_RX_BUFFER_SIZE);

		// ��������DMA����
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
//		// ���������
//	}

//	if (DMA_GetITStatus(DMA1_Stream5, DMA_IT_TCIF5) != RESET)
//	{
//		DMA_ClearITPendingBit(DMA1_Stream5, DMA_IT_TCIF5);

//		// ֹͣDMA����
//		DMA_Cmd(DMA1_Stream5, DISABLE);

//		// ��ȡ���յ������ݳ���
//		USART2_RX_Count = USART2_RX_BUFFER_SIZE - DMA_GetCurrDataCounter(DMA1_Stream5);

//		// ������յ�������

//		ProcessUARTData(USART2_RX_Buffer, USART2_RX_Count, rx_data_right, &lidar_right, &uart_state, &uart_index);

//		// ��������DMA��������
//		DMA_SetCurrDataCounter(DMA1_Stream5, USART2_RX_BUFFER_SIZE);

//		// ��������DMA����
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

//	// ʹ��DMA1ʱ��
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

//	// DMAͨ������
//	DMA_DeInit(DMA1_Stream5);
//	while (DMA_GetCmdStatus(DMA1_Stream5) != DISABLE)
//	{
//	}

//	DMA_InitStructure.DMA_Channel = DMA_Channel_4;							// ͨ��ѡ��
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;		// �����ַ
//	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)USART2_RX_Buffer;		// �ڴ��ַ
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;					// ���䷽��
//	DMA_InitStructure.DMA_BufferSize = USART2_RX_BUFFER_SIZE;				// �����С
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		// �����ַ������
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					// �ڴ��ַ����
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // �������ݿ��
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			// �ڴ����ݿ��
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							// ѭ��ģʽ
//	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						// ���ȼ�
//	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;					// ����FIFO
//	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
//	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;			// ���δ���
//	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; // ���δ���

//	DMA_Init(DMA1_Stream5, &DMA_InitStructure);

//	// ����DMA�ж�
//	DMA_ITConfig(DMA1_Stream5, DMA_IT_TC | DMA_IT_TE, ENABLE);

//	// ʹ��DMA
//	DMA_Cmd(DMA1_Stream5, ENABLE);

//	// ����NVIC
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
//		// ���������
//	}

//	if (DMA_GetITStatus(DMA1_Stream2, DMA_IT_TCIF2) != RESET)
//	{
//		DMA_ClearITPendingBit(DMA1_Stream2, DMA_IT_TCIF2);

//		// ֹͣDMA����
//		DMA_Cmd(DMA1_Stream2, DISABLE);

//		// ��ȡ���յ������ݳ���
//		UART4_RX_Count = UART4_RX_BUFFER_SIZE - DMA_GetCurrDataCounter(DMA1_Stream2);

//		// ������յ�������
//		// ProcessUARTData(UART4_RX_Buffer, UART4_RX_Count, rx_data_left, &lidar_left);
//		ProcessUARTData(UART4_RX_Buffer, UART4_RX_Count, rx_data_left, &lidar_left, &uart_state, &uart_index);

//		// ��������DMA��������
//		DMA_SetCurrDataCounter(DMA1_Stream2, UART4_RX_BUFFER_SIZE);

//		// ��������DMA����
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

//	// ʹ��DMA1ʱ��
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

//	// DMAͨ������
//	DMA_DeInit(DMA1_Stream2);
//	while (DMA_GetCmdStatus(DMA1_Stream2) != DISABLE)
//	{
//	}

//	DMA_InitStructure.DMA_Channel = DMA_Channel_4;							// ͨ��ѡ��
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART4->DR;		// �����ַ
//	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)UART4_RX_Buffer;		// �ڴ��ַ
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;					// ���䷽��
//	DMA_InitStructure.DMA_BufferSize = UART4_RX_BUFFER_SIZE;				// �����С
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		// �����ַ������
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					// �ڴ��ַ����
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // �������ݿ��
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			// �ڴ����ݿ��
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							// ѭ��ģʽ
//	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						// ���ȼ�
//	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;					// ����FIFO
//	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
//	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;			// ���δ���
//	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; // ���δ���

//	DMA_Init(DMA1_Stream2, &DMA_InitStructure);

//	// ����DMA�ж�
//	DMA_ITConfig(DMA1_Stream2, DMA_IT_TC | DMA_IT_TE, ENABLE);

//	// ʹ��DMA
//	DMA_Cmd(DMA1_Stream2, ENABLE);

//	// ����NVIC
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream2_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

//	USART_DMACmd(UART4, USART_DMAReq_Rx, ENABLE);
//}