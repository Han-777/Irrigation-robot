#include "guandian.h"
void GuanDian_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	
	// GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	// GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	// GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
	// GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	// GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	// GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	// GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	// GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	// GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
	// GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	// GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	// GPIO_Init(GPIOD,&GPIO_InitStruct);
	
	// GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	// GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	// GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_5|GPIO_Pin_6;
	// GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	// GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	// GPIO_Init(GPIOE,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOG,&GPIO_InitStruct);
}
//void GuanDian_Control(void)
//{
////	if(Left==1||Right==1)
////	{
////		Car_Stop();
////		
////	}
//	if(Left==1)
//		LED1=0;
////	else if(Left==0&&Right==0)
////	{
////		Car_go();
////	}
//	else if(Left==0)
//		LED2=0;
//}