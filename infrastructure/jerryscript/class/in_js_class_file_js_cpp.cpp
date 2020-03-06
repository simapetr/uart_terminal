/**
  ****************************************************************************
  * @file    in_js_class_file_js_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    18.04.2018
  * @brief   JerryScript wrapper for for wxfile class
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

#include <wx/utils.h>
#include <wx/file.h>
#include "in_js_class_file_js_h.h"
#include "in_jerryscript_core_h.h"

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @defgroup JerryScript
  * @brief JavaScript interpret
  * @{
  */

/**
  * @defgroup Class
  * @brief JavaScript class
  * @{
  */

/**
  * @defgroup File
  * @brief File class definition
  * @{
  */

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Registration object in to class
 *
 * @param void
 * @return void
 *
 */

void file_js_c::reg_host_class (void)
{
jerry_value_t global_jerry_value;
jerry_value_t object_jerry_value;
jerry_value_t funct_jerry_value;
jerry_value_t name_jerry_value;

    // Create method
    object_jerry_value = jerry_create_object ();
    // Read file
    funct_jerry_value = jerry_create_external_function(this->read);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"read");
    jerry_set_property(object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Read file
    funct_jerry_value = jerry_create_external_function(this->read_b);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"read_b");
    jerry_set_property(object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Write file
    funct_jerry_value = jerry_create_external_function(this->write);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"write");
    jerry_set_property(object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Append file
    funct_jerry_value = jerry_create_external_function(this->append);
    name_jerry_value = jerry_create_string((const jerry_char_t*)"append");
    jerry_set_property(object_jerry_value, name_jerry_value, funct_jerry_value);
    jerry_release_value(name_jerry_value);
    jerry_release_value(funct_jerry_value);
    // Create class
    global_jerry_value = jerry_get_global_object();
    name_jerry_value = jerry_create_string((const jerry_char_t*)"file");
    jerry_set_property (global_jerry_value, name_jerry_value, object_jerry_value);

    funct_jerry_value = jerry_get_property (global_jerry_value, name_jerry_value);
    jerry_set_object_native_pointer(funct_jerry_value, this, NULL);
    // Release storage value
    jerry_release_value(name_jerry_value);
    jerry_release_value(object_jerry_value);
    return;
}

/** @brief Read file (JS function "read")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t file_js_c::read(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
file_js_c* p_bkp_this = NULL;
wxString path_str = wxEmptyString;
wxString data_str = wxEmptyString;
uint32_t data_len_ui32;
static uint8_t *p_data_sui8 = NULL;

    if(jerry_get_object_native_pointer(jerry_get_global_object(), &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<file_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 1 && p_bkp_this)
        {
            if(jerry_value_is_string(p_args_ui32[0]))
            {
                // Call class method
                if (p_bkp_this)
                {
                    data_len_ui32 = jerry_get_string_size(p_args_ui32[0]);
                    p_data_sui8 = new uint8_t[data_len_ui32];
                    jerry_string_to_char_buffer(p_args_ui32[0],p_data_sui8,data_len_ui32);
                    path_str = wxEmptyString;
                    for (uint32_t char_cnt_ui32 = 0 ; char_cnt_ui32 < data_len_ui32 ; char_cnt_ui32++)
                    {
                        path_str += p_data_sui8[char_cnt_ui32];
                    }
                    delete[] p_data_sui8;
                    wxFile* p_stcipt_wxfile = new wxFile(path_str, wxFile::read);
                    if(p_stcipt_wxfile->IsOpened())
                    {
                        p_stcipt_wxfile->ReadAll(&data_str);
                        p_stcipt_wxfile->Close();
                    }
                    delete p_stcipt_wxfile;

                }
            }
        }
        else
        {
            printf("Error file.read wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_string((const jerry_char_t*)data_str.To8BitData().data());
}

/** @brief Read file (JS function "read_b")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t file_js_c::read_b(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
void* p_arg_void;
file_js_c* p_bkp_this = NULL;
wxString path_str = wxEmptyString;
uint32_t data_len_ui32;
static uint8_t *p_data_sui8 = NULL;
jerry_value_t data_array_jerry_value = jerry_create_array(0);


    if(jerry_get_object_native_pointer(jerry_get_global_object(), &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<file_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 1 && p_bkp_this)
        {
            if(jerry_value_is_string(p_args_ui32[0]))
            {
                // Call class method
                if (p_bkp_this)
                {
                    data_len_ui32 = jerry_get_string_size(p_args_ui32[0]);
                    p_data_sui8 = new uint8_t[data_len_ui32];
                    jerry_string_to_char_buffer(p_args_ui32[0],p_data_sui8,data_len_ui32);
                    path_str = wxEmptyString;
                    for (uint32_t char_cnt_ui32 = 0 ; char_cnt_ui32 < data_len_ui32 ; char_cnt_ui32++)
                    {
                        path_str += p_data_sui8[char_cnt_ui32];
                    }
                    delete[] p_data_sui8;
                    wxFile* p_stcipt_wxfile = new wxFile(path_str, wxFile::read);
                    if(p_stcipt_wxfile->IsOpened())
                    {
                        data_len_ui32 = p_stcipt_wxfile->Length();
                        p_data_sui8 = new uint8_t[data_len_ui32];
                        p_stcipt_wxfile->Read(p_data_sui8,data_len_ui32);
                        // Create Jerry array
                        data_array_jerry_value = jerry_create_array(data_len_ui32);
                        for (uint32_t char_cnt_ui32 = 0 ; char_cnt_ui32 < data_len_ui32 ; char_cnt_ui32++)
                        {
                            jerry_set_property_by_index(data_array_jerry_value, char_cnt_ui32, jerry_create_number(p_data_sui8[char_cnt_ui32]));
                        }
                        p_stcipt_wxfile->Close();
                    }
                    delete p_stcipt_wxfile;
                }
            }
        }
        else
        {
            printf("Error file.read_b wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return data_array_jerry_value;
}

/** @brief Read file (JS function "write")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t file_js_c::write(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
bool status_b = false;
void* p_arg_void;
file_js_c* p_bkp_this = NULL;
wxString path_str;
wxString data_str;
uint32_t data_len_ui32;
uint8_t *p_data_sui8;

    if(jerry_get_object_native_pointer(jerry_get_global_object(), &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<file_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 2 && p_bkp_this)
        {
            if(jerry_value_is_string(p_args_ui32[0]) && jerry_value_is_array(p_args_ui32[1]))
            {
                data_len_ui32 = jerry_get_string_size(p_args_ui32[0]);
                p_data_sui8 = new uint8_t[data_len_ui32];
                jerry_string_to_char_buffer(p_args_ui32[0],p_data_sui8,data_len_ui32);
                path_str = wxEmptyString;
                for (uint32_t char_cnt_ui32 = 0 ; char_cnt_ui32 < data_len_ui32 ; char_cnt_ui32++)
                {
                    path_str += p_data_sui8[char_cnt_ui32];
                }
                delete[] p_data_sui8;
                wxFile* p_stcipt_wxfile = new wxFile(path_str, wxFile::write);
                if(p_stcipt_wxfile->IsOpened())
                {
                    data_len_ui32 = jerry_get_array_length(p_args_ui32[1]);
                    p_data_sui8 = new uint8_t[data_len_ui32];
                    for (uint32_t data_cnt_ui32 = 0; data_cnt_ui32 < data_len_ui32; data_cnt_ui32++)
                    {
                        p_data_sui8[data_cnt_ui32] = jerry_get_number_value(jerry_get_property_by_index(p_args_ui32[1], data_cnt_ui32));
                    }
                    p_stcipt_wxfile->Write(p_data_sui8, data_len_ui32);
                    delete[] p_data_sui8;
                    p_stcipt_wxfile->Close();
                    status_b = true;
                }
                delete p_stcipt_wxfile;
            }
            else if(jerry_value_is_string(p_args_ui32[0]) && jerry_value_is_string(p_args_ui32[1]))
            {
                data_len_ui32 = jerry_get_string_size(p_args_ui32[0]);
                p_data_sui8 = new uint8_t[data_len_ui32];
                jerry_string_to_char_buffer(p_args_ui32[0],p_data_sui8,data_len_ui32);
                path_str = wxEmptyString;
                for (uint32_t char_cnt_ui32 = 0 ; char_cnt_ui32 < data_len_ui32 ; char_cnt_ui32++)
                {
                    path_str += p_data_sui8[char_cnt_ui32];
                }
                delete[] p_data_sui8;
                wxFile* p_stcipt_wxfile = new wxFile(path_str, wxFile::write);
                if(p_stcipt_wxfile->IsOpened())
                {
                    // Read function argument string data
                    data_len_ui32 = jerry_get_string_size(p_args_ui32[1]);
                    p_data_sui8 = new uint8_t[data_len_ui32];
                    jerry_string_to_char_buffer(p_args_ui32[1],p_data_sui8,data_len_ui32);
                    data_str = wxEmptyString;
                    for (uint32_t char_cnt_ui32 = 0 ; char_cnt_ui32 < data_len_ui32 ; char_cnt_ui32++)
                    {
                        data_str += p_data_sui8[char_cnt_ui32];
                    }
                    delete[] p_data_sui8;
                    p_stcipt_wxfile->Write(data_str);
                    p_stcipt_wxfile->Close();
                    status_b = true;
                }
                delete p_stcipt_wxfile;
            }
            else
            {

            }
        }
        else
        {
            printf("Error file.write wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_boolean(status_b);
}

/** @brief Read file (JS function "append")
 *
 * @param [IN] funct_ui32 : Unused
 * @param [IN] this_ui32 : Pointer on construct class
 * @param [IN] p_args_ui32 : Pointer on argument field
 * @param [IN] args_cnt_ui32 : Argument field size
 * @return uint32_t : returned data
 *
 */

uint32_t file_js_c::append(const uint32_t funct_ui32, const uint32_t this_ui32, const uint32_t *p_args_ui32, const uint32_t args_cnt_ui32)
{
bool status_b = false;
void* p_arg_void;
file_js_c* p_bkp_this = NULL;
wxString path_str;
wxString data_str;
uint32_t data_len_ui32;
uint8_t *p_data_sui8;

    if(jerry_get_object_native_pointer(jerry_get_global_object(), &p_arg_void, NULL))
    {
        // Extract this
        p_bkp_this = reinterpret_cast<file_js_c*>(p_arg_void);
        // Extract function argument
        if(args_cnt_ui32 == 2 && p_bkp_this)
        {
            if(jerry_value_is_string(p_args_ui32[0]) && jerry_value_is_array(p_args_ui32[1]))
            {
                data_len_ui32 = jerry_get_string_size(p_args_ui32[0]);
                p_data_sui8 = new uint8_t[data_len_ui32];
                jerry_string_to_char_buffer(p_args_ui32[0],p_data_sui8,data_len_ui32);
                path_str = wxEmptyString;
                for (uint32_t char_cnt_ui32 = 0 ; char_cnt_ui32 < data_len_ui32 ; char_cnt_ui32++)
                {
                    path_str += p_data_sui8[char_cnt_ui32];
                }
                delete[] p_data_sui8;
                wxFile* p_stcipt_wxfile = new wxFile(path_str, wxFile::write_append);
                if(p_stcipt_wxfile->IsOpened())
                {
                    data_len_ui32 = jerry_get_array_length(p_args_ui32[1]);
                    p_data_sui8 = new uint8_t[data_len_ui32];
                    for (uint32_t data_cnt_ui32 = 0; data_cnt_ui32 < data_len_ui32; data_cnt_ui32++)
                    {
                        p_data_sui8[data_cnt_ui32] = jerry_get_number_value(jerry_get_property_by_index(p_args_ui32[1], data_cnt_ui32));
                    }
                    p_stcipt_wxfile->Write(p_data_sui8, data_len_ui32);
                    delete[] p_data_sui8;
                    p_stcipt_wxfile->Close();
                    status_b = true;
                }
                delete p_stcipt_wxfile;
            }
            else if(jerry_value_is_string(p_args_ui32[0]) && jerry_value_is_string(p_args_ui32[1]))
            {
                data_len_ui32 = jerry_get_string_size(p_args_ui32[0]);
                p_data_sui8 = new uint8_t[data_len_ui32];
                jerry_string_to_char_buffer(p_args_ui32[0],p_data_sui8,data_len_ui32);
                path_str = wxEmptyString;
                for (uint32_t char_cnt_ui32 = 0 ; char_cnt_ui32 < data_len_ui32 ; char_cnt_ui32++)
                {
                    path_str += p_data_sui8[char_cnt_ui32];
                }
                delete[] p_data_sui8;
                wxFile* p_stcipt_wxfile = new wxFile(path_str, wxFile::write_append);
                if(p_stcipt_wxfile->IsOpened())
                {
                    // Read function argument string data
                    data_len_ui32 = jerry_get_string_size(p_args_ui32[1]);
                    p_data_sui8 = new uint8_t[data_len_ui32];
                    jerry_string_to_char_buffer(p_args_ui32[1],p_data_sui8,data_len_ui32);
                    data_str = wxEmptyString;
                    for (uint32_t char_cnt_ui32 = 0 ; char_cnt_ui32 < data_len_ui32 ; char_cnt_ui32++)
                    {
                        data_str += p_data_sui8[char_cnt_ui32];
                    }
                    delete[] p_data_sui8;
                    p_stcipt_wxfile->Write(data_str);
                    p_stcipt_wxfile->Close();
                    status_b = true;
                }
                delete p_stcipt_wxfile;
            }
            else
            {

            }
        }
        else
        {
            printf("Error file.append wrong parameter\n");
        }
    }
    // Cast it back to JavaScript and return
    return jerry_create_boolean(status_b);
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

/**
* @}
*/

/*****************************************************END OF FILE************/
