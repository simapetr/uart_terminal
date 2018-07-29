/**
  ****************************************************************************
  * @file    in_main_app_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.1
  * @date    04.03.2014
  * @brief   Application window creator
  *            - OnInit
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
   * Basic communication for windows serial port
   *
   * Supported function:
   * - UART transmitting data in ASCI and HEX
   * - UART reading data in ASCI and HEX
   * - UART control line read and write
   * - Load JavaScript
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
 * @param  void
 * @return void
 *
 */

bool main_app::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	main_frame* Frame = new main_frame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}

/**
* @}
*/

/**
* @}
*/

/*****************************************************END OF FILE************/
