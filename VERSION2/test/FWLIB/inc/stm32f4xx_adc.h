/**
  ******************************************************************************
  * @file    stm32f4xx_adc.h
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   This file contains all the functions prototypes for the ADC firmware 
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
#ifndef __STM32F4xx_ADC_H
#define __STM32F4xx_ADC_H

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

/** @addtogroup ADC
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief   ADC Init structure definition  
  */ 
typedef struct
{
  uint32_t ADC_Resolution;                /*!< Configures the ADC resolution dual mode. 
                                               This parameter can be a value of @ref ADC_resolution */                                   
  FunctionalState ADC_ScanConvMode;       /*!< Specifies whether the conversion 
                                               is performed in Scan (multichannels) 
                                               or Single (one channel) mode.
                                               This parameter can be set to ENABLE or DISABLE */ 
  FunctionalState ADC_ContinuousConvMode; /*!< Specifies whether the conversion 
                                               is performed in Continuous or Single mode.
                                               This parameter can be set to ENABLE or DISABLE. */
  uint32_t ADC_ExternalTrigConvEdge;      /*!< Select the external trigger edge and
                                               enable the trigger of a regular group. 
                                               This parameter can be a value of 
                                               @ref ADC_external_trigger_edge_for_regular_channels_conversion */
  uint32_t ADC_ExternalTrigConv;          /*!< Select the external event used to trigger 
                                               the start of conversion of a regular group.
                                               This parameter can be a value of 
                                               @ref ADC_extrenal_trigger_sources_for_regular_channels_conversion */
  uint32_t ADC_DataAlign;                 /*!< Specifies whether the ADC data  alignment
                                               is left or right. This parameter can be 
                                               a value of @ref ADC_data_align */
  uint8_t  ADC_NbrOfConversion;           /*!< Specifies the number of ADC conversions
                                               that will be done using the sequencer for
                                               regular channel group.
                                               This parameter must range from 1 to 16. */
}LEGACY_ADC_InitTypeDef;
  
/** 
  * @brief   ADC Common Init structure definition  
  */ 
typedef struct 
{
  uint32_t ADC_Mode;                      /*!< Configures the ADC to operate in 
                                               independent or multi mode. 
                                               This parameter can be a value of @ref ADC_Common_mode */                                              
  uint32_t ADC_Prescaler;                 /*!< Select the frequency of the clock 
                                               to the ADC. The clock is common for all the ADCs.
                                               This parameter can be a value of @ref ADC_Prescaler */
  uint32_t ADC_DMAAccessMode;             /*!< Configures the Direct memory access 
                                              mode for multi ADC mode.
                                               This parameter can be a value of 
                                               @ref ADC_Direct_memory_access_mode_for_multi_mode */
  uint32_t ADC_TwoSamplingDelay;          /*!< Configures the Delay between 2 sampling phases.
                                               This parameter can be a value of 
                                               @ref ADC_delay_between_2_sampling_phases */
  
}LEGACY_ADC_CommonInitTypeDef;


/* Exported constants --------------------------------------------------------*/

/** @defgroup ADC_Exported_Constants
  * @{
  */ 
#define IS_ADC_ALL_PERIPH(PERIPH) (((PERIPH) == ADC1) || \
                                   ((PERIPH) == ADC2) || \
                                   ((PERIPH) == ADC3))  

/** @defgroup ADC_Common_mode 
  * @{
  */ 
#define LL_ADC_MULTI_INDEPENDENT                       ((uint32_t)0x00000000)       
#define LL_ADC_MULTI_DUAL_REG_SIM_INJ_SIM         ((uint32_t)0x00000001)
#define LL_ADC_MULTI_DUAL_REG_SIM_INJ_ALT           ((uint32_t)0x00000002)
#define LL_ADC_MULTI_DUAL_INJ_SIMULT                   ((uint32_t)0x00000005)
#define LL_ADC_MULTI_DUAL_REG_SIMULT                     ((uint32_t)0x00000006)
#define LL_ADC_MULTI_DUAL_REG_INTERL                        ((uint32_t)0x00000007)
#define LL_ADC_MULTI_DUAL_INJ_ALTERN                     ((uint32_t)0x00000009)
#define LL_ADC_MULTI_TRIPLE_REG_SIM_INJ_SIM       ((uint32_t)0x00000011)
#define LL_ADC_MULTI_TRIPLE_REG_SIM_INJ_ALT         ((uint32_t)0x00000012)
#define LL_ADC_MULTI_TRIPLE_INJ_SIMULT                 ((uint32_t)0x00000015)
#define LL_ADC_MULTI_TRIPLE_REG_SIMULT                   ((uint32_t)0x00000016)
#define LL_ADC_MULTI_TRIPLE_REG_INTERL                      ((uint32_t)0x00000017)
#define LL_ADC_MULTI_TRIPLE_INJ_ALTERN                   ((uint32_t)0x00000019)
#define IS_ADC_MODE(MODE) (((MODE) == LL_ADC_MULTI_INDEPENDENT) || \
                           ((MODE) == LL_ADC_MULTI_DUAL_REG_SIM_INJ_SIM) || \
                           ((MODE) == LL_ADC_MULTI_DUAL_REG_SIM_INJ_ALT) || \
                           ((MODE) == LL_ADC_MULTI_DUAL_INJ_SIMULT) || \
                           ((MODE) == LL_ADC_MULTI_DUAL_REG_SIMULT) || \
                           ((MODE) == LL_ADC_MULTI_DUAL_REG_INTERL) || \
                           ((MODE) == LL_ADC_MULTI_DUAL_INJ_ALTERN) || \
                           ((MODE) == LL_ADC_MULTI_TRIPLE_REG_SIM_INJ_SIM) || \
                           ((MODE) == LL_ADC_MULTI_TRIPLE_REG_SIM_INJ_ALT) || \
                           ((MODE) == LL_ADC_MULTI_TRIPLE_INJ_SIMULT) || \
                           ((MODE) == LL_ADC_MULTI_TRIPLE_REG_SIMULT) || \
                           ((MODE) == LL_ADC_MULTI_TRIPLE_REG_INTERL) || \
                           ((MODE) == LL_ADC_MULTI_TRIPLE_INJ_ALTERN))
/**
  * @}
  */ 


/** @defgroup ADC_Prescaler 
  * @{
  */ 
#define LL_ADC_CLOCK_SYNC_PCLK_DIV2                         ((uint32_t)0x00000000)
#define LL_ADC_CLOCK_SYNC_PCLK_DIV4                         ((uint32_t)0x00010000)
#define LL_ADC_CLOCK_SYNC_PCLK_DIV6                         ((uint32_t)0x00020000)
#define LL_ADC_CLOCK_SYNC_PCLK_DIV8                         ((uint32_t)0x00030000)
#define IS_ADC_PRESCALER(PRESCALER) (((PRESCALER) == LL_ADC_CLOCK_SYNC_PCLK_DIV2) || \
                                     ((PRESCALER) == LL_ADC_CLOCK_SYNC_PCLK_DIV4) || \
                                     ((PRESCALER) == LL_ADC_CLOCK_SYNC_PCLK_DIV6) || \
                                     ((PRESCALER) == LL_ADC_CLOCK_SYNC_PCLK_DIV8))
/**
  * @}
  */ 


/** @defgroup ADC_Direct_memory_access_mode_for_multi_mode 
  * @{
  */ 
#define LL_ADC_MULTI_REG_DMA_EACH_ADC      ((uint32_t)0x00000000)     /* DMA mode disabled */
#define LL_ADC_MULTI_REG_DMA_LIMIT_1             ((uint32_t)0x00004000)     /* DMA mode 1 enabled (2 / 3 half-words one by one - 1 then 2 then 3)*/
#define LL_ADC_MULTI_REG_DMA_UNLMT_2             ((uint32_t)0x00008000)     /* DMA mode 2 enabled (2 / 3 half-words by pairs - 2&1 then 1&3 then 3&2)*/
#define LL_ADC_MULTI_REG_DMA_UNLMT_3             ((uint32_t)0x0000C000)     /* DMA mode 3 enabled (2 / 3 bytes by pairs - 2&1 then 1&3 then 3&2) */
#define IS_ADC_DMA_ACCESS_MODE(MODE) (((MODE) == LL_ADC_MULTI_REG_DMA_EACH_ADC) || \
                                      ((MODE) == LL_ADC_MULTI_REG_DMA_LIMIT_1) || \
                                      ((MODE) == LL_ADC_MULTI_REG_DMA_UNLMT_2) || \
                                      ((MODE) == LL_ADC_MULTI_REG_DMA_UNLMT_3))
                                     
/**
  * @}
  */ 


/** @defgroup ADC_delay_between_2_sampling_phases 
  * @{
  */ 
#define LL_ADC_MULTI_TWOSMP_DELAY_5CYCLES               ((uint32_t)0x00000000)
#define LL_ADC_MULTI_TWOSMP_DELAY_6CYCLES               ((uint32_t)0x00000100)
#define LL_ADC_MULTI_TWOSMP_DELAY_7CYCLES               ((uint32_t)0x00000200)
#define LL_ADC_MULTI_TWOSMP_DELAY_8CYCLES               ((uint32_t)0x00000300)
#define LL_ADC_MULTI_TWOSMP_DELAY_9CYCLES               ((uint32_t)0x00000400)
#define LL_ADC_MULTI_TWOSMP_DELAY_10CYCLES              ((uint32_t)0x00000500)
#define LL_ADC_MULTI_TWOSMP_DELAY_11CYCLES              ((uint32_t)0x00000600)
#define LL_ADC_MULTI_TWOSMP_DELAY_12CYCLES              ((uint32_t)0x00000700)
#define LL_ADC_MULTI_TWOSMP_DELAY_13CYCLES              ((uint32_t)0x00000800)
#define LL_ADC_MULTI_TWOSMP_DELAY_14CYCLES              ((uint32_t)0x00000900)
#define LL_ADC_MULTI_TWOSMP_DELAY_15CYCLES              ((uint32_t)0x00000A00)
#define LL_ADC_MULTI_TWOSMP_DELAY_16CYCLES              ((uint32_t)0x00000B00)
#define LL_ADC_MULTI_TWOSMP_DELAY_17CYCLES              ((uint32_t)0x00000C00)
#define LL_ADC_MULTI_TWOSMP_DELAY_18CYCLES              ((uint32_t)0x00000D00)
#define LL_ADC_MULTI_TWOSMP_DELAY_19CYCLES              ((uint32_t)0x00000E00)
#define LL_ADC_MULTI_TWOSMP_DELAY_20CYCLES              ((uint32_t)0x00000F00)
#define IS_ADC_SAMPLING_DELAY(DELAY) (((DELAY) == LL_ADC_MULTI_TWOSMP_DELAY_5CYCLES) || \
                                      ((DELAY) == LL_ADC_MULTI_TWOSMP_DELAY_6CYCLES) || \
                                      ((DELAY) == LL_ADC_MULTI_TWOSMP_DELAY_7CYCLES) || \
                                      ((DELAY) == LL_ADC_MULTI_TWOSMP_DELAY_8CYCLES) || \
                                      ((DELAY) == LL_ADC_MULTI_TWOSMP_DELAY_9CYCLES) || \
                                      ((DELAY) == LL_ADC_MULTI_TWOSMP_DELAY_10CYCLES) || \
                                      ((DELAY) == LL_ADC_MULTI_TWOSMP_DELAY_11CYCLES) || \
                                      ((DELAY) == LL_ADC_MULTI_TWOSMP_DELAY_12CYCLES) || \
                                      ((DELAY) == LL_ADC_MULTI_TWOSMP_DELAY_13CYCLES) || \
                                      ((DELAY) == LL_ADC_MULTI_TWOSMP_DELAY_14CYCLES) || \
                                      ((DELAY) == LL_ADC_MULTI_TWOSMP_DELAY_15CYCLES) || \
                                      ((DELAY) == LL_ADC_MULTI_TWOSMP_DELAY_16CYCLES) || \
                                      ((DELAY) == LL_ADC_MULTI_TWOSMP_DELAY_17CYCLES) || \
                                      ((DELAY) == LL_ADC_MULTI_TWOSMP_DELAY_18CYCLES) || \
                                      ((DELAY) == LL_ADC_MULTI_TWOSMP_DELAY_19CYCLES) || \
                                      ((DELAY) == LL_ADC_MULTI_TWOSMP_DELAY_20CYCLES))
                                     
/**
  * @}
  */ 


/** @defgroup ADC_resolution 
  * @{
  */ 
#define LL_ADC_RESOLUTION_12B                         ((uint32_t)0x00000000)
#define LL_ADC_RESOLUTION_10B                         ((uint32_t)0x01000000)
#define LL_ADC_RESOLUTION_8B                          ((uint32_t)0x02000000)
#define LL_ADC_RESOLUTION_6B                          ((uint32_t)0x03000000)
#define IS_ADC_RESOLUTION(RESOLUTION) (((RESOLUTION) == LL_ADC_RESOLUTION_12B) || \
                                       ((RESOLUTION) == LL_ADC_RESOLUTION_10B) || \
                                       ((RESOLUTION) == LL_ADC_RESOLUTION_8B) || \
                                       ((RESOLUTION) == LL_ADC_RESOLUTION_6B))
                                      
/**
  * @}
  */ 


/** @defgroup ADC_external_trigger_edge_for_regular_channels_conversion 
  * @{
  */ 
#define ADC_ExternalTrigConvEdge_None          ((uint32_t)0x00000000)
#define ADC_ExternalTrigConvEdge_Rising        ((uint32_t)0x10000000)
#define ADC_ExternalTrigConvEdge_Falling       ((uint32_t)0x20000000)
#define ADC_ExternalTrigConvEdge_RisingFalling ((uint32_t)0x30000000)
#define IS_ADC_EXT_TRIG_EDGE(EDGE) (((EDGE) == ADC_ExternalTrigConvEdge_None) || \
                             ((EDGE) == ADC_ExternalTrigConvEdge_Rising) || \
                             ((EDGE) == ADC_ExternalTrigConvEdge_Falling) || \
                             ((EDGE) == ADC_ExternalTrigConvEdge_RisingFalling))
/**
  * @}
  */ 


/** @defgroup ADC_extrenal_trigger_sources_for_regular_channels_conversion 
  * @{
  */ 
#define ADC_ExternalTrigConv_T1_CC1                ((uint32_t)0x00000000)
#define ADC_ExternalTrigConv_T1_CC2                ((uint32_t)0x01000000)
#define ADC_ExternalTrigConv_T1_CC3                ((uint32_t)0x02000000)
#define ADC_ExternalTrigConv_T2_CC2                ((uint32_t)0x03000000)
#define ADC_ExternalTrigConv_T2_CC3                ((uint32_t)0x04000000)
#define ADC_ExternalTrigConv_T2_CC4                ((uint32_t)0x05000000)
#define ADC_ExternalTrigConv_T2_TRGO               ((uint32_t)0x06000000)
#define ADC_ExternalTrigConv_T3_CC1                ((uint32_t)0x07000000)
#define ADC_ExternalTrigConv_T3_TRGO               ((uint32_t)0x08000000)
#define ADC_ExternalTrigConv_T4_CC4                ((uint32_t)0x09000000)
#define ADC_ExternalTrigConv_T5_CC1                ((uint32_t)0x0A000000)
#define ADC_ExternalTrigConv_T5_CC2                ((uint32_t)0x0B000000)
#define ADC_ExternalTrigConv_T5_CC3                ((uint32_t)0x0C000000)
#define ADC_ExternalTrigConv_T8_CC1                ((uint32_t)0x0D000000)
#define ADC_ExternalTrigConv_T8_TRGO               ((uint32_t)0x0E000000)
#define ADC_ExternalTrigConv_Ext_IT11              ((uint32_t)0x0F000000)
#define IS_ADC_EXT_TRIG(REGTRIG) (((REGTRIG) == ADC_ExternalTrigConv_T1_CC1) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T1_CC2) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T1_CC3) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T2_CC2) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T2_CC3) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T2_CC4) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T2_TRGO) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T3_CC1) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T3_TRGO) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T4_CC4) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T5_CC1) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T5_CC2) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T5_CC3) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T8_CC1) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T8_TRGO) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_Ext_IT11))
/**
  * @}
  */ 


/** @defgroup ADC_data_align 
  * @{
  */ 
#define LL_ADC_DATA_ALIGN_RIGHT                        ((uint32_t)0x00000000)
#define LL_ADC_DATA_ALIGN_LEFT                         ((uint32_t)0x00000800)
#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == LL_ADC_DATA_ALIGN_RIGHT) || \
                                  ((ALIGN) == LL_ADC_DATA_ALIGN_LEFT))
/**
  * @}
  */ 


/** @defgroup ADC_channels 
  * @{
  */ 
#define LL_ADC_CHANNEL_0                               ((uint8_t)0x00)
#define LL_ADC_CHANNEL_1                               ((uint8_t)0x01)
#define LL_ADC_CHANNEL_2                               ((uint8_t)0x02)
#define LL_ADC_CHANNEL_3                               ((uint8_t)0x03)
#define LL_ADC_CHANNEL_4                               ((uint8_t)0x04)
#define LL_ADC_CHANNEL_5                               ((uint8_t)0x05)
#define LL_ADC_CHANNEL_6                               ((uint8_t)0x06)
#define LL_ADC_CHANNEL_7                               ((uint8_t)0x07)
#define LL_ADC_CHANNEL_8                               ((uint8_t)0x08)
#define LL_ADC_CHANNEL_9                               ((uint8_t)0x09)
#define LL_ADC_CHANNEL_10                              ((uint8_t)0x0A)
#define LL_ADC_CHANNEL_11                              ((uint8_t)0x0B)
#define LL_ADC_CHANNEL_12                              ((uint8_t)0x0C)
#define LL_ADC_CHANNEL_13                              ((uint8_t)0x0D)
#define LL_ADC_CHANNEL_14                              ((uint8_t)0x0E)
#define LL_ADC_CHANNEL_15                              ((uint8_t)0x0F)
#define LL_ADC_CHANNEL_16                              ((uint8_t)0x10)
#define LL_ADC_CHANNEL_17                              ((uint8_t)0x11)
#define LL_ADC_CHANNEL_18                              ((uint8_t)0x12)

#if defined (STM32F40_41xxx)
#define ADC_Channel_TempSensor                      ((uint8_t)LL_ADC_CHANNEL_16)
#endif /* STM32F40_41xxx */

#if defined (STM32F427_437xx) || defined (STM32F429_439xx) || defined (STM32F401xx) || defined (STM32F411xE)
#define ADC_Channel_TempSensor                      ((uint8_t)LL_ADC_CHANNEL_18)
#endif /* STM32F427_437xx || STM32F429_439xx || STM32F401xx || STM32F411xE */

#define ADC_Channel_Vrefint                         ((uint8_t)LL_ADC_CHANNEL_17)
#define ADC_Channel_Vbat                            ((uint8_t)LL_ADC_CHANNEL_18)

#define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) == LL_ADC_CHANNEL_0) || \
                                 ((CHANNEL) == LL_ADC_CHANNEL_1) || \
                                 ((CHANNEL) == LL_ADC_CHANNEL_2) || \
                                 ((CHANNEL) == LL_ADC_CHANNEL_3) || \
                                 ((CHANNEL) == LL_ADC_CHANNEL_4) || \
                                 ((CHANNEL) == LL_ADC_CHANNEL_5) || \
                                 ((CHANNEL) == LL_ADC_CHANNEL_6) || \
                                 ((CHANNEL) == LL_ADC_CHANNEL_7) || \
                                 ((CHANNEL) == LL_ADC_CHANNEL_8) || \
                                 ((CHANNEL) == LL_ADC_CHANNEL_9) || \
                                 ((CHANNEL) == LL_ADC_CHANNEL_10) || \
                                 ((CHANNEL) == LL_ADC_CHANNEL_11) || \
                                 ((CHANNEL) == LL_ADC_CHANNEL_12) || \
                                 ((CHANNEL) == LL_ADC_CHANNEL_13) || \
                                 ((CHANNEL) == LL_ADC_CHANNEL_14) || \
                                 ((CHANNEL) == LL_ADC_CHANNEL_15) || \
                                 ((CHANNEL) == LL_ADC_CHANNEL_16) || \
                                 ((CHANNEL) == LL_ADC_CHANNEL_17) || \
                                 ((CHANNEL) == LL_ADC_CHANNEL_18))
/**
  * @}
  */ 


/** @defgroup ADC_sampling_times 
  * @{
  */ 
#define LL_ADC_SAMPLINGTIME_3CYCLES                    ((uint8_t)0x00)
#define LL_ADC_SAMPLINGTIME_15CYCLES                   ((uint8_t)0x01)
#define LL_ADC_SAMPLINGTIME_28CYCLES                   ((uint8_t)0x02)
#define LL_ADC_SAMPLINGTIME_56CYCLES                   ((uint8_t)0x03)
#define LL_ADC_SAMPLINGTIME_84CYCLES                   ((uint8_t)0x04)
#define LL_ADC_SAMPLINGTIME_112CYCLES                  ((uint8_t)0x05)
#define LL_ADC_SAMPLINGTIME_144CYCLES                  ((uint8_t)0x06)
#define LL_ADC_SAMPLINGTIME_480CYCLES                  ((uint8_t)0x07)
#define IS_ADC_SAMPLE_TIME(TIME) (((TIME) == LL_ADC_SAMPLINGTIME_3CYCLES) || \
                                  ((TIME) == LL_ADC_SAMPLINGTIME_15CYCLES) || \
                                  ((TIME) == LL_ADC_SAMPLINGTIME_28CYCLES) || \
                                  ((TIME) == LL_ADC_SAMPLINGTIME_56CYCLES) || \
                                  ((TIME) == LL_ADC_SAMPLINGTIME_84CYCLES) || \
                                  ((TIME) == LL_ADC_SAMPLINGTIME_112CYCLES) || \
                                  ((TIME) == LL_ADC_SAMPLINGTIME_144CYCLES) || \
                                  ((TIME) == LL_ADC_SAMPLINGTIME_480CYCLES))
/**
  * @}
  */ 


/** @defgroup ADC_external_trigger_edge_for_injected_channels_conversion 
  * @{
  */ 
#define ADC_ExternalTrigInjecConvEdge_None          ((uint32_t)0x00000000)
#define LL_ADC_INJ_TRIG_EXT_RISING        ((uint32_t)0x00100000)
#define LL_ADC_INJ_TRIG_EXT_FALLING       ((uint32_t)0x00200000)
#define LL_ADC_INJ_TRIG_EXT_RISINGFALLING ((uint32_t)0x00300000)
#define IS_ADC_EXT_INJEC_TRIG_EDGE(EDGE) (((EDGE) == ADC_ExternalTrigInjecConvEdge_None) || \
                                          ((EDGE) == LL_ADC_INJ_TRIG_EXT_RISING) || \
                                          ((EDGE) == LL_ADC_INJ_TRIG_EXT_FALLING) || \
                                          ((EDGE) == LL_ADC_INJ_TRIG_EXT_RISINGFALLING))
                                            
/**
  * @}
  */ 


/** @defgroup ADC_extrenal_trigger_sources_for_injected_channels_conversion 
  * @{
  */ 
#define LL_ADC_INJ_TRIG_EXT_TIM1_CH4            ((uint32_t)0x00000000)
#define LL_ADC_INJ_TRIG_EXT_TIM1_TRGO           ((uint32_t)0x00010000)
#define LL_ADC_INJ_TRIG_EXT_TIM2_CH1            ((uint32_t)0x00020000)
#define LL_ADC_INJ_TRIG_EXT_TIM2_TRGO           ((uint32_t)0x00030000)
#define LL_ADC_INJ_TRIG_EXT_TIM3_CH2            ((uint32_t)0x00040000)
#define LL_ADC_INJ_TRIG_EXT_TIM3_CH4            ((uint32_t)0x00050000)
#define LL_ADC_INJ_TRIG_EXT_TIM4_CH1            ((uint32_t)0x00060000)
#define LL_ADC_INJ_TRIG_EXT_TIM4_CH2            ((uint32_t)0x00070000)
#define LL_ADC_INJ_TRIG_EXT_TIM4_CH3            ((uint32_t)0x00080000)
#define LL_ADC_INJ_TRIG_EXT_TIM4_TRGO           ((uint32_t)0x00090000)
#define LL_ADC_INJ_TRIG_EXT_TIM5_CH4            ((uint32_t)0x000A0000)
#define LL_ADC_INJ_TRIG_EXT_TIM5_TRGO           ((uint32_t)0x000B0000)
#define LL_ADC_INJ_TRIG_EXT_TIM8_CH2            ((uint32_t)0x000C0000)
#define LL_ADC_INJ_TRIG_EXT_TIM8_CH3            ((uint32_t)0x000D0000)
#define LL_ADC_INJ_TRIG_EXT_TIM8_CH4            ((uint32_t)0x000E0000)
#define LL_ADC_INJ_TRIG_EXT_EXTI_LINE15          ((uint32_t)0x000F0000)
#define IS_ADC_EXT_INJEC_TRIG(INJTRIG) (((INJTRIG) == LL_ADC_INJ_TRIG_EXT_TIM1_CH4) || \
                                        ((INJTRIG) == LL_ADC_INJ_TRIG_EXT_TIM1_TRGO) || \
                                        ((INJTRIG) == LL_ADC_INJ_TRIG_EXT_TIM2_CH1) || \
                                        ((INJTRIG) == LL_ADC_INJ_TRIG_EXT_TIM2_TRGO) || \
                                        ((INJTRIG) == LL_ADC_INJ_TRIG_EXT_TIM3_CH2) || \
                                        ((INJTRIG) == LL_ADC_INJ_TRIG_EXT_TIM3_CH4) || \
                                        ((INJTRIG) == LL_ADC_INJ_TRIG_EXT_TIM4_CH1) || \
                                        ((INJTRIG) == LL_ADC_INJ_TRIG_EXT_TIM4_CH2) || \
                                        ((INJTRIG) == LL_ADC_INJ_TRIG_EXT_TIM4_CH3) || \
                                        ((INJTRIG) == LL_ADC_INJ_TRIG_EXT_TIM4_TRGO) || \
                                        ((INJTRIG) == LL_ADC_INJ_TRIG_EXT_TIM5_CH4) || \
                                        ((INJTRIG) == LL_ADC_INJ_TRIG_EXT_TIM5_TRGO) || \
                                        ((INJTRIG) == LL_ADC_INJ_TRIG_EXT_TIM8_CH2) || \
                                        ((INJTRIG) == LL_ADC_INJ_TRIG_EXT_TIM8_CH3) || \
                                        ((INJTRIG) == LL_ADC_INJ_TRIG_EXT_TIM8_CH4) || \
                                        ((INJTRIG) == LL_ADC_INJ_TRIG_EXT_EXTI_LINE15))
/**
  * @}
  */ 


/** @defgroup ADC_injected_channel_selection 
  * @{
  */ 
#define ADC_InjectedChannel_1                       ((uint8_t)0x14)
#define ADC_InjectedChannel_2                       ((uint8_t)0x18)
#define ADC_InjectedChannel_3                       ((uint8_t)0x1C)
#define ADC_InjectedChannel_4                       ((uint8_t)0x20)
#define IS_ADC_INJECTED_CHANNEL(CHANNEL) (((CHANNEL) == ADC_InjectedChannel_1) || \
                                          ((CHANNEL) == ADC_InjectedChannel_2) || \
                                          ((CHANNEL) == ADC_InjectedChannel_3) || \
                                          ((CHANNEL) == ADC_InjectedChannel_4))
/**
  * @}
  */ 


/** @defgroup ADC_analog_watchdog_selection 
  * @{
  */ 
#define ADC_AnalogWatchdog_SingleRegEnable         ((uint32_t)0x00800200)
#define ADC_AnalogWatchdog_SingleInjecEnable       ((uint32_t)0x00400200)
#define ADC_AnalogWatchdog_SingleRegOrInjecEnable  ((uint32_t)0x00C00200)
#define ADC_AnalogWatchdog_AllRegEnable            ((uint32_t)0x00800000)
#define ADC_AnalogWatchdog_AllInjecEnable          ((uint32_t)0x00400000)
#define ADC_AnalogWatchdog_AllRegAllInjecEnable    ((uint32_t)0x00C00000)
#define ADC_AnalogWatchdog_None                    ((uint32_t)0x00000000)
#define IS_ADC_ANALOG_WATCHDOG(WATCHDOG) (((WATCHDOG) == ADC_AnalogWatchdog_SingleRegEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_SingleInjecEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_SingleRegOrInjecEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_AllRegEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_AllInjecEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_AllRegAllInjecEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_None))
/**
  * @}
  */ 


/** @defgroup ADC_interrupts_definition 
  * @{
  */ 
#define ADC_IT_EOC                                 ((uint16_t)0x0205)  
#define ADC_IT_AWD                                 ((uint16_t)0x0106)  
#define ADC_IT_JEOC                                ((uint16_t)0x0407)  
#define ADC_IT_OVR                                 ((uint16_t)0x201A)  
#define IS_ADC_IT(IT) (((IT) == ADC_IT_EOC) || ((IT) == ADC_IT_AWD) || \
                       ((IT) == ADC_IT_JEOC)|| ((IT) == ADC_IT_OVR)) 
/**
  * @}
  */ 


/** @defgroup ADC_flags_definition 
  * @{
  */ 
#define ADC_FLAG_AWD                               ((uint8_t)0x01)
#define ADC_FLAG_EOC                               ((uint8_t)0x02)
#define ADC_FLAG_JEOC                              ((uint8_t)0x04)
#define ADC_FLAG_JSTRT                             ((uint8_t)0x08)
#define ADC_FLAG_STRT                              ((uint8_t)0x10)
#define ADC_FLAG_OVR                               ((uint8_t)0x20)   
  
#define IS_ADC_CLEAR_FLAG(FLAG) ((((FLAG) & (uint8_t)0xC0) == 0x00) && ((FLAG) != 0x00))   
#define IS_ADC_GET_FLAG(FLAG) (((FLAG) == ADC_FLAG_AWD) || \
                               ((FLAG) == ADC_FLAG_EOC) || \
                               ((FLAG) == ADC_FLAG_JEOC) || \
                               ((FLAG)== ADC_FLAG_JSTRT) || \
                               ((FLAG) == ADC_FLAG_STRT) || \
                               ((FLAG)== ADC_FLAG_OVR))     
/**
  * @}
  */ 


/** @defgroup ADC_thresholds 
  * @{
  */ 
#define IS_ADC_THRESHOLD(THRESHOLD) ((THRESHOLD) <= 0xFFF)
/**
  * @}
  */ 


/** @defgroup ADC_injected_offset 
  * @{
  */ 
#define IS_ADC_OFFSET(OFFSET) ((OFFSET) <= 0xFFF)
/**
  * @}
  */ 


/** @defgroup ADC_injected_length 
  * @{
  */ 
#define IS_ADC_INJECTED_LENGTH(LENGTH) (((LENGTH) >= 0x1) && ((LENGTH) <= 0x4))
/**
  * @}
  */ 


/** @defgroup ADC_injected_rank 
  * @{
  */ 
#define IS_ADC_INJECTED_RANK(RANK) (((RANK) >= 0x1) && ((RANK) <= 0x4))
/**
  * @}
  */ 


/** @defgroup ADC_regular_length 
  * @{
  */ 
#define IS_ADC_REGULAR_LENGTH(LENGTH) (((LENGTH) >= 0x1) && ((LENGTH) <= 0x10))
/**
  * @}
  */ 


/** @defgroup ADC_regular_rank 
  * @{
  */ 
#define IS_ADC_REGULAR_RANK(RANK) (((RANK) >= 0x1) && ((RANK) <= 0x10))
/**
  * @}
  */ 


/** @defgroup ADC_regular_discontinuous_mode_number 
  * @{
  */ 
#define IS_ADC_REGULAR_DISC_NUMBER(NUMBER) (((NUMBER) >= 0x1) && ((NUMBER) <= 0x8))
/**
  * @}
  */ 


/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/  

/*  Function used to set the ADC configuration to the default reset state *****/  
void LL_ADC_CommonDeInit(__LL_ADC_COMMON_INSTANCE(ADC1));

/* Initialization and Configuration functions *********************************/
void ADC_Init(ADC_TypeDef* ADCx, LEGACY_ADC_InitTypeDef* ADC_InitStruct);
void ADC_StructInit(LEGACY_ADC_InitTypeDef* ADC_InitStruct);
void LL_ADC_CommonInit(__LL_ADC_COMMON_INSTANCE(ADC1), LEGACY_ADC_CommonInitTypeDef* ADC_CommonInitStruct);
void LL_ADC_CommonStructInit(LEGACY_ADC_CommonInitTypeDef* ADC_CommonInitStruct);
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);

/* Analog Watchdog configuration functions ************************************/
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog);
LL_ADC_SetAnalogWDThresholds(ADC_TypeDef* ADCx, LL_ADC_AWD_THRESHOLD_HIGH, uint16_t HighThreshold);
void LL_ADC_SetAnalogWDThresholds(ADC_TypeDef* ADCx, LL_ADC_AWD_THRESHOLD_LOW, uint16_t LowThreshold);
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel);

/* Temperature Sensor, Vrefint and VBAT management functions ******************/
void ADC_TempSensorVrefintCmd(FunctionalState NewState);
void ADC_VBATCmd(FunctionalState NewState);

/* Regular Channels Configuration functions ***********************************/
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void LL_ADC_REG_StartConversionSWStart(ADC_TypeDef* ADCx);
FlagStatus READ_BIT(ADC_TypeDef* ADCx->CR2 , ADC_CR2_JSWSTART);
void ADC_EOCOnEachRegularChannelCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_ContinuousModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_DiscModeChannelCountConfig(ADC_TypeDef* ADCx, uint8_t Number);
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
uint16_t LL_ADC_REG_ReadConversionData12(ADC_TypeDef* ADCx);
uint32_t *(__IO uint32_t *) (0x40012308U);

/* Regular Channels DMA Configuration functions *******************************/
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_DMARequestAfterLastTransferCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_MultiModeDMARequestAfterLastTransferCmd(FunctionalState NewState);

/* Injected channels Configuration functions **********************************/
void ADC_InjectedChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void ADC_InjectedSequencerLengthConfig(ADC_TypeDef* ADCx, uint8_t Length);
void ADC_SetInjectedOffset(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel, uint16_t Offset);
void LL_ADC_INJ_SetTriggerSource(ADC_TypeDef* ADCx, uint32_t ADC_ExternalTrigInjecConv);
void ADC_ExternalTrigInjectedConvEdgeConfig(ADC_TypeDef* ADCx, uint32_t ADC_ExternalTrigInjecConvEdge);
void LL_ADC_INJ_StartConversionSWStart(ADC_TypeDef* ADCx);
FlagStatus READ_BIT(ADC_TypeDef* ADCx->CR2, ADC_CR2_JSWSTART);
void ADC_AutoInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_InjectedDiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
uint16_t ADC_GetInjectedConversionValue(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel);

/* Interrupts and flags management functions **********************************/
void ADC_ITConfig(ADC_TypeDef* ADCx, uint16_t ADC_IT, FunctionalState NewState);
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8_t ADC_FLAG);
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint8_t ADC_FLAG);
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint16_t ADC_IT);
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint16_t ADC_IT);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_ADC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
