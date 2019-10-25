#include <control_thread0.h>
#include <lcd_thread.h>

#define DIGITAL_3V 233
#define MAX_RMP 3000.0

#define HALF_SPEED_RES 37
#define SPEED_RESOLUTION 75
#define SAMPLING_TIME 0.1 //seconds
#define UNUSED(x) (void)(x)
#define K_p 0.07
#define K_i 0.01
#define K_d 0.005

UINT lcd_message[3]={0,0,0};

bool first_iteration = 1;

uint16_t u16ADC_Data, u16setpoint_rpm, u16pulses,  u16prev_pulses;
uint32_t pwm_out_int;
float pulses_average, setpoint_rpm_1, setpoint_rpm_2, setpoint_rpm_3, setpoint_rpm_new, setpoint_rpm_average, setpoint_rpm,
      revolutions, speed_rpm, error, integral, derivative, last_error, pwm_out;

void control_thread0_entry(void)
{
    /* ADC configuration P00*/
    g_adc0.p_api->open(g_adc0.p_ctrl, g_adc0.p_cfg);
    g_adc0.p_api->scanCfg(g_adc0.p_ctrl, g_adc0.p_channel_cfg);
    g_adc0.p_api->scanStart(g_adc0.p_ctrl);

    /* PWM configuration*/
    g_timer1.p_api->open(g_timer1.p_ctrl, g_timer1.p_cfg);
    g_timer1.p_api->start(g_timer1.p_ctrl);

    /* DAC for testing purposes*/
    g_dac0.p_api->open(g_dac0.p_ctrl, g_dac0.p_cfg);
    g_dac0.p_api->start(g_dac0.p_ctrl);

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
        lcd_message[2]=(UINT) u16setpoint_rpm;

        /* send message to Thread LCD */
        tx_queue_send(&g_new_queue_lcd, lcd_message, TX_NO_WAIT);

        tx_thread_sleep (1);
    }
}

void sampling_time_callback(timer_callback_args_t *p_args)
{
    UNUSED(p_args);
    /*-----------------------------------Setpoint-----------------------------------------*/
    /* Read ADC value P00*/
    g_adc0.p_api->read(g_adc0.p_ctrl, ADC_REG_CHANNEL_0, &u16ADC_Data);

    /* Limit the entry to the digital value at which the pot gives a 3V output  */
    if (u16ADC_Data > DIGITAL_3V) u16ADC_Data = DIGITAL_3V;

    //Map the ADC input into RPM using the required linear function in RPM
    setpoint_rpm_new = (float)(u16ADC_Data * MAX_RMP/DIGITAL_3V);

    //Set the previous setpoint values to the current one to avoid averaging with 0.
    if (first_iteration)
    {
        setpoint_rpm_3 = setpoint_rpm_new;
        setpoint_rpm_2 = setpoint_rpm_new;
        setpoint_rpm_1 = setpoint_rpm_new;
    }

    setpoint_rpm_3 = setpoint_rpm_2;
    setpoint_rpm_2 = setpoint_rpm_1;
    setpoint_rpm_1 = setpoint_rpm_new;

    setpoint_rpm_average = (float)(setpoint_rpm_1 + setpoint_rpm_2 + setpoint_rpm_3)/3.0;

    //To reduce noise map the setpoint to multiples of SPEED_RESOLUTION rounding up when module is >HALF_SPEED_RES
    u16setpoint_rpm = (uint16_t)setpoint_rpm_average;
    u16setpoint_rpm /= SPEED_RESOLUTION;
    if (u16setpoint_rpm % SPEED_RESOLUTION > HALF_SPEED_RES) u16setpoint_rpm ++;
    u16setpoint_rpm *= SPEED_RESOLUTION;

    /*-----------------------------------Speed-----------------------------------------*/
    //Avoid averaging the first time the speed is calculated
    if (first_iteration)
    {
        u16prev_pulses = u16pulses;
        first_iteration = 0;
    }

    //Number of revolutions during the last sampling time
    pulses_average = (float) ((u16pulses + u16prev_pulses)/2.0);
    revolutions = (float) (pulses_average/4.0);
    u16prev_pulses = u16pulses;

    //Flush the pulses value
    u16pulses = 0;

    //Calculate the speed
    speed_rpm  = (float)(60.0 * revolutions);
    speed_rpm /= (float) SAMPLING_TIME;

    //For gain calculations print the speed into an analog pin
    g_dac0.p_api->write(g_dac0.p_ctrl,(uint16_t)speed_rpm);

    /*--------------------Control-------------------------------------------------------*/
    //Calculate the error
    error = (float) u16setpoint_rpm - speed_rpm;

    integral += error;
    // To avoid integral windup we simply restrict the integral error to a reasonable value.
    if(integral > 50) integral = 50;

    derivative = error - last_error;

    last_error = error;

    //PID
    pwm_out = ((float)(K_p * error)) + ((float)(K_i * integral)) + (float)((K_d * derivative));
    pwm_out *=-1;

    if (pwm_out > 100) pwm_out = 100;
    else if (pwm_out < 0) pwm_out = 0;

    pwm_out_int = (uint32_t) pwm_out;
    /*---------------------------------------------------------------------------------*/

    /* Change PWM dutyCycle Pin=P46           100 slow    0 fast*/
    g_timer1.p_api->dutyCycleSet(g_timer1.p_ctrl, pwm_out_int, TIMER_PWM_UNIT_PERCENT, 1);
}

void input_capture_callback(input_capture_callback_args_t *p_args)
{
    UNUSED(p_args);
    u16pulses++;
}
