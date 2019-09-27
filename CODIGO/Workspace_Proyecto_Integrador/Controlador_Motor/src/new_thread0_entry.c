#include "new_thread0.h"
#include "main_thread.h"

#define LOW 1
#define HIGH 0

uint16_t u16ADC_Data = 0;
uint16_t FilteredData = 0;
UINT lcd_message[2]={12,13};

static uint32_t capture_counter = 0;

void new_thread0_entry(void)
{
    /* ADC configuration P00*/
    g_adc0.p_api->open(g_adc0.p_ctrl, g_adc0.p_cfg);
    g_adc0.p_api->scanCfg(g_adc0.p_ctrl, g_adc0.p_channel_cfg);
    g_adc0.p_api->scanStart(g_adc0.p_ctrl);

    /* PWM configuration*/
    g_timer1.p_api->open(g_timer1.p_ctrl, g_timer1.p_cfg);
    g_timer1.p_api->start(g_timer1.p_ctrl);


    /*Sampling time Timer configuration*/
    g_timer0.p_api->open (g_timer0.p_ctrl, g_timer0.p_cfg);
    g_timer0.p_api->start (g_timer0.p_ctrl);


    /*Input capture configuration*/
    g_input_capture.p_api->open(g_input_capture.p_ctrl, g_input_capture.p_cfg);
    g_input_capture.p_api->enable(g_input_capture.p_ctrl);

    while(1)
    {
        lcd_message[0]=(UINT) FilteredData;

        /* send message to Thread 1 */
        // (TX_QUEUE *queue_ptr, VOID *source_ptr, ULONG wait_option);
        tx_queue_send(&g_new_queue_lcd, lcd_message, TX_NO_WAIT);

        tx_thread_sleep (1);
    }
}

void sampling_time_callback(timer_callback_args_t *p_args)
{
    /* Read ADC value*/
    g_adc0.p_api->read(g_adc0.p_ctrl, ADC_REG_CHANNEL_0, &u16ADC_Data);
    FilteredData = (u16ADC_Data * 100)/255;

    /* Change PWM dutyCycle P46*/
    g_timer1.p_api->dutyCycleSet(g_timer1.p_ctrl, FilteredData, TIMER_PWM_UNIT_PERCENT, 1);

}

void input_capture_callback(input_capture_callback_args_t *p_args)
{
    capture_counter = p_args->counter;
}

