#include "task.h"

// void task_A(void)
//{
//	char i = 0;
//	int plant = 0;

//	for (i = 0; i < 6; i++)
//	{
//		Rotation(1, 0); // ���ˮ���ƶ�����ˮ
//		Rotation(1, 1); // �ұ�ˮ���ƶ�����ˮ
//	}
//}

// void task_B(void)
//{
//	char i = 0;

//	//	delay_init(168);
//	//	TIM_SetCompare4(TIM8,Balance_angle);	//ƽ��Ƕ�
//	//	delay_ms(1000);

//	for (i = 0; i < 6; i++)
//	{
//		Rotation(2, 0);
//		Rotation(2, 1);
//	}
//}

// void task_C(void)
//{
//	char i = 0;

//	for (i = 0; i < 6; i++)
//	{
//		Rotation(3, 0);
//		Rotation(3, 1);
//	}
//}

// void task_D(void)
//{

//	Rotation(4, 0);
//	Rotation(4, 1);
//}
// int Flower_Count = 0;
// void Task_Init(void)
//{
//	if (Flag_R == 1)
//	{
//		TTL_Hex2Dec();
//		R_r = 1; // ���������жϵ�
//		//		Flower_Count++;
//		//		printf("distance_r=%d\r\n",Dist_right);//���Լ����ܲ�����������
//		//		printf("Flower_Count=%d, N_Flag=%d/r/n",Flower_Count,N_Flag);
//		delay_ms(500);
//		if (N_Flag == 0) // ˫�ر���
//		{
//			Rotation(1, 1);
//		}
//		else if (N_Flag == 2)
//		{
//			Rotation(2, 1);
//		}
//		else if (N_Flag == 4)
//		{
//			Rotation(3, 1);
//		}
//		else if (N_Flag == 6)
//		{
//			Rotation(4, 1);
//		}
//		R_r = 0;
//		Flag_R = 0;
//		TTL_Hex2Dec();
//	}
//	if (Flag_L == 1)
//	{
//		TTL_Hex2Dec();
//		L_l = 1;
//		//		Flower_Count++;
//		//		printf("distance_l=%d\r\n",Dist_left);//���Լ����ܲ�����������
//		//		printf("Flower_Count=%d,N_Flag=%d/r/n",Flower_Count,N_Flag);
//		delay_ms(500);
//		if (N_Flag == 0) // ˫�ر���
//		{
//			Rotation(1, 0);
//		}
//		else if (N_Flag == 2)
//		{
//			Rotation(2, 0);
//		}
//		else if (N_Flag == 4)
//		{
//			Rotation(3, 0);
//		}
//		else if (N_Flag == 6)
//		{
//			Rotation(4, 0);
//		}
//		L_l = 0;
//		Flag_L = 0;
//		TTL_Hex2Dec();
//	}
//	//	BEEP=0;
//	delay_ms(500);

//	EXTInterruppt_Mode();
//	NVIC_Configuration();
//	set = 1;	  // �¼ӵģ���С���տ�ʼ��һ���ٶ�
//	delay_ms(20); //
//	TIM7_Int_Init(1000 - 1, 840 - 1);
//	delay_ms(80); //
//	set = 0;
//	delay_ms(80); // 200->100
//	set = 0;
//	//	BEEP=1;
//}
