/**
  ****************************************************************************
  * @file    in_js_class_graph_js_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    18.07.2018
  * @brief   JerryScript wrapper for graph class
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
#include "in_js_class_graph_js_h.h"
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
  * @defgroup Graph
  * @brief Graph interface
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

void graph_js_c::reg_host_class (void* p_gui_main_frame_void)
{
jerry_value_t global_jerry_value;
jerry_value_t object_jerry_value;
jerry_value_t funct_jerry_value;
jerry_value_t name_jerry_value;

    this->lp_gui_main_frame_void = p_gui_main_frame_void;
    // Create method
    object_jerry_value = jerry_create_object ();
    // Add graph
    funct_jerry_value = jerry_create_external_function(this->add);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"add");
    jerry_set_property (object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Insert signal in to graph
    funct_jerry_value = jerry_create_external_function(this->insert_signal);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"insert_signal");
    jerry_set_property (object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Set data in graph
    funct_jerry_value = jerry_create_external_function(this->set_data);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"set_data");
    jerry_set_property (object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Show graph
    funct_jerry_value = jerry_create_external_function(this->show);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"show");
    jerry_set_property (object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Create class
    global_jerry_value = jerry_get_global_object();
    name_jerry_value = jerry_create_string((const jerry_char_t*)"graph");
    jerry_set_property (global_jerry_value, name_jerry_value, object_jerry_value);

    funct_jerry_value = jerry_get_property (global_jerry_value, name_jerry_value);
    jerry_set_object_native_pointer(funct_jerry_value, this, NULL);
    // Release storage value
    jerry_release_value(name_jerry_value);
    jerry_release_value(object_jerry_value);
    return;
}

/** @brief Add graph (JS method "add")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t graph_js_c::add(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
graph_js_c* p_bkp_this = NULL;
uint32_t graph_num_ui32 = 0;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<graph_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 3 && p_bkp_this)
        {
            if(
               jerry_value_is_number (p_args_ui32[0]) &&
               jerry_value_is_number (p_args_ui32[1]) &&
               jerry_value_is_number (p_args_ui32[2])
              )
            {
                // Call class method
                if (p_bkp_this)
                {
                    graph_num_ui32 = ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->get_graph_frame()->add_graph(jerry_get_number_value(p_args_ui32[0]),jerry_get_number_value(p_args_ui32[1]),jerry_get_number_value(p_args_ui32[2]));
                }
            }
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_number(graph_num_ui32);
}

/** @brief Insert signal in to graph (JS method "insert_signal")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t graph_js_c::insert_signal(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
graph_js_c* p_bkp_this = NULL;
uint32_t signal_num_ui32 = 0;
wxString name_str = wxEmptyString;
uint32_t data_len_ui32;
static uint8_t *p_data_sui8 = NULL;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<graph_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 5 && p_bkp_this)
        {
            if(
               jerry_value_is_number (p_args_ui32[0]) &&
               jerry_value_is_string (p_args_ui32[1]) &&
               jerry_value_is_number (p_args_ui32[2]) &&
               jerry_value_is_number (p_args_ui32[3]) &&
               jerry_value_is_number (p_args_ui32[4])
              )
            {
                // Call class method
                if (p_bkp_this)
                {
                    data_len_ui32 = jerry_get_string_size(p_args_ui32[1]);
                    p_data_sui8 = new uint8_t[data_len_ui32];
                    jerry_string_to_char_buffer(p_args_ui32[1],p_data_sui8,data_len_ui32);
                    name_str = wxEmptyString;
                    for (uint32_t char_cnt_ui32 = 0 ; char_cnt_ui32 < data_len_ui32 ; char_cnt_ui32++)
                    {
                        name_str += p_data_sui8[char_cnt_ui32];
                    }
                    delete[] p_data_sui8;
                    // Call function
                    signal_num_ui32 = ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->get_graph_frame()->insert_signal((uint32_t)jerry_get_number_value(p_args_ui32[0]),name_str,(uint32_t)jerry_get_number_value(p_args_ui32[2]),(uint32_t)jerry_get_number_value(p_args_ui32[3]),(uint32_t)jerry_get_number_value(p_args_ui32[4]));
                }
            }
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_number(signal_num_ui32);
}

/** @brief Set graph data (JS method "set_data")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t graph_js_c::set_data(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
graph_js_c* p_bkp_this = NULL;
bool status_b = true;
uint32_t data_len_ui32;
uint32_t data_cnt_ui32;
vector<double> v_data_d;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<graph_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 2 && p_bkp_this)
        {
            if(jerry_value_is_number(p_args_ui32[0]) && jerry_value_is_array(p_args_ui32[1]))
            {
                data_len_ui32 = jerry_get_array_length(p_args_ui32[1]);
                v_data_d.clear();
                for (data_cnt_ui32 = 0; data_cnt_ui32 < data_len_ui32; data_cnt_ui32++)
                {
                    v_data_d.push_back(jerry_get_number_value(jerry_get_property_by_index(p_args_ui32[1], data_cnt_ui32)));
                }
                // Call function
                status_b = ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->get_graph_frame()->set_graph_data((uint32_t)jerry_get_number_value(p_args_ui32[0]),v_data_d);
            }
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_boolean(status_b);
}

/** @brief Show graph frame (JS method "show")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t graph_js_c::show(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
graph_js_c* p_bkp_this = NULL;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<graph_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 1 && p_bkp_this)
        {
            if(jerry_value_is_boolean(p_args_ui32[0]))
            {
                // Call function
                ((main_frame*)(p_bkp_this->lp_gui_main_frame_void))->get_graph_frame()->Show(jerry_get_boolean_value(p_args_ui32[0]));
            }
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

/**
* @}
*/

/*****************************************************END OF FILE************/
