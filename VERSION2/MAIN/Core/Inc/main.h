/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RELAY_GPIO_Pin GPIO_PIN_6
#define RELAY_GPIO_GPIO_Port GPIOI
#define HEAD_PE_Pin GPIO_PIN_5
#define HEAD_PE_GPIO_Port GPIOI
#define RIGHT_PE_Pin GPIO_PIN_4
#define RIGHT_PE_GPIO_Port GPIOI
#define RIGHT_PE_EXTI_IRQn EXTI4_IRQn
#define GRAY11_GPIO_Pin GPIO_PIN_5
#define GRAY11_GPIO_GPIO_Port GPIOD
#define GRAY10_GPIO_Pin GPIO_PIN_4
#define GRAY10_GPIO_GPIO_Port GPIOD
#define RLD_UART4_TX_Pin GPIO_PIN_10
#define RLD_UART4_TX_GPIO_Port GPIOC
#define GRAY12_GPIO_Pin GPIO_PIN_6
#define GRAY12_GPIO_GPIO_Port GPIOD
#define GRAY9_GPIO_Pin GPIO_PIN_3
#define GRAY9_GPIO_GPIO_Port GPIOD
#define RLD_UART4_RX_Pin GPIO_PIN_11
#define RLD_UART4_RX_GPIO_Port GPIOC
#define GRAY1_GPIO_Pin GPIO_PIN_3
#define GRAY1_GPIO_GPIO_Port GPIOB
#define GRAY13_GPIO_Pin GPIO_PIN_7
#define GRAY13_GPIO_GPIO_Port GPIOD
#define GYRO_UART5_TX_Pin GPIO_PIN_12
#define GYRO_UART5_TX_GPIO_Port GPIOC
#define LEFT_PE_Pin GPIO_PIN_3
#define LEFT_PE_GPIO_Port GPIOI
#define LEFT_PE_EXTI_IRQn EXTI3_IRQn
#define GYRO_UART5_RX_Pin GPIO_PIN_2
#define GYRO_UART5_RX_GPIO_Port GPIOD
#define BTH_USART1_RX_Pin GPIO_PIN_10
#define BTH_USART1_RX_GPIO_Port GPIOA
#define BTH_USART1_TX_Pin GPIO_PIN_9
#define BTH_USART1_TX_GPIO_Port GPIOA
#define MP3_VIRTUAL_UART_RX_Pin GPIO_PIN_9
#define MP3_VIRTUAL_UART_RX_GPIO_Port GPIOI
#define MP3_VIRTUAL_UART_TX_Pin GPIO_PIN_8
#define MP3_VIRTUAL_UART_TX_GPIO_Port GPIOI
#define GRAY4_GPIO_Pin GPIO_PIN_1
#define GRAY4_GPIO_GPIO_Port GPIOC
#define GRAY5_GPIO_Pin GPIO_PIN_2
#define GRAY5_GPIO_GPIO_Port GPIOC
#define GRAY6_GPIO_Pin GPIO_PIN_3
#define GRAY6_GPIO_GPIO_Port GPIOC
#define LLD_USART2_TX_Pin GPIO_PIN_2
#define LLD_USART2_TX_GPIO_Port GPIOA
#define MV_USART3_TX_Pin GPIO_PIN_10
#define MV_USART3_TX_GPIO_Port GPIOB
#define MV_USART3_RX_Pin GPIO_PIN_11
#define MV_USART3_RX_GPIO_Port GPIOB
#define PITCH_TIM_Pin GPIO_PIN_6
#define PITCH_TIM_GPIO_Port GPIOA
#define YAW_TIM_Pin GPIO_PIN_7
#define YAW_TIM_GPIO_Port GPIOA
#define GRAY0_GPIO_Pin GPIO_PIN_2
#define GRAY0_GPIO_GPIO_Port GPIOB
#define GRAY7_GPIO_Pin GPIO_PIN_4
#define GRAY7_GPIO_GPIO_Port GPIOC
#define GRAY3_GPIO_Pin GPIO_PIN_15
#define GRAY3_GPIO_GPIO_Port GPIOB
#define LLD_USART2_RX_Pin GPIO_PIN_3
#define LLD_USART2_RX_GPIO_Port GPIOA
#define GRAY8_GPIO_Pin GPIO_PIN_5
#define GRAY8_GPIO_GPIO_Port GPIOC
#define GRAY2_GPIO_Pin GPIO_PIN_14
#define GRAY2_GPIO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
