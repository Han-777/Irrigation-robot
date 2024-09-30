#include "bsp_exti.h"
#include "stdlib.h"
#include "memory.h"

static uint8_t exti_instance_idx = 0;
static EXTIInstance *exti_instance[DEVICE_EXTI_CNT] = {NULL};

/**
 * @brief exti regisister function
 *
 * @retval exti instance
 */
EXTIInstance *EXTI_Register(EXTIInstance *init_config)
{
    if (exti_instance_idx >= DEVICE_EXTI_CNT)
        while (1)
            ;
    EXTIInstance *instance = (EXTIInstance *)malloc(sizeof(EXTIInstance));
    memset(instance, 0, sizeof(EXTIInstance));

    instance->exti_pin = init_config->exti_pin;
    instance->exti_callback = init_config->exti_callback;

    exti_instance[exti_instance_idx++] = instance;
    return instance;
}

/**
 * @brief exti call back funcion
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    for (uint8_t i = 0; i < exti_instance_idx; ++i)
    {
        if (exti_instance[i]->exti_pin == GPIO_Pin)
        {
            if (exti_instance[i]->exti_callback != NULL)
                exti_instance[i]->exti_callback(GPIO_Pin);
            return;
        }
    }
}
