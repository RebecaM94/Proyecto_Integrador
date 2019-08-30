#include "hal_data.h"

#define LOW 1
#define HIGH 0

uint16_t u16ADC_Data, FilteredData;

void hal_entry(void)
{
    g_adc0.p_api->open(g_adc0.p_ctrl, g_adc0.p_cfg);
    g_adc0.p_api->scanCfg(g_adc0.p_ctrl, g_adc0.p_channel_cfg);
    g_adc0.p_api->scanStart(g_adc0.p_ctrl);

    while(1)
    {
        g_adc0.p_api->read(g_adc0.p_ctrl, ADC_REG_CHANNEL_0, &u16ADC_Data);
        FilteredData = (u16ADC_Data * 100)/255;
    }
}
