/*--------------------------------------------------------------*/
//��ֹ�ظ�����
#ifndef	__LINE_H__
#define __LINE_H__
/*--------------------------------------------------------------*/
#include "sys.h"
#define OUT1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)//0Ϊ��������
#define OUT2 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)//
#define OUT3 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)
#define OUT4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)
#define OUT5 GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_9)//

#define OUT6 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//0Ϊ��������
#define OUT7 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)//
#define OUT8 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)
#define OUT9 GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_7)
#define OUT10 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)//
#define OUT11 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)//0Ϊ��������
#define OUT12 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)//

#define New_OUT_Left GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)//��,�µķ����ܻҶ�
#define New_OUT_Right GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)//��,�µķ����ܻҶ�
void Line_Init(void);
int Get_Count(void);
#endif

