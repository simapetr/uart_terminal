#ifndef IN_THREAD_WORKER_H_H_INCLUDED
#define IN_THREAD_WORKER_H_H_INCLUDED

/**
  ****************************************************************************
  * @file    in_thread_h.h
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

#include <wx/thread.h>
#include "stdint.h"

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @addtogroup Thread
  * @{
  */

/**
  ****************************************************************************
  * Type
  ****************************************************************************
  */

typedef void (*thread_fct_t)(void* p_parametr_void);

/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */

class thread_c : public wxThread
{
public:

    thread_c(void *p_parameter_void, thread_fct_t function_thread_fct);
    ~thread_c(void);
    void signal(void);
    void stop(void);

protected:

    virtual ExitCode Entry();

    void *lp_parameter_void;
    bool l_run_flag_b;
    bool l_stop_recursive_b;
    uint8_t l_timeout_cnt_ui8;
    thread_fct_t l_function_thread_fct;
    wxMutex *lp_data_wxmutex;
    wxCondition *lp_data_wxcondition;

};

/**
* @}
*/

/**
* @}
*/

/*****************************************************END OF FILE************/

#endif // IN_THREAD_WORKER_H_H_INCLUDED
