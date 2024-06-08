#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "servo.h"
#include "balanceTank.h"
#include "usart.h"
// /*=====================public========================*/
// extern float pitch,roll,yaw; 		//ŷ����
// extern short aacx,aacy,aacz;		  //���ٶȴ�����ԭʼ����
// extern short gyrox,gyroy,gyroz;	//������ԭʼ����
// extern float a;
u8 RxData;
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();
	MPU_Init();		
	while(mpu_dmp_init());
	servoInit();

	USART2_Init(9600);
	TIM2_Init(999, 719); // 72M / 1000 / 720 = 100Hz = 10ms (used as timer)
	
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
