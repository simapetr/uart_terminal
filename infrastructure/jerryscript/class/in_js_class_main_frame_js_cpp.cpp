/**
  ****************************************************************************
  * @file    in_js_class_main_frame_js_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    25.04.2018
  * @brief   JerryScript wrapper for main_frame class
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
#include "in_js_class_main_frame_js_h.h"
#include "in_jerryscript_core_h.h"
#include "ap_uart_terminal_frame_h.h"

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @defgroup JerryScript
  * @brief JavaScript interpret
  * @{
  */

/**
  * @defgroup Class
  * @brief JavaScript class
  * @{
  */

/**
  * @defgroup main_frame
  * @brief Main frame interface
  * @{
  */

/**
  ****************************************************************************
  * Define
  ****************************************************************************
  */

#define d_buffer_size 4096

/**
  ****************************************************************************
  * Struct
  ****************************************************************************
  */

typedef struct
{
    uint32_t length_ui32;
    uint8_t data_sui8[d_buffer_size];
}send_buffer_t;

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

vector<send_buffer_t> lv_main_send_buffer;

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Registration object in to class
 *
 * @param [IN] p_gui_main_frame_void : Pointer on registered class
 * @param [IN] p_data_wxcondition : Rx data call event
 * @return void
 *
 */

void main_frame_js_c::reg_host_class (void* p_gui_main_frame_void, wxCondition *p_data_wxcondition)
{
jerry_value_t global_jerry_value;
jerry_value_t object_jerry_value;
jerry_value_t funct_jerry_value;
jerry_value_t name_jerry_value;

    this->lp_gui_main_frame_void = p_gui_main_frame_void;
    this->lp_data_wxcondition = p_data_wxcondition;
    // Create method
    object_jerry_value = jerry_create_object ();
    // GUI enable
    funct_jerry_value = jerry_create_external_function(this->gui);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"gui");
    jerry_set_property (object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Console enable
    funct_jerry_value = jerry_create_external_function(this->console_rx_enable);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"console_rx_enable");
    jerry_set_property (object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Console enable status
    funct_jerry_value = jerry_create_external_function(this->is_console_rx_enable);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"is_console_rx_enable");
    jerry_set_property (object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Print string (Different name for sole std printf overload)
    funct_jerry_value = jerry_create_external_function(this->js_printf);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"printf");
    jerry_set_property (object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Print status
    funct_jerry_value = jerry_create_external_function(this->status);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"status");
    jerry_set_property (object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Clear console
    funct_jerry_value = jerry_create_external_function(this->clear);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"clear");
    jerry_set_property (object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Open port
    funct_jerry_value = jerry_create_external_function(this->open);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"open");
    jerry_set_property (object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Close port
    funct_jerry_value = jerry_create_external_function(this->close);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"close");
    jerry_set_property (object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Get port open status
    funct_jerry_value = jerry_create_external_function(this->get_open_status);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"get_open_status");
    jerry_set_property (object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Get port open status
    funct_jerry_value = jerry_create_external_function(this->get_data);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"get_data");
    jerry_set_property (object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Get port open status
    funct_jerry_value = jerry_create_external_function(this->set_progress);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"set_progress");
    jerry_set_property (object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Event registration
    funct_jerry_value = jerry_create_external_function(this->reg_event);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"reg_event");
    jerry_set_property (object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Hide main frame
    funct_jerry_value = jerry_create_external_function(this->hide);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"hide");
    jerry_set_property (object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Create class
    global_jerry_value = jerry_get_global_object();
    name_jerry_value = jerry_create_string((const jerry_char_t*)"main_frame");
    jerry_set_property (global_jerry_value, name_jerry_value, object_jerry_value);

    funct_jerry_value = jerry_get_property (global_jerry_value, name_jerry_value);
    jerry_set_object_native_pointer(funct_jerry_value, this, NULL);
    // Release storage value
    jerry_release_value(name_jerry_value);
    jerry_release_value(object_jerry_value);
    return;
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

uint32_t main_frame_js_c::gui(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
main_frame_js_c* p_bkp_this = NULL;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<main_frame_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 1 && p_bkp_this)
        {
            if(jerry_value_is_boolean(p_args_ui32[0]))
            {
                // Call class method
                if (p_bkp_this)
                {
                    ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->gui((bool)p_args_ui32[0]);
                }
            }
        }
        else
        {
            printf("Error main_frame.gui wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_undefined();
}

/** @brief GUI enable console rx data (JS method "console_rx_enable")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t main_frame_js_c::console_rx_enable(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
main_frame_js_c* p_bkp_this = NULL;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<main_frame_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 1 && p_bkp_this)
        {
            if(jerry_value_is_boolean(p_args_ui32[0]))
            {
                // Call class method
                if (p_bkp_this)
                {
                    ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->console_rx_enable(jerry_get_boolean_value(p_args_ui32[0]));
                }
            }
        }
        else
        {
            printf("Error main_frame.console_rx_enable wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_undefined();
}

/** @brief GUI enable console rx data (JS method "is_console_rx_enable")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t main_frame_js_c::is_console_rx_enable(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
main_frame_js_c* p_bkp_this = NULL;
bool status_b = true;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<main_frame_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 0 && p_bkp_this)
        {
            // Call class method
            if (p_bkp_this)
            {
                status_b = ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->is_console_rx_enable();
            }
        }
        else
        {
            printf("Error main_frame.is_console_rx_enable wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_boolean(status_b);
}

/** @brief GUI textctrl console printf data (JS method "printf")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t main_frame_js_c::js_printf(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
main_frame_js_c* p_bkp_this = NULL;
wxString console_text_str;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<main_frame_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 1 && p_bkp_this)
        {
            if(jerry_value_is_string(p_args_ui32[0]))
            {
                // Read function argument
                const uint32_t data_len_ui32 = jerry_get_string_size(p_args_ui32[0]);
                uint8_t *p_data_sui8 = new uint8_t[data_len_ui32];
                jerry_string_to_char_buffer(p_args_ui32[0],p_data_sui8,data_len_ui32);
                // Convert to wxString
                console_text_str = wxEmptyString;
                for (uint32_t char_cnt_ui32 = 0 ; char_cnt_ui32 < data_len_ui32 ; char_cnt_ui32++)
                {
                    console_text_str += p_data_sui8[char_cnt_ui32];
                }
                delete[] p_data_sui8;
                // Call class method
                if (p_bkp_this)
                {
                    ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->js_printf(console_text_str);
                }
            }
        }
        else
        {
            printf("Error main_frame.printf wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_undefined();
}

/** @brief GUI StatusText status bar (JS method "status")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t main_frame_js_c::status(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
main_frame_js_c* p_bkp_this = NULL;
wxString console_text_str;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<main_frame_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 1 && p_bkp_this)
        {
            if(jerry_value_is_string(p_args_ui32[0]))
            {
                // Read function argument
                const uint32_t data_len_ui32 = jerry_get_string_size(p_args_ui32[0]);
                uint8_t *p_data_sui8 = new uint8_t[data_len_ui32];
                jerry_string_to_char_buffer(p_args_ui32[0],p_data_sui8,data_len_ui32);
                // Convert to wxString
                console_text_str = wxEmptyString;
                for (uint32_t char_cnt_ui32 = 0 ; char_cnt_ui32 < data_len_ui32 ; char_cnt_ui32++)
                {
                    console_text_str += p_data_sui8[char_cnt_ui32];
                }
                delete[] p_data_sui8;
                // Call class method
                if (p_bkp_this)
                {
                    ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->js_status(console_text_str);
                }
            }
        }
        else
        {
            printf("Error main_frame.status wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_undefined();
}

/** @brief GUI textctrl console clear data (JS method "clear")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t main_frame_js_c::clear(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
main_frame_js_c* p_bkp_this = NULL;
wxString console_text_str;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<main_frame_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 0 && p_bkp_this)
        {
            if (p_bkp_this)
            {
                ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->js_clear();
            }
        }
        else
        {
            printf("Error main_frame.clear wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_undefined();
}

/** @brief GUI Open port (JS method "open")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t main_frame_js_c::open(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
main_frame_js_c* p_bkp_this = NULL;
wxString console_text_str;
uart_cfg_t port_uart_cfg;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<main_frame_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 0 && p_bkp_this)
        {
            if (p_bkp_this)
            {
                ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->js_open_port();
            }
        }
        else if(args_cnt_ui32 == 6 && p_bkp_this)
        {
            if(
               jerry_value_is_number (p_args_ui32[0]) &&
               jerry_value_is_number (p_args_ui32[1]) &&
               jerry_value_is_number (p_args_ui32[2]) &&
               jerry_value_is_number (p_args_ui32[3]) &&
               jerry_value_is_number (p_args_ui32[4]) &&
               jerry_value_is_number (p_args_ui32[5])
              )
            {
                // Read function argument
                port_uart_cfg.bite_timeout_ui32 = (uint32_t)jerry_get_number_value(p_args_ui32[0]);
                port_uart_cfg.baudrate_ui32 = (uint32_t)jerry_get_number_value(p_args_ui32[1]);
                port_uart_cfg.stop_bits_ui8 = (uint8_t)jerry_get_number_value(p_args_ui32[2]);
                port_uart_cfg.parity_ui8 = (uint8_t)jerry_get_number_value(p_args_ui32[3]);
                port_uart_cfg.bit_length_ui8 = (uint8_t)jerry_get_number_value(p_args_ui32[4]);
                port_uart_cfg.port_num_ui8 = (uint8_t)jerry_get_number_value(p_args_ui32[5]);
                // Call class method
                if (p_bkp_this)
                {
                    ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->js_set_config(port_uart_cfg);
                    ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->js_open_port();
                }
            }
        }
        else
        {
            printf("Error main_frame.open wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_undefined();
}

/** @brief GUI close port (JS method "close")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t main_frame_js_c::close(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
main_frame_js_c* p_bkp_this = NULL;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<main_frame_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 0 && p_bkp_this)
        {
            if (p_bkp_this)
            {
                ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->js_close_port();
            }
        }
        else
        {
            printf("Error main_frame.close wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_undefined();
}

/** @brief GUI Get port open status (JS method "get_open_status")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t main_frame_js_c::get_open_status(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
main_frame_js_c* p_bkp_this = NULL;
uart_status_t open_uart_status = e_00_open_error;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<main_frame_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 0 && p_bkp_this)
        {
            if (p_bkp_this)
            {
                open_uart_status = ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->js_get_open_status();
            }
        }
        else
        {
            printf("Error main_frame.get_open_status wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_number((double)open_uart_status);
}

/** @brief GUI Get input text (JS method "get_data")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t main_frame_js_c::get_data(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
main_frame_js_c* p_bkp_this = NULL;
wxString text_str;
wxString data_str;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<main_frame_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 1 && p_bkp_this)
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
                data_str = ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->get_data(text_str);
            }
        }
        else
        {
            printf("Error main_frame.get_data wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_string((const jerry_char_t*)data_str.To8BitData().data());
}

/** @brief GUI Get input text (JS method "set_status")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t main_frame_js_c::set_progress(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
main_frame_js_c* p_bkp_this = NULL;
wxString text_str;
wxString data_str;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<main_frame_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 2 && p_bkp_this)
        {
            if(jerry_value_is_string(p_args_ui32[0]) && jerry_value_is_number(p_args_ui32[1]))
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
                ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->set_progress(text_str, jerry_get_number_value(p_args_ui32[1]));
            }
        }
        else if(args_cnt_ui32 == 1 && p_bkp_this)
        {
            if(jerry_value_is_number(p_args_ui32[0]))
            {
                ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->set_progress(wxEmptyString, jerry_get_number_value(p_args_ui32[0]));
            }
        }
        else
        {
            printf("Error main_frame.set_progress wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_undefined();
}

/** @brief Set GUI send data event (JS method "reg_event")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t main_frame_js_c::reg_event(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
uint32_t status_ui32 = 0;
void* p_arg_void;
main_frame_js_c* p_bkp_this = NULL;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<main_frame_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 1 && p_bkp_this)
        {
            if(jerry_value_is_string(p_args_ui32[0]))
            {
                // Reg event function name
                const uint32_t data_len_ui32 = jerry_get_string_size(p_args_ui32[0]);
                jerry_string_to_char_buffer(p_args_ui32[0],&p_bkp_this->l_rx_event_name_sui8[0],data_len_ui32);
                p_bkp_this->l_rx_event_name_sui8[data_len_ui32] = 0x00;
                // Reg function create
                p_bkp_this->l_global_ui32 = (uint32_t)jerry_get_global_object();
                if(p_bkp_this->l_global_ui32)
                {
                    p_bkp_this->l_reg_fct_ui32 = (uint32_t)jerry_get_property((jerry_value_t)p_bkp_this->l_global_ui32, p_args_ui32[0]);
                }
                ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->set_send_event(p_bkp_this->send_event, p_bkp_this);
                status_ui32 = 1;
            }
        }
        else
        {
            printf("Error main_frame.reg_event wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_number(status_ui32);
}

/** @brief Hide main frame (JS method "hide")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t main_frame_js_c::hide(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
main_frame_js_c* p_bkp_this = NULL;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<main_frame_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 1 && p_bkp_this)
        {
            if(jerry_value_is_boolean(p_args_ui32[0]))
            {
                // Set main frame visibility
                ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->js_hide(!jerry_get_boolean_value(p_args_ui32[0]));
            }
        }
        else
        {
            printf("Error main_frame.hide wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_undefined();
}

/** @brief Call Tx data send event (Must be called form JS thread)
 *
 * @param [IN] p_parametr_void : Handle on registered object
 * @return uint32_t : number of item in UART buffer
 *
 */

uint32_t main_frame_js_c::call(void* p_parametr_void)
{
main_frame_js_c *p_bkp_this = (main_frame_js_c*)p_parametr_void;
static send_buffer_t data_send_buffer;
jerry_value_t val_args[1];
jerry_value_t data_item_val;
jerry_value_t eval_ret;

    if(lv_main_send_buffer.size())
    {
        // Get data from fifo
        data_send_buffer = lv_main_send_buffer[0];
        lv_main_send_buffer.erase(lv_main_send_buffer.begin() + 0);
        // Set parameters
        for (uint32_t data_cnt_ui32 = 0; data_cnt_ui32 < data_send_buffer.length_ui32 ; data_cnt_ui32++)
        {
            data_item_val = jerry_create_number(double(data_send_buffer.data_sui8[data_cnt_ui32]));
            eval_ret = jerry_set_property_by_index (val_args[0], data_cnt_ui32, data_item_val);
            jerry_release_value (eval_ret);
            jerry_release_value (data_item_val);
        }
        // Call function
        if (p_bkp_this->l_reg_fct_ui32 && p_bkp_this->l_global_ui32)
        {
            eval_ret = jerry_call_function (p_bkp_this->l_reg_fct_ui32, p_bkp_this->l_global_ui32, val_args, 1);
            jerry_release_value (eval_ret);
        }
        // Clear buffer item
        jerry_release_value (val_args[0]);
    }
    return lv_main_send_buffer.size();
}

/**
  ****************************************************************************
  * Private
  ****************************************************************************
  */


/** @brief Data in UART buffer event
 *
 * @param [IN] p_parametr_void : Handle on registered object
 * @param [IN] event_type_ui32 : Event type field
 * @param [IN] p_data_sui8 : Buffer with data
 * @param [IN] length_ui32 : Data length
 * @return void
 *
 */

void main_frame_js_c::send_event(void* p_parametr_void, uint8_t *p_data_sui8, uint32_t length_ui32)
{
main_frame_js_c *p_bkp_this = (main_frame_js_c*)p_parametr_void;
uint32_t data_cnt_ui32;
send_buffer_t data_send_buffer;

    // Save length
    if (length_ui32 > d_buffer_size)
    {
        data_send_buffer.length_ui32 = d_buffer_size;
    }
    else
    {
        data_send_buffer.length_ui32 = length_ui32;
    }
    // Set data
    for(data_cnt_ui32 = 0 ; data_cnt_ui32 < data_send_buffer.length_ui32 ; data_cnt_ui32++)
    {
        data_send_buffer.data_sui8[data_cnt_ui32] = p_data_sui8[data_cnt_ui32];
    }
    // Save data
    lv_main_send_buffer.push_back(data_send_buffer);
    // Set event
    p_bkp_this->lp_data_wxcondition->Broadcast();
    return;
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

/**
* @}
*/

/*****************************************************END OF FILE************/
