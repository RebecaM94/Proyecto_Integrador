/* HAL-only entry function */
#include "hal_data.h"

#define LOW 1
#define HIGH 0

bool change = 0;
uint8_t uartCaracter = 'R';
uint8_t uartRXCaracter;

ioport_level_t P05_Status = IOPORT_LEVEL_LOW;
ioport_level_t P06_Status = IOPORT_LEVEL_LOW;

ioport_level_t P60_Status = IOPORT_LEVEL_LOW;
ioport_level_t P61_Status = IOPORT_LEVEL_LOW;
ioport_level_t P62_Status = IOPORT_LEVEL_LOW;


void hal_entry(void)
{
    g_uart0.p_api->open(g_uart0.p_ctrl, g_uart0.p_cfg);

    g_external_irq10.p_api->open(g_external_irq10.p_ctrl, g_external_irq10.p_cfg);


    while(1){
        //g_ioport.p_api->pinRead(IOPORT_PORT_00_PIN_05, &P05_Status);
        //g_ioport.p_api->pinRead(IOPORT_PORT_00_PIN_06, &P06_Status);

        if(HIGH == P06_Status)
           {
               P60_Status = HIGH;
               P62_Status = LOW;
           }
         else
           {
               P60_Status = LOW;
           }

        if(HIGH == P05_Status)
           {
                P61_Status = HIGH;
           }
         else
            {
                P61_Status = LOW;
            }

        if (change)
        {
            change = false;
            g_uart0.p_api->write(g_uart0.p_ctrl, &uartCaracter, 1);
            P62_Status = HIGH;
        }

        g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, P60_Status);
        g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_01, P61_Status);
        g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_02, P62_Status);
    }
}


void button_callback_SW5(external_irq_callback_args_t *p_args)
{
    change = true;
}

void user_uart_callback(uart_callback_args_t *p_args)
{
    if(p_args->event == UART_EVENT_RX_CHAR)
    {
        uartRXCaracter = (uint8_t)p_args->data;
    }
}
