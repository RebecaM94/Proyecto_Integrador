/* generated thread header file - do not edit */
#ifndef NEW_THREAD0_H_
#define NEW_THREAD0_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus 
extern "C" void new_thread0_entry(void);
#else 
extern void new_thread0_entry(void);
#endif
#include "r_dac.h"
#include "r_dac_api.h"
#include "r_gpt_input_capture.h"
#include "r_input_capture_api.h"
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_adc.h"
#include "r_adc_api.h"
#ifdef __cplusplus
extern "C"
{
#endif
/** DAC on DAC Instance. */
extern const dac_instance_t g_dac0;
/** Timer on GPT Instance. */
extern const input_capture_instance_t g_input_capture;
#ifndef input_capture_callback
void input_capture_callback(input_capture_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer0;
#ifndef sampling_time_callback
void sampling_time_callback(timer_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer1;
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
/** ADC on ADC Instance. */
extern const adc_instance_t g_adc0;
#ifndef NULL
void NULL(adc_callback_args_t *p_args);
#endif
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* NEW_THREAD0_H_ */
