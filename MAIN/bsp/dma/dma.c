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

// void DMA1_Stream0_IRQHandler(void)
// {
// 	static u8 Count = 0;
// 	static u8 last_rsnum = 0;
// 	static u8 rsimu_flag = 0; // ���տ�ʼ��־λ
// 	static u8 rsacc_flag = 0;
// 	u8 Usart_Receive;

// 	if (DMA_GetITStatus(DMA1_Stream0, DMA_IT_TCIF0) != RESET)
// 	{
// 		DMA_ClearITPendingBit(DMA1_Stream0, DMA_IT_TCIF0);

// 		// �л�������
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

// 		// ������յ�������
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

// 			// �������������
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

// 		// ��������DMA����
// 		DMA_SetCurrDataCounter(DMA1_Stream0, UART5_RX_BUFFER_SIZE);
// 		DMA_Cmd(DMA1_Stream0, ENABLE);
// 	}

// 	if (DMA_GetITStatus(DMA1_Stream0, DMA_IT_HTIF0) != RESET)
// 	{
// 		DMA_ClearITPendingBit(DMA1_Stream0, DMA_IT_HTIF0);
// 		// �봫���жϴ����߼�����ѡ��
// 	}
// }

// void UART5_IRQHandler(void)
// {
// 	// �����ش���
// 	if (USART_GetFlagStatus(USARTx, USART_FLAG_ORE) != RESET)
// 	{
// 		// ������ش����־
// 		USART_ReceiveData(USARTx); // ��ȡSR��DR
// 	}

// 	/*
// 	��ʹ��DMA��������ʱ��DMA���Զ������յ������ݴ�USART���ݼĴ������䵽�ڴ滺��������ʱ��USART�Ľ����жϣ�RXNE��ͨ�����ᴥ������Ϊ���ݴ�������DMA����ġ�

// 	Ϊ�˼��һ֡���ݵĽ�����ͨ��������USART�Ŀ����жϣ�IDLE������USART���յ�һ֡���ݲ��ҽ����߿���ʱ���ᴥ�������жϡ��ڿ����ж��У����Դ�����յ������ݲ���������DMA��

// 	*/
// 	if (USART_GetITStatus(UART5, USART_IT_IDLE) != RESET)
// 	{
// 		// ���IDLE�жϱ�־
// 		USART_ClearITPendingBit(UART5, USART_IT_IDLE);

// 		// ��ȡ���յ������ݳ���
// 		uint16_t rxCount = UART5_RX_BUFFER_SIZE - DMA_GetCurrDataCounter(DMA1_Stream0);

// 		// ȷ����ǰʹ�õĻ�����
// 		uint8_t *currentBuffer = (DMA_GetCurrentMemoryTarget(DMA1_Stream0) == 0) ? UART5_RX_Buffer_B : UART5_RX_Buffer_A;

// 		// ������յ�������
// 		ProcessReceivedData(currentBuffer, rxCount);
// 	}
// }

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
