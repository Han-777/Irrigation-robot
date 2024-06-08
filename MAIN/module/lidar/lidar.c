#include "lidar.h"
uint16_t Distance_left_max = 30;
uint16_t Distance_left_min = 20;
uint16_t Distance_right_max = 35;
uint16_t Distance_right_min = 20;

// usart2-left
char rx_data_right[9];
uint16_t Dist_right;

// usart4-right
char rx_data_left[9];
uint16_t Dist_left;

void UART4_IRQHandler(void)
{
	u8 Res;
	static u8 count = 0;
	static u8 i = 0;
	u8 j = 0;
	uint16_t Dist;

	if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	{
		Res = USART_ReceiveData(UART4); // 读取接收到的数据
		switch (count)
		{
		case 0:
			if (Res == 0x59)
			{
				count++;
				rx_data_right[i] = Res;
				i++;
			}
			else
			{
				count = 0;
				i = 0;
			}
			break;
		case 1:
			if (Res == 0x59)
			{
				count++;
				rx_data_right[i] = Res;
				i++;
			}
			else
			{
				count = 0;
				i = 0;
			}
			break;
		case 2:
			rx_data_right[i] = Res;
			i++;
			if (i == 8)
				count++;
			break;
		case 3:
			for (j = 0; j < 8; j++)
			{
				rx_data_right[8] += rx_data_right[j];
			}
			if (rx_data_right[8] == Res)
			{
				Dist = ((uint16_t)(rx_data_right[3] << 8) | rx_data_right[2]);
				if(Dist < 0 || Dist > 100)
				{
					Dist = 100;
				}
			}
			Dist_right = Dist;
			count = 0;
			i = 0;
			rx_data_right[8] = 0;
			break;
		}
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);
	}
}

void USART2_IRQHandler(void)
{
	u8 Res;
	static u8 count = 0;
	static u8 i = 0;
	u8 j = 0;
	uint16_t Dist = 0;

	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		Res = USART_ReceiveData(USART2); // 读取接收到的数据
		switch (count)
		{
		case 0:
			if (Res == 0x59)
			{
				count++;
				rx_data_left[i] = Res;
				i++;
			}
			else
			{
				count = 0;
				i = 0;
			}
			break;
		case 1:
			if (Res == 0x59)
			{
				count++;
				rx_data_left[i] = Res;
				i++;
			}
			else
			{
				count = 0;
				i = 0;
			}
			break;
		case 2:
			rx_data_left[i] = Res;
			i++;
			if (i == 8)
				count++;
			break;
		case 3:
			for (j = 0; j < 8; j++)
			{
				rx_data_left[8] += rx_data_left[j];
			}
			if (rx_data_left[8] == Res)
			{
				Dist = ((uint16_t)(rx_data_left[3] << 8) | rx_data_left[2]);
				if (Dist < 0 || Dist > 100)
				{
					Dist = 100;
				}
			}
			Dist_left = Dist;
			count = 0;
			i = 0;
			rx_data_left[8] = 0;
			break;
		}
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}
}
