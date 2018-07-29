#ifndef IN_JS_CLASS_GUI_JS_H_H_INCLUDED
#define IN_JS_CLASS_GUI_JS_H_H_INCLUDED

/**
  ****************************************************************************
  * @file    in_js_class_gui_js_h.h
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    25.04.2018
  * @brief   JerryScript wrapper for main_frame class
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
  * @addtogroup GUI
  * @{
  */

/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */

//class main_frame

class main_frame_js_c
{
public:

    void reg_host_class (void* p_gui_main_frame_void);
    static uint32_t console_rx_enable(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
    static uint32_t is_console_rx_enable(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
    static uint32_t printf(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
    static uint32_t status(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
    static uint32_t clear(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
    static uint32_t open(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
    static uint32_t close(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
    static uint32_t get_open_status(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
    static uint32_t get_data(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
    static uint32_t set_progress(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);

private:

	void* lp_gui_main_frame_void;
	void* lp_data_wxtextentrydialog_void;

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

#endif // IN_JS_CLASS_GUI_JS_H_H_INCLUDED
