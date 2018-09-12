#ifndef IN_JS_CLASS_PANEL_JS_H_H_INCLUDED
#define IN_JS_CLASS_PANEL_JS_H_H_INCLUDED

/**
  ****************************************************************************
  * @file    in_js_class_sizer_js_h.h
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    26.08.2018
  * @brief   JerryScript wrapper for panel
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
  * @addtogroup Panel
  * @{
  */

/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */

class panel_js_c
{
public:

    void reg_host_class (void* p_gui_interface_void);
    static uint32_t add(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
    static uint32_t get_sizer(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);

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

#endif // IN_JS_CLASS_PANEL_JS_H_H_INCLUDED
