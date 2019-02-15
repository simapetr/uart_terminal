#ifndef IN_JS_CLASS_UART_JS_H_H_INCLUDED
#define IN_JS_CLASS_UART_JS_H_H_INCLUDED

/**
  ****************************************************************************
  * @file    in_js_class_uart_js_h.h
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    18.04.2018
  * @brief   JerryScript wrapper for uart_port class
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
#include "hw_dr_uart_driver_h.h"
#include "in_thread_worker_h.h"

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
  * @addtogroup UART
  * @{
  */

/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */

class uart_js_c
{
public:

    void reg_host_class (uart_port* p_com_uart_port);
    void dereg_host_class (void);
    static uint32_t open(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
    static uint32_t close(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
    static uint32_t reg_event(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
    static uint32_t write(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
    static uint32_t get_ctrl(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);
    static uint32_t set_ctrl(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32);

private:

    static void rx_event(void* p_parametr_void, uint32_t event_type_ui32, uint8_t *p_data_sui8, uint32_t length_ui32);
    static void rx_queue(void* p_parametr_void);
    static void tx_queue(void* p_parametr_void);

	uart_port* lp_com_uart_port;
	uint8_t l_rx_event_name_sui8[256];
    thread_c *lp_rx_thread;
    thread_c *lp_tx_thread;
    uint32_t l_reg_fct_ui32;
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

#endif // IN_JS_CLASS_UART_JS_H_H_INCLUDED
