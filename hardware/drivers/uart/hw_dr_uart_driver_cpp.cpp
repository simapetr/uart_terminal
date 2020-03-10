/**
  ****************************************************************************
  * @file    hw_dr_uart_driver_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V2.3
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

#include "hw_dr_uart_driver_h.h"
#include <stdio.h>
#include <commdlg.h>
#include <windef.h>


/**
  * @defgroup Hardware
  * @brief Hardware layer
  * @{
  */

/**
  * @defgroup Driver
  * @brief Device driver
  * @{
  */

/**
  * @defgroup UART
  * @brief UART communication bus
  * @{
  */

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Constructor
 *
 * @param void
 * @return void
 *
 */

uart_port::uart_port(void)
{
    // Get available port
    this->get_port();
    // Initialization private variable
    this->port_handle = NULL;
    this->rd_port_overlapped.hEvent = NULL;
    this->wr_port_overlapped.hEvent = NULL;
    // initialize critical section
	InitializeCriticalSection(&this->data_critical_section);
    // Initialization port state
    this->port_uart_status = e_06_close;
}

/** @brief Destructor
 *
 * @param void
 * @return void
 *
 */

uart_port::~uart_port(void)
{
    this->close();
}

/** @brief Get pointer on port array
 *
 * @param void
 * @return string : Pointer on available port array
 *
 */

string* uart_port::get_port(void)
{
uint32_t item_cnt_ui32;
uint32_t port_buffer_ui32 = 0;
DWORD num_avalible_port_dword = 0;
TCHAR value_buffer_stchar[128];
DWORD value_read_length_dword;
BYTE  data_buffer_stchar[16];
DWORD data_read_length_dword;
HKEY registry_hkey;
LONG registry_read_res_long = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"HARDWARE\\DEVICEMAP\\SERIALCOMM", 0, KEY_READ, &registry_hkey);

    // Get the class name and the value count.
    if (ERROR_SUCCESS == registry_read_res_long)
    {
        registry_read_res_long = RegQueryInfoKey(registry_hkey, NULL, NULL, NULL, NULL, NULL, NULL, &num_avalible_port_dword, NULL, NULL, NULL, NULL);
        if (ERROR_SUCCESS == registry_read_res_long)
        {
            // Clear port string
            this->port_buffer_str.clear();
            // Read value data
            for (item_cnt_ui32 = 0 ; item_cnt_ui32 < num_avalible_port_dword ; item_cnt_ui32++)
            {
                value_read_length_dword = 128;
                data_read_length_dword = 16;
                value_buffer_stchar[0] = '\0';
                data_buffer_stchar[0] = '\0';
                registry_read_res_long = RegEnumValue(registry_hkey, item_cnt_ui32, value_buffer_stchar, &value_read_length_dword, NULL, NULL, data_buffer_stchar, &data_read_length_dword);
                if (ERROR_SUCCESS == registry_read_res_long)
                {
                    sscanf((const char*)data_buffer_stchar,"COM%u",&port_buffer_ui32);
                    this->port_buffer_str.push_back((uint8_t)port_buffer_ui32);
                }
            }
        }
        // Close registry
        RegCloseKey(registry_hkey);
    }
    return &this->port_buffer_str;
}

/** @brief Open and set UART port communication
 *
 * @param [IN] p_data_uart_cfg : UART port configuration struct
 * @return Status
 *
 */

uart_status_t uart_port::open(uart_cfg_t *p_data_uart_cfg)
{
uart_status_t data_uart_status = e_00_open_error;
// Port name buffer
char uart_name_si8[20];
// Port number position
size_t port_position_size = string::npos;

    // Save bus configuration
    this->data_uart_cfg = *p_data_uart_cfg;
    if (this->port_uart_status == e_01_open)
    {
        data_uart_status = e_07_opened;
    }
    else
    {
        port_position_size = this->port_buffer_str.find_first_of(this->data_uart_cfg.port_num_ui8);
        if ((this->data_uart_cfg.port_num_ui8 > 0) && (port_position_size != string::npos))
        {
            if (this->port_uart_status != e_01_open)
            {
                if (this->port_uart_status != e_06_close)
                {
                    this->close();
                }
                // enter critical section
                EnterCriticalSection(&this->data_critical_section);
                // Open port
                sprintf(&uart_name_si8[0],"\\\\.\\COM%d",(int)this->data_uart_cfg.port_num_ui8);
                this->port_handle = CreateFile(&uart_name_si8[0], GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
                if (this->port_handle != INVALID_HANDLE_VALUE)
                {
                    // Test for open port
                    if (GetCommState(this->port_handle, &this->port_setting_dcb))
                    {
                        // Timeout setting
                        GetCommTimeouts(this->port_handle,&this->port_timeouts_commtimeouts);
                        if (this->data_uart_cfg.bite_timeout_ui32)
                        {
                            this->port_timeouts_commtimeouts.ReadIntervalTimeout = this->data_uart_cfg.bite_timeout_ui32;
                            this->port_timeouts_commtimeouts.ReadTotalTimeoutMultiplier = 1;
                            this->port_timeouts_commtimeouts.ReadTotalTimeoutConstant = 1;
                            this->port_timeouts_commtimeouts.WriteTotalTimeoutMultiplier = 0;
                            this->port_timeouts_commtimeouts.WriteTotalTimeoutConstant = 0;
                            if (!SetCommTimeouts(this->port_handle, &this->port_timeouts_commtimeouts))
                            {
                                data_uart_status = e_04_write_timeout_error;
                            }
                        }
                        if (data_uart_status != e_04_write_timeout_error)
                        {
                            // Initialization DCB struct
                            memset(&this->port_setting_dcb, 0,sizeof(DCB));
                            this->port_setting_dcb.DCBlength = sizeof(DCB);
                            // Configuration setting
                            this->port_setting_dcb.BaudRate = (DWORD)this->data_uart_cfg.baudrate_ui32;
                            this->port_setting_dcb.ByteSize = (BYTE)this->data_uart_cfg.bit_length_ui8;
                            this->port_setting_dcb.Parity = (BYTE)this->data_uart_cfg.parity_ui8;
                            this->port_setting_dcb.StopBits = (BYTE)this->data_uart_cfg.stop_bits_ui8;
                            this->port_setting_dcb.fDsrSensitivity = 0;
                            this->port_setting_dcb.fDtrControl = DTR_CONTROL_ENABLE;
                            this->port_setting_dcb.fOutxDsrFlow = 0;
                            if (SetCommState(this->port_handle, &this->port_setting_dcb))
                            {
                                SetCommMask(this->port_handle, (EV_RXCHAR | EV_CTS | EV_DSR | EV_RING | EV_RLSD));
                                this->flush();
                                printf("UART open : %u %u %u-%u-%u\n", this->data_uart_cfg.port_num_ui8, this->data_uart_cfg.baudrate_ui32, this->data_uart_cfg.bit_length_ui8, this->data_uart_cfg.parity_ui8, this->data_uart_cfg.stop_bits_ui8);
                                data_uart_status =  e_01_open;
                            }
                            else
                            {
                                data_uart_status =  e_03_write_configuration_error;
                            }
                        }
                        else
                        {
                            data_uart_status =  e_04_write_timeout_error;
                        }
                    }
                    else
                    {
                        data_uart_status =  e_00_open_error;
                    }
                    // Set overlaped event
                    memset(&this->rd_port_overlapped, 0x00, sizeof(this->rd_port_overlapped));
                    this->rd_port_overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
                    this->rd_port_overlapped.Offset = 0;
                    this->rd_port_overlapped.OffsetHigh = 0;
                    memset(&this->wr_port_overlapped, 0x00, sizeof(this->wr_port_overlapped));
                    this->wr_port_overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
                    this->wr_port_overlapped.Offset = 0;
                    this->wr_port_overlapped.OffsetHigh = 0;
                    // Run com event thread
                    this->uart_thread_handle = CreateThread(0, 0x1000, (LPTHREAD_START_ROUTINE)this->uart_thread, (LPVOID) this, 0, &this->uart_thread_id_dword);
                }
                else
                {
                    data_uart_status = e_02_handle_error;
                }
                // release critical section
                LeaveCriticalSection(&this->data_critical_section);
            }
        }
        this->port_uart_status = data_uart_status;
    }
    return data_uart_status;
}

/** @brief Close UART port communication
 *
 * @param void
 * @return void
 *
 */

void uart_port::close(void)
{
    if (this->port_uart_status != e_06_close)
    {
        if (this->port_handle != INVALID_HANDLE_VALUE)
        {
            // Terminate event thread
            this->uart_thread_run_ui32 = 0;
            Sleep(200);
            PurgeComm(this->port_handle, PURGE_TXCLEAR | PURGE_RXCLEAR);
            CloseHandle(this->port_handle);
            // Initialization UART handle
            this->port_handle = NULL;
            // Change port state
            this->port_uart_status = e_06_close;
        }
        else
        {
            this->port_uart_status = e_05_close_error;
        }
    }
    return;
}

/** @brief Associate driver event function
 *
 * @param [IN] function_uart_event_fct : Pointer on event function
 * @param [IN] p_parameter_void : Input thread parameter
 * @param  p_parametr_void : parameter for event function
 *    @arg 0 : Event is registered
 *    @arg 1 : Event stored
 *
 */

uint8_t uart_port::set(uart_event_fct function_uart_event_fct , void* p_parametr_void)
{
uint8_t status_ui8 = 1;
uint8_t event_counter_ui8 = 0;
uart_event_buffer_t data_bkp_uart_event_buffer;

    for (event_counter_ui8 = 0 ; (event_counter_ui8 < this->lv_rx_uart_event_buffer.size()) && (status_ui8 == 1) ; event_counter_ui8++)
	{
		if (
            this->lv_rx_uart_event_buffer[event_counter_ui8].p_usr_uart_event_fct == function_uart_event_fct &&
            this->lv_rx_uart_event_buffer[event_counter_ui8].p_parametr_void == p_parametr_void
           )
		{
			status_ui8 = 0;
		}
	}
	if ( status_ui8 == 1)
	{
		data_bkp_uart_event_buffer.p_usr_uart_event_fct = function_uart_event_fct;
		data_bkp_uart_event_buffer.p_parametr_void = p_parametr_void;
        this->lv_rx_uart_event_buffer.push_back(data_bkp_uart_event_buffer);
	}
	return status_ui8;
}

/** @brief Delete associated event function
 *
 * @param [IN] function_uart_event_fct : Pointer on event function
 * @return uint8_t : Status event registration
 *    @arg 0 : Event was not associated
 *    @arg 1 : Event deleted
 *
 */

uint8_t uart_port::clear(uart_event_fct function_uart_event_fct)
{
uint8_t status_ui8 = 0;
uint8_t event_counter_ui8 = 0;

    for (event_counter_ui8 = 0 ; event_counter_ui8 < this->lv_rx_uart_event_buffer.size() ; event_counter_ui8++)
	{
		if ( this->lv_rx_uart_event_buffer[event_counter_ui8].p_usr_uart_event_fct == function_uart_event_fct)
		{
		    this->lv_rx_uart_event_buffer.erase(this->lv_rx_uart_event_buffer.begin() + event_counter_ui8);
			status_ui8 = 1;
		}
	}
    return status_ui8;
}

/** @brief Delete all associated event
 *
 * @param void
 * @return void
 *
 */

void uart_port::clear(void)
{
    this->lv_rx_uart_event_buffer.clear();
    return;
}

/** @brief Get port status (call after construction object for test correct open)
 *
 * @param void
 * @return uint8_t : uart_status_t
 *
 */

uart_status_t uart_port::get_state(void)
{
    return this->port_uart_status;
}

/** @brief Get port configuration
 *
 * @param void
 * @return uart_cfg_t : Port configuration structure
 *
 */

uart_cfg_t uart_port::get(void)
{
    return this->data_uart_cfg;
}

/** @brief Erase communication buffer
 *
 * @param void
 * @return uint8_t : status
 *    @arg 0 : Clear procedure fail
 *    @arg 1 : Buffer is empty
 *
 */

uint8_t uart_port::flush (void)
{
    return FlushFileBuffers(this->port_handle);
}

/** @brief Write character
 *
 * @param [IN] data_ui8 : Data character
 * @return uint8_t : status
 *    @arg 0 : Data not send
 *    @arg 1 : Data send correctly
 *
 */

uint8_t uart_port::send(uint8_t data_ui8)
{
uint8_t status_value_ui8 = 0;
DWORD write_bite_dword = 0;

    EnterCriticalSection(&this->data_critical_section);
    if (!WriteFile(this->port_handle, &data_ui8, 1, NULL, &wr_port_overlapped))
    {
        if (ERROR_IO_PENDING == GetLastError())
        {
            if (GetOverlappedResult(this->port_handle, &wr_port_overlapped, &write_bite_dword, true))
            {
                if(write_bite_dword == 1)
                {
                    status_value_ui8 = 1;
                }
                else
                {
                    printf("Tx error length %d\n", (uint32_t)write_bite_dword);
                }
            }
            else
            {
                printf("Tx error overlapped %d.\n", (uint32_t)GetLastError());
            }
        }
    }
    else
    {
        printf("Tx error write file\n");
    }
    LeaveCriticalSection(&this->data_critical_section);
    return status_value_ui8;
}

/** @brief Write data string
 *
 * @param [IN] p_data_sui8 : Pointer on data buffer
 * @param [IN] len_ui32 : Buffer length
 * @return uint8_t : status
 *    @arg 0 : Data not send
 *    @arg 1 : Data send correctly
 *
 */

uint8_t uart_port::send(uint8_t *p_data_sui8, uint32_t len_ui32)
{
uint8_t status_value_ui8 = 0;
DWORD write_bite_dword = 0;

    EnterCriticalSection(&data_critical_section);
    if (!WriteFile(this->port_handle, p_data_sui8, len_ui32, NULL, &wr_port_overlapped))
    {
        if (ERROR_IO_PENDING == GetLastError())
        {
            if (GetOverlappedResult(this->port_handle, &wr_port_overlapped, &write_bite_dword, true))
            {
                if(write_bite_dword == len_ui32)
                {
                    status_value_ui8 = 1;
                }
                else
                {
                    printf("Tx error length %d\n", (uint32_t)write_bite_dword);
                }
            }
            else
            {
                printf("Tx error overlapped %d.\n", (uint32_t)GetLastError());
            }
        }
    }
    else
    {
        printf("Tx error write file\n");
    }
    LeaveCriticalSection(&this->data_critical_section);
    return status_value_ui8;
}

/** @brief Get com state
 *
 * @param [IN] pin_uart_com_ctrl_in : Pin ID
 * @return uint8_t : Pin state
 *
 */

uint8_t uart_port::get(uart_com_ctrl_in_t pin_uart_com_ctrl_in)
{
uint8_t status_ui8 = 0;
DWORD status_dword;

    // Read modem status
    if (GetCommModemStatus(this->port_handle, &status_dword))
    {
        switch(pin_uart_com_ctrl_in)
        {
            case e_cts:
            {
                status_ui8 = ((status_dword & MS_CTS_ON) > 1) ? 0 : 1;
            }
            break;
            case e_dsr:
            {
                status_ui8 = ((status_dword & MS_DSR_ON) > 1) ? 0 : 1;
            }
            break;
            case e_ring:
            {
                status_ui8 = ((status_dword & MS_RING_ON) > 1) ? 0 : 1;
            }
            break;
            case e_rlsd:
            {
                status_ui8 = ((status_dword & MS_RLSD_ON) > 1) ? 0 : 1;
            }
            break;
            default:
            {

            }
            break;
        }
    }
    return status_ui8;
}

/** @brief Set com state
 *
 * @param [IN] pin_uart_com_ctrl_out : Pin ID
 * @param [IN] state_ui8 : UART control pin state
 * @return uint8_t : Pin state
 *
 */

void uart_port::set(uart_com_ctrl_out_t pin_uart_com_ctrl_out, uint8_t state_ui8)
{
    switch(pin_uart_com_ctrl_out)
    {
        case e_dtr:
        {
            if(state_ui8)
            {
                EscapeCommFunction(this->port_handle,CLRDTR);
            }
            else
            {
                EscapeCommFunction(this->port_handle,SETDTR);
            }
        }
        break;
        case e_rts:
        {
            if(state_ui8)
            {
                EscapeCommFunction(this->port_handle,CLRRTS);
            }
            else
            {
                EscapeCommFunction(this->port_handle,SETRTS);
            }
        }
        break;
        case e_break:
        {
            if(state_ui8)
            {
                EscapeCommFunction(this->port_handle,CLRBREAK);
            }
            else
            {
                EscapeCommFunction(this->port_handle,SETBREAK);
            }
        }
        break;
        case e_xoff:
        {
            EscapeCommFunction(this->port_handle,SETXOFF);
        }
        break;
        case e_xon:
        {
            EscapeCommFunction(this->port_handle,SETXON);
        }
        break;
        default:
        {

        }
        break;
    }
    return;
}

/** @brief UART read thread
 *
 * @param [IN] parametr_pvoid : Create parameter
 * @return DWORD : Thread terminate status
 *
 */

DWORD WINAPI uart_port::uart_thread(PVOID parametr_pvoid)
{
uart_port *p_bkp_this = (uart_port*)parametr_pvoid;
DWORD read_bite_dword;
BOOL read_flag_b = TRUE;
DWORD error_dword = 0;
BOOL wait_com_result_b = TRUE;
DWORD event_mask_dword;
COMSTAT port_comstat;

    if(p_bkp_this)
    {
        p_bkp_this->uart_thread_run_ui32 = 1;
        while(p_bkp_this->uart_thread_run_ui32)
        {
            if (WaitCommEvent(p_bkp_this->port_handle, &event_mask_dword, &p_bkp_this->rd_port_overlapped))
            {
                p_bkp_this->l_rx_data_ptr_ui16 = 0;
                p_bkp_this->call(event_mask_dword, &p_bkp_this->l_rx_data_sui8[0], p_bkp_this->l_rx_data_ptr_ui16);
            }
            else
            {
                // Wait for overlaped event
                switch (WaitForSingleObject(p_bkp_this->rd_port_overlapped.hEvent, INFINITE))
                {
                    case WAIT_TIMEOUT:
                    {
                        printf("Wait Rx failed top\n");
                    }
                    break;
                    case WAIT_OBJECT_0:
                    {
                        // Check if is IO pending
                        DWORD dwRet = GetLastError();
                        if( ERROR_IO_PENDING == dwRet)
                        {
                            EnterCriticalSection(&p_bkp_this->data_critical_section);
                            p_bkp_this->l_rx_data_ptr_ui16 = 0;
                            read_flag_b = TRUE;
                            while (read_flag_b)
                            {
                                wait_com_result_b = ClearCommError(p_bkp_this->port_handle, &error_dword, &port_comstat);
                                if (port_comstat.cbInQue == 0)
                                {
                                    read_flag_b = FALSE;
                                }
                                else
                                {
                                    if (wait_com_result_b)
                                    {
                                        if (!ReadFile( p_bkp_this->port_handle, &p_bkp_this->l_rx_data_sui8[p_bkp_this->l_rx_data_ptr_ui16], 1, NULL, &p_bkp_this->rd_port_overlapped))
                                        {
                                            if (GetLastError() == ERROR_IO_PENDING)
                                            {
                                                if (GetOverlappedResult(p_bkp_this->port_handle, &p_bkp_this->rd_port_overlapped, &read_bite_dword, true))
                                                {
                                                    if(read_bite_dword)
                                                    {
                                                        p_bkp_this->l_rx_data_ptr_ui16++;
                                                    }
                                                    else
                                                    {
                                                        read_flag_b = FALSE;
                                                    }
                                                }
                                                else
                                                {
                                                    printf("Rx error owerlaped %d.\n", (int)GetLastError());
                                                }
                                            }
                                            else
                                            {
                                                printf("Rx failed read error %d.\n", (int)GetLastError());
                                            }
                                        }
                                        else
                                        {
                                            p_bkp_this->l_rx_data_ptr_ui16++;
                                            if(p_bkp_this->l_rx_data_ptr_ui16 == 0xFFFF)
                                            {
                                                // Send full buffer
                                                read_flag_b = FALSE;
                                            }
                                        }
                                    }
                                }
                            }
                            // Call all registered event
                            if(p_bkp_this->l_rx_data_ptr_ui16 || (event_mask_dword &(~EV_RXCHAR)))
                            {
                                // Call events
                                p_bkp_this->call(event_mask_dword, &p_bkp_this->l_rx_data_sui8[0], p_bkp_this->l_rx_data_ptr_ui16);
                            }
                            LeaveCriticalSection(&p_bkp_this->data_critical_section);
                        }
                    }
                    break;
                    default:
                    {
                        printf("Wait Rx failed top default\n");
                    }
                    break;
                }
            }
        }
    }
    return NO_ERROR;
}

/** @brief Call all registered Rx event
 *
 * @param [IN] event_type_ui32 : Call event type
 * @param [IN] p_data_sui8 : Rx data buffer
 * @param [IN] length_ui32 : Rx data length
 * @return void
 *
 */

void uart_port::call(uint32_t event_type_ui32, uint8_t *p_data_sui8, uint32_t length_ui32)
{
uint32_t event_counter_ui32;
uint32_t port_ui32;

    // Get port number
    port_ui32 = this->data_uart_cfg.port_num_ui8;
    port_ui32 <<= 24;
    event_type_ui32 |= port_ui32;
    // Call all callback
    for (event_counter_ui32 = 0 ; event_counter_ui32 < this->lv_rx_uart_event_buffer.size() ; event_counter_ui32++)
    {
        // Call event
        this->lv_rx_uart_event_buffer[event_counter_ui32].p_usr_uart_event_fct(this->lv_rx_uart_event_buffer[event_counter_ui32].p_parametr_void, event_type_ui32, p_data_sui8, length_ui32);
    }
    return;
}

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
