#ifndef IN_JS_CLASS_PROJECT_JS_H_H_INCLUDED
#define IN_JS_CLASS_PROJECT_JS_H_H_INCLUDED

/**
  ****************************************************************************
  * @file    in_js_class_project_js_h.h
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
  * @addtogroup Project
  * @{
  */

/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */

class project_js_c
{
    public:

        void reg_host_class (wxString project_str);
        static uint32_t read(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
        static uint32_t write(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);

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

#endif // IN_JS_CLASS_PROJECT_JS_H_H_INCLUDED
