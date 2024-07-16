/**
  ******************************************************************************
  * @file    stm32f4xx_exti.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the EXTI peripheral:           
  *           + Initialization and Configuration
  *           + Interrupts and flags management
  *
@verbatim  

 ===============================================================================
                              ##### EXTI features #####
 ===============================================================================

 [..] External interrupt/event lines are mapped as following:
   (#) All available GPIO pins are connected to the 16 external 
       interrupt/event lines from EXTI0 to EXTI15.
   (#) EXTI line 16 is connected to the PVD Output
   (#) EXTI line 17 is connected to the RTC Alarm event
   (#) EXTI line 18 is connected to the USB OTG FS Wakeup from suspend event
   (#) EXTI line 19 is connected to the Ethernet Wakeup event
   (#) EXTI line 20 is connected to the USB OTG HS (configured in FS) Wakeup event 
   (#) EXTI line 21 is connected to the RTC Tamper and Time Stamp events
   (#) EXTI line 22 is connected to the RTC Wakeup event

                       ##### How to use this driver #####
 ===============================================================================
 
 [..] In order to use an I/O pin as an external interrupt source, follow steps 
      below:
   (#) Configure the I/O in input mode using GPIO_Init()
   (#) Select the input source pin for the EXTI line using SYSCFG_EXTILineConfig()
   (#) Select the mode(interrupt, event) and configure the trigger 
       selection (Rising, falling or both) using EXTI_Init()
   (#) Configure NVIC IRQ channel mapped to the EXTI line using NVIC_Init()

 [..]     
   (@) SYSCFG APB clock must be enabled to get write access to SYSCFG_EXTICRx
       registers using RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

@endverbatim
  *
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_ll_exti.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup EXTI 
  * @brief EXTI driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define LL_EXTI_LINE_NONE    ((uint32_t)0x00000)  /* No interrupt selected */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup EXTI_Private_Functions
  * @{
  */

/** @defgroup EXTI_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim   
 ===============================================================================
             ##### Initialization and Configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the EXTI peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void LL_EXTI_DeInit()
{
  EXTI->IMR = 0x00000000;
  EXTI->EMR = 0x00000000;
  EXTI->RTSR = 0x00000000;
  EXTI->FTSR = 0x00000000;
  EXTI->PR = 0x007FFFFF;
}

/**
  * @brief  Initializes the EXTI peripheral according to the specified
  *         parameters in the EXTI_InitStruct.
  * @param  EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure
  *         that contains the configuration information for the EXTI peripheral.
  * @retval None
  */
void LL_EXTI_Init(LL_EXTI_InitTypeDef* EXTI_InitStruct)
{
  uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_EXTI_MODE(EXTI_InitStruct->Mode));
  assert_param(IS_EXTI_TRIGGER(EXTI_InitStruct->Trigger));
  assert_param(IS_EXTI_LINE(EXTI_InitStruct->Line_0_31));  
  assert_param(IS_FUNCTIONAL_STATE(EXTI_InitStruct->LineCommand));

  tmp = (uint32_t)EXTI_BASE;
     
  if (EXTI_InitStruct->LineCommand != DISABLE)
  {
    /* Clear EXTI line configuration */
    EXTI->IMR &= ~EXTI_InitStruct->Line_0_31;
    EXTI->EMR &= ~EXTI_InitStruct->Line_0_31;
    
    tmp += EXTI_InitStruct->Mode;

    *(__IO uint32_t *) tmp |= EXTI_InitStruct->Line_0_31;

    /* Clear Rising Falling edge configuration */
    EXTI->RTSR &= ~EXTI_InitStruct->Line_0_31;
    EXTI->FTSR &= ~EXTI_InitStruct->Line_0_31;
    
    /* Select the trigger for the selected external interrupts */
    if (EXTI_InitStruct->Trigger == LL_EXTI_TRIGGER_RISING_FALLING)
    {
      /* Rising Falling edge */
      EXTI->RTSR |= EXTI_InitStruct->Line_0_31;
      EXTI->FTSR |= EXTI_InitStruct->Line_0_31;
    }
    else
    {
      tmp = (uint32_t)EXTI_BASE;
      tmp += EXTI_InitStruct->Trigger;

      *(__IO uint32_t *) tmp |= EXTI_InitStruct->Line_0_31;
    }
  }
  else
  {
    tmp += EXTI_InitStruct->Mode;

    /* Disable the selected external lines */
    *(__IO uint32_t *) tmp &= ~EXTI_InitStruct->Line_0_31;
  }
}

/**
  * @brief  Fills each EXTI_InitStruct member with its reset value.
  * @param  EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void LL_EXTI_StructInit(LL_EXTI_InitTypeDef* EXTI_InitStruct)
{
  EXTI_InitStruct->Line_0_31 = LL_EXTI_LINE_NONE;
  EXTI_InitStruct->Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct->Trigger = LL_EXTI_TRIGGER_FALLING;
  EXTI_InitStruct->LineCommand = DISABLE;
}

/**
  * @brief  Generates a Software interrupt on selected EXTI line.
  * @param  EXTI_Line: specifies the EXTI line on which the software interrupt
  *         will be generated.
  *         This parameter can be any combination of EXTI_Linex where x can be (0..22)
  * @retval None
  */
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line)
{
  /* Check the parameters */
  assert_param(IS_EXTI_LINE(EXTI_Line));
  
  EXTI->SWIER |= EXTI_Line;
}

/**
  * @}
  */

/** @defgroup EXTI_Group2 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions 
 *
@verbatim   
 ===============================================================================
             ##### Interrupts and flags management functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Checks whether the specified EXTI line flag is set or not.
  * @param  EXTI_Line: specifies the EXTI line flag to check.
  *          This parameter can be EXTI_Linex where x can be(0..22)
  * @retval The new state of EXTI_Line (SET or RESET).
  */
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_GET_EXTI_LINE(EXTI_Line));
  
  if ((EXTI->PR & EXTI_Line) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the EXTI's line pending flags.
  * @param  EXTI_Line: specifies the EXTI lines flags to clear.
  *          This parameter can be any combination of EXTI_Linex where x can be (0..22)
  * @retval None
  */
void EXTI_ClearFlag(uint32_t EXTI_Line)
{
  /* Check the parameters */
  assert_param(IS_EXTI_LINE(EXTI_Line));
  
  EXTI->PR = EXTI_Line;
}

/**
  * @brief  Checks whether the specified EXTI line is asserted or not.
  * @param  EXTI_Line: specifies the EXTI line to check.
  *          This parameter can be EXTI_Linex where x can be(0..22)
  * @retval The new state of EXTI_Line (SET or RESET).
  */
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_GET_EXTI_LINE(EXTI_Line));
  
  if ((EXTI->PR & EXTI_Line) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
  
}

/**
  * @brief  Clears the EXTI's line pending bits.
  * @param  EXTI_Line: specifies the EXTI lines to clear.
  *          This parameter can be any combination of EXTI_Linex where x can be (0..22)
  * @retval None
  */
void EXTI_ClearITPendingBit(uint32_t EXTI_Line)
{
  /* Check the parameters */
  assert_param(IS_EXTI_LINE(EXTI_Line));
  
  EXTI->PR = EXTI_Line;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
