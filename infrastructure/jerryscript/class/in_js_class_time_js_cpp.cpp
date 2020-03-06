/**
  ****************************************************************************
  * @file    in_js_class_time_js_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    18.04.2018
  * @brief   JerryScript wrapper for time
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
#include <wx/time.h>
#include <wx/datetime.h>
#include "in_js_class_time_js_h.h"
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
  * @defgroup Time
  * @brief Time class definition
  * @{
  */

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Registration object in to class
 *
 * @param void
 * @return void
 *
 */

void time_js_c::reg_host_class (void)
{
jerry_value_t global_jerry_value;
jerry_value_t object_jerry_value;
jerry_value_t funct_jerry_value;
jerry_value_t name_jerry_value;

    // Create method
    object_jerry_value = jerry_create_object();
    // Register read actual UTC time (epoch time in s)
    funct_jerry_value = jerry_create_external_function(this->now);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"now");
    jerry_set_property(object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Register read actual UTC time (epoch time in ms)
    funct_jerry_value = jerry_create_external_function(this->now_ms);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"now_ms");
    jerry_set_property(object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Register convert second epoch UTC time to text time & date (YYYY-MM-DD HH:MM:SS)
    funct_jerry_value = jerry_create_external_function(this->str);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"str");
    jerry_set_property(object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Register convert second epoch UTC time to local text time & date (YYYY-MM-DD HH:MM:SS)
    funct_jerry_value = jerry_create_external_function(this->local_str);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"local_str");
    jerry_set_property(object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Create class
    global_jerry_value = jerry_get_global_object();
    name_jerry_value = jerry_create_string((const jerry_char_t*)"time");
    jerry_set_property (global_jerry_value, name_jerry_value, object_jerry_value);

    funct_jerry_value = jerry_get_property (global_jerry_value, name_jerry_value);
    jerry_set_object_native_pointer(funct_jerry_value, this, NULL);
    // Release storage value
    jerry_release_value(name_jerry_value);
    jerry_release_value(object_jerry_value);
    return;
}

/** @brief Get actual epoch time in s (JS function "now")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t time_js_c::now(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
time_js_c* p_bkp_this = NULL;
double time_d = 0.0;

    if(jerry_get_object_native_pointer(jerry_get_global_object(), &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<time_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 0 && p_bkp_this)
        {
            time_d = (double)wxGetUTCTime();
        }
        else
        {
            printf("Error time.now wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_number(time_d);
}

/** @brief Get actual epoch time in ms (JS function "now_ms")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t time_js_c::now_ms(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
time_js_c* p_bkp_this = NULL;
double time_d = 0.0;

    if(jerry_get_object_native_pointer(jerry_get_global_object(), &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<time_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 0 && p_bkp_this)
        {
            time_d = wxGetUTCTimeMillis().ToDouble();
        }
        else
        {
            printf("Error time.now_ms wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_number(time_d);
}

/** @brief Convert time in UTC second to time & date string value (JS function "str")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t time_js_c::str(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
time_js_c* p_bkp_this = NULL;
wxDateTime value_wxdatetime;
wxString data_str;

    if(jerry_get_object_native_pointer(jerry_get_global_object(), &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<time_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 1 && p_bkp_this)
        {
            if(jerry_value_is_number(p_args_ui32[0]))
            {
                // Read function argument
                value_wxdatetime.Set((time_t)jerry_get_number_value(p_args_ui32[0]));
                data_str.Printf("%04u-%02u-%02u %02u:%02u:%02u", value_wxdatetime.GetYear(0), (value_wxdatetime.GetMonth(0) + 1), value_wxdatetime.GetDay(0), value_wxdatetime.GetHour(0), value_wxdatetime.GetMinute(0), value_wxdatetime.GetSecond(0));
            }
        }
        else
        {
            printf("Error time.str wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_string((const jerry_char_t*)data_str.To8BitData().data());
}

/** @brief Convert time in local second to local time & date string value (JS function "local_str")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t time_js_c::local_str(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
time_js_c* p_bkp_this = NULL;
wxDateTime value_wxdatetime;
wxString data_str;

    if(jerry_get_object_native_pointer(jerry_get_global_object(), &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<time_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 1 && p_bkp_this)
        {
            if(jerry_value_is_number(p_args_ui32[0]))
            {
                // Read function argument
                value_wxdatetime.Set((time_t)jerry_get_number_value(p_args_ui32[0]));
                data_str.Printf("%04u-%02u-%02u %02u:%02u:%02u", value_wxdatetime.GetYear(), (value_wxdatetime.GetMonth() + 1), value_wxdatetime.GetDay(), value_wxdatetime.GetHour(), value_wxdatetime.GetMinute(), value_wxdatetime.GetSecond());
            }
        }
        else
        {
            printf("Error time.local_str wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_string((const jerry_char_t*)data_str.To8BitData().data());
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
