/**
  ****************************************************************************
  * @file    in_js_gui_button_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    10.09.2018
  * @brief   GUI window button component
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
#include <wx/button.h>

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @addtogroup JerryScript
  * @{
  */

/**
  * @addtogroup GUI
  * @{
  */

/**
  * @addtogroup Button
  * @brief GUI button component
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
    wxButton* p_data_wxbutton;
    int32_t object_id_i32;
}button_buffer_t;

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

static vector<button_buffer_t> lv_data_button_buffer;
static uint32_t l_cnt_button_ui32 = 0;

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Add button
 *
 * @param sizer_index_d : Parent sizer index
 * @param text_str : Button text
 * @param proportion_d : Relative proportion item in sizer
 * @param expand_b : Expand
 * @return uint32_t : New button buffer index
 *
 */

uint32_t gui_frame::add_button (double sizer_index_d, wxString text_str, double proportion_d, bool expand_b)
{
button_buffer_t l_data_button_buffer;
uint32_t index_ui32 = lv_data_button_buffer.size();

    l_data_button_buffer.sizer_index_d = sizer_index_d;
    l_data_button_buffer.text_str = text_str;
    l_data_button_buffer.expand_b = expand_b;
    l_data_button_buffer.proportion_d = proportion_d;
    l_data_button_buffer.p_data_wxbutton = NULL;
    l_data_button_buffer.object_id_i32 = 0;
    l_data_button_buffer.event_str = wxEmptyString;
    lv_data_button_buffer.push_back(l_data_button_buffer);
    while(!lv_data_button_buffer[index_ui32].p_data_wxbutton){wxMilliSleep(1);}
    wxMilliSleep(1);
    return index_ui32;
}

/** @brief Set button event
 *
 * @param button_index_d : Button index
 * @param event_fct_str : Reg function name
 * @return bool : Button event reg status
 *
 */

bool gui_frame::set_button_event (double button_index_d, wxString event_fct_str)
{
bool status_b = false;

    if (button_index_d < lv_data_button_buffer.size())
    {
        lv_data_button_buffer[button_index_d].event_str = event_fct_str;
        status_b = true;
    }
    return status_b;
}

/**
  ****************************************************************************
  * Local function
  ****************************************************************************
  */

/** @brief Button click
 *
 * @param  event : Event parameter
 * @return void
 *
 */

void gui_frame::on_button_click(wxCommandEvent& event)
{
uint32_t event_cnt_ui32;

    for(event_cnt_ui32 = 0 ; event_cnt_ui32 < lv_data_button_buffer.size() ; event_cnt_ui32++)
    {
        if (lv_data_button_buffer[event_cnt_ui32].object_id_i32 == event.GetId())
        {
            // Call event function
            if (lv_data_button_buffer[event_cnt_ui32].event_str != wxEmptyString)
            {
                ((jerryscript_c*)(this->lp_jerryscript_void))->call_event(lv_data_button_buffer[event_cnt_ui32].event_str, event_cnt_ui32);
            }
        }
    }
    return;
}

/** @brief Button constructor event (must be called from GUI context)
 *
 * @param void
 * @return void
 *
 */

void gui_frame::on_update_button(void)
{
wxPanel* p_data_wxpanel;
wxBoxSizer* p_data_wxboxsizer;
wxString button_name_str;
wxButton* p_buffer_wxbutton = NULL;

    // Add button
    while (l_cnt_button_ui32 < lv_data_button_buffer.size())
    {
        // Get box sizer
        p_data_wxboxsizer = this->get_sizer(lv_data_button_buffer[l_cnt_button_ui32].sizer_index_d);
        // Get origin panel
        p_data_wxpanel = this->get_sizer_panel(lv_data_button_buffer[l_cnt_button_ui32].sizer_index_d);
        // Get new object ID
        lv_data_button_buffer[l_cnt_button_ui32].object_id_i32 = wxNewId();
        // Set new name
        button_name_str.Printf("id_button_%u", l_cnt_button_ui32);
        // Create new button
        p_buffer_wxbutton = new wxButton(p_data_wxpanel, lv_data_button_buffer[l_cnt_button_ui32].object_id_i32, lv_data_button_buffer[l_cnt_button_ui32].text_str, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, button_name_str);
        if (p_buffer_wxbutton)
        {
            // Insert in to sizer
            if(lv_data_button_buffer[l_cnt_button_ui32].expand_b)
            {
                p_data_wxboxsizer->Add(p_buffer_wxbutton, lv_data_button_buffer[l_cnt_button_ui32].proportion_d, wxALL|wxEXPAND, 5);
            }
            else
            {
                p_data_wxboxsizer->Add(p_buffer_wxbutton, lv_data_button_buffer[l_cnt_button_ui32].proportion_d, wxALL, 5);
            }
            p_data_wxboxsizer->Fit(p_data_wxpanel);
            p_data_wxboxsizer->SetSizeHints(p_data_wxpanel);
            p_data_wxboxsizer->Layout();
            lp_main_wxauimanager->Update();
            // Bind event
            p_buffer_wxbutton->Bind(wxEVT_BUTTON, &gui_frame::on_button_click, this);
            // Save object
            lv_data_button_buffer[l_cnt_button_ui32].p_data_wxbutton = p_buffer_wxbutton;
        }
        l_cnt_button_ui32++;
    }
    return;
}

/** @brief Button destructor event (must be called from GUI context)
 *
 * @param void
 * @return void
 *
 */

void gui_frame::on_clear_button(void)
{
    lv_data_button_buffer.clear();
    l_cnt_button_ui32 = 0;
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

/**
* @}
*/

/*****************************************************END OF FILE************/


