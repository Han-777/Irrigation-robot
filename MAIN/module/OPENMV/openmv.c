#include "openmv.h"

u8 cx = 0, cy = 0, color = 0, z = 0;

void USART3_IRQHandler(void)
{

	u8 com_data;
	u8 i;
	static u8 RxCounter1 = 0;
	static u16 RxBuffer1[10] = {0};
	static u8 RxState = 0;
	static u8 RxFlag1 = 0;
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		//				LED1=0;
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		com_data = USART_ReceiveData(USART3);

		if (RxState == 0 && com_data == 0x2C)
		{

			RxState = 1;
			RxBuffer1[RxCounter1++] = com_data;
		}

		else if (RxState == 1 && com_data == 0x12)
		{
			RxState = 2;
			RxBuffer1[RxCounter1++] = com_data;
		}

		else if (RxState == 2)
		{
			//					LED2=0;

			RxBuffer1[RxCounter1++] = com_data;

			if (RxCounter1 >= 10 || com_data == 0x5B) // RxBuffer1????,??????
			{
				RxState = 3;
				RxFlag1 = 1;
				cx = RxBuffer1[RxCounter1 - 5];
				cy = RxBuffer1[RxCounter1 - 4];
				color = RxBuffer1[RxCounter1 - 3];
				z = RxBuffer1[RxCounter1 - 2];
				USART_SendData(USART3, color);
			}
		}

		else if (RxState == 3) //???????????
		{
			if (RxBuffer1[RxCounter1 - 1] == 0x5B)
			{

				USART_ITConfig(USART3, USART_IT_RXNE, DISABLE); //??DTSABLE??
				if (RxFlag1)
				{
					//									OLED_Refresh();
					//									OLED_ShowNum(0, 0,Cx,3,16,1);
					//									OLED_ShowNum(0,17,Cy,3,16,1);
					//									OLED_ShowNum(0,33,Cw,3,16,1);
					//									OLED_ShowNum(0,49,Ch,3,16,1);
				}
				RxFlag1 = 0;
				RxCounter1 = 0;
				RxState = 0;
				USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
			}
			else //????
			{
				RxState = 0;
				RxCounter1 = 0;
				for (i = 0; i < 10; i++)
				{
					RxBuffer1[i] = 0x00; //?????????
				}
			}
		}

		else //????
		{
			RxState = 0;
			RxCounter1 = 0;
			for (i = 0; i < 10; i++)
			{
				RxBuffer1[i] = 0x00; //?????????
			}
		}
	}
}
// int linshi[6]={0x01,0x02,0x01,0x03,0x03,0x02};
int Openmv_gain()
{
	//	static int jishu1;
	//
	//	return linshi[jishu1++];
	delay_init(168);
	USART_Cmd(USART3, ENABLE);
	if (color == 0x01)
		return 0x03; //?? ????
	else if (color == 0x02)
		return 0x01; //?? ????
	else if (color == 0x04)
		return 0x02; //?? ????
	else
		return 0x01;
	USART_Cmd(USART3, DISABLE);
}