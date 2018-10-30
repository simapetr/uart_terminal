#ifndef IN_MAIN_APP_H_H
#define IN_MAIN_APP_H_H

/**
  ****************************************************************************
  * @file    in_main_app_h.h
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
  ****************************************************************************
  * Library
  ****************************************************************************
  */

#include <wx/app.h>

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @addtogroup Main
  * @{
  */

/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */

class main_app : public wxApp
{
    public:
        virtual bool OnInit();
    private:
        wxArrayString* lp_cmd_buffer_arraystring;
};

/**
* @}
*/

/**
* @}
*/

/*****************************************************END OF FILE************/

#endif // IN_MAIN_APP_H_H
