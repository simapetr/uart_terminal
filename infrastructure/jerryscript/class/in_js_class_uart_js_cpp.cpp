/**
  ****************************************************************************
  * @file    in_js_class_uart_js_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    18.04.2018
  * @brief   JerryScript wrapper for uart_port class
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
#include "in_js_class_uart_js_h.h"
#include "in_jerryscript_core_h.h"

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
  * @defgroup UART
  * @brief UART class definition
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
    uint32_t event_type_ui32;
    uint32_t length_ui32;
    uint8_t data_sui8[d_buffer_size];
}packet_buffer_t;

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

vector<packet_buffer_t> lv_main_packet_buffer;

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Registration object in to class
 *
 * @param [IN] p_com_uart_port : Pointer on registered class
 * @param [IN] p_data_wxcondition : Rx data call event
 * @return void
 *
 */

void uart_js_c::reg_host_class (uart_port* p_com_uart_port, wxCondition *p_data_wxcondition)
{
jerry_value_t global_jerry_value;
jerry_value_t object_jerry_value;
jerry_value_t funct_jerry_value;
jerry_value_t name_jerry_value;

    this->lp_com_uart_port = p_com_uart_port;
    this->lp_data_wxcondition = p_data_wxcondition;
    // Create method
    object_jerry_value = jerry_create_object ();
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
    // Event registration
    funct_jerry_value = jerry_create_external_function(this->reg_event);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"reg_event");
    jerry_set_property (object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Write bite
    funct_jerry_value = jerry_create_external_function(this->write);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"write");
    jerry_set_property (object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Get control
    funct_jerry_value = jerry_create_external_function(this->get_ctrl);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"get_ctrl");
    jerry_set_property (object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Set control
    funct_jerry_value = jerry_create_external_function(this->set_ctrl);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"set_ctrl");
    jerry_set_property (object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Create class
    global_jerry_value = jerry_get_global_object();
    name_jerry_value = jerry_create_string((const jerry_char_t*)"uart");
    jerry_set_property (global_jerry_value, name_jerry_value, object_jerry_value);

    funct_jerry_value = jerry_get_property (global_jerry_value, name_jerry_value);
    jerry_set_object_native_pointer(funct_jerry_value, this, NULL);
    // Release storage value
    jerry_release_value(name_jerry_value);
    jerry_release_value(object_jerry_value);
    // Initialize value
    this->l_reg_fct_ui32 = 0;
    this->l_global_ui32 = 0;
    // Initialization Rx event function name
    this->l_rx_event_name_sui8[0] = 0x00;
    return;
}

/** @brief Deregistration object in to class
 *
 * @param void
 * @return void
 *
 */

void uart_js_c::dereg_host_class (void)
{
    this->lp_com_uart_port->clear(this->rx_event);
    return;
}

/** @brief Open UART port (JS method "open")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t uart_js_c::open(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
double status_d = 0;
void* p_arg_void;
uart_js_c* p_bkp_this = NULL;
uart_cfg_t port_uart_cfg;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<uart_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 6 && p_bkp_this)
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
                    status_d = p_bkp_this->lp_com_uart_port->open(&port_uart_cfg);
                }
            }
        }
        else
        {
            printf("Error uart.open wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_number(status_d);
}

/** @brief Close UART port (JS method "close")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t uart_js_c::close(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
uart_js_c* p_bkp_this = NULL;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<uart_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 0 && p_bkp_this)
        {
            // Call class method
            if (p_bkp_this)
            {
                wxMilliSleep(100);
                p_bkp_this->lp_com_uart_port->close();
            }
        }
        else
        {
            printf("Error uart.close wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_undefined();
}

/** @brief Set Rx event (JS method "reg_event")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t uart_js_c::reg_event(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
uint32_t status_ui32 = 0;
void* p_arg_void;
uart_js_c* p_bkp_this = NULL;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<uart_js_c*>(p_arg_void);
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
                p_bkp_this->lp_com_uart_port->set(p_bkp_this->rx_event, p_bkp_this);
                status_ui32 = 1;
            }
        }
        else
        {
            printf("Error uart.reg_event wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_number(status_ui32);
}

/** @brief Write UART (JS method "write")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t uart_js_c::write(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
double status_d = 0;
void* p_arg_void;
uart_js_c* p_bkp_this = NULL;
uint32_t data_cnt_ui32;
packet_buffer_t data_packet_buffer;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<uart_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 1 && p_bkp_this)
        {
            if(jerry_value_is_number (p_args_ui32[0]))
            {
                // Call class method
                data_packet_buffer.length_ui32 = 1;
                data_packet_buffer.data_sui8[0] = (uint8_t)jerry_get_number_value(p_args_ui32[0]);
                status_d = (double)p_bkp_this->lp_com_uart_port->send(data_packet_buffer.data_sui8, data_packet_buffer.length_ui32);
            }
            else if (jerry_value_is_array (p_args_ui32[0]))
            {
                // Call class method
                data_packet_buffer.length_ui32 = jerry_get_array_length(p_args_ui32[0]);
                if (data_packet_buffer.length_ui32 > d_buffer_size)
                {
                    data_packet_buffer.length_ui32 = d_buffer_size;
                }
                for (data_cnt_ui32 = 0; data_cnt_ui32 < data_packet_buffer.length_ui32; data_cnt_ui32++)
                {
                    data_packet_buffer.data_sui8[data_cnt_ui32] = (uint8_t)jerry_get_number_value(jerry_get_property_by_index(p_args_ui32[0], data_cnt_ui32));
                }
                status_d = (double)p_bkp_this->lp_com_uart_port->send(data_packet_buffer.data_sui8, data_packet_buffer.length_ui32);
            }
            else if(jerry_value_is_string (p_args_ui32[0]))
            {
                // Read function argument
                data_packet_buffer.length_ui32 = jerry_get_string_size(p_args_ui32[0]);
                if (data_packet_buffer.length_ui32 > d_buffer_size)
                {
                    data_packet_buffer.length_ui32 = d_buffer_size;
                }
                jerry_string_to_char_buffer(p_args_ui32[0],data_packet_buffer.data_sui8,data_packet_buffer.length_ui32);
                status_d = (double)p_bkp_this->lp_com_uart_port->send(data_packet_buffer.data_sui8, data_packet_buffer.length_ui32);
            }
            else
            {

            }
        }
        else if(args_cnt_ui32 == 2 && p_bkp_this)
        {
            if(
               jerry_value_is_array (p_args_ui32[0]) &&
               jerry_value_is_number (p_args_ui32[1])
              )
            {
                // Read function argument
                data_packet_buffer.length_ui32 = jerry_get_array_length(p_args_ui32[0]);
                // Call class method
                for (data_cnt_ui32 = 0; data_cnt_ui32 < data_packet_buffer.length_ui32; data_cnt_ui32++)
                {
                    data_packet_buffer.data_sui8[data_cnt_ui32] = (uint8_t)jerry_get_number_value(jerry_get_property_by_index(p_args_ui32[0], data_cnt_ui32));
                }
                status_d = (double)p_bkp_this->lp_com_uart_port->send(data_packet_buffer.data_sui8, data_packet_buffer.length_ui32);
            }
        }
        else
        {
            printf("Error uart.write wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_number(status_d);
}

/** @brief Get UART control line status (JS method "get_ctrl")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t uart_js_c::get_ctrl(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
bool status_b = true;
void* p_arg_void;
uart_js_c* p_bkp_this = NULL;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<uart_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 1 && p_bkp_this)
        {
            if(jerry_value_is_string(p_args_ui32[0]))
            {
                // Read function argument
                const uint32_t data_len_ui32 = jerry_get_string_size(p_args_ui32[0]);
                uint8_t *p_data_sui8 = new uint8_t[data_len_ui32];
                jerry_string_to_char_buffer(p_args_ui32[0],p_data_sui8,data_len_ui32);
                // Call class method
                if (p_bkp_this)
                {
                    if(!strncmp((char*)p_data_sui8, "RX", data_len_ui32))
                    {
                        status_b = p_bkp_this->lp_com_uart_port->get(e_rx);
                    }
                    else if(!strncmp((char*)p_data_sui8, "CTS", data_len_ui32))
                    {
                        status_b = p_bkp_this->lp_com_uart_port->get(e_cts);
                    }
                    else if(!strncmp((char*)p_data_sui8, "DSR", data_len_ui32))
                    {
                        status_b = p_bkp_this->lp_com_uart_port->get(e_dsr);
                    }
                    else if(!strncmp((char*)p_data_sui8, "RING", data_len_ui32))
                    {
                        status_b = p_bkp_this->lp_com_uart_port->get(e_ring);
                    }
                    else if(!strncmp((char*)p_data_sui8, "RLSD", data_len_ui32))
                    {
                        status_b = p_bkp_this->lp_com_uart_port->get(e_rlsd);
                    }
                    else
                    {

                    }
                }
                delete[] p_data_sui8;
            }
        }
        else
        {
            printf("Error uart.get_ctrl wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_boolean(status_b);
}

/** @brief Set UART control line status (JS method "set_ctrl")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t uart_js_c::set_ctrl(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
uart_js_c* p_bkp_this = NULL;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<uart_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 2 && p_bkp_this)
        {
            if(jerry_value_is_string(p_args_ui32[0]) && jerry_value_is_boolean(p_args_ui32[1]))
            {
                // Read function argument
                const uint32_t data_len_ui32 = jerry_get_string_size(p_args_ui32[0]);
                uint8_t *p_data_sui8 = new uint8_t[data_len_ui32];
                jerry_string_to_char_buffer(p_args_ui32[0],p_data_sui8,data_len_ui32);
                // Call class method
                if (p_bkp_this)
                {
                    if(!strncmp((char*)p_data_sui8, "DTR", data_len_ui32))
                    {
                        p_bkp_this->lp_com_uart_port->set(e_dtr,jerry_get_boolean_value(p_args_ui32[1]));
                    }
                    else if(!strncmp((char*)p_data_sui8, "RTS", data_len_ui32))
                    {
                        p_bkp_this->lp_com_uart_port->set(e_rts,jerry_get_boolean_value(p_args_ui32[1]));
                    }
                    else if(!strncmp((char*)p_data_sui8, "BREAK", data_len_ui32))
                    {
                        p_bkp_this->lp_com_uart_port->set(e_break,jerry_get_boolean_value(p_args_ui32[1]));
                    }
                    else if(!strncmp((char*)p_data_sui8, "XOFF", data_len_ui32))
                    {
                        p_bkp_this->lp_com_uart_port->set(e_xoff,jerry_get_boolean_value(p_args_ui32[1]));
                    }
                    else if(!strncmp((char*)p_data_sui8, "XON", data_len_ui32))
                    {
                        p_bkp_this->lp_com_uart_port->set(e_xon,jerry_get_boolean_value(p_args_ui32[1]));
                    }
                    else
                    {

                    }
                }
                delete[] p_data_sui8;
            }
        }
        else
        {
            printf("Error uart.set_ctrl wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_undefined();
}

/** @brief Call UART data RX event (Must be called form JS thread)
 *
 * @param [IN] p_parametr_void : Handle on registered object
 * @return uint32_t : number of item in UART buffer
 *
 */

uint32_t uart_js_c::call(void* p_parametr_void)
{
uart_js_c *p_bkp_this = (uart_js_c*)p_parametr_void;
static packet_buffer_t data_packet_buffer;
jerry_value_t val_args[2];
jerry_value_t data_item_val;
jerry_value_t eval_ret;

    if(lv_main_packet_buffer.size())
    {
        // Get data from fifo
        data_packet_buffer = lv_main_packet_buffer[0];
        lv_main_packet_buffer.erase(lv_main_packet_buffer.begin() + 0);
        // Set parameters
        val_args[0] = jerry_create_number(data_packet_buffer.event_type_ui32);
        val_args[1] = jerry_create_array(data_packet_buffer.length_ui32);
        for (uint32_t data_cnt_ui32 = 0; data_cnt_ui32 < data_packet_buffer.length_ui32 ; data_cnt_ui32++)
        {
            data_item_val = jerry_create_number(double(data_packet_buffer.data_sui8[data_cnt_ui32]));
            eval_ret = jerry_set_property_by_index (val_args[1], data_cnt_ui32, data_item_val);
            jerry_release_value (eval_ret);
            jerry_release_value (data_item_val);
        }
        // Call function
        if (p_bkp_this->l_reg_fct_ui32 && p_bkp_this->l_global_ui32)
        {
            eval_ret = jerry_call_function (p_bkp_this->l_reg_fct_ui32, p_bkp_this->l_global_ui32, val_args, 2);
            jerry_release_value (eval_ret);
        }
        // Clear buffer item
        jerry_release_value (val_args[0]);
        jerry_release_value (val_args[1]);
    }
    return lv_main_packet_buffer.size();
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

void uart_js_c::rx_event(void* p_parametr_void, uint32_t event_type_ui32, uint8_t *p_data_sui8, uint32_t length_ui32)
{
uart_js_c *p_bkp_this = (uart_js_c*)p_parametr_void;
uint32_t data_cnt_ui32;
packet_buffer_t data_packet_buffer;

    // Save event type
    data_packet_buffer.event_type_ui32 = event_type_ui32;
    // Save length
    if (length_ui32 > d_buffer_size)
    {
        data_packet_buffer.length_ui32 = d_buffer_size;
    }
    else
    {
        data_packet_buffer.length_ui32 = length_ui32;
    }
    // Set data
    for(data_cnt_ui32 = 0 ; data_cnt_ui32 < data_packet_buffer.length_ui32 ; data_cnt_ui32++)
    {
        data_packet_buffer.data_sui8[data_cnt_ui32] = p_data_sui8[data_cnt_ui32];
    }
    // Save data
    lv_main_packet_buffer.push_back(data_packet_buffer);
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
