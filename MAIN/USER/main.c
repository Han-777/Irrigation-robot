#include "sys.h"
#include "lcd.h"
#include "servo.h"
#include "chassis.h"

int main(void)
{
	delay_init(168);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); // 4抢占 0响应 (数字越小优先级越高！)
	LCD_Init();
	POINT_COLOR = BLUE; // 画笔颜色
	Motor_Init();
	Encoder_TIM_Init_All();
	TIM7_Int_Init(1000 - 1, 8400 - 1); // 84M / 8400 / 1000 = 0.1s = 100ms
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
	while (1)
	{
		Chinese_Show_one(10, 10, 0, 16, 0);
		Chinese_Show_one(64, 20, 1, 16, 0);

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
