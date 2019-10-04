#include "new_thread0.h"
#include "main_thread.h"

#define SAMPLING_TIME 0.1 //seconds

#define UNUSED(x) (void)(x)

UINT lcd_message[3]={0,0,0};

bool first_flag = 1;

#define K_p 0.07
#define K_i 0.01
#define K_d 0

uint16_t u16ADC_Data;
float setpoint_rpm;

uint16_t pulses, prev_pulses;
float revolutions, speed_rpm;
float error, integral, derivative, last_error, pwm_out;
uint32_t pwm_out_int;

ioport_level_t P70_Status = IOPORT_LEVEL_HIGH;

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
        lcd_message[0]=(UINT) (100 - pwm_out_int); //dutyCycle
        lcd_message[1]=(UINT) speed_rpm; //
        lcd_message[2]=(UINT) setpoint_rpm;

        /* send message to Thread 1 */
        // (TX_QUEUE *queue_ptr, VOID *source_ptr, ULONG wait_option);
        tx_queue_send(&g_new_queue_lcd, lcd_message, TX_NO_WAIT);

        tx_thread_sleep (1);
    }
}

void sampling_time_callback(timer_callback_args_t *p_args)
{
    UNUSED(p_args);

    /* Read ADC value*/
    g_adc0.p_api->read(g_adc0.p_ctrl, ADC_REG_CHANNEL_0, &u16ADC_Data);

    //TODO map this entry to the possible speed values that the sensor/u can read
    //Map the ADC input into RPM using the required linear function RPM = 11.764705882353 (ADCvalue 0-255)
    setpoint_rpm = (float)(u16ADC_Data * 11.764705882353);

    if (first_flag)
    {
        prev_pulses = pulses;
        first_flag = 0;
    }

    //Number of revolutions during the last sampling time
    pulses = (pulses + prev_pulses)/2;
    revolutions = (float) (pulses/4.0);

    prev_pulses = pulses;

    //Flush the pulses to avoid overflow
    pulses = 0;

    //Calculate the speed
    speed_rpm  = (float)(60.0 * revolutions);
    speed_rpm /= (float) SAMPLING_TIME;

    /*--------------------Control-------------------------------------------------------*/
    //Calculate the error
     error = setpoint_rpm - speed_rpm;

     integral += error;
     // To avoid integral windup we simply restrict the integral error to a reasonable value.
     if(integral > 50) integral = 50;

     derivative = error - last_error;

     last_error = error;

     //PID
     pwm_out = (K_p * error) + (K_i * integral) + (K_d * derivative);
     pwm_out *=-1;

     if (pwm_out > 100) pwm_out = 100;
     else if (pwm_out < 0) pwm_out = 0;

     pwm_out_int = (uint32_t) pwm_out;
     /*---------------------------------------------------------------------------------*/

    /* Change PWM dutyCycle P46---- 100 slow    0 fast*/
    g_timer1.p_api->dutyCycleSet(g_timer1.p_ctrl, pwm_out_int, TIMER_PWM_UNIT_PERCENT, 1);
}

void input_capture_callback(input_capture_callback_args_t *p_args)
{
    UNUSED(p_args);
    pulses++;
}

