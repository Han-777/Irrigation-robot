#include "InfCollect.h"
uint16_t Distance_left_max=30;
uint16_t Distance_left_min=20;
uint16_t Distance_right_max=35;
uint16_t Distance_right_min=20;
void TFmini_right_init(uint32_t bound)
{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);                 //ʹ��GPIOCʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);                 //ʹ��UART4ʱ��
 
	//����4��Ӧ���Ÿ���ӳ��			PC10-TXD,PC11-RXD
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4); //GPIOC10����ΪUART4
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4); //GPIOC11����ΪUART4
	
	//UART4�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOC10��GPIOC11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;             //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	       //�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;             //����
	GPIO_Init(GPIOC,&GPIO_InitStructure);                    //��ʼ��PC10��PC11

  //UART4 ��ʼ������ 
	USART_InitStructure.USART_BaudRate = bound;                                    //����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                    //�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                         //һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;                            //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	               //�շ�ģʽ
  USART_Init(UART4, &USART_InitStructure);                                       //��ʼ������1
	
  USART_Cmd(UART4, ENABLE);   //ʹ�ܴ���1 
	
	USART_ClearFlag(UART4, USART_FLAG_TC);
	

	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//��������ж�

	//USART3 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;        //����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;		    //�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			    //IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	                        //����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
}
void TFmini_right_init_close(uint32_t bound)
{
	//GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,DISABLE);                 //ʹ��GPIOCʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,DISABLE);                 //ʹ��UART4ʱ��
 
	//����4��Ӧ���Ÿ���ӳ��			PC10-TXD,PC11-RXD
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4); //GPIOC10����ΪUART4
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4); //GPIOC11����ΪUART4
	
	//UART4�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOC10��GPIOC11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;             //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	       //�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;             //����
	GPIO_Init(GPIOC,&GPIO_InitStructure);                    //��ʼ��PC10��PC11

  //UART4 ��ʼ������ 
	USART_InitStructure.USART_BaudRate = bound;                                    //����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                    //�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                         //һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;                            //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	               //�շ�ģʽ
  USART_Init(UART4, &USART_InitStructure);                                       //��ʼ������1
	
  USART_Cmd(UART4, DISABLE);   //ʹ�ܴ���1 
	
	USART_ClearFlag(UART4, USART_FLAG_TC);
	

	USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);//��������ж�

	//USART3 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;        //����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;		    //�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;			    //IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	                        //����ָ���Ĳ�����ʼ��VIC�Ĵ���
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
			Res =USART_ReceiveData(UART4);	//��ȡ���յ�������
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
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOCʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��UART5ʱ��
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOC12����ΪUART5
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOD2����ΪUART5
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3; //GPIOC12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART2, &USART_InitStructure); //��ʼ������1
	
	USART_ClearFlag(USART2, USART_FLAG_RXNE);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�
	
	USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���1 
}
void TFmini_left_init_close(uint32_t bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,DISABLE); //ʹ��GPIOCʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,DISABLE);//ʹ��UART5ʱ��
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOC12����ΪUART5
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOD2����ΪUART5
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3; //GPIOC12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART2, &USART_InitStructure); //��ʼ������1
	
	USART_ClearFlag(USART2, USART_FLAG_RXNE);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);//��������ж�
	
	USART_Cmd(USART2, DISABLE);  //ʹ�ܴ���1 
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
			Res =USART_ReceiveData(USART2);	//��ȡ���յ�������
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
