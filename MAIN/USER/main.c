#include "sys.h"
#include "lcd.h"
#include "servo.h"
#include "chassis.h"

int main(void)
{
	delay_init(168);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); // 4抢占 0响应 (数字越小优先级越高！)
													//	LCD_Init();
													//	POINT_COLOR = BLUE; // 画笔颜色
	chassis_Init();
	TIM7_Int_Init(1000 - 1, 840 - 1); // 84M / 4200 / 1000 = 10ms
	delay_ms(1000);

	//	Car_Load(40, 40);
	//	delay_ms(10000);
	//	Turn_Left_90_Angles();
	//	delay_ms(10000);
	//	Car_stop();
	//	delay_ms(5000);
	//	Turn_Right_90_Angles();
	//	delay_ms(10000);

	Car_stop();
	servo_Init_All();
	//	gray_GPIO_Init();
	//	photoelectricity_GPIO_Init();
	//	delay_ms(5000);
	//	Car_stop();
	//	delay_ms(1000);
	//	for (int i = 0; i < 180; i++)
	//	{
	//		Servo_Pitch_Control(i);
	//		delay_ms(100);
	//		Servo_Yaw_Control(i);
	//		delay_ms(100);
	//	}

	Servo_Pitch_Control(90);
	Servo_Yaw_Control(90);
	int i = 0;
	int yaw = 0;
	while (1)
	{
		//		Chinese_Show_one(10, 10, 0, 16, 0);
		// LCD_ShowNum(10, 10, cnt, 5, 16);
		//		Chinese_Show_one(64, 20, 1, 16, 0);
		//		lcd_dis();
		if (OUT1 == 0 || OUT2 == 0 || OUT3 == 0 || OUT4 == 0 || OUT5 == 0 || OUT6 == 0 || OUT7 == 1 | OUT8 == 1 || OUT9 == 1 || OUT10 == 1 || OUT11 == 1)
		{

			// 二次判断，看是否要用
			//			if(N_Flag==3)
			//			{
			//				delay_ms(10);
			//			}
			//			if(N_Flag>=5)
			//			{
			//				delay_ms(40);
			//			}
			if (Get_Count() >= 2)
			{

				if (((Flower_Count >= 5 && Flower_Count <= 7) || (Flower_Count >= 11 && Flower_Count <= 13) || (Flower_Count >= 17 && Flower_Count <= 30)) && (FLAG == 1))
				{
					Car_stop();
					TIM7_Close();
					NVIC_Configuration_Close();
					k++; // k反复为0，1两值
					N_Flag++;
					//					printf("N_FLAG:%d",N_Flag);
					delay_ms(1000);
				}
			}
		}
		//		LCD_ShowString(30,40,200,24,24,"Hello");
		//		LCD_ShowString(30,70,200,16,16,"Song Hao Nan tong xue");
		//		LCD_ShowString(30,90,200,16,16,"<~~>");
		//		LCD_ShowString(30,130,200,12,12,"2022/3/31");
		//		Chinese_Show_one(60, 75, 2, 16, 0);
		//		Chinese_Show_one(130, 145, 4, 16, 0);
		//		Chinese_Show_one(200, 215, 6, 16, 0);
		//		Chinese_Show_one(0, 15, 0, 16, 0);
		//		Chinese_Show_one(60, 75, 1, 16, 0);
		//		Chinese_Show_one(130, 145, 2, 16, 0);
		//		Chinese_Show_one(200, 215, 3, 16, 0);
		//		i++;
		//		LCD_ShowNum(40, 100, i, 5, 16);
		// LCD_hanqing(0x01, 0);
		// LCD_ShowString(10, 20, 40, 40, 8, (u8 *)"dddabcd");
		//		OLED_ShowString(1, 1, "Left:");
		//		OLED_ShowString(2, 1, "Right:");

		delay_ms(100);
	}
}
