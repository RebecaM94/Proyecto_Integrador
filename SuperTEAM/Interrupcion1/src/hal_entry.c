/* HAL-only entry function */
#include "hal_data.h"

ioport_level_t led_0_level = IOPORT_LEVEL_HIGH;
bsp_leds_t Leds;

void hal_entry(void)
{
    /* TODO: add your own code here */
    R_BSP_LedsGet(&Leds);
    g_external_irq0.p_api->open(g_external_irq0.p_ctrl,g_external_irq0.p_cfg);
    while(1)
    {
    }
}

void button_callback_SW5(external_irq_callback_args_t *p_args)
{
    g_ioport.p_api->pinWrite(Leds.p_leds[0], led_0_level);
    g_ioport.p_api->pinWrite(Leds.p_leds[1], led_0_level);
    g_ioport.p_api->pinWrite(Leds.p_leds[2], led_0_level);

    led_0_level =!led_0_level;// 1 - led_0_level;
}
