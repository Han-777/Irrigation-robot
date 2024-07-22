#ifndef _BSP_EXTI__H
#define _BSP_EXTI__H

#include "main.h"
#include <stdint.h>

#define DEVICE_EXTI_CNT 2

typedef void (*exti_module_callback)(uint16_t exti_line_handle);

typedef struct
{
    uint16_t exti_pin; // exti pin
    exti_module_callback exti_callback;
} EXTIInstance;

/**
 * @brief exti regisister function
 *
 * @retval exti instance
 */
EXTIInstance *EXTI_Register(EXTIInstance *init_config);

/**
 * @brief exti call back funcion
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif
