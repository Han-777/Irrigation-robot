#include "gray.h"

/******�͵�ƽΪ�Ӵ�������*******/
/********�������Ҫһһ��ӽ�ȥ***************/

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
//	delay_ms(25);//���ʱ����Ա�
//}
int Get_Count(void)
{
	int i=0;
	if(OUT0==0)
	{
		i++;
	}
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
	if(OUT6==0)
	{
		i++;
	}
	if(OUT7==1) // 1 -> 0
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
	if(OUT12==1)
	{
		i++;
	}
	if(OUT13==1)
	{
		i++;
	}
	return i;
}