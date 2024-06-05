#include "InfCollect.h"
uint16_t Distance_left_max=30;
uint16_t Distance_left_min=20;
uint16_t Distance_right_max=35;
uint16_t Distance_right_min=20;
void TFmini_right_init(uint32_t bound)
{
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);                 //使能GPIOC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);                 //使能UART4时钟
 
	//串口4对应引脚复用映射			PC10-TXD,PC11-RXD
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4); //GPIOC10复用为UART4
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4); //GPIOC11复用为UART4
	
	//UART4端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOC10与GPIOC11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;             //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	       //速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;             //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure);                    //初始化PC10，PC11

  //UART4 初始化设置 
	USART_InitStructure.USART_BaudRate = bound;                                    //波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                    //字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                         //一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;                            //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	               //收发模式
  USART_Init(UART4, &USART_InitStructure);                                       //初始化串口1
	
  USART_Cmd(UART4, ENABLE);   //使能串口1 
	
	USART_ClearFlag(UART4, USART_FLAG_TC);
	

	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启相关中断

	//USART3 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;        //串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;		    //子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			    //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	                        //根据指定的参数初始化VIC寄存器
	
}
void TFmini_right_init_close(uint32_t bound)
{
	//GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,DISABLE);                 //使能GPIOC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,DISABLE);                 //使能UART4时钟
 
	//串口4对应引脚复用映射			PC10-TXD,PC11-RXD
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4); //GPIOC10复用为UART4
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4); //GPIOC11复用为UART4
	
	//UART4端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOC10与GPIOC11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;             //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	       //速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;             //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure);                    //初始化PC10，PC11

  //UART4 初始化设置 
	USART_InitStructure.USART_BaudRate = bound;                                    //波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                    //字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                         //一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;                            //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	               //收发模式
  USART_Init(UART4, &USART_InitStructure);                                       //初始化串口1
	
  USART_Cmd(UART4, DISABLE);   //使能串口1 
	
	USART_ClearFlag(UART4, USART_FLAG_TC);
	

	USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);//开启相关中断

	//USART3 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;        //串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;		    //子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;			    //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	                        //根据指定的参数初始化VIC寄存器
}
char rx_data_right[9];
uint16_t Dist_right;

void UART4_IRQHandler(void)
{
	u8 Res;
	static u8 count=0;
	static u8 i=0;
	u8 j=0;
	uint16_t Dist;
	
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  
		{
			Res =USART_ReceiveData(UART4);	//读取接收到的数据
			switch(count)
			{
				case 0:
					if(Res==0x59)
					{
						count++;rx_data_right[i]=Res;i++;
					}
					else
					{
						count=0;i=0;
					}
					break;
				case 1:
					if(Res==0x59)
					{
						count++;rx_data_right[i]=Res;i++;
					}
					else
					{
						count=0;i=0;
					}
					break;
				case 2:
					rx_data_right[i]=Res;
					i++;
					if(i==8)
						count++;
					break;
				case 3:
					for(j=0;j<8;j++)
					{
						rx_data_right[8]+=rx_data_right[j];
					}
					if(rx_data_right[8]==Res)
					{
						Dist 	=  ((uint16_t)(rx_data_right[3]<<8)|rx_data_right[2]);
						if(Dist>=0 && Dist<=100)
							;
						else
							Dist=100;
					}
					Dist_right=Dist;
					count=0;
					i=0;
					rx_data_right[8]=0;
					break;
			}
			USART_ClearITPendingBit(UART4,USART_IT_RXNE);
		}
}


void TFmini_left_init(uint32_t bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能UART5时钟
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOC12复用为UART5
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOD2复用为UART5
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3; //GPIOC12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART2, &USART_InitStructure); //初始化串口1
	
	USART_ClearFlag(USART2, USART_FLAG_RXNE);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启相关中断
	
	USART_Cmd(USART2, ENABLE);  //使能串口1 
}
void TFmini_left_init_close(uint32_t bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,DISABLE); //使能GPIOC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,DISABLE);//使能UART5时钟
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOC12复用为UART5
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOD2复用为UART5
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3; //GPIOC12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART2, &USART_InitStructure); //初始化串口1
	
	USART_ClearFlag(USART2, USART_FLAG_RXNE);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);//开启相关中断
	
	USART_Cmd(USART2, DISABLE);  //使能串口1 
}
char rx_data_left[9];
uint16_t Dist_left;

void USART2_IRQHandler(void)
{
	u8 Res;
	static u8 count=0;
	static u8 i=0;
	u8 j=0;
	uint16_t Dist=0;
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  
		{
			Res =USART_ReceiveData(USART2);	//读取接收到的数据
			switch(count)
			{
				case 0:
					if(Res==0x59)
					{
						count++;rx_data_left[i]=Res;i++;
					}
					else
					{
						count=0;i=0;
					}
					break;
				case 1:
					if(Res==0x59)
					{
						count++;rx_data_left[i]=Res;i++;
					}
					else
					{
						count=0;i=0;
					}
					break;
				case 2:
					rx_data_left[i]=Res;
					i++;
					if(i==8)
						count++;
					break;
				case 3:
					for(j=0;j<8;j++)
					{
						rx_data_left[8]+=rx_data_left[j];
					}
					if(rx_data_left[8]==Res)
					{
						Dist 	=  ((uint16_t)(rx_data_left[3]<<8)|rx_data_left[2]);
						if(Dist>=0 && Dist<=100)
							;
						else
							Dist=100;
					}
					Dist_left=Dist;
					count=0;
					i=0;
					rx_data_left[8]=0;
					break;
			}
			USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		}
}
