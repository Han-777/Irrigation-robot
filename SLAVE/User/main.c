#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "key.h"
#include "sys.h"
#include "servo.h"

//uint8_t KeyNum;
//float Angle;
//extern uint8_t res;

int main(void)
{
	OLED_Init();
	servoInit();
	delay_init();
	// Servo_Init();
	// Key_Init();
	
	OLED_ShowString(1, 1, "Angle1:");
	OLED_ShowString(2, 1, "Angle2:");
	OLED_ShowString(3, 1, "Angle3:");
	OLED_ShowString(4, 1, "Angle4:");

//		for (int i = 0; i < 120; ++i)
//		{
//			ServoControl(i, i, i, i);
//			OLED_ShowNum(1, 8, i, 3);
//			delay_ms(20);
//		}
	while (1)
	{
		ServoControl(100, 100, 100, 100);
//		for (int i = 0; i < 180; ++i)
//		{
//			ServoControl(i, i, i, i);
//			OLED_ShowNum(1, 8, i, 3);
//			delay_ms(20);
//		}
//		for (int i = 180; i > 0; --i)
//		{
//			ServoControl(i, i, i, i);
//			OLED_ShowNum(1, 8, i, 3);
//			delay_ms(20);
//		}
		
	}
}
