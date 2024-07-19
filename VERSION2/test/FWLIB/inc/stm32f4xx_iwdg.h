/**
  ******************************************************************************
  * @file    stm32f4xx_iwdg.h
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   This file contains all the functions prototypes for the IWDG 
  *          firmware library.
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
#ifndef __STM32F4xx_IWDG_H
#define __STM32F4xx_IWDG_H

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

/** @addtogroup IWDG
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup IWDG_Exported_Constants
  * @{
  */
  
/** @defgroup IWDG_WriteAccess
  * @{
  */
#define IWDG_WriteAccess_Enable     ((uint16_t)0x5555)
#define IWDG_WriteAccess_Disable    ((uint16_t)0x0000)
#define IS_IWDG_WRITE_ACCESS(ACCESS) (((ACCESS) == IWDG_WriteAccess_Enable) || \
                                      ((ACCESS) == IWDG_WriteAccess_Disable))
/**
  * @}
  */

/** @defgroup IWDG_prescaler 
  * @{
  */
#define LL_IWDG_PRESCALER_4            ((uint8_t)0x00)
#define LL_IWDG_PRESCALER_8            ((uint8_t)0x01)
#define LL_IWDG_PRESCALER_16           ((uint8_t)0x02)
#define LL_IWDG_PRESCALER_32           ((uint8_t)0x03)
#define LL_IWDG_PRESCALER_64           ((uint8_t)0x04)
#define LL_IWDG_PRESCALER_128          ((uint8_t)0x05)
#define LL_IWDG_PRESCALER_256          ((uint8_t)0x06)
#define IS_IWDG_PRESCALER(PRESCALER) (((PRESCALER) == LL_IWDG_PRESCALER_4)  || \
                                      ((PRESCALER) == LL_IWDG_PRESCALER_8)  || \
                                      ((PRESCALER) == LL_IWDG_PRESCALER_16) || \
                                      ((PRESCALER) == LL_IWDG_PRESCALER_32) || \
                                      ((PRESCALER) == LL_IWDG_PRESCALER_64) || \
                                      ((PRESCALER) == LL_IWDG_PRESCALER_128)|| \
                                      ((PRESCALER) == LL_IWDG_PRESCALER_256))
/**
  * @}
  */

/** @defgroup IWDG_Flag 
  * @{
  */
#define IWDG_FLAG_PVU               ((uint16_t)0x0001)
#define IWDG_FLAG_RVU               ((uint16_t)0x0002)
#define IS_IWDG_FLAG(FLAG) (((FLAG) == IWDG_FLAG_PVU) || ((FLAG) == IWDG_FLAG_RVU))
#define IS_IWDG_RELOAD(RELOAD) ((RELOAD) <= 0xFFF)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/* Prescaler and Counter configuration functions ******************************/
void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess);
void LL_IWDG_SetPrescaler(IWDG, uint8_t IWDG_Prescaler);
void LL_IWDG_SetReloadCounter(IWDG, uint16_t Reload);
void LL_IWDG_ReloadCounter(IWDG);

/* IWDG activation function ***************************************************/
void LL_IWDG_Enable(IWDG);

/* Flag management function ***************************************************/
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_IWDG_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
