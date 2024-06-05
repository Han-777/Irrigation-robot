#include "sys.h"
#include "motor.h"
#include "oled.h"
#include "encoder.h"
#include "servo.h"

int main(void)
{
	delay_init(168);
	OLED_Init();
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
	gray_GPIO_Init();
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
	while(1)
	{	
		OLED_ShowString(1, 1, "Left:");
		OLED_ShowString(2, 1, "Right:");
		delay_ms(100);
	}		
}	
