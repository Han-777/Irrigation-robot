#include "stm32f10x.h" // Device header
#include "sys.h"
#include "balanceTank.h"
// /*=====================public========================*/
// extern float pitch,roll,yaw; 		//ŷ����
// extern short aacx,aacy,aacz;		  //���ٶȴ�����ԭʼ����
// extern short gyrox,gyroy,gyroz;	//������ԭʼ����
// extern float a;
u8 RxData;
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // ����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
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
