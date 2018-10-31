/**
  ****************************************************************************
  * @file    in_js_gui_check_box_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    10.09.2018
  * @brief   GUI window check box component
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
#include <wx/checkbox.h>

/**
  * @addtogroup Application
  * @{
  */

/**
  * @addtogroup GUI
  * @{
  */

/**
  * @addtogroup Check_box
  * @brief GUI check box component
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
    wxString event_str;
    double proportion_d;
    double expand_b;
    bool update_b;
    bool state_b;
    wxCheckBox* p_data_wxcheckbox;
    int32_t object_id_i32;
}check_box_buffer_t;

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

vector<check_box_buffer_t> lv_data_check_box_buffer;

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Add check box
 *
 * @param sizer_index_d : Parent sizer index
 * @param text_str : Check box text
 * @param proportion_d : Relative proportion item in sizer
 * @param expand_b : Expand
 * @param state_b : Initial state
 * @return uint32_t : New check box buffer index
 *
 */

uint32_t gui_frame::add_check_box (double sizer_index_d, wxString text_str, double proportion_d, bool expand_b, bool state_b)
{
check_box_buffer_t data_check_box_buffer;
uint32_t sizer_index_ui32 = lv_data_check_box_buffer.size();

    data_check_box_buffer.sizer_index_d = sizer_index_d;
    data_check_box_buffer.text_str = text_str;
    data_check_box_buffer.expand_b = expand_b;
    data_check_box_buffer.proportion_d = proportion_d;
    data_check_box_buffer.p_data_wxcheckbox = NULL;
    data_check_box_buffer.object_id_i32 = 0;
    data_check_box_buffer.event_str = wxEmptyString;
    data_check_box_buffer.state_b = state_b;
    data_check_box_buffer.update_b = false;
    lv_data_check_box_buffer.push_back(data_check_box_buffer);
    wxMilliSleep(40);
    return sizer_index_ui32;
}

/** @brief Set check box event
 *
 * @param check_box_index_d : Check box index
 * @param event_fct_str : Reg function name
 * @return bool : Check box event reg status
 *
 */

bool gui_frame::set_check_box_event (double check_box_index_d, wxString event_fct_str)
{
bool status_b = false;

    if (check_box_index_d < lv_data_check_box_buffer.size())
    {
        lv_data_check_box_buffer[check_box_index_d].event_str = event_fct_str;
        status_b = true;
    }
    return status_b;
}

/** @brief Set check box state
 *
 * @param check_box_index_d : Check box index
 * @param state_b : New state
 * @return bool : Status
 *
 */

bool gui_frame::set_check_box (double check_box_index_d, bool state_b)
{
bool status_b = false;

    if (check_box_index_d < lv_data_check_box_buffer.size())
    {
        lv_data_check_box_buffer[check_box_index_d].state_b = state_b;
        lv_data_check_box_buffer[check_box_index_d].update_b = true;
        status_b = true;
    }
    return status_b;
}

/** @brief Get check box state
 *
 * @param check_box_index_d : Check box index
 * @return bool : Check box State
 *
 */

bool gui_frame::get_check_box (double check_box_index_d)
{
bool status_b = false;

    if (check_box_index_d < lv_data_check_box_buffer.size())
    {
        status_b = lv_data_check_box_buffer[check_box_index_d].state_b;
    }
    return status_b;
}

/**
  ****************************************************************************
  * Local function
  ****************************************************************************
  */

/** @brief Check box click
 *
 * @param  event : Event parameter
 * @return void
 *
 */

void gui_frame::on_check_box_click(wxCommandEvent& event)
{
uint32_t event_cnt_ui32;

    for(event_cnt_ui32 = 0 ; event_cnt_ui32 < lv_data_check_box_buffer.size() ; event_cnt_ui32++)
    {
        if (lv_data_check_box_buffer[event_cnt_ui32].object_id_i32 == event.GetId())
        {
            // Call event function
            if (lv_data_check_box_buffer[event_cnt_ui32].event_str != wxEmptyString)
            {
                lv_data_check_box_buffer[event_cnt_ui32].state_b = event.IsChecked();
                ((jerryscript_c*)(this->lp_jerryscript_void))->call_event(lv_data_check_box_buffer[event_cnt_ui32].event_str, event_cnt_ui32);
            }
        }
    }
    return;
}

/** @brief Check box constructor event (must be called from GUI context)
 *
 * @param void
 * @return void
 *
 */

void gui_frame::on_update_check_box(void)
{
static uint32_t f_check_box_cnt_ui32 = 0;
wxPanel* p_data_wxpanel;
wxBoxSizer* p_data_wxboxsizer;
wxString check_box_name_str;
uint32_t item_cnt_ui32;

    // Add check_box
    while (f_check_box_cnt_ui32 < lv_data_check_box_buffer.size())
    {
        // Get box sizer
        p_data_wxboxsizer = lv_data_sizer_buffer[lv_data_check_box_buffer[f_check_box_cnt_ui32].sizer_index_d].p_data_wxboxsizer;
        // Get origin panel
        p_data_wxpanel = lv_data_panel_buffer[lv_data_sizer_buffer[lv_data_check_box_buffer[f_check_box_cnt_ui32].sizer_index_d].panel_index_d].p_data_wxpanel;
        // Get new object ID
        lv_data_check_box_buffer[f_check_box_cnt_ui32].object_id_i32 = wxNewId();
        // Set new name
        check_box_name_str.Printf("id_check_box_%u", f_check_box_cnt_ui32);
        // Create new check_box
        lv_data_check_box_buffer[f_check_box_cnt_ui32].p_data_wxcheckbox = new wxCheckBox(p_data_wxpanel, lv_data_check_box_buffer[f_check_box_cnt_ui32].object_id_i32, lv_data_check_box_buffer[f_check_box_cnt_ui32].text_str, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, check_box_name_str);
        if (lv_data_check_box_buffer[f_check_box_cnt_ui32].p_data_wxcheckbox)
        {
            // Insert in to sizer
            if(lv_data_check_box_buffer[f_check_box_cnt_ui32].expand_b)
            {
                p_data_wxboxsizer->Add(lv_data_check_box_buffer[f_check_box_cnt_ui32].p_data_wxcheckbox, lv_data_check_box_buffer[f_check_box_cnt_ui32].proportion_d, wxALL|wxEXPAND, 5);
            }
            else
            {
                p_data_wxboxsizer->Add(lv_data_check_box_buffer[f_check_box_cnt_ui32].p_data_wxcheckbox, lv_data_check_box_buffer[f_check_box_cnt_ui32].proportion_d, wxALL, 5);
            }
            p_data_wxboxsizer->Fit(p_data_wxpanel);
            p_data_wxboxsizer->SetSizeHints(p_data_wxpanel);
            p_data_wxboxsizer->Layout();
            lp_main_wxauimanager->Update();
            // Bind event
            lv_data_check_box_buffer[f_check_box_cnt_ui32].p_data_wxcheckbox->Bind(wxEVT_CHECKBOX, &gui_frame::on_check_box_click, this);
        }
        f_check_box_cnt_ui32++;
    }
    for (item_cnt_ui32 = 0 ; item_cnt_ui32 < lv_data_check_box_buffer.size() ; item_cnt_ui32++)
    {
        if (lv_data_check_box_buffer[item_cnt_ui32].update_b)
        {
            lv_data_check_box_buffer[item_cnt_ui32].update_b = false;
            if (lv_data_check_box_buffer[item_cnt_ui32].p_data_wxcheckbox)
            {
                lv_data_check_box_buffer[item_cnt_ui32].p_data_wxcheckbox->SetValue(lv_data_check_box_buffer[item_cnt_ui32].state_b);
            }
        }
    }
    return;
}

/** @brief Check box destructor event (must be called from GUI context)
 *
 * @param void
 * @return void
 *
 */

void gui_frame::on_clear_check_box(void)
{
    lv_data_check_box_buffer.clear();
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


