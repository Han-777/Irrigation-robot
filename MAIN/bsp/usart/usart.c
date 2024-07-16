#include "usart.h"
/**************************************************************************
						Bluetooth ��ʼ�� USART1
**************************************************************************/

void Bluetooth_USART_Init(u32 bound)
{
	// GPIO????
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  //??GPIOA??
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //??USART1??

	//??1????????
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);  // GPIOA9???USART1
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); // GPIOA10???USART1

	// USART1????
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; // GPIOA9?GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;			//????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//??50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//??????
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//??
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//???PA9,PA10

	// USART1 ?????
	USART_InitStructure.USART_BaudRate = bound;										//?????
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						//???8?????
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							//?????
	USART_InitStructure.USART_Parity = USART_Parity_No;								//??????
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //????????
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//????
	USART_Init(USART1, &USART_InitStructure);										//?????1

	USART_Cmd(USART1, ENABLE); //????1

	// USART_ClearFlag(USART1, USART_FLAG_TC);

	// #if EN_USART1_RX
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //??????

	// Usart1 NVIC ??
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		  //??1????
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //?????3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //????3
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, DISABLE);
	USART_ITConfig(USART1, USART_IT_RXNE, DISABLE); // ��������ж�

	USART_Cmd(USART1, DISABLE); //????1

	// NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		  //??1????
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //?????3
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //????3
	// NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;		  // IRQ????
	// NVIC_Init(&NVIC_InitStructure);							  //??????????VIC????
}

/**************************************************************************
						TFmini_Left ��ʼ�� USART2
**************************************************************************/

void TFmini_right_USART_Init(uint32_t bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  // ʹ��GPIOCʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); // ʹ��UART5ʱ��

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); // GPIOC12����ΪUART5
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); // GPIOD2����ΪUART5

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; // GPIOC12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		   // ���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   // �ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		   // ���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		   // ����
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						// �ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							// һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;								// ����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					// �շ�ģʽ
	USART_Init(USART2, &USART_InitStructure);										// ��ʼ������1

	USART_ClearFlag(USART2, USART_FLAG_RXNE);

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;		  // ����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; // ��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		  // �����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);							  // ����ָ���Ĳ�����ʼ��VIC�Ĵ���

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // ��������ж�

	USART_Cmd(USART2, ENABLE); // ʹ�ܴ���1
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
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, DISABLE);
	USART_ITConfig(USART2, USART_IT_RXNE, DISABLE); // ��������ж�
	DMA_Cmd(DMA1_Stream5, DISABLE);
	// USART_Cmd(USART2, DISABLE); // ʹ�ܴ���1
}

/**************************************************************************
						OpenMV ��ʼ�� USART3
**************************************************************************/
void OpenMV_USART_Init(u32 bound)
{
	// PB10 TX    //  PB11   RX   USART3
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);

	USART_ClearFlag(USART3, USART_FLAG_TC);

	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART3, ENABLE);
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
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, DISABLE);
	USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);

	// USART_Cmd(USART3, DISABLE);
}
/**************************************************************************
						TFmini_Right ��ʼ�� USART4
**************************************************************************/

void TFmini_left_USART_Init(uint32_t bound)
{
	// GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); // ʹ��GPIOCʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE); // ʹ��UART4ʱ��

	// ����4��Ӧ���Ÿ���ӳ��			PC10-TXD,PC11-RXD
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4); // GPIOC10����ΪUART4
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4); // GPIOC11����ΪUART4

	// UART4�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; // GPIOC10��GPIOC11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;			 // ���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // �ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			 // ���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			 // ����
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 // ��ʼ��PC10��PC11

	// UART4 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;										// ����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						// �ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							// һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;								// ����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					// �շ�ģʽ
	USART_Init(UART4, &USART_InitStructure);										// ��ʼ������1

	USART_Cmd(UART4, ENABLE); // ʹ�ܴ���1

	USART_ClearFlag(UART4, USART_FLAG_TC);

	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE); // ��������ж�

	// USART3 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;		  // ����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; // ��ռ���ȼ�3
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
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, DISABLE);
	USART_ITConfig(UART4, USART_IT_RXNE, DISABLE); // ��������ж�
	DMA_Cmd(DMA1_Stream2, DISABLE);
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
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE); // ʹ��GPIOCʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);						 // ʹ��UART4ʱ��

	// ����4��Ӧ���Ÿ���ӳ��			PC10-TXD,PC11-RXD
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);  // GPIOC10����ΪUART4
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5); // GPIOC11����ΪUART4

	// UART4�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;		  // GPIOC10��GPIOC11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	  // ���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // �ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	  // ���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	  // ����
	GPIO_Init(GPIOC, &GPIO_InitStructure);			  // ��ʼ��PC10��PC11

	// UART4�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;		  // GPIOC10��GPIOC11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	  // ���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // �ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	  // ���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	  // ����
	GPIO_Init(GPIOD, &GPIO_InitStructure);			  // ��ʼ��PC10��PC11

	// UART4 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;										// ����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						// �ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							// һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;								// ����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					// �շ�ģʽ
	USART_Init(UART5, &USART_InitStructure);										// ��ʼ������1

	USART_Cmd(UART5, ENABLE); // ʹ�ܴ���1

	USART_ClearFlag(UART5, USART_FLAG_TC);

	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE); // ��������ж�

	// USART3 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;		  // ����1�ж�ͨ
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // ��ռ���ȼ�3
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
	DMA_Cmd(DMA1_Stream0, DISABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, DISABLE);
	USART_ITConfig(UART5, USART_IT_RXNE, DISABLE); // ��������ж�
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
