#include "stm32f10x.h" // Device header
#include "sys.h"
#include "balanceTank.h"
// /*=====================public========================*/
// extern float pitch,roll,yaw; 		//欧拉角
// extern short aacx,aacy,aacz;		  //加速度传感器原始数据
// extern short gyrox,gyroy,gyroz;	//陀螺仪原始数据
// extern float a;
u8 RxData;
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	delay_init();
	Control_Init();
	while (1)
	{

		//		mpu_get();
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
