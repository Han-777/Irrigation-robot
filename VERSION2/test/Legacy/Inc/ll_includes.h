/**
  ******************************************************************************
  * @file    ll_includes.h
  * @author  MCD Application Team
  * @brief   SPL vs LL includes file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LL_INCLUDES_H
#define __LL_INCLUDES_H

/* Includes ------------------------------------------------------------------*/
#include "cmsis_ref.h"

/* LL drivers common to all LL projects */
#if defined(STM32F0)
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_utils.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_exti.h"
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_adc.h"
#include "stm32f0xx_ll_comp.h"
#include "stm32f0xx_ll_cortex.h"
#include "stm32f0xx_ll_crc.h"
#include "stm32f0xx_ll_crs.h"
#include "stm32f0xx_ll_dac.h"
#include "stm32f0xx_ll_dma.h"
#include "stm32f0xx_ll_i2c.h"
#include "stm32f0xx_ll_iwdg.h"
#include "stm32f0xx_ll_rtc.h"
#include "stm32f0xx_ll_spi.h"
#include "stm32f0xx_ll_tim.h"
#include "stm32f0xx_ll_usart.h"
#include "stm32f0xx_ll_wwdg.h"
#endif /* STM32F0 */

#if defined(STM32F1)
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_pwr.h"
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_adc.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_crc.h"
#include "stm32f1xx_ll_dac.h"
#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_i2c.h"
#include "stm32f1xx_ll_iwdg.h"
#include "stm32f1xx_ll_rtc.h"
#include "stm32f1xx_ll_spi.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_wwdg.h"
#endif /* STM32F1 */

#if defined(STM32F2)
#include "stm32f2xx_ll_bus.h"
#include "stm32f2xx_ll_rcc.h"
#include "stm32f2xx_ll_system.h"
#include "stm32f2xx_ll_utils.h"
#include "stm32f2xx_ll_pwr.h"
#include "stm32f2xx_ll_exti.h"
#include "stm32f2xx_ll_gpio.h"
#include "stm32f2xx_ll_adc.h"
#include "stm32f2xx_ll_cortex.h"
#include "stm32f2xx_ll_crc.h"
#include "stm32f2xx_ll_dac.h"
#include "stm32f2xx_ll_dma.h"
#include "stm32f2xx_ll_i2c.h"
#include "stm32f2xx_ll_iwdg.h"
#include "stm32f2xx_ll_rtc.h"
#include "stm32f2xx_ll_spi.h"
#include "stm32f2xx_ll_tim.h"
#include "stm32f2xx_ll_usart.h"
#include "stm32f2xx_ll_wwdg.h"
#include "stm32f2xx_ll_rng.h"
#endif /* STM32F2 */

#if defined(STM32F3)
#include "stm32f3xx_ll_bus.h"
#include "stm32f3xx_ll_rcc.h"
#include "stm32f3xx_ll_system.h"
#include "stm32f3xx_ll_utils.h"
#include "stm32f3xx_ll_pwr.h"
#include "stm32f3xx_ll_exti.h"
#include "stm32f3xx_ll_gpio.h"
#include "stm32f3xx_ll_adc.h"
#include "stm32f3xx_ll_comp.h"
#include "stm32f3xx_ll_cortex.h"
#include "stm32f3xx_ll_crc.h"
#include "stm32f3xx_ll_dac.h"
#include "stm32f3xx_ll_dma.h"
#include "stm32f3xx_ll_hrtim.h"
#include "stm32f3xx_ll_i2c.h"
#include "stm32f3xx_ll_iwdg.h"
#include "stm32f3xx_ll_opamp.h"
#include "stm32f3xx_ll_rtc.h"
#include "stm32f3xx_ll_spi.h"
#include "stm32f3xx_ll_tim.h"
#include "stm32f3xx_ll_usart.h"
#include "stm32f3xx_ll_wwdg.h"
#endif /* STM32F3 */

#if defined(STM32F4)
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_adc.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_crc.h"
#include "stm32f4xx_ll_dac.h"
#include "stm32f4xx_ll_dma.h"
#include "stm32f4xx_ll_dma2d.h"
#include "stm32f4xx_ll_i2c.h"
#include "stm32f4xx_ll_iwdg.h"
#include "stm32f4xx_ll_rtc.h"
#include "stm32f4xx_ll_spi.h"
#include "stm32f4xx_ll_tim.h"
#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_wwdg.h"
#include "stm32f4xx_ll_rng.h"
#include "stm32f4xx_ll_lptim.h"
#endif /* STM32F4 */

#if defined(STM32F7)
#include "stm32f7xx_ll_bus.h"
#include "stm32f7xx_ll_rcc.h"
#include "stm32f7xx_ll_system.h"
#include "stm32f7xx_ll_utils.h"
#include "stm32f7xx_ll_pwr.h"
#include "stm32f7xx_ll_exti.h"
#include "stm32f7xx_ll_gpio.h"
#include "stm32f7xx_ll_adc.h"
#include "stm32f7xx_ll_cortex.h"
#include "stm32f7xx_ll_crc.h"
#include "stm32f7xx_ll_dac.h"
#include "stm32f7xx_ll_dma.h"
#include "stm32f7xx_ll_dma2d.h"
#include "stm32f7xx_ll_i2c.h"
#include "stm32f7xx_ll_iwdg.h"
#include "stm32f7xx_ll_rtc.h"
#include "stm32f7xx_ll_rng.h"
#include "stm32f7xx_ll_spi.h"
#include "stm32f7xx_ll_tim.h"
#include "stm32f7xx_ll_lptim.h"
#include "stm32f7xx_ll_usart.h"
#include "stm32f7xx_ll_wwdg.h"
#endif /* STM32F7 */

#if defined(STM32L0)
#include "stm32l0xx_ll_bus.h"
#include "stm32l0xx_ll_rcc.h"
#include "stm32l0xx_ll_system.h"
#include "stm32l0xx_ll_utils.h"
#include "stm32l0xx_ll_pwr.h"
#include "stm32l0xx_ll_exti.h"
#include "stm32l0xx_ll_gpio.h"
#include "stm32l0xx_ll_adc.h"
#include "stm32l0xx_ll_comp.h"
#include "stm32l0xx_ll_cortex.h"
#include "stm32l0xx_ll_crc.h"
#include "stm32l0xx_ll_crs.h"
#include "stm32l0xx_ll_dac.h"
#include "stm32l0xx_ll_dma.h"
#include "stm32l0xx_ll_i2c.h"
#include "stm32l0xx_ll_iwdg.h"
#include "stm32l0xx_ll_lptim.h"
#include "stm32l0xx_ll_lpuart.h"
#include "stm32l0xx_ll_rng.h"
#include "stm32l0xx_ll_rtc.h"
#include "stm32l0xx_ll_spi.h"
#include "stm32l0xx_ll_tim.h"
#include "stm32l0xx_ll_usart.h"
#include "stm32l0xx_ll_wwdg.h"
#endif /* STM32L0 */

#if defined(STM32L1)
#include "stm32l1xx_ll_bus.h"
#include "stm32l1xx_ll_rcc.h"
#include "stm32l1xx_ll_system.h"
#include "stm32l1xx_ll_utils.h"
#include "stm32l1xx_ll_pwr.h"
#include "stm32l1xx_ll_exti.h"
#include "stm32l1xx_ll_gpio.h"
#include "stm32l1xx_ll_adc.h"
#include "stm32l1xx_ll_comp.h"
#include "stm32l1xx_ll_cortex.h"
#include "stm32l1xx_ll_crc.h"
#include "stm32l1xx_ll_dac.h"
#include "stm32l1xx_ll_dma.h"
#include "stm32l1xx_ll_i2c.h"
#include "stm32l1xx_ll_iwdg.h"
#include "stm32l1xx_ll_opamp.h"
#include "stm32l1xx_ll_rtc.h"
#include "stm32l1xx_ll_spi.h"
#include "stm32l1xx_ll_tim.h"
#include "stm32l1xx_ll_usart.h"
#include "stm32l1xx_ll_wwdg.h"
#endif /* STM32L1 */

#if defined(STM32L4)
#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_system.h"
#include "stm32l4xx_ll_utils.h"
#include "stm32l4xx_ll_pwr.h"
#include "stm32l4xx_ll_exti.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_adc.h"
#include "stm32l4xx_ll_comp.h"
#include "stm32l4xx_ll_cortex.h"
#include "stm32l4xx_ll_crc.h"
#include "stm32l4xx_ll_dac.h"
#include "stm32l4xx_ll_dma.h"
#include "stm32l4xx_ll_dma2d.h"
#include "stm32l4xx_ll_i2c.h"
#include "stm32l4xx_ll_iwdg.h"
#include "stm32l4xx_ll_lptim.h"
#include "stm32l4xx_ll_lpuart.h"
#include "stm32l4xx_ll_opamp.h"
#include "stm32l4xx_ll_rng.h"
#include "stm32l4xx_ll_rtc.h"
#include "stm32l4xx_ll_spi.h"
#include "stm32l4xx_ll_swpmi.h"
#include "stm32l4xx_ll_tim.h"
#include "stm32l4xx_ll_usart.h"
#include "stm32l4xx_ll_wwdg.h"
#endif /* STM32L4 */
#if defined(STM32G0)
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_pwr.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_adc.h"
#include "stm32g0xx_ll_cortex.h"
#include "stm32g0xx_ll_crc.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_dmamux.h"
#include "stm32g0xx_ll_i2c.h"
#include "stm32g0xx_ll_iwdg.h"
#include "stm32g0xx_ll_rtc.h"
#include "stm32g0xx_ll_spi.h"
#include "stm32g0xx_ll_tim.h"
#include "stm32g0xx_ll_usart.h"
#include "stm32g0xx_ll_wwdg.h"
#endif /* STM32G0 */
#if defined(STM32C0)
#include "stm32c0xx_ll_bus.h"
#include "stm32c0xx_ll_rcc.h"
#include "stm32c0xx_ll_system.h"
#include "stm32c0xx_ll_utils.h"
#include "stm32c0xx_ll_pwr.h"
#include "stm32c0xx_ll_exti.h"
#include "stm32c0xx_ll_gpio.h"
#include "stm32c0xx_ll_adc.h"
#include "stm32c0xx_ll_cortex.h"
#include "stm32c0xx_ll_crc.h"
#include "stm32c0xx_ll_dma.h"
#include "stm32c0xx_ll_dmamux.h"
#include "stm32c0xx_ll_i2c.h"
#include "stm32c0xx_ll_iwdg.h"
#include "stm32c0xx_ll_rtc.h"
#include "stm32c0xx_ll_spi.h"
#include "stm32c0xx_ll_tim.h"
#include "stm32c0xx_ll_usart.h"
#include "stm32c0xx_ll_wwdg.h"
#endif /* STM32C0 */
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __LL_INCLUDES_H */
