#ifndef IN_JS_CLASS_TIMER_JS_H_H_INCLUDED
#define IN_JS_CLASS_TIMER_JS_H_H_INCLUDED

/**
  ****************************************************************************
  * @file    in_js_class_time_js_h.h
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

#include "in_thread_worker_h.h"
#include <vector>
using namespace std;

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @addtogroup JerryScript
  * @{
  */

/**
  * @addtogroup Class
  * @{
  */

/**
  * @addtogroup Time
  * @{
  */

/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */

class timer_js_c
{
    public:

        void reg_host_class (void);
        void dereg_host_class (void);
        static uint32_t add(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
        static uint32_t set(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
        static uint32_t start(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
        static uint32_t stop(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
        static uint32_t reset(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
        static void call(void* p_parametr_void);

    private:

        uint32_t l_global_ui32;

};

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

#endif // IN_JS_CLASS_TIMER_JS_H_H_INCLUDED
