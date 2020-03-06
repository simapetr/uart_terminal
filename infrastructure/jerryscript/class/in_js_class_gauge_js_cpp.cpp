/**
  ****************************************************************************
  * @file    in_js_class_gauge_js_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    30.10.2018
  * @brief   JerryScript wrapper for component gauge
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
#include "in_js_class_gauge_js_h.h"
#include "in_jerryscript_core_h.h"
#include "in_js_gui_frame_h.h"

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
  * @defgroup Gauge
  * @brief Gauge class definition
  * @{
  */

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Registration object in to class
 *
 * @param [IN] p_gui_interface_void : Pointer on registered class
 * @return void
 *
 */

void gauge_js_c::reg_host_class (void* p_gui_interface_void)
{
jerry_value_t global_jerry_value;
jerry_value_t object_jerry_value;
jerry_value_t funct_jerry_value;
jerry_value_t name_jerry_value;

    // Save GUI interface pointer
    this->lp_gui_interface_void = p_gui_interface_void;
    // Create method
    object_jerry_value = jerry_create_object();
    // Add new check box
    funct_jerry_value = jerry_create_external_function(this->add);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"add");
    jerry_set_property(object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Set check box
    funct_jerry_value = jerry_create_external_function(this->set);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"set");
    jerry_set_property(object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Get check box
    funct_jerry_value = jerry_create_external_function(this->get);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"get");
    jerry_set_property(object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Create class
    global_jerry_value = jerry_get_property(jerry_get_global_object(), jerry_create_string((const jerry_char_t*)"gui"));
    name_jerry_value = jerry_create_string((const jerry_char_t*)"gauge");
    jerry_set_property (global_jerry_value, name_jerry_value, object_jerry_value);

    funct_jerry_value = jerry_get_property (global_jerry_value, name_jerry_value);
    jerry_set_object_native_pointer(funct_jerry_value, this, NULL);
    // Release storage value
    jerry_release_value(name_jerry_value);
    jerry_release_value(object_jerry_value);
    return;
}

/** @brief Add new gauge (JS function "add")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t gauge_js_c::add(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
gauge_js_c* p_bkp_this = NULL;
double gauge_index_d = 0.0;

    if(jerry_get_object_native_pointer(jerry_get_global_object(), &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<gauge_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 4 && p_bkp_this)
        {
            if(
               jerry_value_is_number (p_args_ui32[0]) &&
               jerry_value_is_number (p_args_ui32[1]) &&
               jerry_value_is_boolean (p_args_ui32[2]) &&
               jerry_value_is_number (p_args_ui32[3])
              )
            {
                // Call class method
                if (p_bkp_this)
                {
                    gauge_index_d = ((gui_frame*)(p_bkp_this->lp_gui_interface_void))->add_gauge(jerry_get_number_value(p_args_ui32[0]), jerry_get_number_value(p_args_ui32[1]),jerry_get_boolean_value(p_args_ui32[2]),jerry_get_number_value(p_args_ui32[3]));
                }
            }
        }
        else
        {
            printf("Error gui.gauge.add wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_number(gauge_index_d);
}

/** @brief Set gauge value (JS method "set")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t gauge_js_c::set(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
bool status_b = false;
void* p_arg_void;
gauge_js_c* p_bkp_this = NULL;
wxString text_str = wxEmptyString;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<gauge_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 2 && p_bkp_this)
        {
            if(
               jerry_value_is_number(p_args_ui32[0]) &&
               jerry_value_is_number(p_args_ui32[1])
              )
            {
                status_b = ((gui_frame*)(p_bkp_this->lp_gui_interface_void))->set_gauge(jerry_get_number_value(p_args_ui32[0]), jerry_get_number_value(p_args_ui32[1]));
            }
        }
        else
        {
            printf("Error gui.gauge.set wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_boolean(status_b);
}

/** @brief Get gauge state (JS method "get")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t gauge_js_c::get(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
gauge_js_c* p_bkp_this = NULL;
double value_d = 0;

    if(jerry_get_object_native_pointer(this_ui32, &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<gauge_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 1 && p_bkp_this)
        {
            if(jerry_value_is_number(p_args_ui32[0]))
            {
                value_d = ((gui_frame*)(p_bkp_this->lp_gui_interface_void))->get_gauge(jerry_get_number_value(p_args_ui32[0]));
            }
        }
        else
        {
            printf("Error gui.gauge.get wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_number(value_d);
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
