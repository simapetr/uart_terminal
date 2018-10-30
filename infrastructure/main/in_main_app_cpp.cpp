/**
  ****************************************************************************
  * @file    in_main_app_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.1
  * @date    04.03.2014
  * @brief   Application window creator
  ****************************************************************************
  * @attention
  * <h2><center>&copy; COPYRIGHT PORTTRONIC</center></h2>
  ****************************************************************************
  */

/**
   @mainpage UART terminal
   *
   * <b>Introduction</b>
   *
   * This is windows terminl for UART communication with JavaScript support.
   *
   * Supported function:
   * - Set UART communication parameter
   * - Direct read and write data in text and HEX format
   * - Control DTR, RTS and Tx(break) line
   * - Read CTS, DSR, RING and RLSD
   * - Load JavaScript
   *
   * Used technology:
   * - wxWidget 3.0 GUI (https://github.com/wxWidgets/wxWidgets)
   * - Jerry script ECMAScript 5.1 (https://github.com/jerryscript-project/jerryscript)
   * - Windows file access
   *
   */

/**
  ****************************************************************************
  * Library
  ****************************************************************************
  */

#include "in_main_app_h.h"

//(*AppHeaders
#include "ap_uart_terminal_frame_h.h"
#include <wx/image.h>
//*)

/**
  * @defgroup Infrastructure
  * @brief Infrastructure layer
  * @{
  */

/**
  * @defgroup Main
  * @brief Application entry point
  * @{
  */

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

IMPLEMENT_APP(main_app);

/** @brief Windows window constructor
 *
 * @param void
 * @return void
 *
 */

bool main_app::OnInit()
{
int32_t cmd_cnt_i32;
    // Convert CMD argument
    this->lp_cmd_buffer_arraystring = new wxArrayString();
    for(cmd_cnt_i32 = 0 ; cmd_cnt_i32 < argc ; cmd_cnt_i32++)
    {
        this->lp_cmd_buffer_arraystring->Add(argv[cmd_cnt_i32]);
    }
    // Application initialization
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	main_frame* Frame = new main_frame(0, lp_cmd_buffer_arraystring);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //(*AppInitialize
    //*)
    return wxsOK;
    return wxsOK;

}

/**
* @}
*/

/**
* @}
*/

/*****************************************************END OF FILE************/
