#include "new_thread0.h"

/* thread0 entry function */
void new_thread0_entry(void)
{
    ioport_level_t level = IOPORT_LEVEL_HIGH;

    while (1)
    {
        /* Toggle */
        level = !level;
        g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, level);

        /* TICK = 500ms */
        tx_thread_sleep (50);   //1 Hz
    }
}
