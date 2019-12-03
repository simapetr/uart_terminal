/**
  ****************************************************************************
  * @file    in_thread_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.1
  * @date    14.11.2018
  * @brief   System thread wrapper
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

#include "in_thread_worker_h.h"
#include <wx/utils.h>

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @defgroup Thread
  * @brief Thread wrapper
  * @{
  */

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Constructor
 *
 * @param [IN] p_parameter_void : Thread parameter
 * @param [IN] function_thread_fct : Thread called function
 * @return void
 *
 */

thread_c::thread_c(void *p_parameter_void, thread_fct_t function_thread_fct)
{
    this->lp_parameter_void = p_parameter_void;
    this->l_function_thread_fct = function_thread_fct;
    // Create RX wait event
    this->lp_data_wxmutex = new wxMutex();
    if(this->lp_data_wxmutex)
    {
        this->lp_data_wxcondition = new wxCondition(*this->lp_data_wxmutex);
        if(this->lp_data_wxcondition)
        {
            this->Run();
        }
    }
    this->l_stop_recursive_b = false;
    return;
}

/** @brief Destructor
 *
 * @param void
 * @return void
 *
 */

thread_c::~thread_c( void )
{
    this->stop();
    return;
}

/** @brief Enable thread event
 *
 * @param void
 * @return void
 *
 */

void thread_c::signal(void)
{
    if(this->lp_data_wxcondition)
    {
        this->lp_data_wxcondition->Broadcast();
    }
    return;
}

/** @brief Stop thread
 *
 * @param void
 * @return void
 *
 */

void thread_c::stop(void)
{
    // Check if thread run
    if (this->l_run_flag_b)
    {
        // Check recursive call
        while(l_stop_recursive_b)
        {
            wxMilliSleep(1);
        }
        // Lock function
        this->l_stop_recursive_b = true;
        // Stop thread disable call event
        this->l_run_flag_b = false;
        // Run thread
        this->signal();
        // Set wait timeout
        this->l_timeout_cnt_ui8 = 20;
        // Wait for terminate
        while((!this->l_run_flag_b) && (l_timeout_cnt_ui8))
        {
            wxMilliSleep(1);
            l_timeout_cnt_ui8--;
        }
        // Delete semaphore
        if(this->lp_data_wxcondition)
        {
            delete this->lp_data_wxcondition;
            this->lp_data_wxcondition = NULL;
        }
        // Set new thread state
        this->l_run_flag_b = false;
        // Unlock function
        this->l_stop_recursive_b = false;
    }
    return;
}

/**
  ****************************************************************************
  * Protected function
  ****************************************************************************
  */

wxThread::ExitCode thread_c::Entry()
{
    this->l_run_flag_b = true;
    while(this->l_run_flag_b)
    {
        if(this->lp_data_wxcondition)
        {
            this->lp_data_wxcondition->Wait();
            if(this->l_run_flag_b)
            {
                if (this->l_function_thread_fct)
                {
                    this->l_function_thread_fct(this->lp_parameter_void);
                }
            }
        }
    }
    this->l_run_flag_b = true;
    return (wxThread::ExitCode)0;
}

/**
* @}
*/

/**
* @}
*/

/*****************************************************END OF FILE************/
