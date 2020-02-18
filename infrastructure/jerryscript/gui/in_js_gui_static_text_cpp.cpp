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
#include <wx/stattext.h>

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
    bool update_b;
    wxStaticText* p_data_wxstatictext;
    int32_t object_id_i32;
}static_text_buffer_t;

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

static vector<static_text_buffer_t> lv_data_static_text_buffer;
static uint32_t l_cnt_static_text_ui32 = 0;

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Add static_text
 *
 * @param sizer_index_d : Parent sizer index
 * @param text_str : Text
 * @param proportion_d : Relative proportion item in sizer
 * @param expand_b : Expand
 * @return uint32_t : New static_text buffer index
 *
 */

uint32_t gui_frame::add_static_text (double sizer_index_d, wxString text_str, double proportion_d, bool expand_b)
{
static_text_buffer_t l_data_static_text_buffer;
uint32_t index_ui32 = lv_data_static_text_buffer.size();

    l_data_static_text_buffer.sizer_index_d = sizer_index_d;
    l_data_static_text_buffer.text_str = text_str;
    l_data_static_text_buffer.expand_b = expand_b;
    l_data_static_text_buffer.proportion_d = proportion_d;
    l_data_static_text_buffer.p_data_wxstatictext = NULL;
    l_data_static_text_buffer.object_id_i32 = 0;
    l_data_static_text_buffer.update_b = false;
    lv_data_static_text_buffer.push_back(l_data_static_text_buffer);
    while(!lv_data_static_text_buffer[index_ui32].p_data_wxstatictext){wxMilliSleep(1);}
    wxMilliSleep(1);
    return index_ui32;
}

/** @brief Set static_text text
 *
 * @param static_text_index_d : Static text index
 * @param text_str : Text
 * @return bool : static_text change status
 *
 */

bool gui_frame::set_static_text (double static_text_index_d, wxString text_str)
{
bool status_b = false;

    if (static_text_index_d < lv_data_static_text_buffer.size())
    {
        lv_data_static_text_buffer[static_text_index_d].text_str = text_str;
        lv_data_static_text_buffer[static_text_index_d].update_b = true;
        status_b = true;
    }
    return status_b;
}

/**
  ****************************************************************************
  * Local function
  ****************************************************************************
  */

/** @brief static_text constructor event (must be called from GUI context)
 *
 * @param void
 * @return void
 *
 */

void gui_frame::on_update_static_text(void)
{
wxPanel* p_data_wxpanel;
wxBoxSizer* p_data_wxboxsizer;
wxString static_text_name_str;
uint32_t item_cnt_ui32;
wxStaticText* p_buffer_wxstatictext = NULL;

    // Add Static text
    while (l_cnt_static_text_ui32 < lv_data_static_text_buffer.size())
    {
        // Get box sizer
        p_data_wxboxsizer = this->get_sizer(lv_data_static_text_buffer[l_cnt_static_text_ui32].sizer_index_d);
        // Get origin panel
        p_data_wxpanel = this->get_sizer_panel(lv_data_static_text_buffer[l_cnt_static_text_ui32].sizer_index_d);
        // Get new object ID
        lv_data_static_text_buffer[l_cnt_static_text_ui32].object_id_i32 = wxNewId();
        // Set new name
        static_text_name_str.Printf("id_static_text_%u", l_cnt_static_text_ui32);
        // Create new static text
        p_buffer_wxstatictext = new wxStaticText(p_data_wxpanel, lv_data_static_text_buffer[l_cnt_static_text_ui32].object_id_i32, lv_data_static_text_buffer[l_cnt_static_text_ui32].text_str, wxDefaultPosition, wxDefaultSize, 0, static_text_name_str);
        if(p_buffer_wxstatictext)
        {
            // Insert in to sizer
            if(lv_data_static_text_buffer[l_cnt_static_text_ui32].expand_b)
            {
                p_data_wxboxsizer->Add(p_buffer_wxstatictext, lv_data_static_text_buffer[l_cnt_static_text_ui32].proportion_d, wxALL|wxEXPAND, 5);
            }
            else
            {
                p_data_wxboxsizer->Add(p_buffer_wxstatictext, lv_data_static_text_buffer[l_cnt_static_text_ui32].proportion_d, wxALL, 5);
            }
            p_data_wxboxsizer->Fit(p_data_wxpanel);
            p_data_wxboxsizer->SetSizeHints(p_data_wxpanel);
            p_data_wxboxsizer->Layout();
            lp_main_wxauimanager->Update();
            // Save object
            lv_data_static_text_buffer[l_cnt_static_text_ui32].p_data_wxstatictext = p_buffer_wxstatictext;
        }
        l_cnt_static_text_ui32++;
    }
    for (item_cnt_ui32 = 0 ; item_cnt_ui32 < lv_data_static_text_buffer.size() ; item_cnt_ui32++)
    {
        if (lv_data_static_text_buffer[item_cnt_ui32].update_b)
        {
            lv_data_static_text_buffer[item_cnt_ui32].update_b = false;
            if(lv_data_static_text_buffer[item_cnt_ui32].p_data_wxstatictext)
            {
                lv_data_static_text_buffer[item_cnt_ui32].p_data_wxstatictext->SetLabel(lv_data_static_text_buffer[item_cnt_ui32].text_str);
            }
        }
    }
    return;
}

/** @brief static_text destructor event (must be called from GUI context)
 *
 * @param void
 * @return void
 *
 */

void gui_frame::on_clear_static_text(void)
{
    lv_data_static_text_buffer.clear();
    l_cnt_static_text_ui32 = 0;
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


