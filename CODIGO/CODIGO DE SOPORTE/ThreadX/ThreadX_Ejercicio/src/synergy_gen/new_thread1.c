/* generated thread source file - do not edit */
#include "new_thread1.h"

TX_THREAD new_thread1;
void new_thread1_create(void);
static void new_thread1_func(ULONG thread_input);
static uint8_t new_thread1_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.new_thread1") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
TX_QUEUE g_new_queue1;
static uint8_t queue_memory_g_new_queue1[16];
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void new_thread1_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */
    UINT err_g_new_queue1;
    err_g_new_queue1 = tx_queue_create (&g_new_queue1, (CHAR *) "Queue1", 4, &queue_memory_g_new_queue1,
                                        sizeof(queue_memory_g_new_queue1));
    if (TX_SUCCESS != err_g_new_queue1)
    {
        tx_startup_err_callback (&g_new_queue1, 0);
    }

    UINT err;
    err = tx_thread_create (&new_thread1, (CHAR *) "thread1", new_thread1_func, (ULONG) NULL, &new_thread1_stack, 1024,
                            1, 1, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&new_thread1, 0);
    }
}

static void new_thread1_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    new_thread1_entry ();
}
