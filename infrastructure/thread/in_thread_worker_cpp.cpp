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
 * @param [IN] timeout_ui32 : Thread wait timeout
 * @return void
 *
 */

thread_c::thread_c(void *p_parameter_void, thread_fct_t function_thread_fct, uint32_t timeout_ui32)
{
    this->lp_parameter_void = p_parameter_void;
    this->l_function_thread_fct = function_thread_fct;
    this->l_timeout_ui32 = timeout_ui32;
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
    this->signal();
    return;
}

/**
  ****************************************************************************
  * Protected function
  ****************************************************************************
  */

wxThread::ExitCode thread_c::Entry()
{
wxCondError data_wxconderror;

    this->l_run_flag_b = true;
    while(this->l_run_flag_b)
    {
        if (this->l_function_thread_fct)
        {
            if(this->l_timeout_ui32)
            {
                data_wxconderror = this->lp_data_wxcondition->WaitTimeout(this->l_timeout_ui32);
            }
            else
            {
                data_wxconderror = this->lp_data_wxcondition->Wait();
            }
            if((data_wxconderror != wxCOND_NO_ERROR) || (data_wxconderror != wxCOND_TIMEOUT))
            {
                if(this->l_run_flag_b)
                {
                    this->l_function_thread_fct(this->lp_parameter_void);
                }
            }
        }
    }
    return (wxThread::ExitCode)0;
}

/**
* @}
*/

/**
* @}
*/

/*****************************************************END OF FILE************/
