#ifndef IN_JS_CLASS_TEXTCTRL_JS_H_H_INCLUDED
#define IN_JS_CLASS_TEXTCTRL_JS_H_H_INCLUDED

/**
  ****************************************************************************
  * @file    in_js_class_textctrl_js_h.h
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    29.10.2018
  * @brief   JerryScript wrapper for component textctrl
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
  * @addtogroup Textctrl
  * @{
  */

/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */

class textctrl_js_c
{
    public:

        void reg_host_class (void* p_gui_interface_void);
        static uint32_t add(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
        static uint32_t set(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
        static uint32_t get(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
        static uint32_t append(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);

    private:

        void* lp_gui_interface_void;

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

#endif // IN_JS_CLASS_TEXTCTRL_JS_H_H_INCLUDED
