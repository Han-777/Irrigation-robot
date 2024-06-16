#include "sys.h"
#include "lcd.h"
#include "servo.h"
#include "chassis.h"
#include "gyro.h"

int main(void)
{
	delay_init(168);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); // 4抢占 0响应 (数字越小优先级越高！)
													//	LCD_Init();
													//	POINT_COLOR = BLUE; // 画笔颜色
	delay_ms(100);

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
	chassis_Init();

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
		//		LCD_ShowNum(40, 40, Read_Yaw(), 5, 16);
		//		Chinese_Show_one(64, 20, 1, 16, 0);
		//		lcd_dis();

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
