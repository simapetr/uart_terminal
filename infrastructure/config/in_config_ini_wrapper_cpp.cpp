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

#include "in_config_ini_wrapper_h.h"
#include <wx/fileconf.h>
#include <wx/wfstream.h>

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @defgroup configuration
  * @brief Configuration INI wrapper
  * @{
  */

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Constructor
 *
 * @param [IN] path_str : Configuration file path
 * @return void
 *
 */

config_ini::config_ini( wxString path_str )
{
wxFile config_wxfile;

    if (path_str == wxEmptyString)
    {
        this->ini_file_path_str = wxT("config.ini");
    }
    else
    {
        this->ini_file_path_str = path_str;
    }
	if (!config_wxfile.Exists(this->ini_file_path_str))
    {
        config_wxfile.Create(this->ini_file_path_str);
    }
    return;
}

/** @brief Destructor
 *
 * @param void
 * @return void
 *
 */

config_ini::~config_ini( void )
{

}

/** @brief Read value from INI
 *
 * @param [IN] path_str : Path for read key
 * @param [IN] default_value_str : Default value when key not found
 * @return int32_t : reader value
 *
 */

int32_t config_ini::get_value( wxString path_str, wxString default_value_str )
{
int32_t return_value_i32;
	wxFileInputStream ini_file_stream(this->ini_file_path_str);
	wxFileConfig ini_file_config(ini_file_stream);
	wxSscanf(ini_file_config.Read(path_str, default_value_str), "%d",&return_value_i32);
	return return_value_i32;
}

/** @brief Read string value from INI
 *
 * @param [IN] path_str : Path for read key
 * @param [IN] default_value_str : Default value when key not found
 * @return wxString : reader string value
 *
 */

wxString config_ini::get_string( wxString path_str, wxString default_value_str )
{
	wxFileInputStream ini_file_stream(this->ini_file_path_str);
	wxFileConfig ini_file_config(ini_file_stream);
	return ini_file_config.Read(path_str, default_value_str);
}

/** @brief Set value in to INI
 *
 * @param [IN] path_str : Path for read key
 * @param [IN] value_i32 : Setting value
 * @return void
 *
 */

void config_ini::set_value( wxString path_str, int32_t value_i32 )
{
	wxFileConfig* ini_file_config = new wxFileConfig("", "",this->ini_file_path_str, "",    wxCONFIG_USE_RELATIVE_PATH);
	ini_file_config->Write(path_str, value_i32);
	delete ini_file_config;
	return;
}

/** @brief Set string value in to INI
 *
 * @param [IN] path_str : Path for read key
 * @param [IN] value_str : Setting string value
 * @return void
 *
 */

void config_ini::set_string( wxString path_str, wxString value_str )
{
	wxFileConfig* ini_file_config = new wxFileConfig("", "",this->ini_file_path_str, "",    wxCONFIG_USE_RELATIVE_PATH);
	ini_file_config->Write(path_str, value_str);
	delete ini_file_config;
	return;
}

/**
* @}
*/

/**
* @}
*/

/*****************************************************END OF FILE************/
