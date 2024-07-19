//#include "sys.h"
//#include "mp3.h"

//void VirtualTx_Config(void)
//{
//	GPIO_InitTypeDef  GPIO_InitStruct;
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOG,ENABLE);
//	GPIO_InitStruct.GPIO_Pin=TX_PIN;
//	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
//	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
//	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;	
//	GPIO_Init(GPIOD,&GPIO_InitStruct);
//	GPIO_SetBits(TX_PORT, TX_PIN);	
//	
//	GPIO_InitStruct.GPIO_Pin=RX_PIN;
//	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
//	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
//	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
//	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;	
//	GPIO_Init(GPIOG,&GPIO_InitStruct);
//}

//void VirtualCOM_ByteSend(uint8_t Data)
//{
//    uint8_t i;
//    TX_DATA_L();                // 发送起始位
//    delay_us(BuadRate_9600);
//    for(i=0; i<8; i++)       	  // 发送8位数据位
//    {
//        if (Data & 0x01)
//            TX_DATA_H();        // 1
//        else
//            TX_DATA_L();        // 0
//        Data >>= 1;
//        delay_us(BuadRate_9600);
//    }
//    TX_DATA_H();                // 发送结束位
//    delay_us(BuadRate_9600);
//}

//void VirtualCOM_StringSend(u8 *str)
//{
//	u8 i;
//	for(i=0;i<8;i++)                     
//		VirtualCOM_ByteSend(str[i]);
//		
//}

//u8 slight[8]={0x7E,0x04,0x45,0x00,0x01,0xEF,0x0D,0x0A},		//轻微干旱
//   general[8]={0x7E,0x04,0x45,0x00,0x02,0xEF,0x0D,0x0A},	//一般干旱
//   serious[8]={0x7E,0x04,0x45,0x00,0x03,0xEF,0x0D,0x0A};	//严重干旱

////语音播报
//void MP3_broadcast(u8 mess)
//{
//	if(mess==0x01)
//		VirtualCOM_StringSend(slight);
//	else if(mess==0x02)
//		VirtualCOM_StringSend(general);
//	else if(mess==0x03)
//		VirtualCOM_StringSend(serious);
//}
