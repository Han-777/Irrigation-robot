#include "bluetooth.h"

u8 drought_buff[40] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
   receive_flag;
u8 lcx, lcy, lcolor, lz;
u8 ganhan;

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
		else if (lRxState == 2) // 对完每一次帧头
		{
			//					LED2=0;
			lRxBuffer1[lRxCounter1++] = com_data;
			if (lRxCounter1 >= 10 || com_data == 0x5B) // 到帧尾或数据太长
			{
				lRxState = 3;
				lRxFlag1 = 1;										  // receive finish flag
				drought_buff[ganhan++] = lRxBuffer1[lRxCounter1 - 2]; // -2: 正好取到干旱数据
																	  //						lz=lRxBuffer1[lRxCounter1-2];
																	  //						USART_SendData(USART1,lcolor);
			}
		}
		else if (lRxState == 3)
		{
			if (lRxBuffer1[lRxCounter1 - 1] == 0x5B) // the data is correct
			{
				USART_ITConfig(USART1, USART_IT_RXNE, DISABLE); // bluetooth close
				if (lRxFlag1)
				{
					// display color information
				}
				lRxFlag1 = 0;
				lRxCounter1 = 0;
				lRxState = 0; // clear state variable for next receive
				USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
			}
			else // error info handle
			{
				lRxState = 0;
				lRxCounter1 = 0;
				for (i = 0; i < 10; i++)
				{
					lRxBuffer1[i] = 0x00; // clear receive buffer
				}
			}
		}
		else
		{
			lRxState = 0;
			lRxCounter1 = 0;
			for (i = 0; i < 10; i++)
			{
				lRxBuffer1[i] = 0x00; // strange error: clear the buffer
			}
		}
	}
}
#endif