/**
  ****************************************************************************
  * @file    in_js_class_timer_js_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    19.02.2020
  * @brief   JerryScript event timer
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

#include <wx/time.h>
#include "in_js_class_timer_js_h.h"
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
  * @defgroup Timer
  * @brief Timer class definition
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

void timer_js_c::reg_host_class (void)
{
jerry_value_t global_jerry_value;
jerry_value_t object_jerry_value;
jerry_value_t funct_jerry_value;
jerry_value_t name_jerry_value;

    // Create method
    object_jerry_value = jerry_create_object();
    // Register add new timer event
    funct_jerry_value = jerry_create_external_function(this->add);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"add");
    jerry_set_property(object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Register set timer period
    funct_jerry_value = jerry_create_external_function(this->set);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"set");
    jerry_set_property(object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Register start timer
    funct_jerry_value = jerry_create_external_function(this->start);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"start");
    jerry_set_property(object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Register stop timer
    funct_jerry_value = jerry_create_external_function(this->stop);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"stop");
    jerry_set_property(object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Register reset timer
    funct_jerry_value = jerry_create_external_function(this->reset);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"reset");
    jerry_set_property(object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Create class
    global_jerry_value = jerry_get_global_object();
    name_jerry_value = jerry_create_string((const jerry_char_t*)"timer");
    jerry_set_property (global_jerry_value, name_jerry_value, object_jerry_value);

    funct_jerry_value = jerry_get_property (global_jerry_value, name_jerry_value);
    jerry_set_object_native_pointer(funct_jerry_value, this, NULL);
    // Release storage value
    jerry_release_value(name_jerry_value);
    jerry_release_value(object_jerry_value);
    this->l_global_ui32 = global_jerry_value;
    // Create timer thread
    this->l_run_timer_ui8 = 0;
    this->lp_timer_thread = new thread_c(this, this->worker, 1);
    this->lp_timer_thread->SetPriority(wxPRIORITY_MAX);
    return;
}

/** @brief Deregistration object in to class
 *
 * @param void
 * @return void
 *
 */

void timer_js_c::dereg_host_class (void)
{
    this->l_run_timer_ui8 = 0;
    lv_main_timer_buffer.clear();
    this->lp_timer_thread->stop();
    return;
}

/** @brief Add new timer event (JS function "add")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t timer_js_c::add(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
timer_js_c* p_bkp_this = NULL;
double timer_index_d = 0.0;
timer_buffer_t data_timer_buffer;

    if(jerry_get_object_native_pointer(jerry_get_global_object(), &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<timer_js_c*>(p_arg_void);
        if(p_bkp_this)
        {
            p_bkp_this->l_run_timer_ui8 = 0;
            // Reset one shot flag
            data_timer_buffer.one_flag_b = false;
            // Extract function argument
            if(args_cnt_ui32 == 2 && p_bkp_this)
            {
                if(
                   jerry_value_is_string(p_args_ui32[0]) &&
                   jerry_value_is_number(p_args_ui32[1])
                  )
                {
                    // Call class method
                    if (p_bkp_this)
                    {
                        timer_index_d = p_bkp_this->lv_main_timer_buffer.size();
                        data_timer_buffer.event_fct_ui32 = (uint32_t)jerry_get_property(p_bkp_this->l_global_ui32, p_args_ui32[0]);
                        data_timer_buffer.cnt_d = 0;
                        data_timer_buffer.period_d = jerry_get_number_value(p_args_ui32[1]);
                        data_timer_buffer.run_b = false;
                        data_timer_buffer.one_shot_b = false;
                        if(data_timer_buffer.period_d)
                        {
                            p_bkp_this->lv_main_timer_buffer.push_back(data_timer_buffer);
                        }
                    }
                }
            }
            else if(args_cnt_ui32 == 3 && p_bkp_this)
            {
                if(
                   jerry_value_is_string(p_args_ui32[0]) &&
                   jerry_value_is_number(p_args_ui32[1]) &&
                   jerry_value_is_boolean(p_args_ui32[2])
                  )
                {
                    // Call class method
                    if (p_bkp_this)
                    {
                        timer_index_d = p_bkp_this->lv_main_timer_buffer.size();
                        data_timer_buffer.event_fct_ui32 = (uint32_t)jerry_get_property(p_bkp_this->l_global_ui32, p_args_ui32[0]);
                        data_timer_buffer.cnt_d = 0;
                        data_timer_buffer.period_d = jerry_get_number_value(p_args_ui32[1]);
                        data_timer_buffer.run_b = jerry_get_boolean_value(p_args_ui32[2]);
                        data_timer_buffer.one_shot_b = false;
                        if(data_timer_buffer.period_d)
                        {
                            p_bkp_this->lv_main_timer_buffer.push_back(data_timer_buffer);
                        }
                    }
                }
            }
            else if(args_cnt_ui32 == 4 && p_bkp_this)
            {
                if(
                   jerry_value_is_string(p_args_ui32[0]) &&
                   jerry_value_is_number(p_args_ui32[1]) &&
                   jerry_value_is_boolean(p_args_ui32[2]) &&
                   jerry_value_is_boolean(p_args_ui32[3])
                  )
                {
                    // Call class method
                    if (p_bkp_this)
                    {
                        timer_index_d = p_bkp_this->lv_main_timer_buffer.size();
                        data_timer_buffer.event_fct_ui32 = (uint32_t)jerry_get_property(p_bkp_this->l_global_ui32, p_args_ui32[0]);
                        data_timer_buffer.cnt_d = 0;
                        data_timer_buffer.period_d = jerry_get_number_value(p_args_ui32[1]);
                        data_timer_buffer.run_b = jerry_get_boolean_value(p_args_ui32[2]);
                        data_timer_buffer.one_shot_b = jerry_get_boolean_value(p_args_ui32[3]);
                        if(data_timer_buffer.period_d)
                        {
                            p_bkp_this->lv_main_timer_buffer.push_back(data_timer_buffer);
                        }
                    }
                }
            }
            else
            {

            }
            p_bkp_this->l_run_timer_ui8 = 1;
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_number(timer_index_d);
}

/** @brief Set timer period (JS function "set")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t timer_js_c::set(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
timer_js_c* p_bkp_this = NULL;
double timer_index_d = 0.0;

    if(jerry_get_object_native_pointer(jerry_get_global_object(), &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<timer_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 2 && p_bkp_this)
        {
            if(
               jerry_value_is_number(p_args_ui32[0]) &&
               jerry_value_is_number(p_args_ui32[1])
              )
            {
                timer_index_d = jerry_get_number_value(p_args_ui32[0]);
                // Set timer period
                if (p_bkp_this)
                {
                    if(timer_index_d < p_bkp_this->lv_main_timer_buffer.size())
                    {
                        p_bkp_this->lv_main_timer_buffer[timer_index_d].period_d = jerry_get_number_value(p_args_ui32[1]);
                    }
                }
            }
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_undefined();
}


/** @brief Start timer count (JS function "start")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t timer_js_c::start(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
timer_js_c* p_bkp_this = NULL;
double timer_index_d = 0.0;

    if(jerry_get_object_native_pointer(jerry_get_global_object(), &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<timer_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 1 && p_bkp_this)
        {
            if(jerry_value_is_number(p_args_ui32[0]))
            {
                timer_index_d = jerry_get_number_value(p_args_ui32[0]);
                // Start timer
                if (p_bkp_this)
                {
                    if(timer_index_d < p_bkp_this->lv_main_timer_buffer.size())
                    {
                        p_bkp_this->lv_main_timer_buffer[timer_index_d].cnt_d = 0;
                        p_bkp_this->lv_main_timer_buffer[timer_index_d].run_b = true;
                        p_bkp_this->lv_main_timer_buffer[timer_index_d].one_flag_b = false;
                    }
                }
            }
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_undefined();
}

/** @brief Stop timer count (JS function "stop")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t timer_js_c::stop(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
timer_js_c* p_bkp_this = NULL;
double timer_index_d = 0.0;

    if(jerry_get_object_native_pointer(jerry_get_global_object(), &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<timer_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 1 && p_bkp_this)
        {
            if(jerry_value_is_number(p_args_ui32[0]))
            {
                timer_index_d = jerry_get_number_value(p_args_ui32[0]);
                // Stop timer
                if (p_bkp_this)
                {
                    if(timer_index_d < p_bkp_this->lv_main_timer_buffer.size())
                    {
                        p_bkp_this->lv_main_timer_buffer[timer_index_d].run_b = false;
                    }
                }
            }
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_undefined();
}

/** @brief Reset timer counter (JS function "reset")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t timer_js_c::reset(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
timer_js_c* p_bkp_this = NULL;
double timer_index_d = 0.0;

    if(jerry_get_object_native_pointer(jerry_get_global_object(), &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<timer_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 1 && p_bkp_this)
        {
            if(jerry_value_is_number(p_args_ui32[0]))
            {
                timer_index_d = jerry_get_number_value(p_args_ui32[0]);
                // Reset timer counter
                if (p_bkp_this)
                {
                    if(timer_index_d < p_bkp_this->lv_main_timer_buffer.size())
                    {
                        p_bkp_this->lv_main_timer_buffer[timer_index_d].cnt_d = 0;
                    }
                }
            }
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_undefined();
}

/**
  ****************************************************************************
  * Private function
  ****************************************************************************
  */

/** @brief Script RUN thread
 *
 * @param void
 * @return wxThread::ExitCode : thread end status
 *
 */

void timer_js_c::worker(void* p_parametr_void)
{
timer_js_c* p_bkp_this = (timer_js_c*)p_parametr_void;
static uint32_t buffer_cnt_ui32;
static jerry_value_t eval_ret;
double time_d = wxGetUTCTimeMillis().ToDouble();

    // Thread worker
    if((p_bkp_this) && (p_bkp_this->l_run_timer_ui8))
    {
        for(buffer_cnt_ui32 = 0 ; buffer_cnt_ui32 < p_bkp_this->lv_main_timer_buffer.size() ; buffer_cnt_ui32++)
        {
            if(p_bkp_this->lv_main_timer_buffer[buffer_cnt_ui32].cnt_d == 0)
            {
                p_bkp_this->lv_main_timer_buffer[buffer_cnt_ui32].cnt_d = (time_d + p_bkp_this->lv_main_timer_buffer[buffer_cnt_ui32].period_d);
            }
            if(time_d >= p_bkp_this->lv_main_timer_buffer[buffer_cnt_ui32].cnt_d)
            {
                // Set new trigger
                p_bkp_this->lv_main_timer_buffer[buffer_cnt_ui32].cnt_d += p_bkp_this->lv_main_timer_buffer[buffer_cnt_ui32].period_d;
                if((p_bkp_this->lv_main_timer_buffer[buffer_cnt_ui32].run_b) && (!p_bkp_this->lv_main_timer_buffer[buffer_cnt_ui32].one_flag_b))
                {
                    // Call function
                    if (p_bkp_this->lv_main_timer_buffer[buffer_cnt_ui32].event_fct_ui32)
                    {
                        jerry_value_t val_args[1];
                        uint16_t val_argv = 1;
                        // Create function argument
                        val_args[0] = jerry_create_number(buffer_cnt_ui32);
                        eval_ret = jerry_call_function((jerry_value_t)p_bkp_this->lv_main_timer_buffer[buffer_cnt_ui32].event_fct_ui32, p_bkp_this->l_global_ui32, val_args, val_argv);
                        jerry_release_value(eval_ret);
                        jerry_release_value(val_args[0]);
                    }
                }
                // One shot
                if(p_bkp_this->lv_main_timer_buffer[buffer_cnt_ui32].one_shot_b)
                {
                    p_bkp_this->lv_main_timer_buffer[buffer_cnt_ui32].one_flag_b = true;
                }
            }
        }
    }
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
