#include "new_thread1.h"

ULONG my_rcv_message[2]={0,0};

/* thread0 entry function */
void new_thread1_entry(void)
{
    ioport_level_t level = IOPORT_LEVEL_HIGH;

    while (1)
    {
        /* receive messages */
        // (TX_QUEUE *queue_ptr, VOID *destination_ptr, ULONG wait_option);
        tx_queue_receive(&g_new_queue1, my_rcv_message, 20);

        if(IOPORT_LEVEL_LOW == my_rcv_message[0])
        {
            /* Toggle */
            level = !level;
        }

        g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_01, level);

        /* TICK = 100ms */
        tx_thread_sleep (10);   // Hz
    }
}
