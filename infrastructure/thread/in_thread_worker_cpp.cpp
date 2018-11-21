/**
  ****************************************************************************
  * @file    in_thread_worker_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
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
    this->lp_data_wxcondition->Broadcast();
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
    this->l_run_flag_b = false;
    while(!this->l_run_flag_b){}
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
        if (this->l_function_thread_fct)
        {
            this->lp_data_wxcondition->Wait();
            this->l_function_thread_fct(this->lp_parameter_void);
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
