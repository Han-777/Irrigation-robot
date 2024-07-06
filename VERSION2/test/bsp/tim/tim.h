#ifndef _TIM_H
#define _TIM_H
#include "sys.h"

/**************************************************************************
							    TIM 7
**************************************************************************/
void TIM7_Init(u16 arr,u16 psc);
void TIM7_Close(void);

/**************************************************************************
							Motor PWM TIM (左右反了)
**************************************************************************/
// movement macro (两组函数作用相同)
#define PWML  TIM4->CCR1
#define PWMR  TIM4->CCR2
#define MOTORL_COMPARE(pwm)                     LL_TIM_OC_SetCompareCH1(TIM4, pwm)
#define MOTORR_COMPARE(pwm)                     LL_TIM_OC_SetCompareCH2(TIM4, pwm)

/*------------------- MOTOR_L_PWM---------------------*/

#define MOTORL_PWM_PIN           						   LL_GPIO_PIN_12         
#define MOTORL_PWM_PORT          						   GPIOD               
#define MOTORL_PWM_SOURCE        						   LL_GPIO_PIN_12    
#define MOTORL_PWM_PIN_CLK       						   LL_AHB1_GRP1_PERIPH_GPIOD
					 
#define MOTORL_PWM_TIM           						   TIM4                
#define MOTORL_PWM_AF            						   LL_GPIO_AF_2
#define MOTORL_PWM_TIM_CLK       						   LL_APB1_GRP1_PERIPH_TIM4	
#define MOTORL_PWM_OC_INIT(initStructure)			 LL_TIM_OC_Init(MOTORL_PWM_TIM, LL_TIM_CHANNEL_CH1, (LL_TIM_OC_InitTypeDef*)(initStructure))
#define MOTORL_PWM_OC_PRELOAD_CFIG() 					 LL_TIM_OC_EnablePreload(MOTORL_PWM_TIM, LL_TIM_CHANNEL_CH1)

/*------------------- MOTOR_R_PWM---------------------*/

#define MOTORR_PWM_PIN       						       LL_GPIO_PIN_13       	
#define MOTORR_PWM_PORT      						       GPIOD                 
#define MOTORR_PWM_SOURCE    						       LL_GPIO_PIN_13         
#define MOTORR_PWM_PIN_CLK   						       LL_AHB1_GRP1_PERIPH_GPIOD	 

#define MOTORR_PWM_TIM       						       TIM4                  
#define MOTORR_PWM_AF        						       LL_GPIO_AF_2
#define MOTORR_PWM_TIM_CLK   						       LL_APB1_GRP1_PERIPH_TIM4	 
#define MOTORR_PWM_OC_INIT(initStructure)			 LL_TIM_OC_Init(MOTORR_PWM_TIM, LL_TIM_CHANNEL_CH2, (LL_TIM_OC_InitTypeDef*)(initStructure))
#define MOTORR_PWM_OC_PRELOAD_CFIG() 					 LL_TIM_OC_EnablePreload(MOTORR_PWM_TIM, LL_TIM_CHANNEL_CH2)

void TIM4_PWM_Init(u32 arr, u32 psc);

/**************************************************************************
							Encoder PWM TIM
**************************************************************************/

/*=====================ENCODER1_LEFT=====================*/
// short = int16_t
#define ENCODER1_CNT                                  (short)TIM2->CNT
	
#define ENCODER1_PIN_1           					   LL_GPIO_PIN_1       		 // ENCODER1 ????  
#define ENCODER1_PORT_1          					   GPIOA                 // ENCODER1 GPIO??? 
#define ENCODER1_SOURCE_1        					   LL_GPIO_PIN_1      // ENCODER1 GPIO??? 	
#define ENCODER1_PIN_CLK      					   	   LL_AHB1_GRP1_PERIPH_GPIOA	 // ENCODER1 GPIO??????

#define ENCODER1_PIN_2          					   LL_GPIO_PIN_5       		 // ENCODER1 ????  
#define ENCODER1_PORT_2          					   GPIOA                 // ENCODER1 GPIO???  
#define ENCODER1_SOURCE_2        					   LL_GPIO_PIN_5       // ENCODER1 GPIO???  
//#define ENCODER1_PIN_CLK_2     					   RCC_AHB1Periph_GPIOA	 // ENCODER1 GPIO??????
						 
#define ENCODER1_TIM           						   TIM2                  // ENCODER1 GPIO???  
#define ENCODER1_AF            						   LL_GPIO_AF_1
#define ENCODER1_TIM_CLK       						   LL_APB1_GRP1_PERIPH_TIM2	 // ENCODER1 GPIO??????

//#define ENCODER1_NVIC_TIM           				   TIM2_IRQn	 // ENCODER1 GPIO??????

/*====================ENCODER2_RIGHT==============*/
#define ENCODER2_CNT                                  (short)TIM3->CNT
	
#define ENCODER2_PIN_1           					   LL_GPIO_PIN_6       		 // ENCODER2 ????  
#define ENCODER2_PORT_1          					   GPIOC                 // ENCODER2 GPIO??? 
#define ENCODER2_SOURCE_1        					   LL_GPIO_PIN_6      // ENCODER2 GPIO??? 
#define ENCODER2_PIN_CLK      					   	   LL_AHB1_GRP1_PERIPH_GPIOC	 // ENCODER2 GPIO??????

#define ENCODER2_PIN_2          					   LL_GPIO_PIN_7       		 // ENCODER2 ????  
#define ENCODER2_PORT_2          					   GPIOC                 // ENCODER2 GPIO???  
#define ENCODER2_SOURCE_2        					   LL_GPIO_PIN_7       // ENCODER2 GPIO???  
//#define ENCODER2_PIN_CLK_2     					   RCC_AHB1Periph_GPIOC	 // ENCODER2 GPIO??????
						 
#define ENCODER2_TIM           						   TIM3                  // ENCODER2 GPIO???  
#define ENCODER2_AF            						   LL_GPIO_AF_2
#define ENCODER2_TIM_CLK       						   LL_APB1_GRP1_PERIPH_TIM3	 // ENCODER2 GPIO??????

//#define ENCODER2_NVIC_TIM           				   TIM3_IRQn	 // ENCODER2 GPIO??????


/**************************************************************************
						    Servo TIM13 / TIM4
**************************************************************************/
void Servo_Pitch_PWM_Init(u32 arr,int psc);
void Servo_Yaw_PWM_Init(u32 arr, int psc);

#endif
