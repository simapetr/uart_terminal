#ifndef HW_DR_UART_DRIVER_H_H_INCLUDED
#define HW_DR_UART_DRIVER_H_H_INCLUDED

/**
  ****************************************************************************
  * @file    hw_dr_uart_driver_h.h
  * @author  Ing. Petr Simek
  * @version V2.2
  * @date    29.04.2015
  * @brief   Driver for UART communication
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

#include <stdint.h>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;

#undef DLL_EXPORT

#ifdef NO_LIB
    #define DLL_EXPORT
#else
#ifdef DLL_LIB_BUILD
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif // BUILD_DLL
#endif // DLL_LIB

/**
  * @addtogroup Hardware
  * @{
  */

/**
  * @addtogroup Driver
  * @{
  */

/**
  * @addtogroup UART
  * @{
  */

/**
  ****************************************************************************
  * Enum
  ****************************************************************************
  */

typedef enum
{
    e_rx = 1,
    e_cts = 2,
    e_dsr = 3,
    e_ring = 4,
    e_rlsd = 5,
}uart_com_ctrl_in_t;

typedef enum
{
    e_dtr = 0,
    e_rts = 1,
    e_break = 2,
    e_xoff = 3,
    e_xon = 4
}uart_com_ctrl_out_t;

typedef enum
{
    e_00_open_error = 0,
    e_01_open = 1,
    e_02_handle_error = 2,
    e_03_write_configuration_error = 3,
    e_04_write_timeout_error = 4,
    e_05_close_error = 5,
    e_06_close = 6,
    e_07_opened = 7
}uart_status_t;

/**
  ****************************************************************************
  * Type
  ****************************************************************************
  */

typedef void (*uart_event_fct)(void* p_parametr_void, uint32_t event_type_ui32, uint8_t *p_data_sui8, uint32_t length_ui32);

/**
  ****************************************************************************
  * Struct
  ****************************************************************************
  */

typedef struct
{
    uint32_t bite_timeout_ui32;
    uint32_t baudrate_ui32;
    uint8_t stop_bits_ui8;
    uint8_t parity_ui8;
    uint8_t bit_length_ui8;
    uint8_t port_num_ui8;
}uart_cfg_t;

typedef struct
{
    uart_event_fct p_usr_uart_event_fct;
    void* p_parametr_void;
}uart_event_buffer_t;

/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */

class DLL_EXPORT uart_port
{
public :

    uart_port(void);
    ~uart_port(void);
    string* get_port(void);
    uart_status_t open(uart_cfg_t *p_data_uart_cfg);
    void close(void);
    uint8_t set(uart_event_fct function_uart_event_fct , void* p_parametr_void);
	uint8_t clear(uart_event_fct function_uart_event_fct);
	void clear(void);
	uart_status_t get_state(void);
    uart_cfg_t get(void);
    uint8_t flush(void);
    uint8_t send(uint8_t data_ui8);
    uint8_t send(uint8_t *p_data_sui8, uint32_t len_ui32);
    uint8_t get(uart_com_ctrl_in_t pin_uart_com_ctrl_in);
    void set(uart_com_ctrl_out_t pin_uart_com_ctrl_out, uint8_t state_ui8);

private :

    static DWORD WINAPI uart_thread(PVOID parametr_pvoid);
    void call(uint32_t event_type_ui32, uint8_t *p_data_sui8, uint32_t length_ui32);

    HANDLE uart_thread_handle;
    DWORD uart_thread_id_dword;
    uint32_t uart_thread_run_ui32;

    vector<uart_event_buffer_t> lv_rx_uart_event_buffer;

    // UART variable
    HANDLE port_handle;
    uint8_t l_rx_data_sui8[0x10000];
    uint16_t l_rx_data_ptr_ui16;
    // Overlapped struct
    OVERLAPPED rd_port_overlapped;
    OVERLAPPED wr_port_overlapped;
    // usart config struct
    DCB port_setting_dcb;
    // usart config timeout struct
    COMMTIMEOUTS port_timeouts_commtimeouts;
    // Port status
    COMSTAT port_comstat;
    // Port event type
    DWORD port_event_dword;
    // Critical section
	CRITICAL_SECTION data_critical_section;
	// Bus configuration
	uart_cfg_t data_uart_cfg;
	// Array of available port in system
	string port_buffer_str;
    // UART state
    uart_status_t port_uart_status;
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

/*****************************************************END OF FILE************/

#endif // HW_DR_UART_DRIVER_H_H_INCLUDED
