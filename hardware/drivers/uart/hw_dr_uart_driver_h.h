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
    void get_port(void);
    string* get_bus_array(void);
    uart_status_t open(uart_cfg_t *p_data_uart_cfg);
    void close(void);
    uint8_t create_event(uart_event_fct function_uart_event_fct , void* p_parametr_void);
	uint8_t delete_event(uart_event_fct function_uart_event_fct);
	void delete_event_all(void);
    uart_status_t get_state(void);
    uint32_t get_last_error(void);
    uint32_t wait_rx_event(void);
    uint8_t flush(void);
    uint8_t write_data(uint8_t data_ui8);
    uint8_t write_data(uint8_t *p_data_sui8, uint32_t len_ui32);
    uint8_t write_data(vector<uint8_t>& pv_data_sui8);
    uint8_t read_data(uint8_t *p_data_ui8);
    uint8_t read_data(string *p_data_str);
    uint8_t get_com_ctrl(uart_com_ctrl_in_t pin_uart_com_ctrl_in);
    void set_com_ctrl(uart_com_ctrl_out_t pin_uart_com_ctrl_out, uint8_t state_ui8);

private :

    static DWORD WINAPI uart_thread(PVOID parametr_pvoid);

    HANDLE uart_thread_handle;
    DWORD uart_thread_id_dword;
    uint32_t uart_thread_run_ui32;

    vector<uart_event_buffer_t> lv_rx_uart_event_buffer;

    // UART variable
    HANDLE port_handle;
    // Overlapped struct
    OVERLAPPED port_overlapped;
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
	// Array of available port in system
	string port_buffer_str;
    // UART state
    uart_status_t port_uart_status;
    // Port error
    uint32_t port_error_ui32;
    // Read data
    string read_data_buffer_str;
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
