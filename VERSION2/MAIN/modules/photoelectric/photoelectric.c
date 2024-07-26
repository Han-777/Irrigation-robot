#include "photoelectric.h"
#include "bsp_exti.h"
#include "stdlib.h"
/**
 * @brief pe callback function
 *
 * @note This function should be modified every time when
 *       application changes
 */
static uint8_t pe_state;
static void PECallback(uint16_t pin_handle)
{
    switch (pin_handle)
    {
    case LEFT_PE_Pin:
    {
        pe_state |= LEFT_PE_FLAG;
        break;
    }
    case RIGHT_PE_Pin:
    {
        pe_state |= RIGHT_PE_FLAG;
        break;
    }
    }
}

uint8_t *PE_Init(uint16_t pe_pin_handle)
{
    EXTIInstance conf_s;
    conf_s.exti_pin = pe_pin_handle;
    conf_s.exti_callback = PECallback;
    EXTI_Register(&conf_s);
    return &pe_state;
}
