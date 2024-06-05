#ifndef _TIM_H
#define _TIM_H
#include "sys.h"

/**************************************************************************
							    TIM 7
**************************************************************************/
void TIM7_Int_Init(u16 arr,u16 psc);
void TIM7_Close(void);

/**************************************************************************
							Motor PWM TIM
**************************************************************************/
// movement macro (两组函数作用相同)
#define PWML  TIM4->CCR1
#define PWMR  TIM4->CCR2
#define MOTORL_COMPARE(pwm)                     TIM_SetCompare1(TIM4, pwm)
#define MOTORR_COMPARE(pwm)                     TIM_SetCompare2(TIM4, pwm)

/*------------------- MOTOR_L_PWM---------------------*/

#define MOTORL_PWM_PIN           						   GPIO_Pin_12         
#define MOTORL_PWM_PORT          						   GPIOD               
#define MOTORL_PWM_SOURCE        						   GPIO_PinSource12    
#define MOTORL_PWM_PIN_CLK       						   RCC_AHB1Periph_GPIOD
					 
#define MOTORL_PWM_TIM           						   TIM4                
#define MOTORL_PWM_AF            						   GPIO_AF_TIM4
#define MOTORL_PWM_TIM_CLK       						   RCC_APB1Periph_TIM4	
#define MOTORL_PWM_OC_INIT(initStructure)			 TIM_OC1Init(MOTORL_PWM_TIM, (TIM_OCInitTypeDef*)(initStructure))
#define MOTORL_PWM_OC_PRELOAD_CFIG() 					 TIM_OC1PreloadConfig(MOTORL_PWM_TIM, TIM_OCPreload_Enable)

/*------------------- MOTOR_R_PWM---------------------*/

#define MOTORR_PWM_PIN       						       GPIO_Pin_13       	
#define MOTORR_PWM_PORT      						       GPIOD                 
#define MOTORR_PWM_SOURCE    						       GPIO_PinSource13         
#define MOTORR_PWM_PIN_CLK   						       RCC_AHB1Periph_GPIOD	 

#define MOTORR_PWM_TIM       						       TIM4                  
#define MOTORR_PWM_AF        						       GPIO_AF_TIM4
#define MOTORR_PWM_TIM_CLK   						       RCC_APB1Periph_TIM4	 
#define MOTORR_PWM_OC_INIT(initStructure)			 TIM_OC2Init(MOTORR_PWM_TIM, (TIM_OCInitTypeDef*)(initStructure))
#define MOTORR_PWM_OC_PRELOAD_CFIG() 					 TIM_OC2PreloadConfig(MOTORR_PWM_TIM, TIM_OCPreload_Enable)

void TIM4_PWM_Init(u32 arr, u32 psc);

/**************************************************************************
							Encoder PWM TIM
**************************************************************************/

/*=====================ENCODER1_LEFT=====================*/
// short = int16_t
#define ENCODER1_CNT                                  (short)TIM2->CNT
	
#define ENCODER1_PIN_1           					   GPIO_Pin_1       		 // ENCODER1 ????  
#define ENCODER1_PORT_1          					   GPIOA                 // ENCODER1 GPIO??? 
#define ENCODER1_SOURCE_1        					   GPIO_PinSource1      // ENCODER1 GPIO??? 	
#define ENCODER1_PIN_CLK      					   	   RCC_AHB1Periph_GPIOA	 // ENCODER1 GPIO??????

#define ENCODER1_PIN_2          					   GPIO_Pin_5       		 // ENCODER1 ????  
#define ENCODER1_PORT_2          					   GPIOA                 // ENCODER1 GPIO???  
#define ENCODER1_SOURCE_2        					   GPIO_PinSource5       // ENCODER1 GPIO???  
//#define ENCODER1_PIN_CLK_2     					   RCC_AHB1Periph_GPIOA	 // ENCODER1 GPIO??????
						 
#define ENCODER1_TIM           						   TIM2                  // ENCODER1 GPIO???  
#define ENCODER1_AF            						   GPIO_AF_TIM2
#define ENCODER1_TIM_CLK       						   RCC_APB1Periph_TIM2	 // ENCODER1 GPIO??????

//#define ENCODER1_NVIC_TIM           				   TIM2_IRQn	 // ENCODER1 GPIO??????

/*====================ENCODER2_RIGHT==============*/
#define ENCODER2_CNT                                  (short)TIM3->CNT
	
#define ENCODER2_PIN_1           					   GPIO_Pin_6       		 // ENCODER2 ????  
#define ENCODER2_PORT_1          					   GPIOC                 // ENCODER2 GPIO??? 
#define ENCODER2_SOURCE_1        					   GPIO_PinSource6      // ENCODER2 GPIO??? 
#define ENCODER2_PIN_CLK      					   	   RCC_AHB1Periph_GPIOC	 // ENCODER2 GPIO??????

#define ENCODER2_PIN_2          					   GPIO_Pin_7       		 // ENCODER2 ????  
#define ENCODER2_PORT_2          					   GPIOC                 // ENCODER2 GPIO???  
#define ENCODER2_SOURCE_2        					   GPIO_PinSource7       // ENCODER2 GPIO???  
//#define ENCODER2_PIN_CLK_2     					   RCC_AHB1Periph_GPIOC	 // ENCODER2 GPIO??????
						 
#define ENCODER2_TIM           						   TIM3                  // ENCODER2 GPIO???  
#define ENCODER2_AF            						   GPIO_AF_TIM3
#define ENCODER2_TIM_CLK       						   RCC_APB1Periph_TIM3	 // ENCODER2 GPIO??????

//#define ENCODER2_NVIC_TIM           				   TIM3_IRQn	 // ENCODER2 GPIO??????


/**************************************************************************
						    Servo TIM13 / TIM4
**************************************************************************/
void Servo_Pitch_PWM_Init(u32 arr,int psc);
void Servo_Yaw_PWM_Init(u32 arr, int psc);

#endif
