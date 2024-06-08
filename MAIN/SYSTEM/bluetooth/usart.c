#include "sys.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////
//????ucos,???????????.
#if SYSTEM_SUPPORT_OS
#include "includes.h" //ucos ??
#endif
//////////////////////////////////////////////////////////////////////////////////
//?????????,??????,??????????
// ALIENTEK STM32F4??????
//??1???
//????@ALIENTEK
//????:www.openedv.com
//????:2014/6/10
//??:V1.5
//????,?????
// Copyright(C) ????????????? 2009-2019
// All rights reserved
//********************************************************************************
// V1.3????
//?????????????????.
//????printf???
//???????????.
//???printf????????bug
// V1.4????
// 1,???????IO?bug
// 2,???USART_RX_STA,????????????2?14??
// 3,???USART_REC_LEN,????????????????(???2?14??)
// 4,???EN_USART1_RX?????
// V1.5????
// 1,????UCOSII???
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//??????,??printf??,??????use MicroLIB
u8 drought_buff[40] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //????
	receive_flag;
u8 lcx, lcy, lcolor, lz;
u8 ganhan;

#if 1
#pragma import(__use_no_semihosting)
//??????????
struct __FILE
{
	int handle;
};

FILE __stdout;
//??_sys_exit()??????????
void _sys_exit(int x)
{
	x = x;
}
//???fputc??
int fputc(int ch, FILE *f)
{
	while ((USART1->SR & 0X40) == 0)
		; //????,??????
	USART1->DR = (u8)ch;
	return ch;
}
#endif

#if EN_USART1_RX //???????
//??1??????
//??,??USARTx->SR??????????
u8 USART_RX_BUF[USART_REC_LEN]; //????,??USART_REC_LEN???.
//????
// bit15,	??????
// bit14,	???0x0d
// bit13~0,	??????????
u16 USART_RX_STA = 0; //??????

//???IO ??1
// bound:???
void uart_close(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, DISABLE);	//??GPIOA??
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, DISABLE); //??USART1??

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);  // GPIOA9???USART1
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); // GPIOA10???USART1

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; // GPIOA9?GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;			//????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//??50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//??????
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//??
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//???PA9,PA10

	USART_InitStructure.USART_BaudRate = bound;										//?????
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						//???8?????
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							//?????
	USART_InitStructure.USART_Parity = USART_Parity_No;								//??????
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //????????
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//????
	USART_Init(USART1, &USART_InitStructure);										//?????1

	USART_Cmd(USART1, DISABLE); //????1

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		  //??1????
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //?????3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		  //????3
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;		  // IRQ????
	NVIC_Init(&NVIC_InitStructure);							  //??????????VIC????
}
void uart_init(u32 bound)
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

#if EN_USART1_RX
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //??????

	// Usart1 NVIC ??
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		  //??1????
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //?????3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		  //????3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // IRQ????
	NVIC_Init(&NVIC_InitStructure);							  //??????????VIC????

#endif
}

void USART1_IRQHandler(void) //??1??????
{
	static u16 USART_RX_STA = 0, times = 0; //??????

#ifdef OS_TICKS_PER_SEC //??????????,?????ucosII?.
	OSIntEnter();
#endif
	u8 com_data;
	u8 i;
	static u8 lRxCounter1 = 0;
	static u16 lRxBuffer1[10] = {0};
	static u8 lRxState = 0;
	static u8 lRxFlag1 = 0;
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		//				LED1=0;
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		com_data = USART_ReceiveData(USART1);

		if (lRxState == 0 && com_data == 0x2C)
		{

			lRxState = 1;
			lRxBuffer1[lRxCounter1++] = com_data;
		}

		else if (lRxState == 1 && com_data == 0x12)
		{
			lRxState = 2;
			lRxBuffer1[lRxCounter1++] = com_data;
		}

		else if (lRxState == 2)
		{
			//					LED2=0;

			lRxBuffer1[lRxCounter1++] = com_data;

			if (lRxCounter1 >= 10 || com_data == 0x5B) // RxBuffer1????,??????
			{
				lRxState = 3;
				lRxFlag1 = 1;
				drought_buff[ganhan++] = lRxBuffer1[lRxCounter1 - 2];
				//						lz=lRxBuffer1[lRxCounter1-2];
				//						USART_SendData(USART1,lcolor);
			}
		}

		else if (lRxState == 3) //???????????
		{
			if (lRxBuffer1[lRxCounter1 - 1] == 0x5B)
			{

				USART_ITConfig(USART1, USART_IT_RXNE, DISABLE); //??DTSABLE??
				if (lRxFlag1)
				{
					//									OLED_Refresh();
					//									OLED_ShowNum(0, 0,Cx,3,16,1);
					//									OLED_ShowNum(0,17,Cy,3,16,1);
					//									OLED_ShowNum(0,33,Cw,3,16,1);
					//									OLED_ShowNum(0,49,Ch,3,16,1);
				}
				lRxFlag1 = 0;
				lRxCounter1 = 0;
				lRxState = 0;
				USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
			}
			else //????
			{
				lRxState = 0;
				lRxCounter1 = 0;
				for (i = 0; i < 10; i++)
				{
					lRxBuffer1[i] = 0x00; //?????????
				}
			}
		}

		else //????
		{
			lRxState = 0;
			lRxCounter1 = 0;
			for (i = 0; i < 10; i++)
			{
				lRxBuffer1[i] = 0x00; //?????????
			}
		}
	}
}
#endif

// #include "sys.h"
// #include "usart.h"
////////////////////////////////////////////////////////////////////////////////////
////????ucos,???????????.
// #if SYSTEM_SUPPORT_OS
// #include "includes.h"					//ucos ??
// #endif
////////////////////////////////////////////////////////////////////////////////////
////?????????,??????,??????????
////ALIENTEK STM32F4??????
////??1???
////????@ALIENTEK
////????:www.openedv.com
////????:2014/6/10
////??:V1.5
////????,?????
////Copyright(C) ????????????? 2009-2019
////All rights reserved
////********************************************************************************
////V1.3????
////?????????????????.
////????printf???
////???????????.
////???printf????????bug
////V1.4????
////1,???????IO?bug
////2,???USART_RX_STA,????????????2?14??
////3,???USART_REC_LEN,????????????????(???2?14??)
////4,???EN_USART1_RX?????
////V1.5????
////1,????UCOSII???
////////////////////////////////////////////////////////////////////////////////////
//

////////////////////////////////////////////////////////////////////
////??????,??printf??,??????use MicroLIB
// #if 1
// #pragma import(__use_no_semihosting)
////??????????
// struct __FILE
//{
//	int handle;
// };

// FILE __stdout;
////??_sys_exit()??????????
// void _sys_exit(int x)
//{
//	x = x;
// }
////???fputc??
// int fputc(int ch, FILE *f)
//{
//	while((USART1->SR&0X40)==0);//????,??????
//	USART1->DR = (u8) ch;
//	return ch;
// }
// #endif
//
// #if EN_USART1_RX   //???????
////??1??????
////??,??USARTx->SR??????????
// u8 USART_RX_BUF[USART_REC_LEN];     //????,??USART_REC_LEN???.
////????
////bit15,	??????
////bit14,	???0x0d
////bit13~0,	??????????
// u16 USART_RX_STA=0;       //??????

////???IO ??1
////bound:???
// void uart_init(u32 bound){
//    //GPIO????
//   GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //??GPIOA??
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//??USART1??
//
//	//??1????????
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9???USART1
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10???USART1
//
//	//USART1????
//   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9?GPIOA10
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//????
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//??50MHz
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //??????
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //??
//	GPIO_Init(GPIOA,&GPIO_InitStructure); //???PA9,PA10

//   //USART1 ?????
//	USART_InitStructure.USART_BaudRate = bound;//?????
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//???8?????
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//?????
//	USART_InitStructure.USART_Parity = USART_Parity_No;//??????
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//????????
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//????
//  USART_Init(USART1, &USART_InitStructure); //?????1
//
//  USART_Cmd(USART1, ENABLE);  //????1
//
//	//USART_ClearFlag(USART1, USART_FLAG_TC);
//
// #if EN_USART1_RX
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//??????

//	//Usart1 NVIC ??
//  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//??1????
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//?????3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//????3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ????
//	NVIC_Init(&NVIC_InitStructure);	//??????????VIC????

// #endif
//
// }

// void USART1_IRQHandler(void)                	//??1??????
//{
//	u8 Res;
// #if SYSTEM_SUPPORT_OS 		//??SYSTEM_SUPPORT_OS??,?????OS.
//	OSIntEnter();
// #endif
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //????(?????????0x0d 0x0a??)
//	{
//		Res =USART_ReceiveData(USART1);//(USART1->DR);	//????????
//
//		if((USART_RX_STA&0x8000)==0)//?????
//		{
//			if(USART_RX_STA&0x4000)//????0x0d
//			{
//				if(Res!=0x0a)USART_RX_STA=0;//????,????
//				else USART_RX_STA|=0x8000;	//?????
//			}
//			else //????0X0D
//			{
//				if(Res==0x0d)USART_RX_STA|=0x4000;
//				else
//				{
//					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
//					USART_RX_STA++;
//					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//??????,??????
//				}
//			}
//		}
//   }
// #if SYSTEM_SUPPORT_OS 	//??SYSTEM_SUPPORT_OS??,?????OS.
//	OSIntExit();
// #endif
// }
// #endif

//