#include "gray.h"

/******低电平为接触到白线*******/
/********其他情况要一一添加进去***************/

///******************/
// int Err=0;
// int Pwm_R=0;
// int Pwm_L=0;
// int Err_l=0;
// float Line_Kp=0;
// float Line_Kd=0;
///******************/
// void Line_Revise(void)
//{
//	Err=Err_Line();
//	Pwm_R=Line_Kp*Err+Line_Kd*(Err-Err_l);
//	Pwm_L=(-Line_Kp)*Err+Line_Kd*(Err-Err_l);
//	Err_l=Err;
//	Car_Load(Pwm_L,Pwm_R);
//	delay_ms(25);//这个时间可以变
// }
const int gray_threshold = 2;
int cross_cnt = 0;
int get_gray_cnt(void)
{
	int i = 0;
	if (OUT0 == 0)
	{
		i++;
	}
	if (OUT1 == 0)
	{
		i++;
	}
	if (OUT2 == 0)
	{
		i++;
	}
	if (OUT3 == 0)
	{
		i++;
	}
	if (OUT4 == 0)
	{
		i++;
	}
	if (OUT5 == 0)
	{
		i++;
	}
	if (OUT6 == 0)
	{
		i++;
	}
	if (OUT7 == 0) // 1 -> 0
	{
		i++;
	}
	if (OUT8 == 0)
	{
		i++;
	}
	if (OUT9 == 0)
	{
		i++;
	}
	if (OUT10 == 0)
	{
		i++;
	}
	if (OUT11 == 0)
	{
		i++;
	}
	if (OUT12 == 0)
	{
		i++;
	}
	if (OUT13 == 0)
	{
		i++;
	}
	return i;
}

// this function should followed by next operation, IT CAN NOT BE CALLED MULTIPLE TIMES!!!
int get_cross_flag(void)
{
	if ((OUT0 || OUT1 || OUT2 || OUT3 || OUT4 || OUT5 || OUT6 || OUT7 || OUT8 || OUT9 || OUT10 || OUT11 || OUT12 || OUT13))
	{
		if (get_gray_cnt() >= gray_threshold)
		{
			cross_cnt++;
			if (cross_cnt == 2 || cross_cnt == 4 || cross_cnt == 6)
			{
				clockwise_rotate_flag += ((cross_cnt == 4) ? -1 : 1);
			}
			else if (cross_cnt == 1 || cross_cnt == 3 || cross_cnt == 5)
			{
				clockwise_rotate_flag += ((cross_cnt == 3) ? -1 : 1);
			}
			return 1;
		}
	}
	return 0;
}