#ifndef	__CHASSIS_H__
#define __CHASSIS_H__

#include "sys.h"
#include "gray.h"
/**************************************************************************
	电机控制宏：一路PWM控制两电机，理论上左侧轮速相同，右侧轮速也相同
**************************************************************************/
//#define LIN1   PFout(6)  // Left 
//#define LIN2   PFout(7)  

//#define RIN1   PFout(5)  // Right
//#define RIN2   PDout(11)  

//#define PWML  TIM4->CCR2
//#define PWMR  TIM4->CCR1

//#define LIN1_GPIO_PIN       	GPIO_Pin_6 
//#define LIN2_GPIO_PIN   		GPIO_Pin_7
//#define LIN_GPIO_PORT  			GPIOF
//#define LIN_GPIO_CLK 			RCC_AHB1Periph_GPIOF

//#define RIN1_GPIO_PIN       	GPIO_Pin_5 // F5
//#define RIN2_GPIO_PIN   		GPIO_Pin_11 // D11 
//#define RIN1_GPIO_PORT  		GPIOF
//#define RIN2_GPIO_PORT  		GPIOD
//#define RIN_GPIO_CLK 			RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOF

///*---------------------- MOTOR_L_PWM------------------------*/

//#define MOTORL_PWM_PIN           						   GPIO_Pin_13         
//#define MOTORL_PWM_PORT          						   GPIOD               
//#define MOTORL_PWM_SOURCE        						   GPIO_PinSource13    
//#define MOTORL_PWM_PIN_CLK       						   RCC_AHB1Periph_GPIOD
//					 
//#define MOTORL_PWM_TIM           						   TIM4                
//#define MOTORL_PWM_AF            						   GPIO_AF_TIM4
//#define MOTORL_PWM_TIM_CLK       						   RCC_APB1Periph_TIM4	
//#define MOTORL_PWM_OC_INIT(initStructure)			 TIM_OC1Init(MOTORL_PWM_TIM, (TIM_OCInitTypeDef*)(initStructure))
//#define MOTORL_PWM_OC_PRELOAD_CFIG() 					 TIM_OC1PreloadConfig(MOTORL_PWM_TIM, TIM_OCPreload_Enable)

///*---------------------- MOTOR_R_PWM------------------------*/

//#define MOTORR_PWM_PIN       						       GPIO_Pin_12       	
//#define MOTORR_PWM_PORT      						       GPIOD                 
//#define MOTORR_PWM_SOURCE    						       GPIO_PinSource12         
//#define MOTORR_PWM_PIN_CLK   						       RCC_AHB1Periph_GPIOD	 

//#define MOTORR_PWM_TIM       						       TIM4                  
//#define MOTORR_PWM_AF        						       GPIO_AF_TIM4
//#define MOTORR_PWM_TIM_CLK   						       RCC_APB1Periph_TIM4	 
//#define MOTORR_PWM_OC_INIT(initStructure)			 TIM_OC2Init(MOTORR_PWM_TIM, (TIM_OCInitTypeDef*)(initStructure))
//#define MOTORR_PWM_OC_PRELOAD_CFIG() 					 TIM_OC2PreloadConfig(MOTORR_PWM_TIM, TIM_OCPreload_Enable)

///*---------------------- MOTOR_MOVE-----------------------*/
//#define MOTORL_COMPARE(pwm)                                	TIM_SetCompare2(TIM4, pwm)
//#define MOTORR_COMPARE(pwm)                                	TIM_SetCompare1(TIM4, pwm)
//void Motor_Init(void);

//void Limit(int PWM_Max,int PWM_Min,int* PWM_OUt_L,int* PWM_OUt_R);
//float Abs(float m);
//float Max(float m,float n);
//float Min(float m,float n);
//void Car_Load(int L,int R);
//void Car_stop(void);
//void Turn_Left_90_Angles(void);
//void Turn_Right_90_Angles(void);
//void Motor_Init(void);
//void Protect(void);


//void TIM4_PWM_Init(u32 arr,u32 psc);

#endif

