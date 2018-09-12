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
  * Function
  ****************************************************************************
  */

/** @brief Registration object in to class
 *
 * @param [IN] p_gui_main_frame_void : Pointer on registered class
 * @return void
 *
 */

void main_frame_js_c::reg_host_class (void* p_gui_main_frame_void)
{
jerry_value_t global_jerry_value;
jerry_value_t object_jerry_value;
jerry_value_t funct_jerry_value;
jerry_value_t name_jerry_value;

    this->lp_gui_main_frame_void = p_gui_main_frame_void;
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
    // Print string
    funct_jerry_value = jerry_create_external_function(this->printf);
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

uint32_t main_frame_js_c::printf(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
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
                    ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->printf(console_text_str);
                }
            }
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
                    ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->status(console_text_str);
                }
            }
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
                ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->clear();
            }
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
                ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->open_port();
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
                    ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->set_config(port_uart_cfg);
                    ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->open_port();
                }
            }
        }
        else
        {
            if (p_bkp_this)
            {
                ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->status(wxT("Error main_frame.open wrong parameter\n"));
            }
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
                ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->close_port();
            }
        }
        else
        {
            if (p_bkp_this)
            {
                ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->status(wxT("Error main_frame.close wrong parameter\n"));
            }
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
                open_uart_status = ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->get_open_status();
            }
        }
        else
        {
            if (p_bkp_this)
            {
                ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->printf(wxT("Error main_frame.get_open_status wrong parameter\n"));
            }
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
                ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->set_send_event(p_bkp_this->send_event, p_bkp_this);
                status_ui32 = 1;
            }
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_number(status_ui32);
}

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
jerry_value_t global_obj = jerry_get_global_object ();
jerry_value_t sys_name = jerry_create_string ((const jerry_char_t*)&p_bkp_this->l_rx_event_name_sui8[0]);
jerry_value_t sysloop_func = jerry_get_property (global_obj, sys_name);

    jerry_release_value (sys_name);

    if (jerry_value_has_error_flag (sysloop_func))
    {
        jerry_release_value (global_obj);
        jerry_release_value (sysloop_func);
    }
    else
    {
        if (!jerry_value_is_function (sysloop_func))
        {
            jerry_release_value (global_obj);
            jerry_release_value (sysloop_func);
        }
        else
        {
            // Call function
            jerry_value_t val_args[1];
            uint16_t val_argv = 1;
            val_args[0] = jerry_create_array(length_ui32);
            // Set data array
            for (uint32_t data_cnt_ui32 = 0; data_cnt_ui32 < length_ui32; data_cnt_ui32++)
            {
                jerry_value_t data_jerry_value = jerry_create_number(double(p_data_sui8[data_cnt_ui32]));
                jerry_set_property_by_index (val_args[0], data_cnt_ui32, jerry_value_to_number(data_jerry_value));
                jerry_release_value(data_jerry_value);
            }
            // Call function
            if (jerry_value_has_error_flag(jerry_call_function (sysloop_func, global_obj, val_args, val_argv)))
            {
                //char status = -3;
            }
            jerry_release_value (val_args[0]);
        }
    }
    jerry_release_value (global_obj);
    jerry_release_value (sysloop_func);
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
