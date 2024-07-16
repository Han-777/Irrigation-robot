#include "sys.h"
#include "usart.h"
#include "stdio.h"
#include <stdarg.h>
//////////////////////////////////////////////////////////////////////////////////
// ���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h" //ucos ʹ��
#endif
//////////////////////////////////////////////////////////////////////////////////
// ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
// ALIENTEK STM32������
// ����1��ʼ��
// ����ԭ��@ALIENTEK
// ������̳:www.openedv.com
// �޸�����:2012/8/18
// �汾��V1.5
// ��Ȩ���У�����ؾ���
// Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
// All rights reserved
//********************************************************************************
// V1.3�޸�˵��
// ֧����Ӧ��ͬƵ���µĴ��ڲ���������.
// �����˶�printf��֧��
// �����˴��ڽ��������.
// ������printf��һ���ַ���ʧ��bug
// V1.4�޸�˵��
// 1,�޸Ĵ��ڳ�ʼ��IO��bug
// 2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
// 3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
// 4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
// V1.5�޸�˵��
// 1,�����˶�UCOSII��֧��
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// �������´���,֧��printf����,������Ҫѡ��use MicroLIB
#if 1
#pragma import(__use_no_semihosting)
// ��׼����Ҫ��֧�ֺ���
struct __FILE
{
	int handle;
};

FILE __stdout;
// ����_sys_exit()�Ա���ʹ�ð�����ģʽ
void _sys_exit(int x)
{
	x = x;
}
// �ض���fputc����
int fputc(int ch, FILE *f)
{
	while ((USART2->SR & 0X40) == 0)
		; // ѭ������,ֱ���������
	USART2->DR = (u8)ch;
	return ch;
}
#endif

/*ʹ��microLib�ķ���*/
/*
int fputc(int ch, FILE *f)
{
   USART_SendData(USART1, (uint8_t) ch);

   while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}

   return ch;
}
int GetKey (void)  {

   while (!(USART1->SR & USART_FLAG_RXNE));

   return ((int)(USART1->DR & 0x1FF));
}
*/

#if EN_USART3_RX // ���ʹ���˽���
// ����1�жϷ������
// ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���
u8 USART_RX_BUF[USART_REC_LEN]; // ���ջ���,���USART_REC_LEN���ֽ�.
// ����״̬
// bit15��	������ɱ�־
// bit14��	���յ�0x0d
// bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA = 0; // ����״̬���

void USART2_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStrue;
	USART_InitTypeDef USART_InitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;

	// ����ʹ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	USART_DeInit(USART2); // ��λ����2 -> ����û��

	// ��ʼ�� ���ڶ�ӦIO�� TX-PA2 RX-PA3
	GPIO_InitStrue.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStrue.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStrue.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStrue);

	GPIO_InitStrue.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStrue.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA, &GPIO_InitStrue);

	// ��ʼ�� ����ģʽ״̬
	USART_InitStrue.USART_BaudRate = bound;										// ������
	USART_InitStrue.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // Ӳ��������
	USART_InitStrue.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;					// ���� ���� ģʽ��ʹ��
	USART_InitStrue.USART_Parity = USART_Parity_No;								// û����żУ��
	USART_InitStrue.USART_StopBits = USART_StopBits_1;							// һλֹͣλ
	USART_InitStrue.USART_WordLength = USART_WordLength_8b;						// ÿ�η������ݿ��Ϊ8λ
	USART_Init(USART2, &USART_InitStrue);

	USART_Cmd(USART2, ENABLE);					   // ʹ�ܴ���
//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // ���������ж�

//	// ��ʼ�� �ж����ȼ�
//	NVIC_InitStrue.NVIC_IRQChannel = USART2_IRQn;
//	NVIC_InitStrue.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority = 1;
//	NVIC_InitStrue.NVIC_IRQChannelSubPriority = 1;
//	NVIC_Init(&NVIC_InitStrue);
}

void USART3_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// ʹ�� GPIOB �� USART3 ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	// ���� USART3 Tx (PB10) Ϊ�����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// ���� USART3 Rx (PB11) Ϊ��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// ���� USART3
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	// ʹ�� USART3
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART3, ENABLE);
}

//void Serial_SendByte(uint8_t Byte)
//{
//	USART_SendData(USART2, Byte);
//	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
//}

//uint8_t Serial_RxData;
//uint8_t Serial_RxFlag;

//uint8_t Serial_GetRxData(void)
//{
//	return Serial_RxData;
//}

//uint8_t Serial_GetRxFlag(void)
//{
//	if (Serial_RxFlag == 1)
//	{
//		Serial_RxFlag = 0;
//		return 1;
//	}
//	return 0;
//}

//void USART2_IRQHandler(void)
//{
//	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
//	{
//		Serial_RxData = USART_ReceiveData(USART2);
//		Serial_RxFlag = 1;
//		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
//	}
//}

void USART3_IRQHandler(void) // ����1�жϷ������
{
	u8 Res;
#if SYSTEM_SUPPORT_OS // ���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();
#endif
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) // �����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res = USART_ReceiveData(USART3); // ��ȡ���յ�������

		if ((USART_RX_STA & 0x8000) == 0) // ����δ���
		{
			if (USART_RX_STA & 0x4000) // ���յ���0x0d
			{
				if (Res != 0x0a)
					USART_RX_STA = 0; // ���մ���,���¿�ʼ
				else
					USART_RX_STA |= 0x8000; // ���������
			}
			else // ��û�յ�0X0D
			{
				if (Res == 0x0d)
					USART_RX_STA |= 0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA & 0X3FFF] = Res;
					USART_RX_STA++;
					if (USART_RX_STA > (USART_REC_LEN - 1))
						USART_RX_STA = 0; // �������ݴ���,���¿�ʼ����
				}
			}
		}
	}
#if SYSTEM_SUPPORT_OS // ���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();
#endif
}
#endif
