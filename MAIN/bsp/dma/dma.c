#include "dma.h"
#include "stm32f4xx.h"

void GYRO_DMA_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

	DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(GYRO_DMA_Stream);

	while (DMA_GetCmdStatus(GYRO_DMA_Stream) != DISABLE)
	{
	} // �ȴ�DMA������
	// ����DMA1 Stream0 Channel4����UART5 RX
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

	// // ʹ��DMA1 Stream0
	// DMA_Cmd(DMA1_Stream0, ENABLE);

	// // ʹ��UART5 DMA����
	// USART_DMACmd(UART5, USART_DMAReq_Rx, ENABLE);

	/* ���� DMA Stream */
//	DMA_InitStructure.DMA_Channel = GYRO_DMA_Channel;						// ͨ��ѡ��
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;		// DMA�����ַ
//	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&OPS_data.data[2];	// DMA �洢��0��ַ
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;					// ���赽������
//	DMA_InitStructure.DMA_BufferSize = GRYO_DMA_Buf_Size;					// ���ݴ�����
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		// ���������ģʽ
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					// �洢������ģʽ
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // �������ݳ���:8λ
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			// �洢�����ݳ���:8λ
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							// ʹ������ģʽ
//	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;					// ���ȼ�
//	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
//	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
//	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;			// �洢��ͻ�����δ���
//	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; // ����ͻ�����δ���
//	DMA_Init(OPS_DMA_Stream, &DMA_InitStructure);						// ��ʼ��DMA Stream

//	USART_DMACmd(OPS_UART, USART_DMAReq_Rx, DISABLE); // ��֡�ɹ�ʱ������
//	DMA_Cmd(OPS_DMA_Stream, DISABLE);
}
void MYDMA_Enable(DMA_Stream_TypeDef *DMA_Streamx, u16 ndtr)
{

	DMA_Cmd(DMA_Streamx, DISABLE); // �ر�DMA����

	while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE)
	{
	} // ȷ��DMA���Ա�����

	DMA_SetCurrDataCounter(DMA_Streamx, ndtr); // ���ݴ�����

	DMA_Cmd(DMA_Streamx, ENABLE); // ����DMA����
}

// void UART5_IRQHandler(void)
// {
//     if(USART_GetITStatus(UART5, USART_IT_IDLE) != RESET)
//     {
//         // ���IDLE�жϱ�־
//         USART_ReceiveData(UART5);

//         // ֹͣDMA����
//         DMA_Cmd(DMA1_Stream0, DISABLE);

//         // ������յ������ݳ���
//         uint16_t rx_len = sizeof(Fd_data) - DMA_GetCurrDataCounter(DMA1_Stream0);

//         // ������յ�������
//         ProcessReceivedData(rx_len);

//         // ���DMA��־λ
//         DMA_ClearFlag(DMA1_Stream0, DMA_FLAG_TCIF0 | DMA_FLAG_HTIF0 | DMA_FLAG_TEIF0 | DMA_FLAG_DMEIF0 | DMA_FLAG_FEIF0);

//         // ��������DMA��������
//         DMA_SetCurrDataCounter(DMA1_Stream0, sizeof(Fd_data));

//         // ��������DMA����
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
//     // ... (����ԭ�е�GPIO��UART���ô���)

//     // ����DMA
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

//     // ʹ��DMA
//     DMA_Cmd(DMA1_Stream0, ENABLE);

//     // ʹ��UART5 DMA����
//     USART_DMACmd(UART5, USART_DMAReq_Rx, ENABLE);

//     // ʹ��UART5�����ж�
//     USART_ITConfig(UART5, USART_IT_IDLE, ENABLE);

//     // ... (����ԭ�е�NVIC���ô���)
// }