/**
  ******************************************************************************
  * @file    stm32f4xx_rcc.h
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   This file contains all the functions prototypes for the RCC firmware library.  
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
#ifndef __STM32F4xx_RCC_H
#define __STM32F4xx_RCC_H

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

/** @addtogroup RCC
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint32_t SYSCLK_Frequency; /*!<  SYSCLK clock frequency expressed in Hz */
  uint32_t HCLK_Frequency;   /*!<  HCLK clock frequency expressed in Hz   */
  uint32_t PCLK1_Frequency;  /*!<  PCLK1 clock frequency expressed in Hz  */
  uint32_t PCLK2_Frequency;  /*!<  PCLK2 clock frequency expressed in Hz  */
}LL_RCC_ClocksTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup RCC_Exported_Constants
  * @{
  */
  
/** @defgroup RCC_HSE_configuration 
  * @{
  */
#define RCC_HSE_OFF                      ((uint8_t)0x00)
#define RCC_HSE_ON                       ((uint8_t)0x01)
#define RCC_HSE_Bypass                   ((uint8_t)0x05)
#define IS_RCC_HSE(HSE) (((HSE) == RCC_HSE_OFF) || ((HSE) == RCC_HSE_ON) || \
                         ((HSE) == RCC_HSE_Bypass))
/**
  * @}
  */ 

/** @defgroup RCC_LSE_Dual_Mode_Selection
  * @{
  */
#define RCC_LSE_LOWPOWER_MODE           ((uint8_t)0x00)
#define RCC_LSE_HIGHDRIVE_MODE          ((uint8_t)0x01)
#define IS_RCC_LSE_MODE(MODE)           (((MODE) == RCC_LSE_LOWPOWER_MODE) || \
                                         ((MODE) == RCC_LSE_HIGHDRIVE_MODE))
/**
  * @}
  */

/** @defgroup RCC_PLL_Clock_Source 
  * @{
  */
#define LL_RCC_PLLSOURCE_HSI                ((uint32_t)0x00000000)
#define LL_RCC_PLLSOURCE_HSE                ((uint32_t)0x00400000)
#define IS_RCC_PLL_SOURCE(SOURCE) (((SOURCE) == LL_RCC_PLLSOURCE_HSI) || \
                                   ((SOURCE) == LL_RCC_PLLSOURCE_HSE))
#define IS_RCC_PLLM_VALUE(VALUE) ((VALUE) <= 63)
#define IS_RCC_PLLN_VALUE(VALUE) ((192 <= (VALUE)) && ((VALUE) <= 432))
#define IS_RCC_PLLP_VALUE(VALUE) (((VALUE) == 2) || ((VALUE) == 4) || ((VALUE) == 6) || ((VALUE) == 8))
#define IS_RCC_PLLQ_VALUE(VALUE) ((4 <= (VALUE)) && ((VALUE) <= 15))
 
#define IS_RCC_PLLI2SN_VALUE(VALUE) ((192 <= (VALUE)) && ((VALUE) <= 432))
#define IS_RCC_PLLI2SR_VALUE(VALUE) ((2 <= (VALUE)) && ((VALUE) <= 7))  
#define IS_RCC_PLLI2SM_VALUE(VALUE) ((VALUE) <= 63)  

#define IS_RCC_PLLI2SQ_VALUE(VALUE) ((2 <= (VALUE)) && ((VALUE) <= 15))
#define IS_RCC_PLLSAIN_VALUE(VALUE) ((192 <= (VALUE)) && ((VALUE) <= 432))
#define IS_RCC_PLLSAIQ_VALUE(VALUE) ((2 <= (VALUE)) && ((VALUE) <= 15))
#define IS_RCC_PLLSAIR_VALUE(VALUE) ((2 <= (VALUE)) && ((VALUE) <= 7))  

#define IS_RCC_PLLSAI_DIVQ_VALUE(VALUE) ((1 <= (VALUE)) && ((VALUE) <= 32))
#define IS_RCC_PLLI2S_DIVQ_VALUE(VALUE) ((1 <= (VALUE)) && ((VALUE) <= 32))

#define LL_RCC_PLLSAIDIVR_DIV_2                ((uint32_t)0x00000000)
#define LL_RCC_PLLSAIDIVR_DIV_4                ((uint32_t)0x00010000)
#define LL_RCC_PLLSAIDIVR_DIV_8                ((uint32_t)0x00020000)
#define LL_RCC_PLLSAIDIVR_DIV_16               ((uint32_t)0x00030000)
#define IS_RCC_PLLSAI_DIVR_VALUE(VALUE) (((VALUE) == LL_RCC_PLLSAIDIVR_DIV_2) ||\
                                        ((VALUE) == LL_RCC_PLLSAIDIVR_DIV_4)  ||\
                                        ((VALUE) == LL_RCC_PLLSAIDIVR_DIV_8)  ||\
                                        ((VALUE) == LL_RCC_PLLSAIDIVR_DIV_16))
 
/**
  * @}
  */ 
  
/** @defgroup RCC_System_Clock_Source 
  * @{
  */
#define LL_RCC_SYS_CLKSOURCE_HSI             ((uint32_t)0x00000000)
#define LL_RCC_SYS_CLKSOURCE_HSE             ((uint32_t)0x00000001)
#define LL_RCC_SYS_CLKSOURCE_PLL          ((uint32_t)0x00000002)
#define IS_RCC_SYSCLK_SOURCE(SOURCE) (((SOURCE) == LL_RCC_SYS_CLKSOURCE_HSI) || \
                                      ((SOURCE) == LL_RCC_SYS_CLKSOURCE_HSE) || \
                                      ((SOURCE) == LL_RCC_SYS_CLKSOURCE_PLL))
/**
  * @}
  */ 
  
/** @defgroup RCC_AHB_Clock_Source
  * @{
  */
#define LL_RCC_SYSCLK_DIV_1                  ((uint32_t)0x00000000)
#define LL_RCC_SYSCLK_DIV_2                  ((uint32_t)0x00000080)
#define LL_RCC_SYSCLK_DIV_4                  ((uint32_t)0x00000090)
#define LL_RCC_SYSCLK_DIV_8                  ((uint32_t)0x000000A0)
#define LL_RCC_SYSCLK_DIV_16                 ((uint32_t)0x000000B0)
#define LL_RCC_SYSCLK_DIV_64                 ((uint32_t)0x000000C0)
#define LL_RCC_SYSCLK_DIV_128                ((uint32_t)0x000000D0)
#define LL_RCC_SYSCLK_DIV_256                ((uint32_t)0x000000E0)
#define LL_RCC_SYSCLK_DIV_512                ((uint32_t)0x000000F0)
#define IS_RCC_HCLK(HCLK) (((HCLK) == LL_RCC_SYSCLK_DIV_1) || ((HCLK) == LL_RCC_SYSCLK_DIV_2) || \
                           ((HCLK) == LL_RCC_SYSCLK_DIV_4) || ((HCLK) == LL_RCC_SYSCLK_DIV_8) || \
                           ((HCLK) == LL_RCC_SYSCLK_DIV_16) || ((HCLK) == LL_RCC_SYSCLK_DIV_64) || \
                           ((HCLK) == LL_RCC_SYSCLK_DIV_128) || ((HCLK) == LL_RCC_SYSCLK_DIV_256) || \
                           ((HCLK) == LL_RCC_SYSCLK_DIV_512))
/**
  * @}
  */ 
  
/** @defgroup RCC_APB1_APB2_Clock_Source
  * @{
  */
#define LL_RCC_APB1_DIV_1                    ((uint32_t)0x00000000)
#define LL_RCC_APB1_DIV_2                    ((uint32_t)0x00001000)
#define LL_RCC_APB1_DIV_4                    ((uint32_t)0x00001400)
#define LL_RCC_APB1_DIV_8                    ((uint32_t)0x00001800)
#define LL_RCC_APB1_DIV_16                   ((uint32_t)0x00001C00)
#define IS_RCC_PCLK(PCLK) (((PCLK) == LL_RCC_APB1_DIV_1) || ((PCLK) == LL_RCC_APB1_DIV_2) || \
                           ((PCLK) == LL_RCC_APB1_DIV_4) || ((PCLK) == LL_RCC_APB1_DIV_8) || \
                           ((PCLK) == LL_RCC_APB1_DIV_16))
/**
  * @}
  */ 
  
/** @defgroup RCC_Interrupt_Source 
  * @{
  */
#define LL_RCC_CIR_LSIRDYIE                    ((uint8_t)0x01)
#define LL_RCC_CIR_LSERDYIE                    ((uint8_t)0x02)
#define LL_RCC_CIR_HSIRDYIE                    ((uint8_t)0x04)
#define LL_RCC_CIR_HSERDYIE                    ((uint8_t)0x08)
#define LL_RCC_CIR_PLLRDYIE                    ((uint8_t)0x10)
#define LL_RCC_CIR_PLLI2SRDYIE                 ((uint8_t)0x20) 
#define LL_RCC_CIR_PLLSAIRDYIE                 ((uint8_t)0x40)
#define LL_RCC_CIR_CSSC                       ((uint8_t)0x80)

#define IS_RCC_IT(IT) ((((IT) & (uint8_t)0x80) == 0x00) && ((IT) != 0x00))
#define IS_RCC_GET_IT(IT) (((IT) == LL_RCC_CIR_LSIRDYIE) || ((IT) == LL_RCC_CIR_LSERDYIE) || \
                           ((IT) == LL_RCC_CIR_HSIRDYIE) || ((IT) == LL_RCC_CIR_HSERDYIE) || \
                           ((IT) == LL_RCC_CIR_PLLRDYIE) || ((IT) == LL_RCC_CIR_CSSC) || \
                           ((IT) == LL_RCC_CIR_PLLSAIRDYIE) || ((IT) == LL_RCC_CIR_PLLI2SRDYIE))
#define IS_RCC_CLEAR_IT(IT)((IT) != 0x00)

/**
  * @}
  */ 
  
/** @defgroup RCC_LSE_Configuration 
  * @{
  */
#define RCC_LSE_OFF                      ((uint8_t)0x00)
#define RCC_LSE_ON                       ((uint8_t)0x01)
#define RCC_LSE_Bypass                   ((uint8_t)0x04)
#define IS_RCC_LSE(LSE) (((LSE) == RCC_LSE_OFF) || ((LSE) == RCC_LSE_ON) || \
                         ((LSE) == RCC_LSE_Bypass))
/**
  * @}
  */ 
  
/** @defgroup RCC_RTC_Clock_Source
  * @{
  */
#define LL_RCC_RTC_CLKSOURCE_LSE             ((uint32_t)0x00000100)
#define RCC_RTCCLKSource_LSI             ((uint32_t)0x00000200)
#define LL_RCC_RTC_HSE_DIV_2        ((uint32_t)0x00020300)
#define LL_RCC_RTC_HSE_DIV_3        ((uint32_t)0x00030300)
#define LL_RCC_RTC_HSE_DIV_4        ((uint32_t)0x00040300)
#define LL_RCC_RTC_HSE_DIV_5        ((uint32_t)0x00050300)
#define LL_RCC_RTC_HSE_DIV_6        ((uint32_t)0x00060300)
#define LL_RCC_RTC_HSE_DIV_7        ((uint32_t)0x00070300)
#define LL_RCC_RTC_HSE_DIV_8        ((uint32_t)0x00080300)
#define LL_RCC_RTC_HSE_DIV_9        ((uint32_t)0x00090300)
#define LL_RCC_RTC_HSE_DIV_10       ((uint32_t)0x000A0300)
#define LL_RCC_RTC_HSE_DIV_11       ((uint32_t)0x000B0300)
#define LL_RCC_RTC_HSE_DIV_12       ((uint32_t)0x000C0300)
#define LL_RCC_RTC_HSE_DIV_13       ((uint32_t)0x000D0300)
#define LL_RCC_RTC_HSE_DIV_14       ((uint32_t)0x000E0300)
#define LL_RCC_RTC_HSE_DIV_15       ((uint32_t)0x000F0300)
#define LL_RCC_RTC_HSE_DIV_16       ((uint32_t)0x00100300)
#define LL_RCC_RTC_HSE_DIV_17       ((uint32_t)0x00110300)
#define LL_RCC_RTC_HSE_DIV_18       ((uint32_t)0x00120300)
#define LL_RCC_RTC_HSE_DIV_19       ((uint32_t)0x00130300)
#define LL_RCC_RTC_HSE_DIV_20       ((uint32_t)0x00140300)
#define LL_RCC_RTC_HSE_DIV_21       ((uint32_t)0x00150300)
#define LL_RCC_RTC_HSE_DIV_22       ((uint32_t)0x00160300)
#define LL_RCC_RTC_HSE_DIV_23       ((uint32_t)0x00170300)
#define LL_RCC_RTC_HSE_DIV_24       ((uint32_t)0x00180300)
#define LL_RCC_RTC_HSE_DIV_25       ((uint32_t)0x00190300)
#define LL_RCC_RTC_HSE_DIV_26       ((uint32_t)0x001A0300)
#define LL_RCC_RTC_HSE_DIV_27       ((uint32_t)0x001B0300)
#define LL_RCC_RTC_HSE_DIV_28       ((uint32_t)0x001C0300)
#define LL_RCC_RTC_HSE_DIV_29       ((uint32_t)0x001D0300)
#define LL_RCC_RTC_HSE_DIV_30       ((uint32_t)0x001E0300)
#define LL_RCC_RTC_HSE_DIV_31       ((uint32_t)0x001F0300)
#define IS_RCC_RTCCLK_SOURCE(SOURCE) (((SOURCE) == LL_RCC_RTC_CLKSOURCE_LSE) || \
                                      ((SOURCE) == RCC_RTCCLKSource_LSI) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_2) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_3) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_4) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_5) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_6) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_7) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_8) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_9) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_10) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_11) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_12) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_13) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_14) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_15) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_16) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_17) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_18) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_19) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_20) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_21) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_22) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_23) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_24) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_25) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_26) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_27) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_28) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_29) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_30) || \
                                      ((SOURCE) == LL_RCC_RTC_HSE_DIV_31))
/**
  * @}
  */ 
  
/** @defgroup RCC_I2S_Clock_Source
  * @{
  */
#define LL_RCC_I2S1_CLKSOURCE_PLLI2S             ((uint8_t)0x00)
#define LL_RCC_I2S1_CLKSOURCE_PIN                ((uint8_t)0x01)

#define IS_RCC_I2SCLK_SOURCE(SOURCE) (((SOURCE) == LL_RCC_I2S1_CLKSOURCE_PLLI2S) || ((SOURCE) == LL_RCC_I2S1_CLKSOURCE_PIN))                                
/**
  * @}
  */ 

/** @defgroup RCC_SAI_BlockA_Clock_Source
  * @{
  */
#define LL_RCC_SAI1_B_CLKSOURCE_PLLSAI             ((uint32_t)0x00000000)
#define LL_RCC_SAI1_A_CLKSOURCE_PLLI2S             ((uint32_t)0x00100000)
#define LL_RCC_SAI1_A_CLKSOURCE_PIN                ((uint32_t)0x00200000)

#define IS_RCC_SAIACLK_SOURCE(SOURCE) (((SOURCE) == LL_RCC_SAI1_A_CLKSOURCE_PLLI2S) ||\
                                       ((SOURCE) == LL_RCC_SAI1_B_CLKSOURCE_PLLSAI) ||\
                                       ((SOURCE) == LL_RCC_SAI1_A_CLKSOURCE_PIN))
/**
  * @}
  */ 

/** @defgroup RCC_SAI_BlockB_Clock_Source
  * @{
  */
#define LL_RCC_SAI1_B_CLKSOURCE_PLLSAI             ((uint32_t)0x00000000)
#define LL_RCC_SAI1_B_CLKSOURCE_PLLI2S             ((uint32_t)0x00400000)
#define LL_RCC_SAI1_B_CLKSOURCE_PIN                ((uint32_t)0x00800000)

#define IS_RCC_SAIBCLK_SOURCE(SOURCE) (((SOURCE) == LL_RCC_SAI1_B_CLKSOURCE_PLLI2S) ||\
                                       ((SOURCE) == LL_RCC_SAI1_B_CLKSOURCE_PLLSAI) ||\
                                       ((SOURCE) == LL_RCC_SAI1_B_CLKSOURCE_PIN))
/**
  * @}
  */ 

/** @defgroup RCC_TIM_PRescaler_Selection
  * @{
  */
#define LL_RCC_TIM_PRESCALER_TWICE             ((uint8_t)0x00)
#define LL_RCC_TIM_PRESCALER_FOUR_TIMES                ((uint8_t)0x01)

#define IS_RCC_TIMCLK_PRESCALER(VALUE) (((VALUE) == LL_RCC_TIM_PRESCALER_TWICE) || ((VALUE) == LL_RCC_TIM_PRESCALER_FOUR_TIMES))
/**
  * @}
  */
  
/** @defgroup RCC_AHB1_Peripherals 
  * @{
  */ 
#define LL_AHB1_GRP1_PERIPH_GPIOA             ((uint32_t)0x00000001)
#define LL_AHB1_GRP1_PERIPH_GPIOB             ((uint32_t)0x00000002)
#define LL_AHB1_GRP1_PERIPH_GPIOC             ((uint32_t)0x00000004)
#define LL_AHB1_GRP1_PERIPH_GPIOD             ((uint32_t)0x00000008)
#define LL_AHB1_GRP1_PERIPH_GPIOE             ((uint32_t)0x00000010)
#define LL_AHB1_GRP1_PERIPH_GPIOF             ((uint32_t)0x00000020)
#define LL_AHB1_GRP1_PERIPH_GPIOG             ((uint32_t)0x00000040)
#define LL_AHB1_GRP1_PERIPH_GPIOH             ((uint32_t)0x00000080)
#define LL_AHB1_GRP1_PERIPH_GPIOI             ((uint32_t)0x00000100) 
#define LL_AHB1_GRP1_PERIPH_GPIOJ             ((uint32_t)0x00000200)
#define LL_AHB1_GRP1_PERIPH_GPIOK             ((uint32_t)0x00000400)
#define LL_AHB1_GRP1_PERIPH_CRC               ((uint32_t)0x00001000)
#define LL_AHB1_GRP1_PERIPH_FLITF             ((uint32_t)0x00008000)
#define LL_AHB1_GRP1_PERIPH_SRAM1             ((uint32_t)0x00010000)
#define LL_AHB1_GRP1_PERIPH_SRAM2             ((uint32_t)0x00020000)
#define LL_AHB1_GRP1_PERIPH_BKPSRAM           ((uint32_t)0x00040000)
#define LL_AHB1_GRP1_PERIPH_SRAM3             ((uint32_t)0x00080000)
#define LL_AHB1_GRP1_PERIPH_CCMDATARAM      ((uint32_t)0x00100000)
#define LL_AHB1_GRP1_PERIPH_DMA1              ((uint32_t)0x00200000)
#define LL_AHB1_GRP1_PERIPH_DMA2              ((uint32_t)0x00400000)
#define LL_AHB1_GRP1_PERIPH_DMA2D             ((uint32_t)0x00800000)
#define LL_AHB1_GRP1_PERIPH_ETHMAC           ((uint32_t)0x02000000)
#define LL_AHB1_GRP1_PERIPH_ETHMACTX        ((uint32_t)0x04000000)
#define LL_AHB1_GRP1_PERIPH_ETHMACRX        ((uint32_t)0x08000000)
#define LL_AHB1_GRP1_PERIPH_ETHMACPTP       ((uint32_t)0x10000000)
#define LL_AHB1_GRP1_PERIPH_OTGHS            ((uint32_t)0x20000000)
#define LL_AHB1_GRP1_PERIPH_OTGHSULPI       ((uint32_t)0x40000000)

#define IS_RCC_AHB1_CLOCK_PERIPH(PERIPH) ((((PERIPH) & 0x810BE800) == 0x00) && ((PERIPH) != 0x00))
#define IS_RCC_AHB1_RESET_PERIPH(PERIPH) ((((PERIPH) & 0xDD1FE800) == 0x00) && ((PERIPH) != 0x00))
#define IS_RCC_AHB1_LPMODE_PERIPH(PERIPH) ((((PERIPH) & 0x81106800) == 0x00) && ((PERIPH) != 0x00))

/**
  * @}
  */ 
  
/** @defgroup RCC_AHB2_Peripherals 
  * @{
  */  
#define LL_AHB2_GRP1_PERIPH_DCMI              ((uint32_t)0x00000001)
#define LL_AHB2_GRP1_PERIPH_CRYP              ((uint32_t)0x00000010)
#define LL_AHB2_GRP1_PERIPH_HASH              ((uint32_t)0x00000020)
#define LL_AHB2_GRP1_PERIPH_RNG               ((uint32_t)0x00000040)
#define LL_AHB2_GRP1_PERIPH_OTGFS            ((uint32_t)0x00000080)
#define IS_RCC_AHB2_PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFF0E) == 0x00) && ((PERIPH) != 0x00))
/**
  * @}
  */ 
  
/** @defgroup RCC_AHB3_Peripherals 
  * @{
  */ 
#if defined (STM32F40_41xxx)
#define LL_AHB3_GRP1_PERIPH_FSMC                ((uint32_t)0x00000001)
#endif /* STM32F40_41xxx */

#if defined (STM32F427_437xx) || defined (STM32F429_439xx) 
#define LL_AHB3_GRP1_PERIPH_FMC                ((uint32_t)0x00000001)
#endif /* STM32F427_437xx ||  STM32F429_439xx */

#define IS_RCC_AHB3_PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFFFE) == 0x00) && ((PERIPH) != 0x00))
/**
  * @}
  */ 
  
/** @defgroup RCC_APB1_Peripherals 
  * @{
  */ 
#define LL_APB1_GRP1_PERIPH_TIM2              ((uint32_t)0x00000001)
#define LL_APB1_GRP1_PERIPH_TIM3              ((uint32_t)0x00000002)
#define LL_APB1_GRP1_PERIPH_TIM4              ((uint32_t)0x00000004)
#define LL_APB1_GRP1_PERIPH_TIM5              ((uint32_t)0x00000008)
#define LL_APB1_GRP1_PERIPH_TIM6              ((uint32_t)0x00000010)
#define LL_APB1_GRP1_PERIPH_TIM7              ((uint32_t)0x00000020)
#define LL_APB1_GRP1_PERIPH_TIM12             ((uint32_t)0x00000040)
#define LL_APB1_GRP1_PERIPH_TIM13             ((uint32_t)0x00000080)
#define LL_APB1_GRP1_PERIPH_TIM14             ((uint32_t)0x00000100)
#define LL_APB1_GRP1_PERIPH_WWDG              ((uint32_t)0x00000800)
#define LL_APB1_GRP1_PERIPH_SPI2              ((uint32_t)0x00004000)
#define LL_APB1_GRP1_PERIPH_SPI3              ((uint32_t)0x00008000)
#define LL_APB1_GRP1_PERIPH_USART2            ((uint32_t)0x00020000)
#define LL_APB1_GRP1_PERIPH_USART3            ((uint32_t)0x00040000)
#define LL_APB1_GRP1_PERIPH_UART4             ((uint32_t)0x00080000)
#define LL_APB1_GRP1_PERIPH_UART5             ((uint32_t)0x00100000)
#define LL_APB1_GRP1_PERIPH_I2C1              ((uint32_t)0x00200000)
#define LL_APB1_GRP1_PERIPH_I2C2              ((uint32_t)0x00400000)
#define LL_APB1_GRP1_PERIPH_I2C3              ((uint32_t)0x00800000)
#define LL_APB1_GRP1_PERIPH_CAN1              ((uint32_t)0x02000000)
#define LL_APB1_GRP1_PERIPH_CAN2              ((uint32_t)0x04000000)
#define LL_APB1_GRP1_PERIPH_PWR               ((uint32_t)0x10000000)
#define LL_APB1_GRP1_PERIPH_DAC1               ((uint32_t)0x20000000)
#define LL_APB1_GRP1_PERIPH_UART7             ((uint32_t)0x40000000)
#define LL_APB1_GRP1_PERIPH_UART8             ((uint32_t)0x80000000)
#define IS_RCC_APB1_PERIPH(PERIPH) ((((PERIPH) & 0x09013600) == 0x00) && ((PERIPH) != 0x00))
/**
  * @}
  */ 
  
/** @defgroup RCC_APB2_Peripherals 
  * @{
  */ 
#define LL_APB2_GRP1_PERIPH_TIM1              ((uint32_t)0x00000001)
#define LL_APB2_GRP1_PERIPH_TIM8              ((uint32_t)0x00000002)
#define LL_APB2_GRP1_PERIPH_USART1            ((uint32_t)0x00000010)
#define LL_APB2_GRP1_PERIPH_USART6            ((uint32_t)0x00000020)
#define LL_APB2_GRP1_PERIPH_ADC1               ((uint32_t)0x00000100)
#define LL_APB2_GRP1_PERIPH_ADC1              ((uint32_t)0x00000100)
#define LL_APB2_GRP1_PERIPH_ADC2              ((uint32_t)0x00000200)
#define LL_APB2_GRP1_PERIPH_ADC3              ((uint32_t)0x00000400)
#define LL_APB2_GRP1_PERIPH_SDIO              ((uint32_t)0x00000800)
#define LL_APB2_GRP1_PERIPH_SPI1              ((uint32_t)0x00001000)
#define LL_APB2_GRP1_PERIPH_SPI4              ((uint32_t)0x00002000)
#define LL_APB2_GRP1_PERIPH_SYSCFG            ((uint32_t)0x00004000)
#define LL_APB2_GRP1_PERIPH_TIM9              ((uint32_t)0x00010000)
#define LL_APB2_GRP1_PERIPH_TIM10             ((uint32_t)0x00020000)
#define LL_APB2_GRP1_PERIPH_TIM11             ((uint32_t)0x00040000)
#define LL_APB2_GRP1_PERIPH_SPI5              ((uint32_t)0x00100000)
#define LL_APB2_GRP1_PERIPH_SPI6              ((uint32_t)0x00200000)
#define LL_APB2_GRP1_PERIPH_SAI1              ((uint32_t)0x00400000)
#define LL_APB2_GRP1_PERIPH_LTDC              ((uint32_t)0x04000000)

#define IS_RCC_APB2_PERIPH(PERIPH) ((((PERIPH) & 0xFB8880CC) == 0x00) && ((PERIPH) != 0x00))
#define IS_RCC_APB2_RESET_PERIPH(PERIPH) ((((PERIPH) & 0xFB8886CC) == 0x00) && ((PERIPH) != 0x00))

/**
  * @}
  */ 
  
/** @defgroup RCC_MCO1_Clock_Source_Prescaler
  * @{
  */
#define LL_RCC_MCO1SOURCE_HSI               ((uint32_t)0x00000000)
#define LL_RCC_MCO1SOURCE_LSE               ((uint32_t)0x00200000)
#define LL_RCC_MCO1SOURCE_HSE               ((uint32_t)0x00400000)
#define LL_RCC_MCO1SOURCE_PLLCLK            ((uint32_t)0x00600000)
#define LL_RCC_MCO1_DIV_1                    ((uint32_t)0x00000000)
#define LL_RCC_MCO1_DIV_2                    ((uint32_t)0x04000000)
#define LL_RCC_MCO1_DIV_3                    ((uint32_t)0x05000000)
#define LL_RCC_MCO1_DIV_4                    ((uint32_t)0x06000000)
#define LL_RCC_MCO1_DIV_5                    ((uint32_t)0x07000000)
#define IS_RCC_MCO1SOURCE(SOURCE) (((SOURCE) == LL_RCC_MCO1SOURCE_HSI) || ((SOURCE) == LL_RCC_MCO1SOURCE_LSE) || \
                                   ((SOURCE) == LL_RCC_MCO1SOURCE_HSE) || ((SOURCE) == LL_RCC_MCO1SOURCE_PLLCLK))
                                   
#define IS_RCC_MCO1DIV(DIV) (((DIV) == LL_RCC_MCO1_DIV_1) || ((DIV) == LL_RCC_MCO1_DIV_2) || \
                             ((DIV) == LL_RCC_MCO1_DIV_3) || ((DIV) == LL_RCC_MCO1_DIV_4) || \
                             ((DIV) == LL_RCC_MCO1_DIV_5)) 
/**
  * @}
  */ 
  
/** @defgroup RCC_MCO2_Clock_Source_Prescaler
  * @{
  */
#define LL_RCC_MCO2SOURCE_SYSCLK            ((uint32_t)0x00000000)
#define LL_RCC_MCO2SOURCE_PLLI2S         ((uint32_t)0x40000000)
#define LL_RCC_MCO2SOURCE_HSE               ((uint32_t)0x80000000)
#define LL_RCC_MCO2SOURCE_PLLCLK            ((uint32_t)0xC0000000)
#define LL_RCC_MCO2_DIV_1                    ((uint32_t)0x00000000)
#define LL_RCC_MCO2_DIV_2                    ((uint32_t)0x20000000)
#define LL_RCC_MCO2_DIV_3                    ((uint32_t)0x28000000)
#define LL_RCC_MCO2_DIV_4                    ((uint32_t)0x30000000)
#define LL_RCC_MCO2_DIV_5                    ((uint32_t)0x38000000)
#define IS_RCC_MCO2SOURCE(SOURCE) (((SOURCE) == LL_RCC_MCO2SOURCE_SYSCLK) || ((SOURCE) == LL_RCC_MCO2SOURCE_PLLI2S)|| \
                                   ((SOURCE) == LL_RCC_MCO2SOURCE_HSE) || ((SOURCE) == LL_RCC_MCO2SOURCE_PLLCLK))
                                   
#define IS_RCC_MCO2DIV(DIV) (((DIV) == LL_RCC_MCO2_DIV_1) || ((DIV) == LL_RCC_MCO2_DIV_2) || \
                             ((DIV) == LL_RCC_MCO2_DIV_3) || ((DIV) == LL_RCC_MCO2_DIV_4) || \
                             ((DIV) == LL_RCC_MCO2_DIV_5))                             
/**
  * @}
  */ 
  
/** @defgroup RCC_Flag 
  * @{
  */
#define RCC_FLAG_HSIRDY                  ((uint8_t)0x21)
#define RCC_FLAG_HSERDY                  ((uint8_t)0x31)
#define RCC_FLAG_PLLRDY                  ((uint8_t)0x39)
#define RCC_FLAG_PLLI2SRDY               ((uint8_t)0x3B)
#define RCC_FLAG_PLLSAIRDY               ((uint8_t)0x3D)
#define RCC_FLAG_LSERDY                  ((uint8_t)0x41)
#define RCC_FLAG_LSIRDY                  ((uint8_t)0x61)
#define RCC_FLAG_BORRST                  ((uint8_t)0x79)
#define RCC_FLAG_PINRST                  ((uint8_t)0x7A)
#define RCC_FLAG_PORRST                  ((uint8_t)0x7B)
#define RCC_FLAG_SFTRST                  ((uint8_t)0x7C)
#define RCC_FLAG_IWDGRST                 ((uint8_t)0x7D)
#define RCC_FLAG_WWDGRST                 ((uint8_t)0x7E)
#define RCC_FLAG_LPWRRST                 ((uint8_t)0x7F)

#define IS_RCC_FLAG(FLAG) (((FLAG) == RCC_FLAG_HSIRDY)   || ((FLAG) == RCC_FLAG_HSERDY) || \
                           ((FLAG) == RCC_FLAG_PLLRDY)   || ((FLAG) == RCC_FLAG_LSERDY) || \
                           ((FLAG) == RCC_FLAG_LSIRDY)   || ((FLAG) == RCC_FLAG_BORRST) || \
                           ((FLAG) == RCC_FLAG_PINRST)   || ((FLAG) == RCC_FLAG_PORRST) || \
                           ((FLAG) == RCC_FLAG_SFTRST)   || ((FLAG) == RCC_FLAG_IWDGRST)|| \
                           ((FLAG) == RCC_FLAG_WWDGRST)  || ((FLAG) == RCC_FLAG_LPWRRST)|| \
                           ((FLAG) == RCC_FLAG_PLLI2SRDY)|| ((FLAG) == RCC_FLAG_PLLSAIRDY))

#define IS_RCC_CALIBRATION_VALUE(VALUE) ((VALUE) <= 0x1F)
/**
  * @}
  */ 

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 

/* Function used to set the RCC clock configuration to the default reset state */
void LL_RCC_DeInit();

/* Internal/external clocks, PLL, CSS and MCO configuration functions *********/
void        RCC_HSEConfig(uint8_t RCC_HSE);
ErrorStatus RCC_WaitForHSEStartUp();
void        LL_RCC_HSI_SetCalibTrimming(uint8_t HSICalibrationValue);
void        RCC_HSICmd(FunctionalState NewState);
void        RCC_LSEConfig(uint8_t RCC_LSE);
void        RCC_LSICmd(FunctionalState NewState);
void        MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLP | RCC_PLLCFGR_PLLQ | RCC_PLLCFGR_PLLR,  | uint32_t PLLM << RCC_PLLCFGR_PLLM_Pos | uint32_t PLLN << RCC_PLLCFGR_PLLN_Pos | uint32_t PLLP << RCC_PLLCFGR_PLLP_Pos | uint32_t PLLQ << RCC_PLLCFGR_PLLQ_Pos| {CPY@SPL_PARAM_5} << RCC_PLLCFGR_PLLR_Pos);
void        RCC_PLLCmd(FunctionalState NewState);

#if defined (STM32F40_41xxx) || defined (STM32F401xx)
void        MODIFY_REG(RCC->PLLI2SCFGR, RCC_PLLI2SCFGR_PLLI2SN | RCC_PLLI2SCFGR_PLLI2SQ | RCC_PLLI2SCFGR_PLLI2SR, uint32_t PLLI2SN << RCC_PLLI2SCFGR_PLLI2SN_Pos | uint32_t PLLI2SR << RCC_PLLI2SCFGR_PLLI2SQ_Pos| {CPY@SPL_PARAM_2} << RCC_PLLI2SCFGR_PLLI2SR_Pos);
#elif defined (STM32F411xE)
void        MODIFY_REG(RCC->PLLI2SCFGR, RCC_PLLI2SCFGR_PLLI2SN | RCC_PLLI2SCFGR_PLLI2SQ | RCC_PLLI2SCFGR_PLLI2SR, uint32_t PLLI2SN << RCC_PLLI2SCFGR_PLLI2SN_Pos | uint32_t PLLI2SR << RCC_PLLI2SCFGR_PLLI2SQ_Pos| uint32_t PLLI2SM << RCC_PLLI2SCFGR_PLLI2SR_Pos);
#elif defined (STM32F427_437xx) || defined (STM32F429_439xx)
void        MODIFY_REG(RCC->PLLI2SCFGR, RCC_PLLI2SCFGR_PLLI2SN | RCC_PLLI2SCFGR_PLLI2SQ | RCC_PLLI2SCFGR_PLLI2SR, uint32_t PLLI2SN << RCC_PLLI2SCFGR_PLLI2SN_Pos | uint32_t PLLI2SQ << RCC_PLLI2SCFGR_PLLI2SQ_Pos| uint32_t PLLI2SR << RCC_PLLI2SCFGR_PLLI2SR_Pos);
#else
#endif /* STM32F40_41xxx || STM32F401xx */

void        RCC_PLLI2SCmd(FunctionalState NewState);
void        MODIFY_REG(RCC->PLLSAICFGR, RCC_PLLSAICFGR_PLLSAIN | RCC_PLLSAICFGR_PLLSAIP | RCC_PLLSAICFGR_PLLSAIQ | RCC_PLLSAICFGR_PLLSAIR, uint32_t PLLSAIN << RCC_PLLSAICFGR_PLLSAIN_Pos | uint32_t PLLSAIQ << RCC_PLLSAICFGR_PLLSAIP_Pos | uint32_t PLLSAIR << RCC_PLLSAICFGR_PLLSAIQ_Pos| {CPY@SPL_PARAM_3} << RCC_PLLSAICFGR_PLLSAIR_Pos);
void        RCC_PLLSAICmd(FunctionalState NewState);
void        RCC_ClockSecuritySystemCmd(FunctionalState NewState);
void        LL_RCC_ConfigMCO(uint32_t RCC_MCO1Source, uint32_t RCC_MCO1Div);
void        LL_RCC_ConfigMCO(uint32_t RCC_MCO2Source, uint32_t RCC_MCO2Div);

/* System, AHB and APB busses clocks configuration functions ******************/
void        LL_RCC_SetSysClkSource(uint32_t RCC_SYSCLKSource);
uint8_t     LL_RCC_GetSysClkSource();
void        LL_RCC_SetAHBPrescaler(uint32_t RCC_SYSCLK);
void        LL_RCC_SetAPB1Prescaler(uint32_t RCC_HCLK);
void        RCC_PCLK2Config(uint32_t RCC_HCLK);
void        LL_RCC_GetSystemClocksFreq(LL_RCC_ClocksTypeDef* RCC_Clocks);

/* Peripheral clocks configuration functions **********************************/
LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_HSE);
void        LL_RCC_SetRTC_HSEPrescaler(uint32_t RCC_RTCCLKSource);
void        RCC_RTCCLKCmd(FunctionalState NewState);
void        RCC_BackupResetCmd(FunctionalState NewState);
void        LL_RCC_SetI2SClockSource(uint32_t RCC_I2SCLKSource); 
void        MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_PLLI2SDIVQ, (uint32_t RCC_PLLI2SDivQ - 1));
void        MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_PLLSAIDIVQ,  (uint32_t RCC_PLLSAIDivQ - 1) << 8);
void        LL_RCC_SetSAIClockSource(uint32_t RCC_SAIBlockACLKSource);
void        LL_RCC_SetSAIClockSource(uint32_t RCC_SAIBlockBCLKSource);
void        MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_PLLSAIDIVR, );
void        LL_RCC_SetTIMPrescaler(uint32_t RCC_TIMCLKPrescaler);

void        RCC_AHB1PeriphClockCmd(uint32_t RCC_AHB1Periph, FunctionalState NewState);
void        RCC_AHB2PeriphClockCmd(uint32_t RCC_AHB2Periph, FunctionalState NewState);
void        RCC_AHB3PeriphClockCmd(uint32_t RCC_AHB3Periph, FunctionalState NewState);
void        RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
void        RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);

void        RCC_AHB1PeriphResetCmd(uint32_t RCC_AHB1Periph, FunctionalState NewState);
void        RCC_AHB2PeriphResetCmd(uint32_t RCC_AHB2Periph, FunctionalState NewState);
void        RCC_AHB3PeriphResetCmd(uint32_t RCC_AHB3Periph, FunctionalState NewState);
void        RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
void        RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);

void        RCC_AHB1PeriphClockLPModeCmd(uint32_t RCC_AHB1Periph, FunctionalState NewState);
void        RCC_AHB2PeriphClockLPModeCmd(uint32_t RCC_AHB2Periph, FunctionalState NewState);
void        RCC_AHB3PeriphClockLPModeCmd(uint32_t RCC_AHB3Periph, FunctionalState NewState);
void        RCC_APB1PeriphClockLPModeCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
void        RCC_APB2PeriphClockLPModeCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);

void        RCC_LSEModeConfig(uint8_t Mode);

/* Interrupts and flags management functions **********************************/
void        RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState);
FlagStatus  RCC_GetFlagStatus(uint8_t RCC_FLAG);
void        LL_RCC_ClearResetFlags();
ITStatus    RCC_GetITStatus(uint8_t RCC_IT);
void        RCC_ClearITPendingBit(uint8_t RCC_IT);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_RCC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
