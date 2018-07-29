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
   * - USART transmitting data in ASCI and HEX
   * - USART reading data in ASCI and HEX
   *
   * Change description:
   * - V1.1 Correct basic data send preprocessing.
   * - V1.2 Correct Baudrate setting for seal com port or USB->serial converter.
   * - V1.3 Correct port setting in CDB struct and update com timeout for correct port close.
   * - V1.4 Update project struct implement new objective driver, add block component logic and 9bit character length.
   * - V1.5 Update UART driver, read event bugfix, add check available port from windows registry and update for read packet.
   * - V1.6 Add CR & LF for text mode
   * - V1.7 Fix Create text string.
   *
   * <b>Copyright Notice</b>
   *
   * Copyright (C) 2015 PORTTRONIC All rights reserved.
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
