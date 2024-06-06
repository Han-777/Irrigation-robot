#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "servo.h"
#include "balanceTank.h"
// #include "OLED.h"
//uint8_t KeyNum;
//float Angle;
//extern uint8_t res;


// /*=====================public========================*/
// extern float pitch,roll,yaw; 		//欧拉角
// extern short aacx,aacy,aacz;		  //加速度传感器原始数据
// extern short gyrox,gyroy,gyroz;	//陀螺仪原始数据
// extern float a;

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	delay_init();

	MPU_Init();		
	while(mpu_dmp_init());
	servoInit();

	
	TIM2_Init(4999, 719); // 72M / 200 / 720 = 500s = 2ms (used as timer)
	
	// OLED_ShowString(1, 1, "Angle1:");
	// OLED_ShowString(2, 1, "Angle2:");
	// OLED_ShowString(3, 1, "Angle3:");
	// OLED_ShowString(4, 1, "Angle4:");

//
	
	while (1)
	{


		// servo move
		// ServoControl(100, 100, 100, 100);
		// for (int i = 0; i < 180; ++i)
		// {
		// 	ServoControl(i, i, i, i);
		// 	OLED_ShowNum(1, 8, i, 3);
		// 	delay_ms(20);
		// }
		// for (int i = 180; i > 0; --i)
		// {
		// 	ServoControl(i, i, i, i);
		// 	OLED_ShowNum(1, 8, i, 3);
		// 	delay_ms(20);
		// }
//		if (mpu_get())
//		{
////			MPU_Display_Spect();
//		}

		
	}
}
