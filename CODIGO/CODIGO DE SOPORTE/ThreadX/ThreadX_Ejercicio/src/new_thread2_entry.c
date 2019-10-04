#include "new_thread2.h"
#include "new_thread1.h"  //Agregar g_new_queue1

ULONG my_message[2]={0,0};

/* thread2 entry function */
void new_thread2_entry(void)
{
    ioport_level_t P06_Status = IOPORT_LEVEL_LOW; // SW4 button
    ioport_level_t P05_Status = IOPORT_LEVEL_LOW; // SW5 button

    while (1)
    {
        /* read SW4 */
        g_ioport.p_api->pinRead(IOPORT_PORT_00_PIN_06, &P06_Status);

        /* write YELLOW led */
        g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_02, P06_Status);

        /* read SW5 */
        g_ioport.p_api->pinRead(IOPORT_PORT_00_PIN_05, &P05_Status);

        /* storage */
        my_message[0]=P05_Status;

        /* send message to Thread 1 */
        // (TX_QUEUE *queue_ptr, VOID *source_ptr, ULONG wait_option);
        tx_queue_send(&g_new_queue1, my_message, TX_NO_WAIT);


        /* TICK = 10ms */
        tx_thread_sleep (1);   // Hz
    }
}
