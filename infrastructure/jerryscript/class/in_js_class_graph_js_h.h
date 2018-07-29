#ifndef IN_JS_CLASS_GRAPH_JS_H_H_INCLUDED
#define IN_JS_CLASS_GRAPH_JS_H_H_INCLUDED

/**
  ****************************************************************************
  * @file    in_js_class_graph_js_h.h
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    18.07.2018
  * @brief   JerryScript wrapper for graph class
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
  * @addtogroup Graph
  * @{
  */

/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */

//class main_frame

class graph_js_c
{
public:

    void reg_host_class (void* p_gui_main_frame_void);
    static uint32_t add(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
    static uint32_t insert_signal(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
    static uint32_t set_data(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
    static uint32_t show(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);

private:

	void* lp_gui_main_frame_void;

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

#endif // IN_JS_CLASS_GRAPH_JS_H_H_INCLUDED
