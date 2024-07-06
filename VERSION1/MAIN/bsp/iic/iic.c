#include "iic.h"
/*引脚配置*/
#define OLED_W_SCL(x)		GPIO_WriteBit(GPIOA, GPIO_Pin_12, (BitAction)(x))
#define OLED_W_SDA(x)		GPIO_WriteBit(GPIOA, GPIO_Pin_11, (BitAction)(x))

/*引脚初�?�化*/

void iic_Delay(void)
{
	for (int i = 0; i < 4; i++){}
}

void OLED_I2C_Init(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}

/**
  * @brief  I2C开�?
  * @param  �?
  * @retval �?
  */
void OLED_I2C_Start(void)
{
	OLED_W_SDA(1);
	OLED_W_SCL(1);
	iic_Delay();
	OLED_W_SDA(0);
	OLED_W_SCL(0);
	iic_Delay();
}

/**
  * @brief  I2C停�??
  * @param  �?
  * @retval �?
  */
void OLED_I2C_Stop(void)
{
	OLED_W_SDA(0);
	iic_Delay();
	OLED_W_SCL(1);
	OLED_W_SDA(1);
	iic_Delay();
}

/**
  * @brief  I2C发送一�?字节
  * @param  Byte 要发送的一�?字节
  * @retval �?
  */
void OLED_I2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	delay_us(1);
	for (i = 0; i < 8; i++)
	{
		OLED_W_SDA(Byte & (0x80 >> i));
		OLED_W_SCL(1);
		iic_Delay();
		OLED_W_SCL(0);
		iic_Delay();
		// delay_us(1);
	}
	OLED_W_SCL(1);	//额�?�的一�?时钟，不处理应答信号
	iic_Delay();
	OLED_W_SCL(0);
	iic_Delay();
}

