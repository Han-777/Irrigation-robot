#include "stm32f10x.h"
#include "OLED_Font.h"

/*寮曡剼閰嶇疆*/
// #define OLED_W_SCL(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_6, (BitAction)(x))
// #define OLED_W_SDA(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_7, (BitAction)(x))

#define OLED_W_SCL(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)(x))
#define OLED_W_SDA(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction)(x))

/*寮曡剼鍒濆�嬪寲*/
void OLED_I2C_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}

/**
  * @brief  I2C寮€濮�
  * @param  鏃�
  * @retval 鏃�
  */
void OLED_I2C_Start(void)
{
	OLED_W_SDA(1);
	OLED_W_SCL(1);
	OLED_W_SDA(0);
	OLED_W_SCL(0);
}

/**
  * @brief  I2C鍋滄��
  * @param  鏃�
  * @retval 鏃�
  */
void OLED_I2C_Stop(void)
{
	OLED_W_SDA(0);
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}

/**
  * @brief  I2C鍙戦€佷竴涓�瀛楄妭
  * @param  Byte 瑕佸彂閫佺殑涓€涓�瀛楄妭
  * @retval 鏃�
  */
void OLED_I2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		OLED_W_SDA(Byte & (0x80 >> i));
		OLED_W_SCL(1);
		OLED_W_SCL(0);
	}
	OLED_W_SCL(1);	//棰濆�栫殑涓€涓�鏃堕挓锛屼笉澶勭悊搴旂瓟淇″彿
	OLED_W_SCL(0);
}

/**
  * @brief  OLED鍐欏懡浠�
  * @param  Command 瑕佸啓鍏ョ殑鍛戒护
  * @retval 鏃�
  */
void OLED_WriteCommand(uint8_t Command)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//浠庢満鍦板潃
	OLED_I2C_SendByte(0x00);		//鍐欏懡浠�
	OLED_I2C_SendByte(Command); 
	OLED_I2C_Stop();
}

/**
  * @brief  OLED鍐欐暟鎹�
  * @param  Data 瑕佸啓鍏ョ殑鏁版嵁
  * @retval 鏃�
  */
void OLED_WriteData(uint8_t Data)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//浠庢満鍦板潃
	OLED_I2C_SendByte(0x40);		//鍐欐暟鎹�
	OLED_I2C_SendByte(Data);
	OLED_I2C_Stop();
}

/**
  * @brief  OLED璁剧疆鍏夋爣浣嶇疆
  * @param  Y 浠ュ乏涓婅�掍负鍘熺偣锛屽悜涓嬫柟鍚戠殑鍧愭爣锛岃寖鍥达細0~7
  * @param  X 浠ュ乏涓婅�掍负鍘熺偣锛屽悜鍙虫柟鍚戠殑鍧愭爣锛岃寖鍥达細0~127
  * @retval 鏃�
  */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
	OLED_WriteCommand(0xB0 | Y);					//璁剧疆Y浣嶇疆
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//璁剧疆X浣嶇疆楂�4浣�
	OLED_WriteCommand(0x00 | (X & 0x0F));			//璁剧疆X浣嶇疆浣�4浣�
}

/**
  * @brief  OLED娓呭睆
  * @param  鏃�
  * @retval 鏃�
  */
void OLED_Clear(void)
{  
	uint8_t i, j;
	for (j = 0; j < 8; j++)
	{
		OLED_SetCursor(j, 0);
		for(i = 0; i < 128; i++)
		{
			OLED_WriteData(0x00);
		}
	}
}

/**
  * @brief  OLED鏄剧ず涓€涓�瀛楃��
  * @param  Line 琛屼綅缃�锛岃寖鍥达細1~4
  * @param  Column 鍒椾綅缃�锛岃寖鍥达細1~16
  * @param  Char 瑕佹樉绀虹殑涓€涓�瀛楃�︼紝鑼冨洿锛欰SCII鍙�瑙佸瓧绗�
  * @retval 鏃�
  */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{      	
	uint8_t i;
	OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);		//璁剧疆鍏夋爣浣嶇疆鍦ㄤ笂鍗婇儴鍒�
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Char - ' '][i]);			//鏄剧ず涓婂崐閮ㄥ垎鍐呭��
	}
	OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);	//璁剧疆鍏夋爣浣嶇疆鍦ㄤ笅鍗婇儴鍒�
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Char - ' '][i + 8]);		//鏄剧ず涓嬪崐閮ㄥ垎鍐呭��
	}
}

/**
  * @brief  OLED鏄剧ず瀛楃�︿覆
  * @param  Line 璧峰�嬭�屼綅缃�锛岃寖鍥达細1~4
  * @param  Column 璧峰�嬪垪浣嶇疆锛岃寖鍥达細1~16
  * @param  String 瑕佹樉绀虹殑瀛楃�︿覆锛岃寖鍥达細ASCII鍙�瑙佸瓧绗�
  * @retval 鏃�
  */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)
	{
		OLED_ShowChar(Line, Column + i, String[i]);
	}
}

/**
  * @brief  OLED娆℃柟鍑芥暟
  * @retval 杩斿洖鍊肩瓑浜嶺鐨刌娆℃柟
  */
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y--)
	{
		Result *= X;
	}
	return Result;
}

/**
  * @brief  OLED鏄剧ず鏁板瓧锛堝崄杩涘埗锛屾�ｆ暟锛�
  * @param  Line 璧峰�嬭�屼綅缃�锛岃寖鍥达細1~4
  * @param  Column 璧峰�嬪垪浣嶇疆锛岃寖鍥达細1~16
  * @param  Number 瑕佹樉绀虹殑鏁板瓧锛岃寖鍥达細0~4294967295
  * @param  Length 瑕佹樉绀烘暟瀛楃殑闀垮害锛岃寖鍥达細1~10
  * @retval 鏃�
  */
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i, Number / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
  * @brief  OLED鏄剧ず鏁板瓧锛堝崄杩涘埗锛屽甫绗﹀彿鏁帮級
  * @param  Line 璧峰�嬭�屼綅缃�锛岃寖鍥达細1~4
  * @param  Column 璧峰�嬪垪浣嶇疆锛岃寖鍥达細1~16
  * @param  Number 瑕佹樉绀虹殑鏁板瓧锛岃寖鍥达細-2147483648~2147483647
  * @param  Length 瑕佹樉绀烘暟瀛楃殑闀垮害锛岃寖鍥达細1~10
  * @retval 鏃�
  */
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
{
	uint8_t i;
	uint32_t Number1;
	if (Number >= 0)
	{
		OLED_ShowChar(Line, Column, '+');
		Number1 = Number;
	}
	else
	{
		OLED_ShowChar(Line, Column, '-');
		Number1 = -Number;
	}
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i + 1, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
  * @brief  OLED鏄剧ず鏁板瓧锛堝崄鍏�杩涘埗锛屾�ｆ暟锛�
  * @param  Line 璧峰�嬭�屼綅缃�锛岃寖鍥达細1~4
  * @param  Column 璧峰�嬪垪浣嶇疆锛岃寖鍥达細1~16
  * @param  Number 瑕佹樉绀虹殑鏁板瓧锛岃寖鍥达細0~0xFFFFFFFF
  * @param  Length 瑕佹樉绀烘暟瀛楃殑闀垮害锛岃寖鍥达細1~8
  * @retval 鏃�
  */
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i, SingleNumber;
	for (i = 0; i < Length; i++)							
	{
		SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
		if (SingleNumber < 10)
		{
			OLED_ShowChar(Line, Column + i, SingleNumber + '0');
		}
		else
		{
			OLED_ShowChar(Line, Column + i, SingleNumber - 10 + 'A');
		}
	}
}

/**
  * @brief  OLED鏄剧ず鏁板瓧锛堜簩杩涘埗锛屾�ｆ暟锛�
  * @param  Line 璧峰�嬭�屼綅缃�锛岃寖鍥达細1~4
  * @param  Column 璧峰�嬪垪浣嶇疆锛岃寖鍥达細1~16
  * @param  Number 瑕佹樉绀虹殑鏁板瓧锛岃寖鍥达細0~1111 1111 1111 1111
  * @param  Length 瑕佹樉绀烘暟瀛楃殑闀垮害锛岃寖鍥达細1~16
  * @retval 鏃�
  */
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i, Number / OLED_Pow(2, Length - i - 1) % 2 + '0');
	}
}

/**
  * @brief  OLED鍒濆�嬪寲
  * @param  鏃�
  * @retval 鏃�
  */
void OLED_Init(void)
{
	uint32_t i, j;
	
	for (i = 0; i < 1000; i++)			//涓婄數寤舵椂
	{
		for (j = 0; j < 1000; j++);
	}
	
	OLED_I2C_Init();			//绔�鍙ｅ垵濮嬪寲
	
	OLED_WriteCommand(0xAE);	//鍏抽棴鏄剧ず
	
	OLED_WriteCommand(0xD5);	//璁剧疆鏄剧ず鏃堕挓鍒嗛�戞瘮/鎸�鑽″櫒棰戠巼
	OLED_WriteCommand(0x80);
	
	OLED_WriteCommand(0xA8);	//璁剧疆澶氳矾澶嶇敤鐜�
	OLED_WriteCommand(0x3F);
	
	OLED_WriteCommand(0xD3);	//璁剧疆鏄剧ず鍋忕Щ
	OLED_WriteCommand(0x00);
	
	OLED_WriteCommand(0x40);	//璁剧疆鏄剧ず寮€濮嬭��
	
	OLED_WriteCommand(0xA1);	//璁剧疆宸﹀彸鏂瑰悜锛�0xA1姝ｅ父 0xA0宸﹀彸鍙嶇疆
	
	OLED_WriteCommand(0xC8);	//璁剧疆涓婁笅鏂瑰悜锛�0xC8姝ｅ父 0xC0涓婁笅鍙嶇疆

	OLED_WriteCommand(0xDA);	//璁剧疆COM寮曡剼纭�浠堕厤缃�
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);	//璁剧疆瀵规瘮搴︽帶鍒�
	OLED_WriteCommand(0xCF);

	OLED_WriteCommand(0xD9);	//璁剧疆棰勫厖鐢靛懆鏈�
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB);	//璁剧疆VCOMH鍙栨秷閫夋嫨绾у埆
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4);	//璁剧疆鏁翠釜鏄剧ず鎵撳紑/鍏抽棴

	OLED_WriteCommand(0xA6);	//璁剧疆姝ｅ父/鍊掕浆鏄剧ず

	OLED_WriteCommand(0x8D);	//璁剧疆鍏呯數娉�
	OLED_WriteCommand(0x14);

	OLED_WriteCommand(0xAF);	//寮€鍚�鏄剧ず
		
	OLED_Clear();				//OLED娓呭睆
}
