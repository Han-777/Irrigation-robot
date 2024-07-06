#include "openmv.h"

u8 cx=0,cy=0,color=0,z=0;
void OPENMV_usart_init(u32 bound)
{
	 //PB10 TX    //  PB11   RX   USART3
  LL_GPIO_InitTypeDef GPIO_InitStructure;
	LL_USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB); 
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
 

	LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_10, LL_GPIO_AF_7); //GPIOC6???USART6
	LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_11, LL_GPIO_AF_7); //GPIOC7???USART6
	
  GPIO_InitStructure.Pin = LL_GPIO_PIN_10 | LL_GPIO_PIN_11; 	//GPIOC6?GPIOC7
	GPIO_InitStructure.Mode = LL_GPIO_MODE_ALTERNATE;						//????
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_HIGH;				//??50MHz
	GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;				  //??????
	GPIO_InitStructure.Pull = LL_GPIO_PULL_UP; 						//??
	GPIO_InitStructure.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOB, &GPIO_InitStructure);									  //???PC6,PC7

	USART_InitStructure.BaudRate = bound;                              				//?????
	USART_InitStructure.DataWidth = LL_USART_DATAWIDTH_8B;               			//???8?????
	USART_InitStructure.StopBits = LL_USART_STOPBITS_1;													//?????
	USART_InitStructure.Parity = LL_USART_PARITY_NONE;															//??????
	USART_InitStructure.HardwareFlowControl = LL_USART_HWCONTROL_NONE; //????????
	USART_InitStructure.TransferDirection = LL_USART_DIRECTION_RX | LL_USART_DIRECTION_TX;									//????
  USART_InitStructure.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART3, &USART_InitStructure); 																			//?????1
	
  LL_USART_Enable(USART3);  														//????1 
	
	LL_USART_ClearFlag_TC(USART3);
	
	LL_USART_EnableIT_RXNE(USART3);    			//??????

  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;				//??1????
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;	//?????0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;				//????0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQ????
	NVIC_Init(&NVIC_InitStructure);		
}


void USART3_IRQHandler(void)			 
{
		
		u8 com_data; 
		u8 i;
		static u8 RxCounter1=0;
		static u16 RxBuffer1[10]={0};
		static u8 RxState = 0;	
		static u8 RxFlag1 = 0;
		if( ((LL_USART_IsEnabledIT_RXNE(USART3))&& (LL_USART_IsActiveFlag_RXNE(USART3)))!=RESET)  	   
		{		
//				LED1=0;
				USART_ClearITPendingBit(USART3,USART_IT_RXNE);   
				com_data = LL_USART_ReceiveData9(USART3);
			
				if(RxState==0&&com_data==0x2C)  
				{
					
					RxState=1;
					RxBuffer1[RxCounter1++]=com_data;
				}
		
				else if(RxState==1&&com_data==0x12) 
				{
					RxState=2;
					RxBuffer1[RxCounter1++]=com_data;
				}
		
				else if(RxState==2)
				{
//					LED2=0;
			
					RxBuffer1[RxCounter1++]=com_data;

					if(RxCounter1>=10||com_data == 0x5B)       //RxBuffer1????,??????
					{
						RxState=3;
						RxFlag1=1;
						cx=RxBuffer1[RxCounter1-5];
						cy=RxBuffer1[RxCounter1-4];
						color=RxBuffer1[RxCounter1-3];
						z=RxBuffer1[RxCounter1-2];
						LL_USART_TransmitData9(USART3, color);
					}
				}
		
				else if(RxState==3)		//???????????
				{
						if(RxBuffer1[RxCounter1-1] == 0x5B)
						{
							
									LL_USART_DisableIT_RXNE(USART3);//??DTSABLE??
									if(RxFlag1)
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
						else   //????
						{
									RxState = 0;
									RxCounter1=0;
									for(i=0;i<10;i++)
									{
											RxBuffer1[i]=0x00;      //?????????
									}
						}
				} 
	
				else   //????
				{
						RxState = 0;
						RxCounter1=0;
						for(i=0;i<10;i++)
						{
								RxBuffer1[i]=0x00;      //?????????
						}
				}

		}
	
		
}
//int linshi[6]={0x01,0x02,0x01,0x03,0x03,0x02};
int Openmv_gain()
{	
//	static int jishu1;
//	
//	return linshi[jishu1++];
	delay_init(168);
	LL_USART_Enable(USART3);
	if (color==0x01)
	 return 0x03;//?? ????
	else if (color==0x02)
		return 0x01;//?? ????
	else if(color==0x04)
		return 0x02;//?? ????
	else
		return 0x01;
		LL_USART_Disable(USART3);

}