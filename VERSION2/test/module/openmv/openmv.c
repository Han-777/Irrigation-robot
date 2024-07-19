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
	if (((LL_USART_IsEnabledIT_RXNE(USART3))&& (LL_USART_IsActiveFlag_RXNE(USART3))) != RESET)
	{
		//				LED1=0;
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		com_data = LL_USART_ReceiveData9(USART3);

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
				LL_USART_TransmitData9(USART3, color);
			}
		}

		else if (RxState == 3) //???????????
		{
			if (RxBuffer1[RxCounter1 - 1] == 0x5B)
			{

				LL_USART_DisableIT_RXNE(USART3); //??DTSABLE??
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
				LL_USART_EnableIT_RXNE(USART3);
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

colorIdx water_times;
// int linshi[6]={0x01,0x02,0x01,0x03,0x03,0x02};
int get_OpenMV(void)
{
	delay_init(168);
	LL_USART_Enable(USART3);
	if (color == MILD_DROUGHT)
		return MILD_DROUGHT; //?? ????
	else if (color == GENERL_DROUGHT)
		return GENERL_DROUGHT; //?? ????
	else if (color == SEVERE_DROUGHT)
		return SEVERE_DROUGHT; //?? ????
	else
		return MILD_DROUGHT;
	LL_USART_Disable(USART3);
}