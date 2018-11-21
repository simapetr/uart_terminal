/**
  ****************************************************************************
  * @file    hw_dr_uart_driver_cpp.cpp
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
    this->get_port();
    // Initialization private variable
    this->port_handle = NULL;
    this->port_overlapped.hEvent = NULL;
    // initialize critical section
	InitializeCriticalSection(&data_critical_section);
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

/** @brief Get UART port list
 *
 * @param void
 * @return void
 *
 */

void uart_port::get_port ( void )
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
    return;
}

/** @brief Get pointer on port array
 *
 * @param void
 * @return string : Pointer on available port array
 *
 */

string* uart_port::get_bus_array(void)
{
    return &this->port_buffer_str;
}

/** @brief Open and set UART port communication
 *
 * @param [IN] p_data_uart_cfg : UART port configuration struct
 * @return Status
 *
 */

uart_status_t uart_port::open (uart_cfg_t *p_data_uart_cfg)
{
uart_status_t data_uart_status = e_00_open_error;
// Port name buffer
char uart_name_si8[20];
// Port number position
size_t port_position_size = string::npos;

    if (this->port_uart_status == e_01_open)
    {
        data_uart_status = e_07_opened;
    }
    else
    {
        port_position_size = this->port_buffer_str.find_first_of(p_data_uart_cfg->port_num_ui8);
        if ((p_data_uart_cfg->port_num_ui8 > 0) && (port_position_size != string::npos))
        {
            if (this->port_uart_status != e_01_open)
            {
                if (this->port_uart_status != e_06_close)
                {
                    this->close();
                }
                // enter critical section
                EnterCriticalSection(&data_critical_section);
                // Open port
                sprintf(&uart_name_si8[0],"\\\\.\\COM%d",(int)p_data_uart_cfg->port_num_ui8);
                this->port_handle = CreateFile(&uart_name_si8[0], GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
                if (this->port_handle != INVALID_HANDLE_VALUE)
                {
                    // Test for open port
                    if (GetCommState(this->port_handle, &this->port_setting_dcb))
                    {
                        // Timeout setting
                        GetCommTimeouts(this->port_handle,&this->port_timeouts_commtimeouts);
                        if (p_data_uart_cfg->bite_timeout_ui32)
                        {
                            this->port_timeouts_commtimeouts.ReadIntervalTimeout = p_data_uart_cfg->bite_timeout_ui32;
                            this->port_timeouts_commtimeouts.ReadTotalTimeoutMultiplier = 1;
                            this->port_timeouts_commtimeouts.ReadTotalTimeoutConstant = 1;
                            this->port_timeouts_commtimeouts.WriteTotalTimeoutMultiplier = 0;
                            this->port_timeouts_commtimeouts.WriteTotalTimeoutConstant = 0;
                        }
                        else
                        {
                            this->port_timeouts_commtimeouts.ReadIntervalTimeout = MAXDWORD;
                            this->port_timeouts_commtimeouts.ReadTotalTimeoutMultiplier = 0;
                            this->port_timeouts_commtimeouts.ReadTotalTimeoutConstant = 0;
                            this->port_timeouts_commtimeouts.WriteTotalTimeoutMultiplier = 0;
                            this->port_timeouts_commtimeouts.WriteTotalTimeoutConstant = 0;
                        }
                        if (SetCommTimeouts(this->port_handle, &this->port_timeouts_commtimeouts))
                        {
                            // Initialization DCB struct
                            memset(&this->port_setting_dcb, 0,sizeof(DCB));
                            this->port_setting_dcb.DCBlength = sizeof(DCB);
                            // Configuration setting
                            this->port_setting_dcb.BaudRate = (DWORD)p_data_uart_cfg->baudrate_ui32;
                            this->port_setting_dcb.ByteSize = (BYTE)p_data_uart_cfg->bit_length_ui8;
                            this->port_setting_dcb.Parity = (BYTE)p_data_uart_cfg->parity_ui8;
                            this->port_setting_dcb.StopBits = (BYTE)p_data_uart_cfg->stop_bits_ui8;
                            this->port_setting_dcb.fDsrSensitivity = 0;
                            this->port_setting_dcb.fDtrControl = DTR_CONTROL_ENABLE;
                            this->port_setting_dcb.fOutxDsrFlow = 0;

                            if (SetCommState(this->port_handle, &this->port_setting_dcb))
                            {
                                SetCommMask(this->port_handle, (EV_RXCHAR | EV_CTS | EV_DSR | EV_RING | EV_RLSD));
                                this->flush();
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
                    memset(&this->port_overlapped, 0x00, sizeof(this->port_overlapped));
                    this->port_overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
                    this->port_overlapped.Offset = 0;
                    this->port_overlapped.OffsetHigh = 0;
                    // Run com event thread
                    this->uart_thread_handle = CreateThread(0, 0x1000, (LPTHREAD_START_ROUTINE)this->uart_thread, (LPVOID) this, 0, &this->uart_thread_id_dword);
                }
                else
                {
                    data_uart_status = e_02_handle_error;
                }
                // release critical section
                LeaveCriticalSection(&data_critical_section);
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

void uart_port::close ( void )
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

uint8_t uart_port::create_event (uart_event_fct function_uart_event_fct , void* p_parametr_void)
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

uint8_t uart_port::delete_event (uart_event_fct function_uart_event_fct)
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

void uart_port::delete_event_all (void)
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

/** @brief Get port last error
 *
 * @param void
 * @return uint32_t : Port last error
 *
 */

uint32_t uart_port::get_last_error(void)
{
    return this->port_error_ui32;
}

/** @brief Wait for receive data
 *
 * @param void
 * @return uint32_t : Com status mask
 *
 */

uint32_t uart_port::wait_rx_event(void)
{
uint32_t status_value_ui32 = 0;
uint8_t read_data_ui8 = 0;
BOOL wait_com_result_b = TRUE;
BOOL read_status_b = TRUE;
BOOL read_flag_b = TRUE;
DWORD error_dword = 0;
DWORD com_event_mask_dword = 0;
DWORD read_bites_dword = 0;

    wait_com_result_b = WaitCommEvent(this->port_handle, &this->port_event_dword, &this->port_overlapped);
    if (!wait_com_result_b)
    {
        switch (error_dword = GetLastError())
        {
            case ERROR_IO_PENDING:
            {
                break;
            }
            case 87:
            {
                break;
            }
            default:
            {
                break;
            }
        }
    }
    else
    {
        wait_com_result_b = ClearCommError(this->port_handle, &error_dword, &this->port_comstat);
    }

    this->port_event_dword = WaitForSingleObject(this->port_overlapped.hEvent,INFINITE);
    switch (this->port_event_dword)
    {
        case WAIT_OBJECT_0:
        {
            GetCommMask(this->port_handle, &com_event_mask_dword);
            status_value_ui32 = com_event_mask_dword;
            status_value_ui32 &= ~EV_RXCHAR;
            if (com_event_mask_dword & EV_RXCHAR)
            {
                // Clear buffer
                this->read_data_buffer_str.clear();
                // Read new data
                while (read_flag_b)
                {
                    EnterCriticalSection(&data_critical_section);
                    wait_com_result_b = ClearCommError(this->port_handle, &error_dword, &this->port_comstat);
                    LeaveCriticalSection(&data_critical_section);
                    if (this->port_comstat.cbInQue == 0)
                    {
                        read_flag_b = FALSE;
                        if (this->read_data_buffer_str.size())
                        {
                            status_value_ui32 = com_event_mask_dword;
                        }
                    }
                    else
                    {
                        EnterCriticalSection(&data_critical_section);
                        if (wait_com_result_b)
                        {
                            read_status_b = ReadFile( this->port_handle, &read_data_ui8, 1, &read_bites_dword, &this->port_overlapped);
                            if (!read_status_b)
                            {
                                switch (error_dword = GetLastError())
                                {
                                    case ERROR_IO_PENDING:
                                    {
                                        wait_com_result_b = FALSE;
                                    }
                                    break;
                                    default:
                                    {
                                    }
                                    break;
                                }
                            }
                            else
                            {
                                this->read_data_buffer_str.push_back(read_data_ui8);
                                wait_com_result_b = TRUE;
                            }
                        }

                        if (!read_status_b)
                        {
                            read_status_b = TRUE;
                            read_status_b = GetOverlappedResult(this->port_handle,&this->port_overlapped,&read_bites_dword,TRUE);
                            if (!read_status_b)
                            {
                            }
                        }
                        LeaveCriticalSection(&data_critical_section);
                    }
                }
            }
        }
        break;
        // An error occurred
        default:
        {
        }
        break;
    }
    return status_value_ui32;
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
    PurgeComm(this->port_handle, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
}

/** @brief Write character
 *
 * @param [IN] data_ui8 : Data character
 * @return uint8_t : status
 *    @arg 0 : Data not send
 *    @arg 1 : Data send correctly
 *
 */

uint8_t uart_port::write_data(uint8_t data_ui8)
{
uint8_t status_value_ui8 = 0;
DWORD write_bite_dword = 0;
    if (WriteFile( this->port_handle, &data_ui8, 1, &write_bite_dword, &this->port_overlapped))
    {
        if (write_bite_dword == 1)
        {
            status_value_ui8 = 1;
        }
    }
    else
    {
        if (ERROR_IO_PENDING == GetLastError())
        {
            status_value_ui8 = 1;
        }
    }
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

uint8_t uart_port::write_data(uint8_t *p_data_sui8, uint32_t len_ui32)
{
uint8_t status_value_ui8 = 0;
DWORD write_bite_dword = 0;
static uint8_t *fp_data_bkp_sui8 = NULL;
uint32_t data_cnt_ui32;

    if (fp_data_bkp_sui8)
    {
        delete[] fp_data_bkp_sui8;
    }
    fp_data_bkp_sui8 = new uint8_t[len_ui32];
    for (data_cnt_ui32 = 0; data_cnt_ui32 < len_ui32; data_cnt_ui32++)
    {
        fp_data_bkp_sui8[data_cnt_ui32] = p_data_sui8[data_cnt_ui32];
    }
    if (WriteFile( this->port_handle, fp_data_bkp_sui8, len_ui32, &write_bite_dword, &this->port_overlapped))
    {
        if (write_bite_dword == len_ui32)
        {
            status_value_ui8 = 1;
        }
    }
    else
    {
        if (ERROR_IO_PENDING == GetLastError())
        {
            status_value_ui8 = 1;
        }
    }

    return status_value_ui8;
}

/** @brief Write data vector
 *
 * @param [IN] pv_data_sui8 : Vector with data
 * @return uint8_t : status
 *    @arg 0 : Data not send
 *    @arg 1 : Data send correctly
 *
 */

uint8_t uart_port::write_data(vector<uint8_t>& pv_data_sui8)
{
uint8_t status_value_ui8 = 0;
DWORD write_bite_dword = 0;
static uint8_t f_data_bkp_sui8[4096];
uint32_t data_cnt_ui32;
static bool recurse_block_b = false;

    if(!recurse_block_b)
    {
        recurse_block_b = true;
        for (data_cnt_ui32 = 0; data_cnt_ui32 < pv_data_sui8.size(); data_cnt_ui32++)
        {
            f_data_bkp_sui8[data_cnt_ui32] = pv_data_sui8[data_cnt_ui32];
        }
        if (WriteFile( this->port_handle, f_data_bkp_sui8, pv_data_sui8.size(), &write_bite_dword, &this->port_overlapped))
        {
            if (write_bite_dword == pv_data_sui8.size())
            {
                status_value_ui8 = 1;
            }
        }
        else
        {
            if (ERROR_IO_PENDING == GetLastError())
            {
                status_value_ui8 = 1;
            }
        }
        recurse_block_b = false;
    }
    return status_value_ui8;
}

/** @brief Read character
 *
 * @param [OUT] p_data_ui8 : Pointer on character buffer
 * @return uint8_t : status
 *    @arg 0 : Data buffer is empty
 *    @arg 1 : Data buffer not empty
 *
 */

uint8_t uart_port::read_data(uint8_t *p_data_ui8)
{
uint8_t status_value_ui8 = 0;

    if (this->read_data_buffer_str.size())
    {
        *p_data_ui8 = this->read_data_buffer_str[0];
        this->read_data_buffer_str.erase(this->read_data_buffer_str.begin());
        status_value_ui8 = 1;
    }
	return status_value_ui8;
}

/** @brief Read data from character buffer
 *
 * @param [OUT] p_data_str : Pointer on character string buffer
 * @return uint8_t : status
 *    @arg 0 : Data buffer is empty
 *    @arg 1 : Data buffer not empty
 *
 */

uint8_t uart_port::read_data(string *p_data_str)
{
uint8_t status_value_ui8 = 0;

    p_data_str->clear();
    while (this->read_data_buffer_str.size())
    {
        p_data_str->push_back(this->read_data_buffer_str[0]);
        this->read_data_buffer_str.erase(this->read_data_buffer_str.begin());
        status_value_ui8 = 1;
    }
    return status_value_ui8;
}

/** @brief Get com state
 *
 * @param [IN] pin_uart_com_ctrl_in : Pin ID
 * @return uint8_t : Pin state
 *
 */

uint8_t uart_port::get_com_ctrl(uart_com_ctrl_in_t pin_uart_com_ctrl_in)
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

void uart_port::set_com_ctrl(uart_com_ctrl_out_t pin_uart_com_ctrl_out, uint8_t state_ui8)
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
uint32_t event_type_ui32;
uint32_t event_counter_ui32 = 0;
string data_buffer_str;
static uint8_t *p_data_sui8;
static uint32_t length_ui32;

	// Create pointer to terminal window
	uart_port *p_bkp_this = (uart_port*)parametr_pvoid;
	// Thread live flag
	p_bkp_this->uart_thread_run_ui32 = 1;
    // Start thread
    while (p_bkp_this->uart_thread_run_ui32)
    {
        event_type_ui32 = p_bkp_this->wait_rx_event();
        // Read data
        data_buffer_str.erase();
        if (p_bkp_this->read_data(&data_buffer_str))
        {
            // Copy data in to buffer
            length_ui32 = data_buffer_str.length();
            p_data_sui8 = (uint8_t*)data_buffer_str.data();
        }
        else
        {
            // Set default data
            length_ui32 = 0;
            p_data_sui8 = NULL;
        }
        // Call all callback
        for (event_counter_ui32 = 0 ; event_counter_ui32 < p_bkp_this->lv_rx_uart_event_buffer.size() ; event_counter_ui32++)
        {
            // Call event
            p_bkp_this->lv_rx_uart_event_buffer[event_counter_ui32].p_usr_uart_event_fct(p_bkp_this->lv_rx_uart_event_buffer[event_counter_ui32].p_parametr_void, event_type_ui32, p_data_sui8, length_ui32);
        }
    }
    return NO_ERROR;
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
