

#include <lcd_thread.h>
#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"


//static bool button_enabled = false;

//extern GX_WINDOW_ROOT * p_window_root;

//static UINT show_window(GX_WINDOW * p_new, GX_WIDGET * p_widget, bool detach_old);
//static void update_text_id(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT string_id);

//UINT window1_handler(GX_WINDOW *widget, GX_EVENT *event_ptr)
//{
//    UINT result = gx_window_event_process(widget, event_ptr);
//    return result;
//
//}

//static UINT show_window(GX_WINDOW * p_new, GX_WIDGET * p_widget, bool detach_old)
//{
//    UINT err = GX_SUCCESS;
//
//    if (!p_new->gx_widget_parent)
//    {
//        err = gx_widget_attach(p_window_root, p_new);
//    }
//    else
//    {
//        err = gx_widget_show(p_new);
//    }
//
//    gx_system_focus_claim(p_new);
//
//    GX_WIDGET * p_old = p_widget;
//    if (p_old && detach_old)
//    {
//        if (p_old != (GX_WIDGET*)p_new)
//        {
//            gx_widget_detach(p_old);
//        }
//    }
//
//    return err;
//}

//static void update_text_id(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT string_id)
//{
//    GX_PROMPT * p_prompt = NULL;
//
//    ssp_err_t err = gx_widget_find(p_widget, id, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET**)&p_prompt);
//    if (TX_SUCCESS == err)
//    {
//        gx_prompt_text_id_set(p_prompt, string_id);
//    }
//}

