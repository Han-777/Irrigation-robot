/**
  ******************************************************************************
  * @file    stm32f4xx_wwdg.h
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   This file contains all the functions prototypes for the WWDG firmware
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
#ifndef __STM32F4xx_WWDG_H
#define __STM32F4xx_WWDG_H

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

/** @addtogroup WWDG
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup WWDG_Exported_Constants
  * @{
  */ 
  
/** @defgroup WWDG_Prescaler 
  * @{
  */
  
#define LL_WWDG_PRESCALER_1    ((uint32_t)0x00000000)
#define LL_WWDG_PRESCALER_2    ((uint32_t)0x00000080)
#define LL_WWDG_PRESCALER_4    ((uint32_t)0x00000100)
#define LL_WWDG_PRESCALER_8    ((uint32_t)0x00000180)
#define IS_WWDG_PRESCALER(PRESCALER) (((PRESCALER) == LL_WWDG_PRESCALER_1) || \
                                      ((PRESCALER) == LL_WWDG_PRESCALER_2) || \
                                      ((PRESCALER) == LL_WWDG_PRESCALER_4) || \
                                      ((PRESCALER) == LL_WWDG_PRESCALER_8))
#define IS_WWDG_WINDOW_VALUE(VALUE) ((VALUE) <= 0x7F)
#define IS_WWDG_COUNTER(COUNTER) (((COUNTER) >= 0x40) && ((COUNTER) <= 0x7F))

/**
  * @}
  */ 

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
  
/*  Function used to set the WWDG configuration to the default reset state ****/  
LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_WWDG);
void LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_WWDG);

/* Prescaler, Refresh window and Counter configuration functions **************/
void LL_WWDG_SetPrescaler(WWDG, uint32_t WWDG_Prescaler);
void LL_WWDG_SetWindow(WWDG, uint8_t WindowValue);
void LL_WWDG_EnableIT_EWKUP(WWDG);
void LL_WWDG_SetCounter(WWDG, uint8_t Counter);

/* WWDG activation function ***************************************************/
LL_WWDG_SetCounter(WWDG, uint8_t Counter);
void LL_WWDG_Enable(WWDG);

/* Interrupts and flags management functions **********************************/
FlagStatus LL_WWDG_IsActiveFlag_EWKUP(WWDG);
void LL_WWDG_ClearFlag_EWKUP(WWDG);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_WWDG_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
