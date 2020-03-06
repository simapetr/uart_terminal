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
#include <wx/time.h>
#include "in_jerryscript_port_h.h"
#include "in_jerryscript_core_h.h"
#include "in_jerryscript_debugger_h.h"
#include "ap_uart_terminal_frame_h.h"

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @defgroup JerryScript
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
  * Struct
  ****************************************************************************
  */

typedef struct
{
    wxString event_str;
    uint32_t component_id_ui32;
}event_buffer_t;

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

bool l_in_js_port_gui_enable_b = false;
vector<event_buffer_t> lv_main_event_buffer;

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
    // Set initialization flag
    this->l_init_flag_b = init_b;
    // Initialize GUI window
    this->lp_data_gui_frame = new gui_frame((wxWindow*)this->lp_gui_main_frame_void, this);
    this->lp_data_gui_frame->Show();
    // Create wait event
    this->lp_data_wxmutex = new wxMutex();
    if(this->lp_data_wxmutex)
    {
        this->lp_data_wxcondition = new wxCondition(*this->lp_data_wxmutex);
    }
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
    // Stop interpreter
    this->stop();
    // Delete frame
    delete this->lp_data_gui_frame;
    this->lp_data_gui_frame = NULL;
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
    // Run working thread
    this->lp_script_thread = new thread_c(this, this->worker);
    this->lp_script_thread->SetPriority(wxPRIORITY_MAX);
    wxMilliSleep(10);
    // Create Worker thread
    if(this->lp_script_thread)
    {
        // Run script
        this->lp_script_thread->signal();
    }
    else
    {
        status_ui32 = 0;
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
    if(this->l_run_script_ui8)
    {
        // Stop script
        this->l_run_script_ui8 = 0;
        wxMilliSleep(50);
        this->lp_data_wxcondition->Broadcast();
        wxMilliSleep(50);
        // Stop thread
        this->lp_script_thread->stop();
        wxMilliSleep(400);
    }
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
event_buffer_t data_event_buffer;

    // Set data
    data_event_buffer.event_str = event_str;
    data_event_buffer.component_id_ui32 = component_id_ui32;
    // Save in to buffer
    lv_main_event_buffer.push_back(data_event_buffer);
    // Set event
    this->lp_data_wxcondition->Broadcast();
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
    this->l_data_timer_js.reg_host_class();
    this->l_data_time_js.reg_host_class();
    this->l_data_file_js.reg_host_class();
    this->l_port_uart_js.reg_host_class(this->lp_com_uart_port, this->lp_data_wxcondition);
    this->l_gui_main_frame_js.reg_host_class(this->lp_gui_main_frame_void, this->lp_data_wxcondition);
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
    this->l_data_timer_js.dereg_host_class();
    this->l_port_uart_js.dereg_host_class();
    return;
}

/** @brief Call GUI event (Must be called form JS thread)
 *
 * @param void
 * @return uint32_t : number of item in UART buffer
 *
 */

uint32_t jerryscript_c::call(void)
{
static event_buffer_t data_event_buffer;
jerry_value_t global_obj;
jerry_value_t sys_name;
jerry_value_t sysloop_func;
jerry_value_t val_args[1];
uint16_t val_argv = 1;

    if(lv_main_event_buffer.size())
    {
        // Get global object
        global_obj = jerry_get_global_object();
        // Get data from fifo
        data_event_buffer = lv_main_event_buffer[0];
        lv_main_event_buffer.erase(lv_main_event_buffer.begin() + 0);
        // Get function reference
        sys_name = jerry_create_string ((const jerry_char_t*)data_event_buffer.event_str.To8BitData().data());
        sysloop_func = jerry_get_property (global_obj, sys_name);
        // Call function
        if (sysloop_func != 4)
        {
            // Create function argument
            val_args[0] = jerry_create_number(data_event_buffer.component_id_ui32);
            // Call function
            jerry_call_function(sysloop_func, global_obj, val_args, val_argv);
        }
        // Release all used variable
        jerry_release_value (val_args[0]);
        jerry_release_value (global_obj);
        jerry_release_value (sysloop_func);
        jerry_release_value (sys_name);
    }
    return lv_main_event_buffer.size();
}

/**
  ****************************************************************************
  * Private
  ****************************************************************************
  */

/** @brief Script RUN thread
 *
 * @param void
 * @return wxThread::ExitCode : thread end status
 *
 */

void jerryscript_c::worker(void* p_parametr_void)
{
jerryscript_c* p_bkp_this = (jerryscript_c*)p_parametr_void;
static jerry_value_t eval_ret_jerry_value;
config_ini *p_position_config_ini;
wxString perspective_str;
int pos_x_int = 0;
int pos_y_int = 0;
int siz_w_int = 0;
int siz_h_int = 0;

    // Run thread
    p_bkp_this->l_run_script_ui8 = 1;
    // Interpreter initialization
    if (!p_bkp_this->l_init_flag_b)
    {
        p_bkp_this->l_init_flag_b = true;
        jerry_init (JERRY_INIT_EMPTY);
        // Set Debug
        if (p_bkp_this->l_debug_b)
        {
            // Initialization debug server
            jerryx_debugger_after_connect (jerryx_debugger_tcp_create (5001) && jerryx_debugger_ws_create ());
        }
    }
    // Reg all class
    p_bkp_this->reg_class();
    // Run script
    if(p_bkp_this->l_jerryscript_code_str != wxEmptyString)
    {
        eval_ret_jerry_value = jerry_eval((const jerry_char_t*) p_bkp_this->l_jerryscript_code_str.To8BitData().data(), p_bkp_this->l_jerryscript_code_str.Length(), false);
        jerry_release_value (eval_ret_jerry_value);
    }
    // Reload window and AUI position
    if (p_bkp_this->lp_data_gui_frame != NULL && ((main_frame*)(p_bkp_this->lp_gui_main_frame_void)) != NULL)
    {
        p_position_config_ini = ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->get_project();
        pos_x_int = p_position_config_ini->get_value(wxT("POSITION/pos_x"), wxT("10"));
        pos_y_int = p_position_config_ini->get_value(wxT("POSITION/pos_y"), wxT("10"));
        p_bkp_this->lp_data_gui_frame->Move(wxPoint(pos_x_int, pos_y_int));
        if (p_position_config_ini->get_value(wxT("POSITION/siz_exp"), wxT("0")))
        {
            p_bkp_this->lp_data_gui_frame->Maximize();
        }
        else
        {
            siz_w_int = p_position_config_ini->get_value(wxT("POSITION/siz_w"), wxT("800"));
            siz_h_int = p_position_config_ini->get_value(wxT("POSITION/siz_h"), wxT("500"));
            p_bkp_this->lp_data_gui_frame->SetClientSize(wxSize(siz_w_int, siz_h_int));
        }
        // Load perspective
        perspective_str = p_position_config_ini->get_string(wxT("POSITION/perspective"),wxT(""));
        if(perspective_str != wxEmptyString)
        {
            // Load AUI position
            wxMilliSleep(10);
            p_bkp_this->lp_data_gui_frame->get_aui_manager()->LoadPerspective(perspective_str);
        }
    }
    while(p_bkp_this->l_run_script_ui8)
    {
        if(p_bkp_this->lp_data_wxcondition)
        {
            switch(p_bkp_this->lp_data_wxcondition->WaitTimeout(1))
            {
                case wxCOND_NO_ERROR:
                {
                    // Call Rx data event
                    while(p_bkp_this->l_port_uart_js.call(&p_bkp_this->l_port_uart_js)){}
                    // Call GUI event
                    while(p_bkp_this->call()){}
                    // Call main frame event
                    while(p_bkp_this->l_gui_main_frame_js.call(&p_bkp_this->l_gui_main_frame_js)){}
                    // Prevent timer call
                    p_bkp_this->l_data_timer_js.call(&p_bkp_this->l_data_timer_js);
                }
                break;
                case wxCOND_TIMEOUT:
                {
                    p_bkp_this->l_data_timer_js.call(&p_bkp_this->l_data_timer_js);
                }
                break;
                default:
                {

                }
                break;
            }
        }
    }
    // Save frame and AUI position
    if (p_bkp_this->lp_data_gui_frame != NULL && ((main_frame*)(p_bkp_this->lp_gui_main_frame_void)) != NULL)
    {
        p_position_config_ini = ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->get_project();
        p_position_config_ini->set_string(wxT("POSITION/perspective"),p_bkp_this->lp_data_gui_frame->get_aui_manager()->SavePerspective());
        // Save window position
        p_bkp_this->lp_data_gui_frame->GetPosition(&pos_x_int, &pos_y_int);
        p_position_config_ini->set_value(wxT("POSITION/pos_x"), pos_x_int);
        p_position_config_ini->set_value(wxT("POSITION/pos_y"), pos_y_int);
        if (p_bkp_this->lp_data_gui_frame->IsMaximized())
        {
            p_position_config_ini->set_value(wxT("POSITION/siz_exp"), 1);
        }
        else
        {
            p_bkp_this->lp_data_gui_frame->GetClientSize(&siz_w_int, &siz_h_int);
            p_position_config_ini->set_value(wxT("POSITION/siz_w"), siz_w_int);
            p_position_config_ini->set_value(wxT("POSITION/siz_h"), siz_h_int);
            p_position_config_ini->set_value(wxT("POSITION/siz_exp"), 0);
        }
    }
    // Unregister class
    p_bkp_this->dereg_class();
    wxMilliSleep(100);
    // Initialize engine
    //jerry_cleanup();
    //wxMilliSleep(100);
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
    else
    {
        printf("Error delay wrong parameter\n");
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
    else
    {
        printf("Error alert wrong parameter\n");
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
