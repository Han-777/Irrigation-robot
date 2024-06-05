#include "line.h"
void Line_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOG|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE,ENABLE);
	
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_7|GPIO_Pin_9|GPIO_Pin_14;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOG,&GPIO_InitStruct);//
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);//
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);//
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOE,&GPIO_InitStruct);//
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_9;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);//
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);//
}
/******低电平为接触到白线*******/
/********其他情况要一一添加进去***************/

///******************/
//int Err=0;
//int Pwm_R=0;
//int Pwm_L=0;
//int Err_l=0;
//float Line_Kp=0;
//float Line_Kd=0;
///******************/
//void Line_Revise(void)
//{
//	Err=Err_Line();
//	Pwm_R=Line_Kp*Err+Line_Kd*(Err-Err_l);
//	Pwm_L=(-Line_Kp)*Err+Line_Kd*(Err-Err_l);
//	Err_l=Err;
//	Car_Load(Pwm_L,Pwm_R);
//	delay_ms(25);//这个时间可以变
//}
int Get_Count(void)
{
	int i=0;
	if(OUT1==0)
	{
		i=i+1;
	}
	if(OUT2==0)
	{
		i++;
	}
	if(OUT3==0)
	{
		i++;
	}
	if(OUT4==0)
	{
		i++;
	}
	if(OUT5==0)
	{
		i++;
	}
	if(OUT7==1)
	{
		i++;
	}
	if(OUT8==1)
	{
		i++;
	}
	if(OUT9==1)
	{
		i++;
	}
	if(OUT10==1)
	{
		i++;
	}
	if(OUT11==1)
	{
		i++;
	}
	
	return i;
}