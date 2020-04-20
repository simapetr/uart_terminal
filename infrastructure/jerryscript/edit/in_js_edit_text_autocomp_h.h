#ifndef IN_JS_EDIT_TEXT_AUTOCOMP_H_H_INCLUDED
#define IN_JS_EDIT_TEXT_AUTOCOMP_H_H_INCLUDED

/**
  ****************************************************************************
  * @file    in_js_edit_text_autocomp_h.h
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    07.04.2020
  * @brief   JerryScript text editor auto competation
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
#include <wx/arrstr.h>
#include <vector>
using namespace std;

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @addtogroup JerryScript
  * @{
  */

/**
  * @addtogroup Edit_text_autocompetation
  * @{
  */

/**
  ****************************************************************************
  * Struct
  ****************************************************************************
  */

typedef struct
{
    wxString doc_str;
    wxString name_str;
    vector<wxString> v_param_str;
}method_t;

typedef struct
{
    wxString type_str;
    wxString name_str;
    bool class_b;
}var_t;

typedef struct
{
    wxString name_str;
    vector<method_t> v_data_method;
    vector<var_t> v_data_var;
}object_t;

/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */

class auto_comp_c
{

    public:

        enum { e_fct = 3, e_var = 1 };

        auto_comp_c(void);
        ~auto_comp_c(void);
        void load_h(wxString file_str);
        void load_js(wxString file_str);
        void load_lex(uint32_t type_ui32, wxString& data_str);
        wxString get(wxArrayString command_arraystring);
        wxArrayString get_info(wxArrayString command_arraystring);

    private:

        wxString get(method_t data_method);
        wxString get_doc(wxString doxy_str);

        vector<object_t> lv_doc_object;
        uint32_t l_object_size_ui32;
        vector<method_t> lv_doc_method;
        uint32_t l_method_size_ui32;
        vector<var_t> lv_doc_var;
        uint32_t l_var_size_ui32;
        wxArrayString l_info_wxarraystring;

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

#endif // IN_JS_EDIT_TEXT_AUTOCOMP_H_H_INCLUDED
