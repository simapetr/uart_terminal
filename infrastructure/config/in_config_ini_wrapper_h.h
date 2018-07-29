#ifndef IN_CONFIG_INI_WRAPPER_H_H_INCLUDED
#define IN_CONFIG_INI_WRAPPER_H_H_INCLUDED

/**
  ****************************************************************************
  * @file    in_config_ini_wrapper__cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.1
  * @date    31.01.2016
  * @brief   INI file processing
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

#include <wx/string.h>

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @addtogroup configuration
  * @{
  */

/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */

class config_ini
{
public:

	config_ini( void );
	~config_ini( void );
	int32_t get_value( wxString path_str, wxString default_value_str );
	wxString get_string( wxString path_str, wxString default_value_str );
	void set_value( wxString path_str, int32_t value_i32 );
	void set_string( wxString path_str, wxString value_str );

	// Error message
	wxString error_text_str;

private:

    // Ini file path
	wxString ini_file_path_str;

};

/**
* @}
*/

/**
* @}
*/

/*****************************************************END OF FILE************/

#endif // IN_CONFIG_INI_WRAPPER_H_H_INCLUDED
