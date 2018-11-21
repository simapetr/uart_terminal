/**
  ****************************************************************************
  * @file    in_js_gui_static_text_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    25.09.2018
  * @brief   GUI window static_text component
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

#include "in_js_gui_frame_h.h"
#include "in_jerryscript_port_h.h"
#include <wx/textctrl.h>

/**
  * @addtogroup Application
  * @{
  */

/**
  * @addtogroup GUI
  * @{
  */

/**
  * @addtogroup Static_text
  * @brief GUI static_text component
  * @{
  */

/**
  ****************************************************************************
  * Define
  ****************************************************************************
  */



/**
  ****************************************************************************
  * Struct
  ****************************************************************************
  */

typedef struct
{
    double sizer_index_d;
    wxString text_str;
    double proportion_d;
    double expand_b;
    bool multiline_b;
    bool update_b;
    bool append_b;
    bool read_b;
    uint32_t read_line_ui32;
    wxString read_text_str;
    wxTextCtrl* p_data_wxtextctrl;
    int32_t object_id_i32;
}textctrl_buffer_t;

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

vector<textctrl_buffer_t> lv_data_textctrl_buffer;
uint32_t l_cnt_textctrl_ui32 = 0;

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Add Text control
 *
 * @param sizer_index_d : Parent sizer index
 * @param text_str : Text
 * @param proportion_d : Relative proportion item in sizer
 * @param expand_b : Expand
 * @param multiline_b : Multiline status
 * @return uint32_t : New textctrl buffer index
 *
 */

uint32_t gui_frame::add_textctrl (double sizer_index_d, wxString text_str, double proportion_d, bool expand_b, bool multiline_b)
{
textctrl_buffer_t l_data_textctrl_buffer;
uint32_t index_ui32 = lv_data_textctrl_buffer.size();

    l_data_textctrl_buffer.sizer_index_d = sizer_index_d;
    l_data_textctrl_buffer.text_str = text_str;
    l_data_textctrl_buffer.expand_b = expand_b;
    l_data_textctrl_buffer.proportion_d = proportion_d;
    l_data_textctrl_buffer.multiline_b = multiline_b;
    l_data_textctrl_buffer.p_data_wxtextctrl = NULL;
    l_data_textctrl_buffer.object_id_i32 = 0;
    l_data_textctrl_buffer.update_b = false;
    l_data_textctrl_buffer.append_b = false;
    l_data_textctrl_buffer.read_b = false;
    l_data_textctrl_buffer.read_line_ui32 = 0;
    l_data_textctrl_buffer.read_text_str = wxEmptyString;
    lv_data_textctrl_buffer.push_back(l_data_textctrl_buffer);
    while(!lv_data_textctrl_buffer[index_ui32].p_data_wxtextctrl){wxMilliSleep(1);}
    return index_ui32;
}

/** @brief Set textctrl text
 *
 * @param static_text_index_d : Static text index
 * @param text_str : Text
 * @return bool : textctrl change status
 *
 */

bool gui_frame::set_textctrl (double static_text_index_d, wxString text_str)
{
bool status_b = false;

    if (static_text_index_d < lv_data_textctrl_buffer.size())
    {
        if (!lv_data_textctrl_buffer[static_text_index_d].update_b)
        {
            lv_data_textctrl_buffer[static_text_index_d].text_str = text_str;
            lv_data_textctrl_buffer[static_text_index_d].append_b = false;
            lv_data_textctrl_buffer[static_text_index_d].update_b = true;
        }
        status_b = true;
    }
    return status_b;
}

/** @brief Append textctrl text
 *
 * @param static_text_index_d : Static text index
 * @param text_str : Text
 * @return bool : textctrl change status
 *
 */

bool gui_frame::append_textctrl (double static_text_index_d, wxString text_str)
{
bool status_b = false;

    if (static_text_index_d < lv_data_textctrl_buffer.size())
    {
        if (!lv_data_textctrl_buffer[static_text_index_d].update_b)
        {
            lv_data_textctrl_buffer[static_text_index_d].text_str = text_str;
            lv_data_textctrl_buffer[static_text_index_d].append_b = true;
            lv_data_textctrl_buffer[static_text_index_d].update_b = true;
            status_b = true;
        }
    }
    return status_b;
}

/** @brief Get textctrl text
 *
 * @param static_text_index_d : Static text index
 * @param line_ui32 : Read line number
 * @return wxString : textctrl text string
 *
 */

wxString gui_frame::get_textctrl (double static_text_index_d, uint32_t line_ui32)
{
wxString text_str = wxEmptyString;

    if (static_text_index_d < lv_data_textctrl_buffer.size())
    {
        lv_data_textctrl_buffer[static_text_index_d].read_line_ui32 = line_ui32;
        lv_data_textctrl_buffer[static_text_index_d].read_b = true;
        wxMilliSleep(40);
        text_str = lv_data_textctrl_buffer[static_text_index_d].read_text_str;
    }
    return text_str;
}

/**
  ****************************************************************************
  * Local function
  ****************************************************************************
  */

/** @brief textctrl constructor event (must be called from GUI context)
 *
 * @param void
 * @return void
 *
 */

void gui_frame::on_update_textctrl(void)
{
wxPanel* p_data_wxpanel;
wxBoxSizer* p_data_wxboxsizer;
wxString textctrl_name_str;
uint32_t item_cnt_ui32;
wxTextCtrl* p_buffer_wxtextctrl = NULL;

    // Add Static text
    while (l_cnt_textctrl_ui32 < lv_data_textctrl_buffer.size())
    {
        // Get box sizer
        p_data_wxboxsizer = this->get_sizer(lv_data_textctrl_buffer[l_cnt_textctrl_ui32].sizer_index_d);
        // Get origin panel
        p_data_wxpanel = this->get_sizer_panel(lv_data_textctrl_buffer[l_cnt_textctrl_ui32].sizer_index_d);
        // Get new object ID
        lv_data_textctrl_buffer[l_cnt_textctrl_ui32].object_id_i32 = wxNewId();
        // Set new name
        textctrl_name_str.Printf("id_textctrl_%u", l_cnt_textctrl_ui32);
        // Create new static text
        if (lv_data_textctrl_buffer[l_cnt_textctrl_ui32].multiline_b)
        {
            p_buffer_wxtextctrl = new wxTextCtrl(p_data_wxpanel, lv_data_textctrl_buffer[l_cnt_textctrl_ui32].object_id_i32, lv_data_textctrl_buffer[l_cnt_textctrl_ui32].text_str, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE, wxDefaultValidator, textctrl_name_str);
        }
        else
        {
            p_buffer_wxtextctrl = new wxTextCtrl(p_data_wxpanel, lv_data_textctrl_buffer[l_cnt_textctrl_ui32].object_id_i32, lv_data_textctrl_buffer[l_cnt_textctrl_ui32].text_str, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, textctrl_name_str);
        }
        if(p_buffer_wxtextctrl)
        {
            // Insert in to sizer
            if(lv_data_textctrl_buffer[l_cnt_textctrl_ui32].expand_b)
            {
                p_data_wxboxsizer->Add(p_buffer_wxtextctrl, lv_data_textctrl_buffer[l_cnt_textctrl_ui32].proportion_d, wxALL|wxEXPAND, 5);
            }
            else
            {
                p_data_wxboxsizer->Add(p_buffer_wxtextctrl, lv_data_textctrl_buffer[l_cnt_textctrl_ui32].proportion_d, wxALL, 5);
            }
            p_data_wxboxsizer->Fit(p_data_wxpanel);
            p_data_wxboxsizer->SetSizeHints(p_data_wxpanel);
            p_data_wxboxsizer->Layout();
            lp_main_wxauimanager->Update();
            // Save object
            lv_data_textctrl_buffer[l_cnt_textctrl_ui32].p_data_wxtextctrl = p_buffer_wxtextctrl;
        }
        l_cnt_textctrl_ui32++;
    }
    for (item_cnt_ui32 = 0 ; item_cnt_ui32 < lv_data_textctrl_buffer.size() ; item_cnt_ui32++)
    {
        if (lv_data_textctrl_buffer[item_cnt_ui32].update_b)
        {
            if (lv_data_textctrl_buffer[item_cnt_ui32].append_b)
            {
                lv_data_textctrl_buffer[item_cnt_ui32].append_b = false;
                if(lv_data_textctrl_buffer[item_cnt_ui32].p_data_wxtextctrl)
                {
                    lv_data_textctrl_buffer[item_cnt_ui32].p_data_wxtextctrl->SetInsertionPointEnd();
                    lv_data_textctrl_buffer[item_cnt_ui32].p_data_wxtextctrl->WriteText(lv_data_textctrl_buffer[item_cnt_ui32].text_str);
                }

            }
            else
            {
                if(lv_data_textctrl_buffer[item_cnt_ui32].p_data_wxtextctrl)
                {
                    lv_data_textctrl_buffer[item_cnt_ui32].p_data_wxtextctrl->SetValue(lv_data_textctrl_buffer[item_cnt_ui32].text_str);
                }
            }
            lv_data_textctrl_buffer[item_cnt_ui32].update_b = false;
        }
        if (lv_data_textctrl_buffer[item_cnt_ui32].read_b)
        {
            //lv_data_textctrl_buffer[item_cnt_ui32].read_text_str = wxEmptyString;
            if(lv_data_textctrl_buffer[item_cnt_ui32].p_data_wxtextctrl)
            {
                if ((int32_t)lv_data_textctrl_buffer[item_cnt_ui32].read_line_ui32 == -1)
                {
                    lv_data_textctrl_buffer[item_cnt_ui32].read_text_str = lv_data_textctrl_buffer[item_cnt_ui32].p_data_wxtextctrl->GetValue();
                }
                else
                {
                    lv_data_textctrl_buffer[item_cnt_ui32].read_text_str = lv_data_textctrl_buffer[item_cnt_ui32].p_data_wxtextctrl->GetLineText(lv_data_textctrl_buffer[item_cnt_ui32].read_line_ui32);
                }
            }
            lv_data_textctrl_buffer[item_cnt_ui32].read_b = false;
        }
    }
    return;
}

/** @brief textctrl destructor event (must be called from GUI context)
 *
 * @param void
 * @return void
 *
 */

void gui_frame::on_clear_textctrl(void)
{
    lv_data_textctrl_buffer.clear();
    l_cnt_textctrl_ui32 = 0;
    return;
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


