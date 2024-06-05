#include "servo.h"

/**
 * @brief  initialize 4 servo and set to default position
 * 1: 2: 3: 4:
 * @param  
 * @param  
 * @retval None
 */
void servoInit()
{
	// 72M / arr(2000) / psc(720) = 50Hz -> 20ms 
	TIM3_Init(1999, 719); 
}
/**
 * @brief  4 servo control function
 * 1: 2: 3: 4:
 * @param  4 angel
 * @retval None
 */
void ServoControl(float angel1, float angel2, float angel3, float angel4)  // (in 500us - 2500us)
{
	// arr = 2000 ~ 20ms ==>> (0.5ms - 2.5ms)*100 = 50 - 250
	Servo1Control(angel1 / 180 * 200 + 50);
	Servo2Control(angel2 / 180 * 200 + 50);
	Servo3Control(angel3 / 180 * 200 + 50);
	Servo4Control(angel4 / 180 * 200 + 50);
}

/**
 * @brief  1 servo control function
 *
 * @param  1 angel
 * @retval None
 */
void Servo1Control(uint16_t Compare)
{
	TIM_SetCompare1(TIM3, Compare);
}

void Servo2Control(uint16_t Compare)
{
	TIM_SetCompare2(TIM3, Compare);
}

void Servo3Control(uint16_t Compare)
{
	TIM_SetCompare3(TIM3, Compare);
}

void Servo4Control(uint16_t Compare)
{
	TIM_SetCompare4(TIM3, Compare);
}

