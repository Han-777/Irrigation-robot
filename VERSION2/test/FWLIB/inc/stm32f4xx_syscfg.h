/**
  ******************************************************************************
  * @file    stm32f4xx_syscfg.h
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   This file contains all the functions prototypes for the SYSCFG firmware
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
#ifndef __STM32F4xx_SYSCFG_H
#define __STM32F4xx_SYSCFG_H

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

/** @addtogroup SYSCFG
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
  
/** @defgroup SYSCFG_Exported_Constants 
  * @{
  */ 

/** @defgroup SYSCFG_EXTI_Port_Sources 
  * @{
  */ 
#define LL_SYSCFG_EXTI_PORTA       ((uint8_t)0x00)
#define LL_SYSCFG_EXTI_PORTB       ((uint8_t)0x01)
#define LL_SYSCFG_EXTI_PORTC       ((uint8_t)0x02)
#define LL_SYSCFG_EXTI_PORTD       ((uint8_t)0x03)
#define LL_SYSCFG_EXTI_PORTE       ((uint8_t)0x04)
#define LL_SYSCFG_EXTI_PORTF       ((uint8_t)0x05)
#define LL_SYSCFG_EXTI_PORTG       ((uint8_t)0x06)
#define LL_SYSCFG_EXTI_PORTH       ((uint8_t)0x07)
#define LL_SYSCFG_EXTI_PORTI       ((uint8_t)0x08)
#define LL_SYSCFG_EXTI_PORTJ       ((uint8_t)0x09)
#define LL_SYSCFG_EXTI_PORTK       ((uint8_t)0x0A)

#define IS_EXTI_PORT_SOURCE(PORTSOURCE) (((PORTSOURCE) == LL_SYSCFG_EXTI_PORTA) || \
                                         ((PORTSOURCE) == LL_SYSCFG_EXTI_PORTB) || \
                                         ((PORTSOURCE) == LL_SYSCFG_EXTI_PORTC) || \
                                         ((PORTSOURCE) == LL_SYSCFG_EXTI_PORTD) || \
                                         ((PORTSOURCE) == LL_SYSCFG_EXTI_PORTE) || \
                                         ((PORTSOURCE) == LL_SYSCFG_EXTI_PORTF) || \
                                         ((PORTSOURCE) == LL_SYSCFG_EXTI_PORTG) || \
                                         ((PORTSOURCE) == LL_SYSCFG_EXTI_PORTH) || \
                                         ((PORTSOURCE) == LL_SYSCFG_EXTI_PORTI) || \
                                         ((PORTSOURCE) == LL_SYSCFG_EXTI_PORTJ) || \
                                         ((PORTSOURCE) == LL_SYSCFG_EXTI_PORTK))
                                         
/**
  * @}
  */ 


/** @defgroup SYSCFG_EXTI_Pin_Sources 
  * @{
  */ 
#define LL_SYSCFG_EXTI_LINE0            ((uint8_t)0x00)
#define LL_SYSCFG_EXTI_LINE1            ((uint8_t)0x01)
#define LL_SYSCFG_EXTI_LINE2            ((uint8_t)0x02)
#define LL_SYSCFG_EXTI_LINE3            ((uint8_t)0x03)
#define LL_SYSCFG_EXTI_LINE4            ((uint8_t)0x04)
#define LL_SYSCFG_EXTI_LINE5            ((uint8_t)0x05)
#define LL_SYSCFG_EXTI_LINE6            ((uint8_t)0x06)
#define LL_SYSCFG_EXTI_LINE7            ((uint8_t)0x07)
#define LL_SYSCFG_EXTI_LINE8            ((uint8_t)0x08)
#define LL_SYSCFG_EXTI_LINE9            ((uint8_t)0x09)
#define LL_SYSCFG_EXTI_LINE10           ((uint8_t)0x0A)
#define LL_SYSCFG_EXTI_LINE11           ((uint8_t)0x0B)
#define LL_SYSCFG_EXTI_LINE12           ((uint8_t)0x0C)
#define LL_SYSCFG_EXTI_LINE13           ((uint8_t)0x0D)
#define LL_SYSCFG_EXTI_LINE14           ((uint8_t)0x0E)
#define LL_SYSCFG_EXTI_LINE15           ((uint8_t)0x0F)
#define IS_EXTI_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == LL_SYSCFG_EXTI_LINE0)  || \
                                       ((PINSOURCE) == LL_SYSCFG_EXTI_LINE1)  || \
                                       ((PINSOURCE) == LL_SYSCFG_EXTI_LINE2)  || \
                                       ((PINSOURCE) == LL_SYSCFG_EXTI_LINE3)  || \
                                       ((PINSOURCE) == LL_SYSCFG_EXTI_LINE4)  || \
                                       ((PINSOURCE) == LL_SYSCFG_EXTI_LINE5)  || \
                                       ((PINSOURCE) == LL_SYSCFG_EXTI_LINE6)  || \
                                       ((PINSOURCE) == LL_SYSCFG_EXTI_LINE7)  || \
                                       ((PINSOURCE) == LL_SYSCFG_EXTI_LINE8)  || \
                                       ((PINSOURCE) == LL_SYSCFG_EXTI_LINE9)  || \
                                       ((PINSOURCE) == LL_SYSCFG_EXTI_LINE10) || \
                                       ((PINSOURCE) == LL_SYSCFG_EXTI_LINE11) || \
                                       ((PINSOURCE) == LL_SYSCFG_EXTI_LINE12) || \
                                       ((PINSOURCE) == LL_SYSCFG_EXTI_LINE13) || \
                                       ((PINSOURCE) == LL_SYSCFG_EXTI_LINE14) || \
                                       ((PINSOURCE) == LL_SYSCFG_EXTI_LINE15))
/**
  * @}
  */ 


/** @defgroup SYSCFG_Memory_Remap_Config 
  * @{
  */ 
#define LL_SYSCFG_REMAP_FLASH       ((uint8_t)0x00)
#define LL_SYSCFG_REMAP_SYSTEMFLASH ((uint8_t)0x01)
#define LL_SYSCFG_REMAP_SRAM        ((uint8_t)0x03)
#define LL_SYSCFG_REMAP_SDRAM       ((uint8_t)0x04)

#if defined (STM32F40_41xxx)
#define LL_SYSCFG_REMAP_FSMC        ((uint8_t)0x02) 
#endif /* STM32F40_41xxx */

#if defined (STM32F427_437xx) || defined (STM32F429_439xx)
#define LL_SYSCFG_REMAP_FMC         ((uint8_t)0x02) 
#endif /* STM32F427_437xx ||  STM32F429_439xx */  

#if defined (STM32F40_41xxx) 
#define IS_SYSCFG_MEMORY_REMAP_CONFING(REMAP) (((REMAP) == LL_SYSCFG_REMAP_FLASH)       || \
                                               ((REMAP) == LL_SYSCFG_REMAP_SYSTEMFLASH) || \
                                               ((REMAP) == LL_SYSCFG_REMAP_SRAM)        || \
                                               ((REMAP) == LL_SYSCFG_REMAP_FSMC))
#endif /* STM32F40_41xxx */

#if defined (STM32F401xx) || defined (STM32F411xE)
#define IS_SYSCFG_MEMORY_REMAP_CONFING(REMAP) (((REMAP) == LL_SYSCFG_REMAP_FLASH)       || \
                                               ((REMAP) == LL_SYSCFG_REMAP_SYSTEMFLASH) || \
                                               ((REMAP) == LL_SYSCFG_REMAP_SRAM))
#endif /* STM32F401xx || STM32F411xE */

#if defined (STM32F427_437xx) || defined (STM32F429_439xx)
#define IS_SYSCFG_MEMORY_REMAP_CONFING(REMAP) (((REMAP) == LL_SYSCFG_REMAP_FLASH)       || \
                                               ((REMAP) == LL_SYSCFG_REMAP_SYSTEMFLASH) || \
                                               ((REMAP) == LL_SYSCFG_REMAP_SRAM)        || \
                                               ((REMAP) == LL_SYSCFG_REMAP_SDRAM)       || \
                                               ((REMAP) == LL_SYSCFG_REMAP_FMC))
#endif /* STM32F427_437xx ||  STM32F429_439xx */
                                                                                              
/**
  * @}
  */ 


/** @defgroup SYSCFG_ETHERNET_Media_Interface 
  * @{
  */ 
#define LL_SYSCFG_PMC_ETHMII    ((uint32_t)0x00000000)
#define LL_SYSCFG_PMC_ETHRMII   ((uint32_t)0x00000001)

#define IS_SYSCFG_ETH_MEDIA_INTERFACE(INTERFACE) (((INTERFACE) == LL_SYSCFG_PMC_ETHMII) || \
                                                 ((INTERFACE) == LL_SYSCFG_PMC_ETHRMII))
/**
  * @}
  */ 

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
 
LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_SYSCFG);
void LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_SYSCFG);
void       LL_SYSCFG_SetRemapMemory(uint8_t SYSCFG_MemoryRemap);
void       SYSCFG_MemorySwappingBank(FunctionalState NewState);
void       LL_SYSCFG_SetEXTISource(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex);
void       LL_SYSCFG_SetPHYInterface(uint32_t SYSCFG_ETH_MediaInterface); 
void       SYSCFG_CompensationCellCmd(FunctionalState NewState); 
FlagStatus LL_SYSCFG_IsActiveFlag_CMPCR();

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_SYSCFG_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
