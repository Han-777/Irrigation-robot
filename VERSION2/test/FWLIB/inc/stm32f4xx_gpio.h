/**
  ******************************************************************************
  * @file    stm32f4xx_gpio.h
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   This file contains all the functions prototypes for the GPIO firmware
  *          library.  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_GPIO_H
#define __STM32F4xx_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "legacy.h"
#include "ll_includes.h"
#include "stm32f4xx_hal_conf.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

#define IS_GPIO_ALL_PERIPH(PERIPH) (((PERIPH) == GPIOA) || \
                                    ((PERIPH) == GPIOB) || \
                                    ((PERIPH) == GPIOC) || \
                                    ((PERIPH) == GPIOD) || \
                                    ((PERIPH) == GPIOE) || \
                                    ((PERIPH) == GPIOF) || \
                                    ((PERIPH) == GPIOG) || \
                                    ((PERIPH) == GPIOH) || \
                                    ((PERIPH) == GPIOI) || \
                                    ((PERIPH) == GPIOJ) || \
                                    ((PERIPH) == GPIOK))

/** 
  * @brief  GPIO Configuration Mode enumeration 
  */   
typedef enum
{ 
  LL_GPIO_MODE_INPUT   = 0x00, /*!< GPIO Input Mode */
  LL_GPIO_MODE_OUTPUT  = 0x01, /*!< GPIO Output Mode */
  LL_GPIO_MODE_ALTERNATE   = 0x02, /*!< GPIO Alternate function Mode */
  LL_GPIO_MODE_ANALOG   = 0x03  /*!< GPIO Analog Mode */
}GPIOMode_TypeDef;
#define IS_GPIO_MODE(MODE) (((MODE) == LL_GPIO_MODE_INPUT)  || ((MODE) == LL_GPIO_MODE_OUTPUT) || \
                            ((MODE) == LL_GPIO_MODE_ALTERNATE)|| ((MODE) == LL_GPIO_MODE_ANALOG))

/** 
  * @brief  GPIO Output type enumeration 
  */  
typedef enum
{ 
  LL_GPIO_OUTPUT_PUSHPULL = 0x00,
  LL_GPIO_OUTPUT_OPENDRAIN = 0x01
}GPIOOType_TypeDef;
#define IS_GPIO_OTYPE(OTYPE) (((OTYPE) == LL_GPIO_OUTPUT_PUSHPULL) || ((OTYPE) == LL_GPIO_OUTPUT_OPENDRAIN))


/** 
  * @brief  GPIO Output Maximum frequency enumeration 
  */  
typedef enum
{ 
  LL_GPIO_SPEED_FREQ_LOW     = 0x00, /*!< Low speed    */
  LL_GPIO_SPEED_FREQ_MEDIUM  = 0x01, /*!< Medium speed */
  LL_GPIO_SPEED_FREQ_HIGH    = 0x02, /*!< Fast speed   */
  LL_GPIO_SPEED_FREQ_VERY_HIGH    = 0x03  /*!< High speed   */
}GPIOSpeed_TypeDef;

/* Add legacy definition */
#define  LL_GPIO_SPEED_FREQ_LOW    LL_GPIO_SPEED_FREQ_LOW    
#define  LL_GPIO_SPEED_FREQ_MEDIUM   LL_GPIO_SPEED_FREQ_MEDIUM 
#define  LL_GPIO_SPEED_FREQ_HIGH   LL_GPIO_SPEED_FREQ_HIGH 
#define  LL_GPIO_SPEED_FREQ_VERY_HIGH  LL_GPIO_SPEED_FREQ_VERY_HIGH  
  
#define IS_GPIO_SPEED(SPEED) (((SPEED) == LL_GPIO_SPEED_FREQ_LOW) || ((SPEED) == LL_GPIO_SPEED_FREQ_MEDIUM) || \
                              ((SPEED) == LL_GPIO_SPEED_FREQ_HIGH)||  ((SPEED) == LL_GPIO_SPEED_FREQ_VERY_HIGH)) 

/** 
  * @brief  GPIO Configuration PullUp PullDown enumeration 
  */ 
typedef enum
{ 
  LL_GPIO_PULL_NO = 0x00,
  LL_GPIO_PULL_UP     = 0x01,
  LL_GPIO_PULL_DOWN   = 0x02
}GPIOPuPd_TypeDef;
#define IS_GPIO_PUPD(PUPD) (((PUPD) == LL_GPIO_PULL_NO) || ((PUPD) == LL_GPIO_PULL_UP) || \
                            ((PUPD) == LL_GPIO_PULL_DOWN))

/** 
  * @brief  GPIO Bit SET and Bit RESET enumeration 
  */ 
typedef enum
{ 
  0 = 0,
  1
}BitAction;
#define IS_GPIO_BIT_ACTION(ACTION) (((ACTION) == 0) || ((ACTION) == 1))


/** 
  * @brief   GPIO Init structure definition  
  */ 
typedef struct
{
  uint32_t GPIO_Pin;              /*!< Specifies the GPIO pins to be configured.
                                       This parameter can be any value of @ref GPIO_pins_define */

  GPIOMode_TypeDef GPIO_Mode;     /*!< Specifies the operating mode for the selected pins.
                                       This parameter can be a value of @ref GPIOMode_TypeDef */

  GPIOSpeed_TypeDef GPIO_Speed;   /*!< Specifies the speed for the selected pins.
                                       This parameter can be a value of @ref GPIOSpeed_TypeDef */

  GPIOOType_TypeDef GPIO_OType;   /*!< Specifies the operating output type for the selected pins.
                                       This parameter can be a value of @ref GPIOOType_TypeDef */

  GPIOPuPd_TypeDef GPIO_PuPd;     /*!< Specifies the operating Pull-up/Pull down for the selected pins.
                                       This parameter can be a value of @ref GPIOPuPd_TypeDef */
}LL_GPIO_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup GPIO_Exported_Constants
  * @{
  */ 

/** @defgroup GPIO_pins_define 
  * @{
  */ 
#define LL_GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected */
#define LL_GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected */
#define LL_GPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected */
#define LL_GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected */
#define LL_GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected */
#define LL_GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected */
#define LL_GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected */
#define LL_GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected */
#define LL_GPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected */
#define LL_GPIO_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected */
#define LL_GPIO_PIN_10                ((uint16_t)0x0400)  /* Pin 10 selected */
#define LL_GPIO_PIN_11                ((uint16_t)0x0800)  /* Pin 11 selected */
#define LL_GPIO_PIN_12                ((uint16_t)0x1000)  /* Pin 12 selected */
#define LL_GPIO_PIN_13                ((uint16_t)0x2000)  /* Pin 13 selected */
#define LL_GPIO_PIN_14                ((uint16_t)0x4000)  /* Pin 14 selected */
#define LL_GPIO_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected */
#define LL_GPIO_PIN_ALL               ((uint16_t)0xFFFF)  /* All pins selected */

#define 0x0000FFFF              ((uint32_t)0x0000FFFF) /* PIN mask for assert test */
#define IS_GPIO_PIN(PIN)           (((PIN) & 0x0000FFFF ) != (uint32_t)0x00)
#define IS_GET_GPIO_PIN(PIN) (((PIN) == LL_GPIO_PIN_0) || \
                              ((PIN) == LL_GPIO_PIN_1) || \
                              ((PIN) == LL_GPIO_PIN_2) || \
                              ((PIN) == LL_GPIO_PIN_3) || \
                              ((PIN) == LL_GPIO_PIN_4) || \
                              ((PIN) == LL_GPIO_PIN_5) || \
                              ((PIN) == LL_GPIO_PIN_6) || \
                              ((PIN) == LL_GPIO_PIN_7) || \
                              ((PIN) == LL_GPIO_PIN_8) || \
                              ((PIN) == LL_GPIO_PIN_9) || \
                              ((PIN) == LL_GPIO_PIN_10) || \
                              ((PIN) == LL_GPIO_PIN_11) || \
                              ((PIN) == LL_GPIO_PIN_12) || \
                              ((PIN) == LL_GPIO_PIN_13) || \
                              ((PIN) == LL_GPIO_PIN_14) || \
                              ((PIN) == LL_GPIO_PIN_15))
/**
  * @}
  */ 


/** @defgroup GPIO_Pin_sources 
  * @{
  */ 
#define LL_GPIO_PIN_0            ((uint8_t)0x00)
#define LL_GPIO_PIN_1            ((uint8_t)0x01)
#define LL_GPIO_PIN_2            ((uint8_t)0x02)
#define LL_GPIO_PIN_3            ((uint8_t)0x03)
#define LL_GPIO_PIN_4            ((uint8_t)0x04)
#define LL_GPIO_PIN_5            ((uint8_t)0x05)
#define LL_GPIO_PIN_6            ((uint8_t)0x06)
#define LL_GPIO_PIN_7            ((uint8_t)0x07)
#define LL_GPIO_PIN_8            ((uint8_t)0x08)
#define LL_GPIO_PIN_9            ((uint8_t)0x09)
#define LL_GPIO_PIN_10           ((uint8_t)0x0A)
#define LL_GPIO_PIN_11           ((uint8_t)0x0B)
#define LL_GPIO_PIN_12           ((uint8_t)0x0C)
#define LL_GPIO_PIN_13           ((uint8_t)0x0D)
#define LL_GPIO_PIN_14           ((uint8_t)0x0E)
#define LL_GPIO_PIN_15           ((uint8_t)0x0F)

#define IS_GPIO_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == LL_GPIO_PIN_0) || \
                                       ((PINSOURCE) == LL_GPIO_PIN_1) || \
                                       ((PINSOURCE) == LL_GPIO_PIN_2) || \
                                       ((PINSOURCE) == LL_GPIO_PIN_3) || \
                                       ((PINSOURCE) == LL_GPIO_PIN_4) || \
                                       ((PINSOURCE) == LL_GPIO_PIN_5) || \
                                       ((PINSOURCE) == LL_GPIO_PIN_6) || \
                                       ((PINSOURCE) == LL_GPIO_PIN_7) || \
                                       ((PINSOURCE) == LL_GPIO_PIN_8) || \
                                       ((PINSOURCE) == LL_GPIO_PIN_9) || \
                                       ((PINSOURCE) == LL_GPIO_PIN_10) || \
                                       ((PINSOURCE) == LL_GPIO_PIN_11) || \
                                       ((PINSOURCE) == LL_GPIO_PIN_12) || \
                                       ((PINSOURCE) == LL_GPIO_PIN_13) || \
                                       ((PINSOURCE) == LL_GPIO_PIN_14) || \
                                       ((PINSOURCE) == LL_GPIO_PIN_15))
/**
  * @}
  */ 

/** @defgroup GPIO_Alternat_function_selection_define 
  * @{
  */ 
/** 
  * @brief   AF 0 selection  
  */ 
#define LL_GPIO_AF_0      ((uint8_t)0x00)  /* RTC_50Hz Alternate Function mapping */
#define LL_GPIO_AF_0           ((uint8_t)0x00)  /* MCO (MCO1 and MCO2) Alternate Function mapping */
#define LL_GPIO_AF_0        ((uint8_t)0x00)  /* TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
#define LL_GPIO_AF_0           ((uint8_t)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping */
#define LL_GPIO_AF_0         ((uint8_t)0x00)  /* TRACE Alternate Function mapping */

/** 
  * @brief   AF 1 selection  
  */ 
#define LL_GPIO_AF_1          ((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define LL_GPIO_AF_1          ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */

/** 
  * @brief   AF 2 selection  
  */ 
#define LL_GPIO_AF_2          ((uint8_t)0x02)  /* TIM3 Alternate Function mapping */
#define LL_GPIO_AF_2          ((uint8_t)0x02)  /* TIM4 Alternate Function mapping */
#define LL_GPIO_AF_2          ((uint8_t)0x02)  /* TIM5 Alternate Function mapping */

/** 
  * @brief   AF 3 selection  
  */ 
#define LL_GPIO_AF_3          ((uint8_t)0x03)  /* TIM8 Alternate Function mapping */
#define LL_GPIO_AF_3          ((uint8_t)0x03)  /* TIM9 Alternate Function mapping */
#define LL_GPIO_AF_3         ((uint8_t)0x03)  /* TIM10 Alternate Function mapping */
#define LL_GPIO_AF_3         ((uint8_t)0x03)  /* TIM11 Alternate Function mapping */

/** 
  * @brief   AF 4 selection  
  */ 
#define LL_GPIO_AF_4          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping */
#define LL_GPIO_AF_4          ((uint8_t)0x04)  /* I2C2 Alternate Function mapping */
#define LL_GPIO_AF_4          ((uint8_t)0x04)  /* I2C3 Alternate Function mapping */

/** 
  * @brief   AF 5 selection  
  */ 
#define LL_GPIO_AF_5          ((uint8_t)0x05)  /* SPI1/I2S1 Alternate Function mapping */
#define LL_GPIO_AF_5          ((uint8_t)0x05)  /* SPI2/I2S2 Alternate Function mapping */
#define LL_GPIO_AF_5         ((uint8_t)0x05)  /* SPI3/I2S3 Alternate Function mapping (Only for STM32F411xE Devices) */
#define LL_GPIO_AF_5          ((uint8_t)0x05)  /* SPI4/I2S4 Alternate Function mapping */
#define LL_GPIO_AF_5          ((uint8_t)0x05)  /* SPI5 Alternate Function mapping      */
#define LL_GPIO_AF_5          ((uint8_t)0x05)  /* SPI6 Alternate Function mapping      */

/** 
  * @brief   AF 6 selection  
  */ 
#define LL_GPIO_AF_6          ((uint8_t)0x06)  /* SPI3/I2S3 Alternate Function mapping */
#define LL_GPIO_AF_6         ((uint8_t)0x06)  /* SPI2 Alternate Function mapping (Only for STM32F411xE Devices) */
#define LL_GPIO_AF_6         ((uint8_t)0x06)  /* SPI4 Alternate Function mapping (Only for STM32F411xE Devices) */
#define LL_GPIO_AF_6         ((uint8_t)0x06)  /* SPI5 Alternate Function mapping (Only for STM32F411xE Devices) */
#define LL_GPIO_AF_6          ((uint8_t)0x06)  /* SAI1 Alternate Function mapping      */

/** 
  * @brief   AF 7 selection  
  */ 
#define LL_GPIO_AF_7         ((uint8_t)0x07)  /* USART1 Alternate Function mapping  */
#define LL_GPIO_AF_7         ((uint8_t)0x07)  /* USART2 Alternate Function mapping  */
#define LL_GPIO_AF_7         ((uint8_t)0x07)  /* USART3 Alternate Function mapping  */
#define LL_GPIO_AF_7          ((uint8_t)0x07)  /* SPI3/I2S3ext Alternate Function mapping */

/** 
  * @brief   AF 7 selection Legacy 
  */ 
#define LL_GPIO_AF_7   LL_GPIO_AF_7

/** 
  * @brief   AF 8 selection  
  */ 
#define LL_GPIO_AF_8         ((uint8_t)0x08)  /* UART4 Alternate Function mapping  */
#define LL_GPIO_AF_8         ((uint8_t)0x08)  /* UART5 Alternate Function mapping  */
#define LL_GPIO_AF_8        ((uint8_t)0x08)  /* USART6 Alternate Function mapping */
#define LL_GPIO_AF_8         ((uint8_t)0x08)  /* UART7 Alternate Function mapping  */
#define LL_GPIO_AF_8         ((uint8_t)0x08)  /* UART8 Alternate Function mapping  */

/** 
  * @brief   AF 9 selection 
  */ 
#define LL_GPIO_AF_9          ((uint8_t)0x09)  /* CAN1 Alternate Function mapping  */
#define LL_GPIO_AF_9          ((uint8_t)0x09)  /* CAN2 Alternate Function mapping  */
#define LL_GPIO_AF_9         ((uint8_t)0x09)  /* TIM12 Alternate Function mapping */
#define LL_GPIO_AF_9         ((uint8_t)0x09)  /* TIM13 Alternate Function mapping */
#define LL_GPIO_AF_9         ((uint8_t)0x09)  /* TIM14 Alternate Function mapping */

#define LL_GPIO_AF_9         ((uint8_t)0x09)  /* I2C2 Alternate Function mapping (Only for STM32F401xx/STM32F411xE Devices) */
#define LL_GPIO_AF_9         ((uint8_t)0x09)  /* I2C3 Alternate Function mapping (Only for STM32F401xx/STM32F411xE Devices) */

/** 
  * @brief   AF 10 selection  
  */ 
#define LL_GPIO_AF_10         ((uint8_t)0xA)  /* OTG_FS Alternate Function mapping */
#define LL_GPIO_AF_10         ((uint8_t)0xA)  /* OTG_HS Alternate Function mapping */

/** 
  * @brief   AF 11 selection  
  */ 
#define LL_GPIO_AF_11             ((uint8_t)0x0B)  /* ETHERNET Alternate Function mapping */

/** 
  * @brief   AF 12 selection  
  */ 
#if defined (STM32F40_41xxx)
#define LL_GPIO_AF_12             ((uint8_t)0xC)  /* FSMC Alternate Function mapping                     */
#endif /* STM32F40_41xxx */

#if defined (STM32F427_437xx) || defined (STM32F429_439xx)
#define LL_GPIO_AF_12              ((uint8_t)0xC)  /* FMC Alternate Function mapping                      */
#endif /* STM32F427_437xx ||  STM32F429_439xx */

#define LL_GPIO_AF_12        ((uint8_t)0xC)  /* OTG HS configured in FS, Alternate Function mapping */
#define LL_GPIO_AF_12             ((uint8_t)0xC)  /* SDIO Alternate Function mapping                     */

/** 
  * @brief   AF 13 selection  
  */ 
#define LL_GPIO_AF_13          ((uint8_t)0x0D)  /* DCMI Alternate Function mapping */

/** 
  * @brief   AF 14 selection  
  */

#define LL_GPIO_AF_14          ((uint8_t)0x0E)  /* LCD-TFT Alternate Function mapping */

/** 
  * @brief   AF 15 selection  
  */ 
#define LL_GPIO_AF_15      ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */

#if defined (STM32F40_41xxx)
#define IS_GPIO_AF(AF)   (((AF) == LL_GPIO_AF_0)  || ((AF) == LL_GPIO_AF_9)     || \
                          ((AF) == LL_GPIO_AF_0)       || ((AF) == LL_GPIO_AF_0)    || \
                          ((AF) == LL_GPIO_AF_0)       || ((AF) == LL_GPIO_AF_0)     || \
                          ((AF) == LL_GPIO_AF_1)      || ((AF) == LL_GPIO_AF_1)      || \
                          ((AF) == LL_GPIO_AF_2)      || ((AF) == LL_GPIO_AF_2)      || \
                          ((AF) == LL_GPIO_AF_2)      || ((AF) == LL_GPIO_AF_3)      || \
                          ((AF) == LL_GPIO_AF_4)      || ((AF) == LL_GPIO_AF_4)      || \
                          ((AF) == LL_GPIO_AF_4)      || ((AF) == LL_GPIO_AF_5)      || \
                          ((AF) == LL_GPIO_AF_5)      || ((AF) == LL_GPIO_AF_9)     || \
                          ((AF) == LL_GPIO_AF_6)      || ((AF) == LL_GPIO_AF_9)     || \
                          ((AF) == LL_GPIO_AF_7)    || ((AF) == LL_GPIO_AF_7)    || \
                          ((AF) == LL_GPIO_AF_7)    || ((AF) == LL_GPIO_AF_8)     || \
                          ((AF) == LL_GPIO_AF_8)     || ((AF) == LL_GPIO_AF_8)    || \
                          ((AF) == LL_GPIO_AF_9)      || ((AF) == LL_GPIO_AF_9)      || \
                          ((AF) == LL_GPIO_AF_10)    || ((AF) == LL_GPIO_AF_10)    || \
                          ((AF) == LL_GPIO_AF_11)       || ((AF) == LL_GPIO_AF_12) || \
                          ((AF) == LL_GPIO_AF_12)      || ((AF) == LL_GPIO_AF_13)      || \
                          ((AF) == LL_GPIO_AF_15)  || ((AF) == LL_GPIO_AF_12))
#endif /* STM32F40_41xxx */

#if defined (STM32F401xx)
#define IS_GPIO_AF(AF)   (((AF) == LL_GPIO_AF_0)  || ((AF) == LL_GPIO_AF_9)     || \
                          ((AF) == LL_GPIO_AF_0)       || ((AF) == LL_GPIO_AF_0)    || \
                          ((AF) == LL_GPIO_AF_0)       || ((AF) == LL_GPIO_AF_0)     || \
                          ((AF) == LL_GPIO_AF_1)      || ((AF) == LL_GPIO_AF_1)      || \
                          ((AF) == LL_GPIO_AF_2)      || ((AF) == LL_GPIO_AF_2)      || \
                          ((AF) == LL_GPIO_AF_2)      || ((AF) == LL_GPIO_AF_3)      || \
                          ((AF) == LL_GPIO_AF_4)      || ((AF) == LL_GPIO_AF_4)      || \
                          ((AF) == LL_GPIO_AF_4)      || ((AF) == LL_GPIO_AF_5)      || \
                          ((AF) == LL_GPIO_AF_5)      || ((AF) == LL_GPIO_AF_9)     || \
                          ((AF) == LL_GPIO_AF_6)      || ((AF) == LL_GPIO_AF_9)     || \
                          ((AF) == LL_GPIO_AF_7)    || ((AF) == LL_GPIO_AF_7)    || \
                          ((AF) == LL_GPIO_AF_12)      || ((AF) == LL_GPIO_AF_8)    || \
                          ((AF) == LL_GPIO_AF_10)    || ((AF) == LL_GPIO_AF_10)    || \
                          ((AF) == LL_GPIO_AF_15)  || ((AF) == LL_GPIO_AF_5))
#endif /* STM32F401xx */

#if defined (STM32F411xE)
#define IS_GPIO_AF(AF)   (((AF) < 16) && ((AF) != 11) && ((AF) != 13) && ((AF) != 14))
#endif /* STM32F411xE */

#if defined (STM32F427_437xx) || defined (STM32F429_439xx)
#define IS_GPIO_AF(AF)   (((AF) == LL_GPIO_AF_0)  || ((AF) == LL_GPIO_AF_9)     || \
                          ((AF) == LL_GPIO_AF_0)       || ((AF) == LL_GPIO_AF_0)    || \
                          ((AF) == LL_GPIO_AF_0)       || ((AF) == LL_GPIO_AF_0)     || \
                          ((AF) == LL_GPIO_AF_1)      || ((AF) == LL_GPIO_AF_1)      || \
                          ((AF) == LL_GPIO_AF_2)      || ((AF) == LL_GPIO_AF_2)      || \
                          ((AF) == LL_GPIO_AF_2)      || ((AF) == LL_GPIO_AF_3)      || \
                          ((AF) == LL_GPIO_AF_4)      || ((AF) == LL_GPIO_AF_4)      || \
                          ((AF) == LL_GPIO_AF_4)      || ((AF) == LL_GPIO_AF_5)      || \
                          ((AF) == LL_GPIO_AF_5)      || ((AF) == LL_GPIO_AF_9)     || \
                          ((AF) == LL_GPIO_AF_6)      || ((AF) == LL_GPIO_AF_9)     || \
                          ((AF) == LL_GPIO_AF_7)    || ((AF) == LL_GPIO_AF_7)    || \
                          ((AF) == LL_GPIO_AF_7)    || ((AF) == LL_GPIO_AF_8)     || \
                          ((AF) == LL_GPIO_AF_8)     || ((AF) == LL_GPIO_AF_8)    || \
                          ((AF) == LL_GPIO_AF_9)      || ((AF) == LL_GPIO_AF_9)      || \
                          ((AF) == LL_GPIO_AF_10)    || ((AF) == LL_GPIO_AF_10)    || \
                          ((AF) == LL_GPIO_AF_11)       || ((AF) == LL_GPIO_AF_12) || \
                          ((AF) == LL_GPIO_AF_12)      || ((AF) == LL_GPIO_AF_13)      || \
                          ((AF) == LL_GPIO_AF_15)  || ((AF) == LL_GPIO_AF_5)      || \
                          ((AF) == LL_GPIO_AF_5)      || ((AF) == LL_GPIO_AF_5)      || \
                          ((AF) == LL_GPIO_AF_8)     || ((AF) == LL_GPIO_AF_8)     || \
                          ((AF) == LL_GPIO_AF_12)       ||  ((AF) == LL_GPIO_AF_6)     || \
                          ((AF) == LL_GPIO_AF_14))
#endif /* STM32F427_437xx ||  STM32F429_439xx */
                          
/**
  * @}
  */ 

/** @defgroup GPIO_Legacy 
  * @{
  */
    
#define LL_GPIO_MODE_ANALOG           LL_GPIO_MODE_ANALOG

#define LL_GPIO_AF_10         LL_GPIO_AF_10
#define LL_GPIO_AF_10         LL_GPIO_AF_10
#define LL_GPIO_AF_12         LL_GPIO_AF_12

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/*  Function used to set the GPIO configuration to the default reset state ****/
void LL_GPIO_DeInit(GPIO_TypeDef* GPIOx);

/* Initialization and Configuration functions *********************************/
GPIO_InitTypeDef* GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
void LL_GPIO_Init(GPIO_TypeDef* GPIOx, LL_GPIO_InitTypeDef* GPIO_InitStruct);
void LL_GPIO_StructInit(LL_GPIO_InitTypeDef* GPIO_InitStruct);
void LL_GPIO_LockPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/* GPIO Read and Write functions **********************************************/
uint8_t LL_GPIO_IsInputPinSet(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t LL_GPIO_ReadInputPort(GPIO_TypeDef* GPIOx);
uint8_t LL_GPIO_IsOutputPinSet(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t LL_GPIO_ReadOutputPort(GPIO_TypeDef* GPIOx);
void LL_GPIO_SetOutputPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void LL_GPIO_ResetOutputPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
void LL_GPIO_WriteOutputPort(GPIO_TypeDef* GPIOx, uint16_t PortVal);
void LL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/* GPIO Alternate functions configuration function ****************************/
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_GPIO_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
