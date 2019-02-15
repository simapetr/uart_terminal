/**
  ****************************************************************************
  * @file    in_jerryscript_port_cpp.cpp
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

#include <wx/utils.h>
#include <wx/msgdlg.h>
#include "in_jerryscript_port_h.h"
#include "in_jerryscript_core_h.h"
#include "debugger.h"
#include "ap_uart_terminal_frame_h.h"

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @defgroup JavaScript
  * @brief Basic JavaScript interpreter
  * @{
  */

/**
  * @defgroup Port
  * @brief JavaScript interpreter port
  * @{
  */

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

bool l_in_js_port_gui_enable_b = false;

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Constructor
 *
 * @param [IN] p_com_uart_port : Communication port object
 * @param [IN] p_gui_main_frame_void : GUI frame pointer
 * @param [IN] debug_b : Script debug enable
 * @param [IN] init_b : Jerry script core initialization
 * @return void
 *
 */

jerryscript_c::jerryscript_c( uart_port* p_com_uart_port, void* p_gui_main_frame_void, bool debug_b, bool init_b)
{
    // Save parent window
    this->lp_gui_main_frame_void = p_gui_main_frame_void;
    // Save debug status
    this->l_debug_b = debug_b;
    // Save port
    this->lp_com_uart_port = p_com_uart_port;
    // Set thread var
    this->lp_worker_jerryscript_thread_c = NULL;
    // Set RUN status
    this->l_run_flag_b = false;
    // Set initialization flag
    this->l_init_flag_b = init_b;
    // Initialize GUI window
    this->lp_data_gui_frame = new gui_frame((wxWindow*)this->lp_gui_main_frame_void, this);
    this->lp_data_gui_frame->Show();
    return;
}

/** @brief Destructor
 *
 * @param void
 * @return void
 *
 */

jerryscript_c::~jerryscript_c( void )
{
    delete this->lp_data_gui_frame;
    this->lp_data_gui_frame = NULL;
    // Stop interpreter
    this->stop();
    return;
}

/** @brief Run script
 *
 * @param [IN] script_str : Script text
 * @return uint32_t : Run status
 *
 */

uint32_t jerryscript_c::run(wxString script_str)
{
uint32_t status_ui32 = 1;

    // Save script
    this->l_jerryscript_code_str = script_str;
    // Create Worker thread
    if(this->lp_worker_jerryscript_thread_c == NULL)
    {
        // Run script
        this->lp_worker_jerryscript_thread_c = new jerryscript_thread_c(this);
        if ( this->lp_worker_jerryscript_thread_c->Run() != wxTHREAD_NO_ERROR )
        {
            delete this->lp_worker_jerryscript_thread_c;
            this->lp_worker_jerryscript_thread_c = NULL;
            status_ui32 = 0;
        }
    }
    else
    {
        if ( !this->lp_worker_jerryscript_thread_c->IsRunning() )
        {
            if ( this->lp_worker_jerryscript_thread_c->Run() != wxTHREAD_NO_ERROR )
            {
                delete this->lp_worker_jerryscript_thread_c;
                this->lp_worker_jerryscript_thread_c = NULL;
                status_ui32 = 0;
            }
        }
        else
        {
            status_ui32 = 2;
        }
    }
    return status_ui32;
}

/** @brief Stop script
 *
 * @param void
 * @return void
 *
 */

void jerryscript_c::stop (void)
{
config_ini *p_position_config_ini;
int pos_x_int = 0;
int pos_y_int = 0;
int siz_w_int = 0;
int siz_h_int = 0;

    if (this->lp_data_gui_frame != NULL && ((main_frame*)(this->lp_gui_main_frame_void)) != NULL)
    {
        p_position_config_ini = ((main_frame*)(this->lp_gui_main_frame_void))->get_project();
        p_position_config_ini->set_string(wxT("POSITION/perspective"),this->lp_data_gui_frame->get_aui_manager()->SavePerspective());
        // Save window position
        this->lp_data_gui_frame->GetPosition(&pos_x_int, &pos_y_int);
        p_position_config_ini->set_value(wxT("POSITION/pos_x"), pos_x_int);
        p_position_config_ini->set_value(wxT("POSITION/pos_y"), pos_y_int);
        if (this->lp_data_gui_frame->IsMaximized())
        {
            p_position_config_ini->set_value(wxT("POSITION/siz_exp"), 1);
        }
        else
        {
            this->lp_data_gui_frame->GetClientSize(&siz_w_int, &siz_h_int);
            p_position_config_ini->set_value(wxT("POSITION/siz_w"), siz_w_int);
            p_position_config_ini->set_value(wxT("POSITION/siz_h"), siz_h_int);
            p_position_config_ini->set_value(wxT("POSITION/siz_exp"), 0);
        }
    }

    wxMilliSleep(100);
    this->l_run_flag_b = false;
    wxMilliSleep(100);
    // Terminate Worker thread
    if(this->lp_worker_jerryscript_thread_c)
    {
        this->lp_worker_jerryscript_thread_c->Kill();
    }
    wxMilliSleep(100);
    return;
}

/** @brief Call JS event function
 *
 * @param [IN] event_str : Event function name
 * @param [IN] component_id_ui32 : GUI component buffer index
 * @return void
 *
 */

void jerryscript_c::call_event (wxString event_str, uint32_t component_id_ui32)
{
jerry_value_t global_obj = jerry_get_global_object ();
jerry_value_t sys_name = jerry_create_string ((const jerry_char_t*)event_str.To8BitData().data());
jerry_value_t sysloop_func = jerry_get_property (global_obj, sys_name);

    if (sysloop_func != 4)
    {
        jerry_value_t val_args[1];
        uint16_t val_argv = 1;
        // Create function argument
        val_args[0] = jerry_create_number(component_id_ui32);
        // Call function
        jerry_call_function(sysloop_func, global_obj, val_args, val_argv);
        jerry_release_value (val_args[0]);
    }
    jerry_release_value (global_obj);
    jerry_release_value (sysloop_func);
    jerry_release_value (sys_name);
    return;
}

/** @brief Register JS class
 *
 * @param void
 * @return void
 *
 */

void jerryscript_c::reg_class (void)
{
jerry_value_t global_jerry_value;
jerry_value_t funct_jerry_value;
jerry_value_t name_jerry_value;

    // Read global object
    global_jerry_value = jerry_get_global_object();
    // Register Delay (in ms)
    funct_jerry_value = jerry_create_external_function(this->delay);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"delay");
    jerry_set_property(global_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Register Alert info dialog
    funct_jerry_value = jerry_create_external_function(this->alert);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"alert");
    jerry_set_property(global_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Register GUI frame control
    funct_jerry_value = jerry_create_external_function(this->gui);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"gui");
    jerry_set_property(global_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Register this pointer
    jerry_set_object_native_pointer(global_jerry_value, this, NULL);
    jerry_release_value(global_jerry_value);
    // Register GUI class
    this->l_data_time_js.reg_host_class();
    this->l_data_file_js.reg_host_class();
    this->l_port_uart_js.reg_host_class(this->lp_com_uart_port);
    this->l_gui_main_frame_js.reg_host_class(this->lp_gui_main_frame_void);
    this->l_gui_panel_js.reg_host_class(this->lp_data_gui_frame);
    this->l_gui_sizer_js.reg_host_class(this->lp_data_gui_frame);
    this->l_gui_graph_js.reg_host_class(this->lp_data_gui_frame);
    this->l_gui_button_js.reg_host_class(this->lp_data_gui_frame);
    this->l_gui_slider_js.reg_host_class(this->lp_data_gui_frame);
    this->l_gui_static_text_js.reg_host_class(this->lp_data_gui_frame);
    this->l_gui_textctrl_js.reg_host_class(this->lp_data_gui_frame);
    this->l_gui_check_box_js.reg_host_class(this->lp_data_gui_frame);
    this->l_gui_gauge_js.reg_host_class(this->lp_data_gui_frame);
    return;
}

/** @brief Deregister JS class
 *
 * @param void
 * @return void
 *
 */

void jerryscript_c::dereg_class (void)
{
    this->l_port_uart_js.dereg_host_class();
    return;
}

/**
  ****************************************************************************
  * Local function
  ****************************************************************************
  */

/** @brief Script RUN thread
 *
 * @param void
 * @return wxThread::ExitCode : thread end status
 *
 */

wxThread::ExitCode jerryscript_thread_c::Entry()
{
static jerry_value_t eval_ret_jerry_value;
config_ini *p_position_config_ini;

    // Interpreter initialization
    if (!this->lp_object_jerryscript->l_init_flag_b)
    {
        this->lp_object_jerryscript->l_init_flag_b = true;
        jerry_init (JERRY_INIT_EMPTY);
        // Set Debug
        if (this->lp_object_jerryscript->l_debug_b)
        {
            // Initialization debug server
            jerryx_debugger_after_connect (jerryx_debugger_tcp_create (5001) && jerryx_debugger_ws_create ());
        }
    }
    // Reg all class
    this->lp_object_jerryscript->reg_class();
    // Run script
    if(this->lp_object_jerryscript->l_jerryscript_code_str != wxEmptyString)
    {
        this->lp_object_jerryscript->l_run_flag_b = true;
        eval_ret_jerry_value = jerry_eval((const jerry_char_t*) this->lp_object_jerryscript->l_jerryscript_code_str.To8BitData().data(), this->lp_object_jerryscript->l_jerryscript_code_str.Length(), false);
        jerry_release_value (eval_ret_jerry_value);
    }
    if (this->lp_object_jerryscript->lp_data_gui_frame != NULL && ((main_frame*)(this->lp_object_jerryscript->lp_gui_main_frame_void)) != NULL)
    {
        p_position_config_ini = ((main_frame*)(this->lp_object_jerryscript->lp_gui_main_frame_void))->get_project();
        this->lp_object_jerryscript->lp_data_gui_frame->Move(wxPoint(p_position_config_ini->get_value(wxT("POSITION/pos_x"), wxT("10")),p_position_config_ini->get_value(wxT("POSITION/pos_y"), wxT("10"))));
        if (p_position_config_ini->get_value(wxT("POSITION/siz_exp"), wxT("0")))
        {
            this->lp_object_jerryscript->lp_data_gui_frame->Maximize();
        }
        else
        {
            this->lp_object_jerryscript->lp_data_gui_frame->SetClientSize(wxSize(p_position_config_ini->get_value(wxT("POSITION/siz_w"), wxT("800")), p_position_config_ini->get_value(wxT("POSITION/siz_h"), wxT("500"))));
        }
        // Load AUI position
        this->lp_object_jerryscript->lp_data_gui_frame->get_aui_manager()->LoadPerspective(p_position_config_ini->get_string(wxT("POSITION/perspective"),wxT("")));
        // Update AUI manager
        this->lp_object_jerryscript->lp_data_gui_frame->get_aui_manager()->Update();
    }
    // Wait for script termination
    while (this->lp_object_jerryscript->l_run_flag_b)
    {
        wxMilliSleep(10);
    }
    // Unregister class
    this->lp_object_jerryscript->dereg_class();
    wxMilliSleep(100);
    // Free interpreter memory
    jerry_cleanup();
    wxMilliSleep(100);
    return (wxThread::ExitCode)0;
}

/** @brief Script thread destructor
 *
 * @param void
 * @return void
 *
 */

jerryscript_thread_c::~jerryscript_thread_c()
{
    wxCriticalSectionLocker enter(this->lp_object_jerryscript->l_jerryscript_thread_wxcriticalSection);
    // the thread is being destroyed; make sure not to leave dangling pointers around
    this->lp_object_jerryscript->lp_worker_jerryscript_thread_c = NULL;
    return;
}

/** @brief Delay in ms (JS function "delay")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t jerryscript_c::delay(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
    // Extract function argument
    if(args_cnt_ui32 == 1)
    {
        if(jerry_value_is_number(p_args_ui32[0]))
        {
            wxMilliSleep((uint32_t)jerry_get_number_value(p_args_ui32[0]));
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_undefined();
}

/** @brief Alert info dialog (JS function "alert")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t jerryscript_c::alert(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
wxString text_str;

    // Extract function argument
    if(args_cnt_ui32 == 1)
    {
        if(jerry_value_is_string(p_args_ui32[0]))
        {
            // Read function argument
            const uint32_t data_len_ui32 = jerry_get_string_size(p_args_ui32[0]);
            uint8_t *p_data_sui8 = new uint8_t[data_len_ui32];
            jerry_string_to_char_buffer(p_args_ui32[0],p_data_sui8,data_len_ui32);
            // Convert to wxString
            text_str = wxEmptyString;
            for (uint32_t char_cnt_ui32 = 0 ; char_cnt_ui32 < data_len_ui32 ; char_cnt_ui32++)
            {
                text_str += p_data_sui8[char_cnt_ui32];
            }
            delete[] p_data_sui8;
            // Call class method
            wxMessageBox( text_str, wxT("Alert"));
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_undefined();
}

/** @brief GUI base function (JS function "gui")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t jerryscript_c::gui(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
jerryscript_c* p_bkp_this = NULL;
wxString text_str = wxEmptyString;
uint32_t data_len_ui32;
static uint8_t *p_data_sui8 = NULL;

    if(jerry_get_object_native_pointer(jerry_get_global_object(), &p_arg_void, NULL))
    {
         // Extract this
        p_bkp_this = reinterpret_cast<jerryscript_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 1 && p_bkp_this)
        {
            if(jerry_value_is_boolean(p_args_ui32[0]))
            {
                p_bkp_this->lp_data_gui_frame->frame_show(jerry_get_boolean_value(p_args_ui32[0]), wxT("GUI application"));
            }
        }
        else if(args_cnt_ui32 == 2 && p_bkp_this)
        {
            if(
               jerry_value_is_boolean(p_args_ui32[0]) &&
               jerry_value_is_string(p_args_ui32[1])
              )
            {
                data_len_ui32 = jerry_get_string_size(p_args_ui32[1]);
                p_data_sui8 = new uint8_t[data_len_ui32];
                jerry_string_to_char_buffer(p_args_ui32[1],p_data_sui8,data_len_ui32);
                text_str = wxEmptyString;
                for (uint32_t char_cnt_ui32 = 0 ; char_cnt_ui32 < data_len_ui32 ; char_cnt_ui32++)
                {
                    text_str += p_data_sui8[char_cnt_ui32];
                }
                delete[] p_data_sui8;
                p_bkp_this->lp_data_gui_frame->frame_show(jerry_get_boolean_value(p_args_ui32[0]), text_str);
            }
        }
        else if(args_cnt_ui32 == 3 && p_bkp_this)
        {
            if(
               jerry_value_is_boolean(p_args_ui32[0]) &&
               jerry_value_is_string(p_args_ui32[1]) &&
               jerry_value_is_boolean(p_args_ui32[2])
              )
            {
                data_len_ui32 = jerry_get_string_size(p_args_ui32[1]);
                p_data_sui8 = new uint8_t[data_len_ui32];
                jerry_string_to_char_buffer(p_args_ui32[1],p_data_sui8,data_len_ui32);
                text_str = wxEmptyString;
                for (uint32_t char_cnt_ui32 = 0 ; char_cnt_ui32 < data_len_ui32 ; char_cnt_ui32++)
                {
                    text_str += p_data_sui8[char_cnt_ui32];
                }
                delete[] p_data_sui8;
                p_bkp_this->lp_data_gui_frame->frame_show(jerry_get_boolean_value(p_args_ui32[0]), text_str);
                ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->Show(jerry_get_boolean_value(p_args_ui32[2]));
            }
        }
        else
        {

        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_undefined();
}

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
