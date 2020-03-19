#ifndef IN_JERRYSCRIPT_PORT_H_H_INCLUDED
#define IN_JERRYSCRIPT_PORT_H_H_INCLUDED

/**
  ****************************************************************************
  * @file    in_jerryscript_port_h.h
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    16.04.2018
  * @brief   JavaScript interpreter port
  ****************************************************************************
  * @attention
  * <h2><center>&copy; COPYRIGHT PORTTRONIC</center></h2>
  ****************************************************************************
  */

/**
  ****************************************************************************
  * Library
  ****************************************************************************
  */

#include <wx/string.h>
#include <wx/thread.h>
#include "in_js_gui_frame_h.h"
#include "hw_dr_uart_driver_h.h"
#include "in_js_class_timer_js_h.h"
#include "in_js_class_time_js_h.h"
#include "in_js_class_file_js_h.h"
#include "in_js_class_project_js_h.h"
#include "in_js_class_uart_js_h.h"
#include "in_js_class_main_frame_js_h.h"
#include "in_js_class_panel_js_h.h"
#include "in_js_class_sizer_js_h.h"
#include "in_js_class_graph_js_h.h"
#include "in_js_class_button_js_h.h"
#include "in_js_class_slider_js_h.h"
#include "in_js_class_static_text_js_h.h"
#include "in_js_class_textctrl_js_h.h"
#include "in_js_class_check_box_js_h.h"
#include "in_js_class_gauge_js_h.h"
#include "in_js_class_led_js_h.h"

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @addtogroup JerryScript
  * @{
  */

/**
  * @addtogroup Port
  * @{
  */

/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */


class jerryscript_c
{
    public:

        jerryscript_c( uart_port* p_com_uart_port, void* p_gui_main_frame_void, bool debug_b, bool init_b);
        ~jerryscript_c( void );
        uint32_t run(wxString script_str);
        void stop (void);
        void call_event (wxString event_str, uint32_t component_id_ui32);
        void reg_class (void);
        void dereg_class (void);
        static uint32_t call(void);

    private:

        static void worker(void* p_parametr_void);
        static uint32_t delay(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
        static uint32_t js_rand(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
        static uint32_t alert(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
        static uint32_t gui(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);

        // External class
        timer_js_c l_data_timer_js;
        time_js_c l_data_time_js;
        file_js_c l_data_file_js;
        project_js_c l_data_project_js;
        uart_js_c l_port_uart_js;
        main_frame_js_c l_gui_main_frame_js;
        panel_js_c l_gui_panel_js;
        sizer_js_c l_gui_sizer_js;
        graph_js_c l_gui_graph_js;
        button_js_c l_gui_button_js;
        slider_js_c l_gui_slider_js;
        static_text_js_c l_gui_static_text_js;
        textctrl_js_c l_gui_textctrl_js;
        check_box_js_c l_gui_check_box_js;
        gauge_js_c l_gui_gauge_js;
        led_js_c l_gui_led_js;
        // Working thread
        thread_c* lp_script_thread;
        uint8_t l_run_script_ui8;
        // File path
        wxString l_jerryscript_code_str;
        bool l_init_flag_b;
        // Project
        wxString l_project_str;
        // GUI
        gui_frame* lp_data_gui_frame;
        void* lp_gui_main_frame_void;
        bool l_debug_b;
        uart_port* lp_com_uart_port;
        // Thread
        wxMutex *lp_data_wxmutex;
        wxCondition *lp_data_wxcondition;
};

/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*****************************************************END OF FILE************/

#endif // IN_JERRYSCRIPT_PORT_H_H_INCLUDED
