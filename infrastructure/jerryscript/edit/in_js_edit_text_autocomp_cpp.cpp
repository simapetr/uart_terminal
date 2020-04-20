/**
  ****************************************************************************
  * @file    in_js_edit_text_autocomp_cpp.cpp
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

#include "in_js_edit_text_autocomp_h.h"

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @addtogroup JerryScript
  * @{
  */

/**
  * @defgroup Edit_text_autocompetation
  * @brief JavaScript text editor autocompetation
  * @{
  */

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

static const wxString l_word_char_str(_T("zyxwvutsrqponmlkjihgfedcba_ZYXWVUTSRQPONMLKJIHGFEDCBA9876543210"));

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

auto_comp_c::auto_comp_c(void)
{
    return;
}

/** @brief Destructor
 *
 * @param void
 * @return void
 *
 */

auto_comp_c::~auto_comp_c(void)
{
    return;
}

/** @brief Load object from c++ header file
 *
 * @param [IN] file_str : Text file string C++ header (modified)
 * @return void
 *
 */

void auto_comp_c::load_h(wxString file_str)
{
uint32_t char_cnt_ui32;
uint8_t comment_ui8 = 0;
bool param_b = false;
wxString last_word_str;
wxString last_last_word_str;
bool class_b = false;
bool method_b = false;
wxString word_str = wxEmptyString;
object_t bfr_object;
var_t bfr_var;
method_t bfr_method;
wxString comment_str;
wxString last_comment_str;

    // Clear buffers
    this->lv_doc_object.clear();
    this->lv_doc_method.clear();
    this->lv_doc_var.clear();
    // Check all file character
    for(char_cnt_ui32 = 0 ; char_cnt_ui32 < file_str.Length() ; char_cnt_ui32++)
    {
        if((file_str[char_cnt_ui32] == '/') && (file_str[(char_cnt_ui32 + 1)] == '*'))
        {
            comment_ui8 = 1;
            comment_str = wxEmptyString;
        }
        else if((file_str[char_cnt_ui32] == '*') && (file_str[(char_cnt_ui32 + 1)] == '/'))
        {
            comment_ui8 = 0;
            comment_str += file_str[char_cnt_ui32];
            comment_str += file_str[(char_cnt_ui32 + 1)];
            last_comment_str = comment_str;
            last_comment_str.Replace('\r', "");
            last_comment_str.Replace("        *", " *");
            last_comment_str.Replace('"', "\"");
        }
        else if((file_str[char_cnt_ui32] == '/') && (file_str[(char_cnt_ui32 + 1)] == '/') && (comment_ui8 == 0))
        {
            comment_ui8 = 2;
        }
        else if((file_str[char_cnt_ui32] == '\n') && (comment_ui8 == 2))
        {
            comment_ui8 = 0;
        }
        else
        {
        }
        if(comment_ui8 == 1)
        {
            comment_str += file_str[char_cnt_ui32];
        }
        if(!comment_ui8)
        {
            if(l_word_char_str.Find(file_str[char_cnt_ui32]) != wxNOT_FOUND)
            {
                word_str += file_str[char_cnt_ui32];
            }
            else
            {
                if(word_str != wxEmptyString)
                {
                    last_last_word_str = last_word_str;
                    last_word_str = word_str;
                    word_str = wxEmptyString;
                    // Method
                    if(param_b)
                    {
                        // Method parameter
                        bfr_method.v_param_str.push_back(last_word_str);
                    }
                    else
                    {
                        // Method doc
                        bfr_method.doc_str = last_comment_str;
                        // Method name
                        bfr_method.name_str = last_word_str;
                    }
                }
                if(file_str[char_cnt_ui32] == '{')
                {
                    class_b = true;
                    // Set object name
                    bfr_object.name_str = last_word_str;
                    // Clear method
                    bfr_object.v_data_method.clear();
                    // Clear variable
                    bfr_object.v_data_var.clear();
                }
                else if(file_str[char_cnt_ui32] == '}')
                {
                    class_b = false;
                    // Save object
                    if(bfr_object.v_data_method.size() || bfr_object.v_data_var.size())
                    {
                        this->lv_doc_object.push_back(bfr_object);
                    }
                }
                else if((file_str[char_cnt_ui32] == '('))
                {
                    param_b = true;
                    method_b = true;
                    bfr_method.v_param_str.clear();
                }
                else if((file_str[char_cnt_ui32] == ')'))
                {
                    param_b = false;
                }
                else if((file_str[char_cnt_ui32] == ';'))
                {
                    if(class_b)
                    {
                        if(method_b)
                        {
                            method_b = false;
                            // Save method
                            bfr_object.v_data_method.push_back(bfr_method);
                        }
                        else
                        {
                            bfr_var.type_str = last_last_word_str;
                            bfr_var.name_str = last_word_str;
                            // Save variable
                            bfr_object.v_data_var.push_back(bfr_var);
                        }
                    }
                    else
                    {
                        if(method_b)
                        {
                            method_b = false;
                            this->lv_doc_method.push_back(bfr_method);
                        }
                        else
                        {
                            // Check if not end code block
                            if(file_str[(char_cnt_ui32 - 1)] != '}')
                            {
                                bfr_var.type_str = last_last_word_str;
                                bfr_var.name_str = last_word_str;
                                bfr_var.class_b = true;
                                // Save variable
                                this->lv_doc_var.push_back(bfr_var);
                            }
                        }
                    }
                }
                else
                {
                }
            }
        }
    }
    // Save size
    this->l_object_size_ui32 = this->lv_doc_object.size();
    this->l_method_size_ui32 = this->lv_doc_method.size();
    this->l_var_size_ui32 = this->lv_doc_var.size();
    return;
}

/** @brief Load object from JavaScript header file
 *
 * @param [IN] file_str : JavaScript file
 * @return void
 *
 */

void auto_comp_c::load_js(wxString file_str)
{
uint32_t char_cnt_ui32;
uint8_t comment_ui8 = 0;
wxArrayString word_arraystring;
wxString last_word_str;
wxString last_last_word_str;
bool method_b = false;
wxString word_str = wxEmptyString;
object_t bfr_object;
var_t bfr_var;
method_t bfr_method;
wxString comment_str;
wxString last_comment_str;
uint32_t block_cnt_ui32 = 0;

    // Erase added object
    if(this->lv_doc_object.size() > this->l_object_size_ui32)
    {
        this->lv_doc_object.erase((this->lv_doc_object.begin() + this->l_object_size_ui32), this->lv_doc_object.end());
    }
    if(this->lv_doc_method.size() > this->l_method_size_ui32)
    {
        this->lv_doc_method.erase((this->lv_doc_method.begin() + this->l_method_size_ui32), this->lv_doc_method.end());
    }
    if(this->lv_doc_var.size() > this->l_var_size_ui32)
    {
        this->lv_doc_var.erase((this->lv_doc_var.begin() + this->l_var_size_ui32), this->lv_doc_var.end());
    }
    // Parse script
    // Check all file character
    for(char_cnt_ui32 = 0 ; char_cnt_ui32 < file_str.Length() ; char_cnt_ui32++)
    {
        if((file_str[char_cnt_ui32] == '/') && (file_str[(char_cnt_ui32 + 1)] == '*'))
        {
            comment_ui8 = 1;
            comment_str = wxEmptyString;
        }
        else if((file_str[char_cnt_ui32] == '*') && (file_str[(char_cnt_ui32 + 1)] == '/'))
        {
            comment_ui8 = 0;
            comment_str += file_str[char_cnt_ui32];
            comment_str += file_str[(char_cnt_ui32 + 1)];
            last_comment_str = comment_str;
            last_comment_str.Replace('\r', "");
            last_comment_str.Replace("        *", " *");
            last_comment_str.Replace('"', "\"");
        }
        else if((file_str[char_cnt_ui32] == '/') && (file_str[(char_cnt_ui32 + 1)] == '/') && (comment_ui8 == 0))
        {
            comment_ui8 = 2;
        }
        else if((file_str[char_cnt_ui32] == '\n') && (comment_ui8 == 2))
        {
            comment_ui8 = 0;
        }
        else
        {
        }
        if(comment_ui8 == 1)
        {
            comment_str += file_str[char_cnt_ui32];
        }
        if(!comment_ui8)
        {
            if(l_word_char_str.Find(file_str[char_cnt_ui32]) != wxNOT_FOUND)
            {
                word_str += file_str[char_cnt_ui32];
            }
            else
            {
                if(word_str != wxEmptyString)
                {
                    word_arraystring.Add(word_str);
                    word_str = wxEmptyString;
                    if((!block_cnt_ui32) && (word_arraystring.size() > 1))
                    {
                        if(method_b)
                        {
                            bfr_method.v_param_str.push_back(word_arraystring[(word_arraystring.size() - 1)]);
                        }
                        if(word_arraystring[(word_arraystring.size() - 2)].IsSameAs("var"))
                        {
                            bfr_var.type_str = word_arraystring[(word_arraystring.size() - 2)];
                            bfr_var.name_str = word_arraystring[(word_arraystring.size() - 1)];
                            bfr_var.class_b = false;
                            // Save global variable
                            this->lv_doc_var.push_back(bfr_var);
                        }
                        if(word_arraystring[(word_arraystring.size() - 2)].IsSameAs("function"))
                        {
                            bfr_method.name_str = word_arraystring[(word_arraystring.size() - 1)];
                            bfr_method.doc_str = last_comment_str;
                            bfr_method.v_param_str.clear();
                            method_b = true;
                        }
                    }
                }
                if(file_str[char_cnt_ui32] == '{')
                {
                    block_cnt_ui32++;
                }
                else if(file_str[char_cnt_ui32] == '}')
                {
                    if(block_cnt_ui32)
                    {
                        block_cnt_ui32--;
                    }
                }
                else if((file_str[char_cnt_ui32] == '('))
                {
                }
                else if((file_str[char_cnt_ui32] == ')'))
                {
                    if(method_b)
                    {
                        method_b = false;
                        // Save global method
                        this->lv_doc_method.push_back(bfr_method);
                    }
                }
                else if((file_str[char_cnt_ui32] == ';'))
                {

                }
                else
                {
                }
            }
        }
    }
    return;
}

/** @brief Get global lexer word
 *
 * @param [IN] type_ui32 : Lexer type
 * @param [IN] data_str : Lexer type
 * @return void
 *
 */

void auto_comp_c::load_lex(uint32_t type_ui32, wxString& data_str)
{
    if(type_ui32 == e_fct)
    {
        data_str = wxEmptyString;
        for(uint32_t method_cnt_ui32 = 0 ; method_cnt_ui32 < this->lv_doc_method.size() ; method_cnt_ui32++)
        {
            if(data_str.Find(this->lv_doc_method[method_cnt_ui32].name_str) == wxNOT_FOUND)
            {
                data_str += (this->lv_doc_method[method_cnt_ui32].name_str + wxT(" "));
            }
        }
    }
    else if(type_ui32 == e_var)
    {
        data_str = wxEmptyString;
        for(uint32_t var_cnt_ui32 = 0 ; var_cnt_ui32 < this->lv_doc_var.size() ; var_cnt_ui32++)
        {
            data_str += (this->lv_doc_var[var_cnt_ui32].name_str + wxT(" "));
        }
    }
    else
    {

    }
    return;
}

/** @brief Get autocomp info
 *
 * @param [IN] command_arraystring : Command file array
 * @return wxString : Autocompetation info string
 *
 */

wxString auto_comp_c::get(wxArrayString command_arraystring)
{
wxString data_str = wxEmptyString;
uint32_t var_index_ui32 = 0;
uint32_t var_class_index_ui32 = 0;

    this->l_info_wxarraystring.clear();
    if(command_arraystring.size())
    {
        if(command_arraystring.size() == 1)
        {
            if(((int)l_word_char_str.find(command_arraystring[0][0]) != wxNOT_FOUND) && ((int)l_word_char_str.find(command_arraystring[0][1]) != wxNOT_FOUND))
            {
                // Get global autocompetation
                data_str = wxEmptyString;
                for(uint32_t method_cnt_ui32 = 0 ; method_cnt_ui32 < this->lv_doc_method.size() ; method_cnt_ui32++)
                {
                    if(data_str.Find(this->lv_doc_method[method_cnt_ui32].name_str) == wxNOT_FOUND)
                    {
                        if((method_cnt_ui32 == (this->lv_doc_method.size() - 1)) && (!this->lv_doc_var.size()))
                        {
                            data_str += this->lv_doc_method[method_cnt_ui32].name_str;
                            data_str += wxT("\n1");
                        }
                        else
                        {
                            data_str += this->lv_doc_method[method_cnt_ui32].name_str;
                            data_str += wxT("\n1\r");
                        }
                    }
                    if(command_arraystring[0].IsSameAs(this->lv_doc_method[method_cnt_ui32].name_str))
                    {
                        this->l_info_wxarraystring.Add(this->get(this->lv_doc_method[method_cnt_ui32]));
                    }
                }
                for(uint32_t var_cnt_ui32 = 0 ; var_cnt_ui32 < this->lv_doc_var.size() ; var_cnt_ui32++)
                {
                    if(var_cnt_ui32 == (this->lv_doc_var.size() - 1))
                    {
                        data_str += this->lv_doc_var[var_cnt_ui32].name_str;
                        if(this->lv_doc_var[var_cnt_ui32].class_b)
                        {
                            data_str += wxT("\n0");
                        }
                        else
                        {
                            data_str += wxT("\n2");
                        }
                    }
                    else
                    {
                        data_str += this->lv_doc_var[var_cnt_ui32].name_str;
                        if(this->lv_doc_var[var_cnt_ui32].class_b)
                        {
                            data_str += wxT("\n0\r");
                        }
                        else
                        {
                            data_str += wxT("\n2\r");
                        }
                    }
                }
            }
        }
        else if(command_arraystring.size() == 2)
        {
            // Find global var index
            for(uint32_t var_cnt_ui32 = 0 ; var_cnt_ui32 < this->lv_doc_var.size() ; var_cnt_ui32++)
            {
                if(command_arraystring[(command_arraystring.size() - 2)].IsSameAs(this->lv_doc_var[var_cnt_ui32].name_str))
                {
                    var_index_ui32 = var_cnt_ui32;
                    var_cnt_ui32 = this->lv_doc_var.size();
                }
            }
            // Find class index
            for(uint32_t class_cnt_ui32 = 0 ; class_cnt_ui32 < this->lv_doc_object.size() ; class_cnt_ui32++)
            {
                if(this->lv_doc_var[var_index_ui32].type_str.IsSameAs(this->lv_doc_object[class_cnt_ui32].name_str))
                {
                    var_class_index_ui32 = class_cnt_ui32;
                }
            }
            // Create method string
            if(var_class_index_ui32 < this->lv_doc_object.size())
            {
                for(uint32_t method_cnt_ui32 = 0 ; method_cnt_ui32 < this->lv_doc_object[var_class_index_ui32].v_data_method.size() ; method_cnt_ui32++)
                {
                    if(data_str.Find(this->lv_doc_object[var_class_index_ui32].v_data_method[method_cnt_ui32].name_str) == wxNOT_FOUND)
                    {
                        if((method_cnt_ui32 == (this->lv_doc_method.size() - 1)) && (!this->lv_doc_var.size()))
                        {
                            data_str += this->lv_doc_object[var_class_index_ui32].v_data_method[method_cnt_ui32].name_str;
                            data_str += wxT("\n1");
                        }
                        else
                        {
                            data_str += this->lv_doc_object[var_class_index_ui32].v_data_method[method_cnt_ui32].name_str;
                            data_str += wxT("\n1\r");
                        }
                    }
                    if(command_arraystring[1].IsSameAs(this->lv_doc_object[var_class_index_ui32].v_data_method[method_cnt_ui32].name_str))
                    {
                        this->l_info_wxarraystring.Add(this->get(this->lv_doc_object[var_class_index_ui32].v_data_method[method_cnt_ui32]));
                    }
                }
                for(uint32_t var_cnt_ui32 = 0 ; var_cnt_ui32 < this->lv_doc_object[var_class_index_ui32].v_data_var.size() ; var_cnt_ui32++)
                {
                    if(var_cnt_ui32 == (this->lv_doc_var.size() - 1))
                    {
                        data_str += this->lv_doc_object[var_class_index_ui32].v_data_var[var_cnt_ui32].name_str;
                        data_str += wxT("\n2");
                    }
                    else
                    {
                        data_str += this->lv_doc_object[var_class_index_ui32].v_data_var[var_cnt_ui32].name_str;
                        data_str += wxT("\n2\r");
                    }
                }
            }
        }
        else
        {
            // Find class index
            for(uint32_t class_cnt_ui32 = 0 ; class_cnt_ui32 < this->lv_doc_object.size() ; class_cnt_ui32++)
            {
                if(command_arraystring[(command_arraystring.size() - 2)].IsSameAs(this->lv_doc_object[class_cnt_ui32].name_str))
                {
                    var_class_index_ui32 = class_cnt_ui32;
                }
            }
            // Create method string
            if(var_class_index_ui32 < this->lv_doc_object.size())
            {
                for(uint32_t method_cnt_ui32 = 0 ; method_cnt_ui32 < this->lv_doc_object[var_class_index_ui32].v_data_method.size() ; method_cnt_ui32++)
                {
                    if(data_str.Find(this->lv_doc_object[var_class_index_ui32].v_data_method[method_cnt_ui32].name_str) == wxNOT_FOUND)
                    {
                        if((method_cnt_ui32 == (this->lv_doc_method.size() - 1)) && (!this->lv_doc_var.size()))
                        {
                            data_str += this->lv_doc_object[var_class_index_ui32].v_data_method[method_cnt_ui32].name_str;
                            data_str += wxT("\n1");
                        }
                        else
                        {
                            data_str += this->lv_doc_object[var_class_index_ui32].v_data_method[method_cnt_ui32].name_str;
                            data_str += wxT("\n1\r");
                        }
                    }
                    if(command_arraystring[(command_arraystring.size() - 1)].IsSameAs(this->lv_doc_object[var_class_index_ui32].v_data_method[method_cnt_ui32].name_str))
                    {
                        this->l_info_wxarraystring.Add(this->get(this->lv_doc_object[var_class_index_ui32].v_data_method[method_cnt_ui32]));
                    }
                }
                for(uint32_t var_cnt_ui32 = 0 ; var_cnt_ui32 < this->lv_doc_object[var_class_index_ui32].v_data_var.size() ; var_cnt_ui32++)
                {
                    if(var_cnt_ui32 == (this->lv_doc_var.size() - 1))
                    {
                        data_str += this->lv_doc_object[var_class_index_ui32].v_data_var[var_cnt_ui32].name_str;
                        data_str += wxT("\n2");
                    }
                    else
                    {
                        data_str += this->lv_doc_object[var_class_index_ui32].v_data_var[var_cnt_ui32].name_str;
                        data_str += wxT("\n2\r");
                    }
                }
            }
        }
    }
    return data_str;
}

/** @brief Get autocomp info
 *
 * @param [IN] command_arraystring : Command file array
 * @return wxString : Autocompetation info string
 *
 */

wxArrayString auto_comp_c::get_info(wxArrayString command_arraystring)
{
    this->get(command_arraystring);
    return this->l_info_wxarraystring;
}

/**
  ****************************************************************************
  * Private function
  ****************************************************************************
  */

/** @brief Get autocomp info data
 *
 * @param [IN] data_method : Method data
 * @return wxString : Info string
 *
 */

wxString auto_comp_c::get(method_t data_method)
{
wxString doc_str;

    // Set function doc
    doc_str = data_method.name_str;
    doc_str += wxT("(");
    for(uint32_t param_cnt_ui32 = 0 ; param_cnt_ui32 < data_method.v_param_str.size() ; param_cnt_ui32++)
    {
        if(param_cnt_ui32 == (data_method.v_param_str.size() - 1))
        {
            doc_str += wxString::Format("%s", data_method.v_param_str[param_cnt_ui32].To8BitData().data());
        }
        else
        {
            doc_str += wxString::Format("%s, ", data_method.v_param_str[param_cnt_ui32].To8BitData().data());
        }

    }
    doc_str += wxT(")\n\n");
    doc_str += this->get_doc(data_method.doc_str);
    return doc_str;
}

/** @brief Get method info from doxygen
 *
 * @param [IN] doxy_str : Function doxygen comment
 * @return wxString : Info string
 *
 */


wxString auto_comp_c::get_doc(wxString doxy_str)
{
wxString doc_str = wxEmptyString;
wxString text_str;
wxString line_str;
wxString replace_str = wxEmptyString;
int find_index_int = 0;
int find_last_index_int;
int param_index_int;

    find_last_index_int = find_index_int;
    while((size_t)find_index_int < doxy_str.size())
    {
        // Get line
        find_index_int = doxy_str.find("\n", (size_t)find_last_index_int);
        line_str = doxy_str.substr(find_last_index_int, (find_index_int - find_last_index_int));
        if(wxNOT_FOUND != (param_index_int = line_str.find("@brief")))
        {
            text_str = line_str.substr(param_index_int, (line_str.size() - param_index_int));
            text_str.Replace("@brief ", "");
            text_str.Replace("@brief", "");
            if(text_str != wxEmptyString)
            {
                doc_str += text_str;
                doc_str += wxT("\n\n");
            }
        }
        else if(wxNOT_FOUND != (param_index_int = line_str.find("@param")))
        {
            text_str = line_str.substr(param_index_int, (line_str.size() - param_index_int));
            text_str.Replace("@param ", "");
            text_str.Replace("@param", "");
            if(text_str != wxEmptyString)
            {
                doc_str += text_str;
                doc_str += wxT("\n");
            }
        }
        else if(wxNOT_FOUND != (param_index_int = line_str.find("@return")))
        {
            text_str = line_str.substr(param_index_int, (line_str.size() - param_index_int));
            text_str.Replace("@return ", "");
            text_str.Replace("@return", "");
            if(text_str != wxEmptyString)
            {
                doc_str += wxT("[OUT] ");
                doc_str += text_str;
                doc_str += wxT("\n");
            }
        }
        else if(wxNOT_FOUND != (param_index_int = line_str.find("@arg")))
        {
            text_str = line_str.substr(param_index_int, (line_str.size() - param_index_int));
            text_str.Replace("@arg ", "     ->");
            text_str.Replace("@arg", "");
            if(text_str != wxEmptyString)
            {
                doc_str += text_str;
                doc_str += wxT("\n");
            }
        }
        else if(wxNOT_FOUND != (param_index_int = line_str.find("@code")))
        {
            replace_str = text_str = line_str.substr(0, param_index_int);
        }
        else
        {

        }
        find_last_index_int = (find_index_int + 1);
    }
    // Add example
    if(((int)doxy_str.find("@code") != wxNOT_FOUND) && ((int)doxy_str.find("@endcode") != wxNOT_FOUND))
    {
        doc_str += wxT("\nExample :");
        text_str = doxy_str.substr(doxy_str.find("@code"), (doxy_str.find("@endcode") - doxy_str.find("@code")));
        text_str.Replace("@code", "");
        text_str.Replace(replace_str, "");
        text_str.RemoveLast();
        doc_str += text_str;
    }
    return doc_str;
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

