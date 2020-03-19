/**
  ****************************************************************************
  * @file    in_js_class_project_js_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    18.03.2020
  * @brief   JerryScript wrapper for script project
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
#include <wx/file.h>
#include "in_js_class_project_js_h.h"
#include "in_jerryscript_core_h.h"
#include "in_config_ini_wrapper_h.h"

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
  * @defgroup Project
  * @brief Project class definition
  * @{
  */

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

static wxString l_project_str;

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Registration object in to class
 *
 * @param [IN] p_position_config_ini : Scrip project data
 * @return void
 *
 */

void project_js_c::reg_host_class (wxString project_str)
{
jerry_value_t global_jerry_value;
jerry_value_t object_jerry_value;
jerry_value_t funct_jerry_value;
jerry_value_t name_jerry_value;

    // Save parameter
    l_project_str = project_str;
    // Create method
    object_jerry_value = jerry_create_object ();
    // Read project file
    funct_jerry_value = jerry_create_external_function(this->read);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"read");
    jerry_set_property(object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Write project file
    funct_jerry_value = jerry_create_external_function(this->write);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"write");
    jerry_set_property(object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Create class
    global_jerry_value = jerry_get_global_object();
    name_jerry_value = jerry_create_string((const jerry_char_t*)"project");
    jerry_set_property (global_jerry_value, name_jerry_value, object_jerry_value);

    funct_jerry_value = jerry_get_property (global_jerry_value, name_jerry_value);
    jerry_set_object_native_pointer(funct_jerry_value, this, NULL);
    // Release storage value
    jerry_release_value(name_jerry_value);
    jerry_release_value(object_jerry_value);
    return;
}

/** @brief Read project variable (JS function "read")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t project_js_c::read(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
project_js_c* p_bkp_this = NULL;
wxString path_str = wxEmptyString;
wxString data_str = wxEmptyString;
wxString parameter_str = wxEmptyString;
double data_d = 0;
uint32_t data_len_ui32;
static uint8_t *p_data_sui8 = NULL;
config_ini *p_position_config_ini;

    if(jerry_get_object_native_pointer(jerry_get_global_object(), &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<project_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 2 && p_bkp_this)
        {
            if(
               jerry_value_is_string(p_args_ui32[0]) &&
               jerry_value_is_string(p_args_ui32[1])
              )
            {
                // Read value path
                data_len_ui32 = jerry_get_string_size(p_args_ui32[0]);
                p_data_sui8 = new uint8_t[data_len_ui32];
                jerry_string_to_char_buffer(p_args_ui32[0],p_data_sui8,data_len_ui32);
                path_str = wxEmptyString;
                for (uint32_t char_cnt_ui32 = 0 ; char_cnt_ui32 < data_len_ui32 ; char_cnt_ui32++)
                {
                    path_str += p_data_sui8[char_cnt_ui32];
                }
                delete[] p_data_sui8;
                // Read default value data string
                data_len_ui32 = jerry_get_string_size(p_args_ui32[1]);
                p_data_sui8 = new uint8_t[data_len_ui32];
                jerry_string_to_char_buffer(p_args_ui32[1],p_data_sui8,data_len_ui32);
                data_str = wxEmptyString;
                for (uint32_t char_cnt_ui32 = 0 ; char_cnt_ui32 < data_len_ui32 ; char_cnt_ui32++)
                {
                    data_str += p_data_sui8[char_cnt_ui32];
                }
                delete[] p_data_sui8;
                // Get string value
                p_position_config_ini = new config_ini(l_project_str);
                if(p_position_config_ini)
                {
                    parameter_str = p_position_config_ini->get_string(path_str, data_str);
                    delete p_position_config_ini;
                }
                return jerry_create_string((const jerry_char_t*)parameter_str.To8BitData().data());
            }
            else if(
               jerry_value_is_string(p_args_ui32[0]) &&
               jerry_value_is_number(p_args_ui32[1])
              )
            {
                // Read value path
                data_len_ui32 = jerry_get_string_size(p_args_ui32[0]);
                p_data_sui8 = new uint8_t[data_len_ui32];
                jerry_string_to_char_buffer(p_args_ui32[0],p_data_sui8,data_len_ui32);
                path_str = wxEmptyString;
                for (uint32_t char_cnt_ui32 = 0 ; char_cnt_ui32 < data_len_ui32 ; char_cnt_ui32++)
                {
                    path_str += p_data_sui8[char_cnt_ui32];
                }
                delete[] p_data_sui8;
                // Read default value data
                data_d = jerry_get_number_value(p_args_ui32[1]);
                data_str.Printf("%f",data_d);
                data_str.Replace(wxT(".000000"), wxT(""),true);
                // Get string value
                p_position_config_ini = new config_ini(l_project_str);
                if(p_position_config_ini)
                {
                    parameter_str = p_position_config_ini->get_string(path_str, data_str);
                    delete p_position_config_ini;
                }
                parameter_str.ToDouble(&data_d);
                return jerry_create_number(data_d);
            }
            else
            {
                printf("Error file.read wrong parameter type\n");
            }
        }
        else
        {
            printf("Error file.read wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_number(data_d);
}

/** @brief Write project variable (JS function "write")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t project_js_c::write(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
project_js_c* p_bkp_this = NULL;
wxString path_str = wxEmptyString;
wxString data_str = wxEmptyString;
double data_d = 0;
uint32_t data_len_ui32;
static uint8_t *p_data_sui8 = NULL;
config_ini *p_position_config_ini;

    if(jerry_get_object_native_pointer(jerry_get_global_object(), &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<project_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 2 && p_bkp_this)
        {
            if(
               jerry_value_is_string(p_args_ui32[0]) &&
               jerry_value_is_string(p_args_ui32[1])
              )
            {
                // Read value path
                data_len_ui32 = jerry_get_string_size(p_args_ui32[0]);
                p_data_sui8 = new uint8_t[data_len_ui32];
                jerry_string_to_char_buffer(p_args_ui32[0],p_data_sui8,data_len_ui32);
                path_str = wxEmptyString;
                for (uint32_t char_cnt_ui32 = 0 ; char_cnt_ui32 < data_len_ui32 ; char_cnt_ui32++)
                {
                    path_str += p_data_sui8[char_cnt_ui32];
                }
                delete[] p_data_sui8;
                // Read value data string
                data_len_ui32 = jerry_get_string_size(p_args_ui32[1]);
                p_data_sui8 = new uint8_t[data_len_ui32];
                jerry_string_to_char_buffer(p_args_ui32[1],p_data_sui8,data_len_ui32);
                data_str = wxEmptyString;
                for (uint32_t char_cnt_ui32 = 0 ; char_cnt_ui32 < data_len_ui32 ; char_cnt_ui32++)
                {
                    data_str += p_data_sui8[char_cnt_ui32];
                }
                delete[] p_data_sui8;
                // Set string value
                p_position_config_ini = new config_ini(l_project_str);
                if(p_position_config_ini)
                {
                    p_position_config_ini->set_string(path_str, data_str);
                    delete p_position_config_ini;
                }
            }
            else if(
               jerry_value_is_string(p_args_ui32[0]) &&
               jerry_value_is_number(p_args_ui32[1])
              )
            {
                // Read value path
                data_len_ui32 = jerry_get_string_size(p_args_ui32[0]);
                p_data_sui8 = new uint8_t[data_len_ui32];
                jerry_string_to_char_buffer(p_args_ui32[0],p_data_sui8,data_len_ui32);
                path_str = wxEmptyString;
                for (uint32_t char_cnt_ui32 = 0 ; char_cnt_ui32 < data_len_ui32 ; char_cnt_ui32++)
                {
                    path_str += p_data_sui8[char_cnt_ui32];
                }
                delete[] p_data_sui8;
                // Read value data
                data_d = jerry_get_number_value(p_args_ui32[1]);
                data_str.Printf("%f",data_d);
                data_str.Replace(wxT(".000000"), wxT(""),true);
                // Set string value
                p_position_config_ini = new config_ini(l_project_str);
                if(p_position_config_ini)
                {
                    p_position_config_ini->set_string(path_str, data_str);
                    delete p_position_config_ini;
                }
            }
            else
            {
                printf("Error file.write wrong parameter type\n");
            }
        }
        else
        {
            printf("Error file.write wrong parameter\n");
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
