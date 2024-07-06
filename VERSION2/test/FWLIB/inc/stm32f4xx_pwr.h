/**
  ******************************************************************************
  * @file    stm32f4xx_pwr.h
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   This file contains all the functions prototypes for the PWR firmware 
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
#ifndef __STM32F4xx_PWR_H
#define __STM32F4xx_PWR_H

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

/** @addtogroup PWR
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup PWR_Exported_Constants
  * @{
  */ 

/** @defgroup PWR_PVD_detection_level 
  * @{
  */ 
#define LL_PWR_PVDLEVEL_0                  PWR_CR_PLS_LEV0
#define LL_PWR_PVDLEVEL_1                  PWR_CR_PLS_LEV1
#define LL_PWR_PVDLEVEL_2                  PWR_CR_PLS_LEV2
#define LL_PWR_PVDLEVEL_3                  PWR_CR_PLS_LEV3
#define LL_PWR_PVDLEVEL_4                  PWR_CR_PLS_LEV4
#define LL_PWR_PVDLEVEL_5                  PWR_CR_PLS_LEV5
#define LL_PWR_PVDLEVEL_6                  PWR_CR_PLS_LEV6
#define LL_PWR_PVDLEVEL_7                  PWR_CR_PLS_LEV7

#define IS_PWR_PVD_LEVEL(LEVEL) (((LEVEL) == LL_PWR_PVDLEVEL_0) || ((LEVEL) == LL_PWR_PVDLEVEL_1)|| \
                                 ((LEVEL) == LL_PWR_PVDLEVEL_2) || ((LEVEL) == LL_PWR_PVDLEVEL_3)|| \
                                 ((LEVEL) == LL_PWR_PVDLEVEL_4) || ((LEVEL) == LL_PWR_PVDLEVEL_5)|| \
                                 ((LEVEL) == LL_PWR_PVDLEVEL_6) || ((LEVEL) == LL_PWR_PVDLEVEL_7))
/**
  * @}
  */

  
/** @defgroup PWR_Regulator_state_in_STOP_mode 
  * @{
  */
#define LL_PWR_MODE_STOP_MAINREGU                        ((uint32_t)0x00000000)
#define LL_PWR_MODE_STOP_LPREGU                    PWR_CR_LPDS

/* --- PWR_Legacy ---*/
#define LL_PWR_MODE_STOP_MAINREGU                            LL_PWR_MODE_STOP_MAINREGU
#define LL_PWR_MODE_STOP_LPREGU                      LL_PWR_MODE_STOP_LPREGU

#define IS_PWR_REGULATOR(REGULATOR) (((REGULATOR) == LL_PWR_MODE_STOP_MAINREGU) || \
                                     ((REGULATOR) == LL_PWR_MODE_STOP_LPREGU))

/**
  * @}
  */

/** @defgroup PWR_Regulator_state_in_UnderDrive_mode 
  * @{
  */
#define LL_PWR_MODE_STOP_MAINREGU_UNDERDRIVE               PWR_CR_MRUDS
#define LL_PWR_MODE_STOP_LPREGU_UNDERDRIVE           ((uint32_t)(PWR_CR_LPDS | PWR_CR_LPUDS))

#define IS_PWR_REGULATOR_UNDERDRIVE(REGULATOR) (((REGULATOR) == LL_PWR_MODE_STOP_MAINREGU_UNDERDRIVE) || \
                                                ((REGULATOR) == LL_PWR_MODE_STOP_LPREGU_UNDERDRIVE))

/**
  * @}
  */

/** @defgroup PWR_STOP_mode_entry 
  * @{
  */
#define PWR_STOPEntry_WFI               ((uint8_t)0x01)
#define PWR_STOPEntry_WFE               ((uint8_t)0x02)
#define IS_PWR_STOP_ENTRY(ENTRY) (((ENTRY) == PWR_STOPEntry_WFI) || ((ENTRY) == PWR_STOPEntry_WFE))
/**
  * @}
  */

/** @defgroup PWR_Regulator_Voltage_Scale 
  * @{
  */
#define LL_PWR_REGU_VOLTAGE_SCALE1    ((uint32_t)0x0000C000)
#define LL_PWR_REGU_VOLTAGE_SCALE2    ((uint32_t)0x00008000)
#define LL_PWR_REGU_VOLTAGE_SCALE3    ((uint32_t)0x00004000)
#define IS_PWR_REGULATOR_VOLTAGE(VOLTAGE) (((VOLTAGE) == LL_PWR_REGU_VOLTAGE_SCALE1) || \
                                           ((VOLTAGE) == LL_PWR_REGU_VOLTAGE_SCALE2) || \
                                           ((VOLTAGE) == LL_PWR_REGU_VOLTAGE_SCALE3))
/**
  * @}
  */

/** @defgroup PWR_Flag 
  * @{
  */
#define PWR_FLAG_WU                     PWR_CSR_WUF
#define PWR_FLAG_SB                     PWR_CSR_SBF
#define PWR_FLAG_PVDO                   PWR_CSR_PVDO
#define PWR_FLAG_BRR                    PWR_CSR_BRR
#define PWR_FLAG_VOSRDY                 PWR_CSR_VOSRDY
#define PWR_FLAG_ODRDY                  PWR_CSR_ODRDY
#define PWR_FLAG_ODSWRDY                PWR_CSR_ODSWRDY
#define PWR_FLAG_UDRDY                  PWR_CSR_UDSWRDY

/* --- FLAG Legacy ---*/
#define PWR_FLAG_REGRDY                  PWR_FLAG_VOSRDY               

#define IS_PWR_GET_FLAG(FLAG) (((FLAG) == PWR_FLAG_WU) || ((FLAG) == PWR_FLAG_SB) || \
                               ((FLAG) == PWR_FLAG_PVDO) || ((FLAG) == PWR_FLAG_BRR) || \
                               ((FLAG) == PWR_FLAG_VOSRDY) || ((FLAG) == PWR_FLAG_ODRDY) || \
                               ((FLAG) == PWR_FLAG_ODSWRDY) || ((FLAG) == PWR_FLAG_UDRDY))


#define IS_PWR_CLEAR_FLAG(FLAG) (((FLAG) == PWR_FLAG_WU) || ((FLAG) == PWR_FLAG_SB) || \
                                 ((FLAG) == PWR_FLAG_UDRDY))

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 

/* Function used to set the PWR configuration to the default reset state ******/ 
void LL_PWR_DeInit();

/* Backup Domain Access function **********************************************/ 
void PWR_BackupAccessCmd(FunctionalState NewState);

/* PVD configuration functions ************************************************/ 
void LL_PWR_SetPVDLevel(uint32_t PWR_PVDLevel);
void PWR_PVDCmd(FunctionalState NewState);

/* WakeUp pins configuration functions ****************************************/ 
void PWR_WakeUpPinCmd(FunctionalState NewState);

/* Main and Backup Regulators configuration functions *************************/ 
void PWR_BackupRegulatorCmd(FunctionalState NewState);
void LL_PWR_SetRegulVoltageScaling(uint32_t PWR_Regulator_Voltage);
void PWR_OverDriveCmd(FunctionalState NewState);
void PWR_OverDriveSWCmd(FunctionalState NewState);
void PWR_UnderDriveCmd(FunctionalState NewState);
void PWR_MainRegulatorLowVoltageCmd(FunctionalState NewState);
void PWR_LowRegulatorLowVoltageCmd(FunctionalState NewState);

/* FLASH Power Down configuration functions ***********************************/ 
void PWR_FlashPowerDownCmd(FunctionalState NewState);

/* Low Power modes configuration functions ************************************/ 
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry);
void PWR_EnterUnderDriveSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry);
LL_PWR_ClearFlag_WU();
LL_PWR_SetPowerMode(LL_PWR_MODE_STANDBY);
LL_LPM_EnableDeepSleep();
void __WFI();

/* Flags management functions *************************************************/ 
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);
void PWR_ClearFlag(uint32_t PWR_FLAG);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_PWR_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
