#include "sys.h"
#include "mp3.h"
#include "lcd.h"
void VirtualTx_Config(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct;
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD | LL_AHB1_GRP1_PERIPH_GPIOG);
	GPIO_InitStruct.Pin = TX_PIN;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	LL_GPIO_SetOutputPin(TX_PORT, TX_PIN);

	GPIO_InitStruct.Pin = RX_PIN;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}

void VirtualCOM_ByteSend(uint8_t Data)
{
	uint8_t i;
	TX_DATA_L(); // 发送起始位
	delay_us(BuadRate_9600);
	for (i = 0; i < 8; i++) // 发送8位数据位
	{
		if (Data & 0x01)
			TX_DATA_H(); // 1
		else
			TX_DATA_L(); // 0
		Data >>= 1;
		delay_us(BuadRate_9600);
	}
	TX_DATA_H(); // 发送结束位
	delay_us(BuadRate_9600);
}

void VirtualCOM_StringSend(u8 *str)
{
	u8 i;
	for (i = 0; i < 8; i++)
		VirtualCOM_ByteSend(str[i]);
}

u8 slight[8] = {0x7E, 0x04, 0x45, 0x00, 0x01, 0xEF, 0x0D, 0x0A},   // 轻微干旱
	general[8] = {0x7E, 0x04, 0x45, 0x00, 0x02, 0xEF, 0x0D, 0x0A}, // 一般干旱
	serious[8] = {0x7E, 0x04, 0x45, 0x00, 0x03, 0xEF, 0x0D, 0x0A}; // 严重干旱

// 语音播报
void MP3_broadcast(colorIdx mess)
{
	if (mess == MILD_DROUGHT)
		VirtualCOM_StringSend(slight);
	else if (mess == GENERL_DROUGHT)
		VirtualCOM_StringSend(general);
	else if (mess == SEVERE_DROUGHT)
		VirtualCOM_StringSend(serious);
	else
		VirtualCOM_StringSend(slight);
}
