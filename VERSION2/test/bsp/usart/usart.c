#include "usart.h"
/**************************************************************************
						Bluetooth ��ʼ�� USART1
**************************************************************************/

void Bluetooth_USART_Init(u32 bound)
{
	// GPIO????
	LL_GPIO_InitTypeDef GPIO_InitStructure;
	LL_USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);  //??GPIOA??
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1); //??USART1??

	//??1????????
	LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_9, LL_GPIO_AF_7);  // GPIOA9???USART1
	LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_10, LL_GPIO_AF_7); // GPIOA10???USART1

	// USART1????
	GPIO_InitStructure.Pin = LL_GPIO_PIN_9 | LL_GPIO_PIN_10; // GPIOA9?GPIOA10
	GPIO_InitStructure.Mode = LL_GPIO_MODE_ALTERNATE;			//????
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_HIGH;		//??50MHz
	GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;			//??????
	GPIO_InitStructure.Pull = LL_GPIO_PULL_UP;			//??
	GPIO_InitStructure.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOA, &GPIO_InitStructure);					//???PA9,PA10

	// USART1 ?????
	USART_InitStructure.BaudRate = bound;										//?????
	USART_InitStructure.DataWidth = LL_USART_DATAWIDTH_8B;						//???8?????
	USART_InitStructure.StopBits = LL_USART_STOPBITS_1;							//?????
	USART_InitStructure.Parity = LL_USART_PARITY_NONE;								//??????
	USART_InitStructure.HardwareFlowControl = LL_USART_HWCONTROL_NONE; //????????
	USART_InitStructure.TransferDirection = LL_USART_DIRECTION_RX | LL_USART_DIRECTION_TX;					//????
	USART_InitStructure.OverSampling = LL_USART_OVERSAMPLING_16;
	LL_USART_Init(USART1, &USART_InitStructure);										//?????1

	LL_USART_Enable(USART1); //????1

	// USART_ClearFlag(USART1, USART_FLAG_TC);

	// #if EN_USART1_RX
	LL_USART_EnableIT_RXNE(USART1); //??????

	// Usart1 NVIC ??
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		  //??1????
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //?????3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		  //????3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // IRQ????
	NVIC_Init(&NVIC_InitStructure);							  //??????????VIC????

	// #endif
}

void Bluetooth_USART_Close(void)
{
	// GPIO_InitTypeDef GPIO_InitStructure;
	// USART_InitTypeDef USART_InitStructure;
	// NVIC_InitTypeDef NVIC_InitStructure;

	// RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, DISABLE);	//??GPIOA??
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, DISABLE); //??USART1??

	// GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);  // GPIOA9???USART1
	// GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); // GPIOA10???USART1

	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; // GPIOA9?GPIOA10
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;			//????
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//??50MHz
	// GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//??????
	// GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//??
	// GPIO_Init(GPIOA, &GPIO_InitStructure);					//???PA9,PA10

	// // USART_InitStructure.USART_BaudRate = bound;										//?????
	// USART_InitStructure.USART_WordLength = USART_WordLength_8b;						//???8?????
	// USART_InitStructure.USART_StopBits = USART_StopBits_1;							//?????
	// USART_InitStructure.USART_Parity = USART_Parity_No;								//??????
	// USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //????????
	// USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//????
	// USART_Init(USART1, &USART_InitStructure);										//?????1
	LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART1);
	LL_USART_DisableIT_RXNE(USART1); // ��������ж�

	LL_USART_Disable(USART1); //????1

	// NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		  //??1????
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //?????3
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //????3
	// NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;		  // IRQ????
	// NVIC_Init(&NVIC_InitStructure);							  //??????????VIC????
}

/**************************************************************************
						TFmini_Left ��ʼ�� USART2
**************************************************************************/

void TFmini_right_USART_Init(uint32_t bound, FunctionalState state)
{
	LL_GPIO_InitTypeDef GPIO_InitStructure;
	LL_USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);  // ʹ��GPIOCʱ��
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2); // ʹ��UART5ʱ��

	LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_3, LL_GPIO_AF_7); // GPIOC12����ΪUART5
	LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_2, LL_GPIO_AF_7); // GPIOD2����ΪUART5

	GPIO_InitStructure.Pin = LL_GPIO_PIN_2 | LL_GPIO_PIN_3; // GPIOC12
	GPIO_InitStructure.Mode = LL_GPIO_MODE_ALTERNATE;		   // ���ù���
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_HIGH;	   // �ٶ�50MHz
	GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;		   // ���츴�����
	GPIO_InitStructure.Pull = LL_GPIO_PULL_UP;		   // ����
	GPIO_InitStructure.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.BaudRate = bound;
	USART_InitStructure.DataWidth = LL_USART_DATAWIDTH_8B;						// �ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.StopBits = LL_USART_STOPBITS_1;							// һ��ֹͣλ
	USART_InitStructure.Parity = LL_USART_PARITY_NONE;								// ����żУ��λ
	USART_InitStructure.HardwareFlowControl = LL_USART_HWCONTROL_NONE; // ��Ӳ������������
	USART_InitStructure.TransferDirection = LL_USART_DIRECTION_RX | LL_USART_DIRECTION_TX;					// �շ�ģʽ
	USART_InitStructure.OverSampling = LL_USART_OVERSAMPLING_16;
	LL_USART_Init(USART2, &USART_InitStructure);										// ��ʼ������1

	USART_ClearFlag(USART2, LL_USART_ISR_RXNE);

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;		  // ����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // ��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		  // �����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);							  // ����ָ���Ĳ�����ʼ��VIC�Ĵ���

	USART_ITConfig(USART2, USART_IT_RXNE, state); // ��������ж�

	LL_USART_Enable(USART2); // ʹ�ܴ���1
}

void TFmini_right_USART_Close(void)
{
	// GPIO_InitTypeDef GPIO_InitStructure;
	// USART_InitTypeDef USART_InitStructure;
	// NVIC_InitTypeDef NVIC_InitStructure;

	// RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, DISABLE);	// ʹ��GPIOCʱ��
	// RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, DISABLE); // ʹ��UART5ʱ��

	// GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); // GPIOC12����ΪUART5
	// GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); // GPIOD2����ΪUART5

	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; // GPIOC12
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		   // ���ù���
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   // �ٶ�50MHz
	// GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		   // ���츴�����
	// GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		   // ����
	// GPIO_Init(GPIOA, &GPIO_InitStructure);

	// // USART_InitStructure.USART_BaudRate = bound;										// ����������
	// USART_InitStructure.USART_WordLength = USART_WordLength_8b;						// �ֳ�Ϊ8λ���ݸ�ʽ
	// USART_InitStructure.USART_StopBits = USART_StopBits_1;							// һ��ֹͣλ
	// USART_InitStructure.USART_Parity = USART_Parity_No;								// ����żУ��λ
	// USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ��Ӳ������������
	// USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					// �շ�ģʽ
	// USART_Init(USART2, &USART_InitStructure);										// ��ʼ������1

	// USART_ClearFlag(USART2, USART_FLAG_RXNE);

	// NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;		  // ����1�ж�ͨ��
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; // ��ռ���ȼ�3
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		  // �����ȼ�3
	// NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // IRQͨ��ʹ��
	// NVIC_Init(&NVIC_InitStructure);							  // ����ָ���Ĳ�����ʼ��VIC�Ĵ���
	LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART2);
	LL_USART_DisableIT_RXNE(USART2); // ��������ж�
	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_5);
	// USART_Cmd(USART2, DISABLE); // ʹ�ܴ���1
}

/**************************************************************************
						OpenMV ��ʼ�� USART3
**************************************************************************/
void OpenMV_USART_Init(u32 bound)
{
	// PB10 TX    //  PB11   RX   USART3
	LL_GPIO_InitTypeDef GPIO_InitStructure;
	LL_USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);

	LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_10, LL_GPIO_AF_7);
	LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_11, LL_GPIO_AF_7);

	GPIO_InitStructure.Pin = LL_GPIO_PIN_10 | LL_GPIO_PIN_11;
	GPIO_InitStructure.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStructure.Pull = LL_GPIO_PULL_UP;
	GPIO_InitStructure.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	USART_InitStructure.BaudRate = bound;
	USART_InitStructure.DataWidth = LL_USART_DATAWIDTH_8B;
	USART_InitStructure.StopBits = LL_USART_STOPBITS_1;
	USART_InitStructure.Parity = LL_USART_PARITY_NONE;
	USART_InitStructure.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	USART_InitStructure.TransferDirection = LL_USART_DIRECTION_RX | LL_USART_DIRECTION_TX;
	USART_InitStructure.OverSampling = LL_USART_OVERSAMPLING_16;
	LL_USART_Init(USART3, &USART_InitStructure);

	LL_USART_ClearFlag_TC(USART3);

	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	LL_USART_EnableIT_RXNE(USART3);

	LL_USART_Enable(USART3);
}

void OpenMV_USART_Close(void)
{
	// PB10 TX    //  PB11   RX   USART3
	// GPIO_InitTypeDef GPIO_InitStructure;
	// USART_InitTypeDef USART_InitStructure;
	// NVIC_InitTypeDef NVIC_InitStructure;

	// RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, DISABLE);
	// RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, DISABLE);

	// GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
	// GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	// GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	// GPIO_Init(GPIOB, &GPIO_InitStructure);

	// // USART_InitStructure.USART_BaudRate = 0;
	// USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// USART_InitStructure.USART_Parity = USART_Parity_No;
	// USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// USART_Init(USART3, &USART_InitStructure);

	// USART_ClearFlag(USART3, USART_FLAG_TC);

	// NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	// NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	// NVIC_Init(&NVIC_InitStructure);
	LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART3);
	LL_USART_DisableIT_RXNE(USART3);

	// USART_Cmd(USART3, DISABLE);
}
/**************************************************************************
						TFmini_Right ��ʼ�� USART4
**************************************************************************/

void TFmini_left_USART_Init(uint32_t bound, FunctionalState state)
{
	// GPIO�˿�����
	LL_GPIO_InitTypeDef GPIO_InitStructure;
	LL_USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC); // ʹ��GPIOCʱ��
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART4); // ʹ��UART4ʱ��

	// ����4��Ӧ���Ÿ���ӳ��			PC10-TXD,PC11-RXD
	LL_GPIO_SetAFPin_8_15(GPIOC, LL_GPIO_PIN_10, LL_GPIO_AF_8); // GPIOC10����ΪUART4
	LL_GPIO_SetAFPin_8_15(GPIOC, LL_GPIO_PIN_11, LL_GPIO_AF_8); // GPIOC11����ΪUART4

	// UART4�˿�����
	GPIO_InitStructure.Pin = LL_GPIO_PIN_10 | LL_GPIO_PIN_11; // GPIOC10��GPIOC11
	GPIO_InitStructure.Mode = LL_GPIO_MODE_ALTERNATE;			 // ���ù���
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_HIGH;		 // �ٶ�50MHz
	GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;			 // ���츴�����
	GPIO_InitStructure.Pull = LL_GPIO_PULL_UP;			 // ����
	GPIO_InitStructure.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOC, &GPIO_InitStructure);					 // ��ʼ��PC10��PC11

	// UART4 ��ʼ������
	USART_InitStructure.BaudRate = bound;										// ����������
	USART_InitStructure.DataWidth = LL_USART_DATAWIDTH_8B;						// �ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.StopBits = LL_USART_STOPBITS_1;							// һ��ֹͣλ
	USART_InitStructure.Parity = LL_USART_PARITY_NONE;								// ����żУ��λ
	USART_InitStructure.HardwareFlowControl = LL_USART_HWCONTROL_NONE; // ��Ӳ������������
	USART_InitStructure.TransferDirection = LL_USART_DIRECTION_RX | LL_USART_DIRECTION_TX;					// �շ�ģʽ
	USART_InitStructure.OverSampling = LL_USART_OVERSAMPLING_16;
	LL_USART_Init(UART4, &USART_InitStructure);										// ��ʼ������1

	LL_USART_Enable(UART4); // ʹ�ܴ���1

	LL_USART_ClearFlag_TC(UART4);

	USART_ITConfig(UART4, USART_IT_RXNE, state); // ��������ж�

	// USART3 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;		  // ����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // ��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		  // �����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);							  // ����ָ���Ĳ�����ʼ��VIC�Ĵ���
}

void TFmini_left_USART_Close(void)
{
	// // GPIO�˿�����
	// GPIO_InitTypeDef GPIO_InitStructure;
	// USART_InitTypeDef USART_InitStructure;
	// NVIC_InitTypeDef NVIC_InitStructure;

	// RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, DISABLE); // ʹ��GPIOCʱ��
	// RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, DISABLE); // ʹ��UART4ʱ��

	// // ����4��Ӧ���Ÿ���ӳ��			PC10-TXD,PC11-RXD
	// GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4); // GPIOC10����ΪUART4
	// GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4); // GPIOC11����ΪUART4

	// // UART4�˿�����
	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; // GPIOC10��GPIOC11
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;			 // ���ù���
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // �ٶ�50MHz
	// GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			 // ���츴�����
	// GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			 // ����
	// GPIO_Init(GPIOC, &GPIO_InitStructure);					 // ��ʼ��PC10��PC11

	// // UART4 ��ʼ������
	// // USART_InitStructure.USART_BaudRate = bound;										// ����������
	// USART_InitStructure.USART_WordLength = USART_WordLength_8b;						// �ֳ�Ϊ8λ���ݸ�ʽ
	// USART_InitStructure.USART_StopBits = USART_StopBits_1;							// һ��ֹͣλ
	// USART_InitStructure.USART_Parity = USART_Parity_No;								// ����żУ��λ
	// USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ��Ӳ������������
	// USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					// �շ�ģʽ
	// USART_Init(UART4, &USART_InitStructure);										// ��ʼ������1

	// USART_Cmd(UART4, DISABLE); // ʹ�ܴ���1

	// USART_ClearFlag(UART4, USART_FLAG_TC);
	LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART4);
	LL_USART_DisableIT_RXNE(UART4); // ��������ж�
	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_2);
	// // USART3 NVIC ����
	// NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;		  // ����1�ж�ͨ��
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; // ��ռ���ȼ�3
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		  // �����ȼ�0
	// NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;		  // IRQͨ��ʹ��
	// NVIC_Init(&NVIC_InitStructure);							  // ����ָ���Ĳ�����ʼ��VIC�Ĵ���
}

/**************************************************************************
						   �����ǳ�ʼ�� USART5
**************************************************************************/
void gyro_USART_Init(uint32_t bound)
{
	// GPIO�˿�����
	LL_GPIO_InitTypeDef GPIO_InitStructure;
	LL_USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC | LL_AHB1_GRP1_PERIPH_GPIOD); // ʹ��GPIOCʱ��
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART5);						 // ʹ��UART4ʱ��

	// ����4��Ӧ���Ÿ���ӳ��			PC10-TXD,PC11-RXD
	LL_GPIO_SetAFPin_0_7(GPIOD, LL_GPIO_PIN_2, LL_GPIO_AF_8);  // GPIOC10����ΪUART4
	LL_GPIO_SetAFPin_8_15(GPIOC, LL_GPIO_PIN_12, LL_GPIO_AF_8); // GPIOC11����ΪUART4

	// UART4�˿�����
	GPIO_InitStructure.Pin = LL_GPIO_PIN_12;		  // GPIOC10��GPIOC11
	GPIO_InitStructure.Mode = LL_GPIO_MODE_ALTERNATE;	  // ���ù���
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_HIGH; // �ٶ�50MHz
	GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;	  // ���츴�����
	GPIO_InitStructure.Pull = LL_GPIO_PULL_UP;	  // ����
	GPIO_InitStructure.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOC, &GPIO_InitStructure);			  // ��ʼ��PC10��PC11

	// UART4�˿�����
	GPIO_InitStructure.Pin = LL_GPIO_PIN_2;		  // GPIOC10��GPIOC11
	GPIO_InitStructure.Mode = LL_GPIO_MODE_ALTERNATE;	  // ���ù���
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_HIGH; // �ٶ�50MHz
	GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;	  // ���츴�����
	GPIO_InitStructure.Pull = LL_GPIO_PULL_UP;	  // ����
	GPIO_InitStructure.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOD, &GPIO_InitStructure);			  // ��ʼ��PC10��PC11

	// UART4 ��ʼ������
	USART_InitStructure.BaudRate = bound;										// ����������
	USART_InitStructure.DataWidth = LL_USART_DATAWIDTH_8B;						// �ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.StopBits = LL_USART_STOPBITS_1;							// һ��ֹͣλ
	USART_InitStructure.Parity = LL_USART_PARITY_NONE;								// ����żУ��λ
	USART_InitStructure.HardwareFlowControl = LL_USART_HWCONTROL_NONE; // ��Ӳ������������
	USART_InitStructure.TransferDirection = LL_USART_DIRECTION_RX | LL_USART_DIRECTION_TX;					// �շ�ģʽ
	USART_InitStructure.OverSampling = LL_USART_OVERSAMPLING_16;
	LL_USART_Init(UART5, &USART_InitStructure);										// ��ʼ������1

	LL_USART_Enable(UART5); // ʹ�ܴ���1

	LL_USART_ClearFlag_TC(UART5);

	LL_USART_EnableIT_RXNE(UART5); // ��������ж�

	// USART3 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;		  // ����1�ж�ͨ
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // ��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  // �����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);							  // ����ָ���Ĳ�����ʼ��VIC�Ĵ���
}

void gyro_USART_Close(void)
{

	// GPIO_InitTypeDef GPIO_InitStructure;
	// USART_InitTypeDef USART_InitStructure;
	// NVIC_InitTypeDef NVIC_InitStructure;

	// RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE); //
	// RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);						 //

	// GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
	// GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);

	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	// GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	// GPIO_Init(GPIOC, &GPIO_InitStructure);

	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	// // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	// // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// // GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	// // GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	// GPIO_Init(GPIOD, &GPIO_InitStructure);

	// USART_InitStructure.USART_WordLength = USART_WordLength_8b;						// �ֳ�Ϊ8λ���ݸ�ʽ
	// USART_InitStructure.USART_StopBits = USART_StopBits_1;							// һ��ֹͣλ
	// USART_InitStructure.USART_Parity = USART_Parity_No;								// ����żУ��λ
	// USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ��Ӳ������������
	// USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					// �շ�ģʽ
	// USART_Init(UART5, &USART_InitStructure);										// ��ʼ������1

	// USART_Cmd(UART5, DISABLE); // ʹ�ܴ���1

	// USART_ClearFlag(UART5, USART_FLAG_TC);
	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_0);

	LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART5);
	LL_USART_DisableIT_RXNE(UART5); // ��������ж�
												   // USART3 NVIC ����
												   // NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;		  // ����1�ж�ͨ��
												   // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // ��ռ���ȼ�3
												   // NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  // �����ȼ�0
												   // NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;		  // IRQͨ��ʹ��
												   // NVIC_Init(&NVIC_InitStructure);
}
/**************************************************************************
						   �����ǳ�ʼ�� USART6
**************************************************************************/
