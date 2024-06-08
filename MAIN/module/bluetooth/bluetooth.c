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
	static u16 USART_RX_STA = 0, times = 0; //
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
