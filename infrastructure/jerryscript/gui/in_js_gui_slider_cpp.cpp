/**
  ****************************************************************************
  * @file    in_js_gui_slider_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    10.09.2018
  * @brief   GUI window slider component
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
#include <wx/slider.h>

/**
  * @addtogroup Application
  * @{
  */

/**
  * @addtogroup GUI
  * @{
  */

/**
  * @addtogroup Slider
  * @brief GUI slider component
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
    wxString event_str;
    double min_d;
    double max_d;
    double proportion_d;
    bool expand_b;
    double value_d;
    bool update_b;
    wxSlider* p_data_wxslider;
    int32_t object_id_i32;
}slider_buffer_t;

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

vector<slider_buffer_t> lv_data_slider_buffer;

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Add slider
 *
 * @param sizer_index_d : Parent sizer index
 * @param min_d : Minimal value
 * @param max_d : Maximal value
 * @param proportion_d : Relative proportion item in sizer
 * @param expand_b : Expand
 * @return uint32_t : New slider buffer index
 *
 */

uint32_t gui_frame::add_slider (double sizer_index_d, double min_d, double max_d, double proportion_d, bool expand_b)
{
slider_buffer_t l_data_slider_buffer;
uint32_t sizer_index_ui32 = lv_data_slider_buffer.size();

    l_data_slider_buffer.sizer_index_d = sizer_index_d;
    l_data_slider_buffer.min_d = min_d;
    l_data_slider_buffer.max_d = max_d;
    l_data_slider_buffer.expand_b = expand_b;
    l_data_slider_buffer.proportion_d = proportion_d;
    l_data_slider_buffer.p_data_wxslider = NULL;
    l_data_slider_buffer.object_id_i32 = 0;
    l_data_slider_buffer.event_str = wxEmptyString;
    l_data_slider_buffer.value_d = 0.0;
    l_data_slider_buffer.update_b = false;
    lv_data_slider_buffer.push_back(l_data_slider_buffer);
    wxMilliSleep(40);
    return sizer_index_ui32;
}

/** @brief Set slider event
 *
 * @param index_d : Component index
 * @param event_fct_str : Reg function name
 * @return bool : Button event reg status
 *
 */

bool gui_frame::set_slider_event (double index_d, wxString event_fct_str)
{
bool status_b = false;

    if (index_d < lv_data_slider_buffer.size())
    {
        lv_data_slider_buffer[index_d].event_str = event_fct_str;
        status_b = true;
    }
    return status_b;
}

/** @brief Get slider data
 *
 * @param index_d : Component index
 * @return int32_t : Button event reg status
 *
 */

int32_t gui_frame::get_slider_data (double index_d)
{
int32_t data_i32 = false;

    if (index_d < lv_data_slider_buffer.size())
    {
        data_i32 = lv_data_slider_buffer[index_d].value_d;
    }
    return data_i32;
}

/** @brief Set slider data
 *
 * @param index_d : Component index
 * @param data_d : Data value
 * @return int32_t : Button event reg status
 *
 */

void gui_frame::set_slider_data (double index_d, double data_d)
{
    if (index_d < lv_data_slider_buffer.size())
    {
        lv_data_slider_buffer[index_d].update_b = true;
        lv_data_slider_buffer[index_d].value_d = data_d;
    }
    return;
}

/**
  ****************************************************************************
  * Local function
  ****************************************************************************
  */

/** @brief Slider change
 *
 * @param  event : Event parameter
 * @return void
 *
 */

void gui_frame::on_slider_update(wxScrollEvent& event)
{
uint32_t event_cnt_ui32;

    for(event_cnt_ui32 = 0 ; event_cnt_ui32 < lv_data_slider_buffer.size() ; event_cnt_ui32++)
    {
        if (lv_data_slider_buffer[event_cnt_ui32].object_id_i32 == event.GetId())
        {
            if(lv_data_slider_buffer[event_cnt_ui32].p_data_wxslider)
            {
                // Read value
                lv_data_slider_buffer[event_cnt_ui32].value_d = lv_data_slider_buffer[event_cnt_ui32].p_data_wxslider->GetValue();
                // Call event function
                if (lv_data_slider_buffer[event_cnt_ui32].event_str != wxEmptyString)
                {
                    ((jerryscript_c*)(this->lp_jerryscript_void))->call_event(lv_data_slider_buffer[event_cnt_ui32].event_str, event_cnt_ui32);
                }
            }
        }
    }
    return;
}

/** @brief Slider constructor event (must be called from GUI context)
 *
 * @param void
 * @return void
 *
 */

void gui_frame::on_update_slider(void)
{
static uint32_t f_item_cnt_ui32 = 0;
wxPanel* p_data_wxpanel;
wxBoxSizer* p_data_wxboxsizer;
wxString slider_name_str;
uint32_t item_cnt_ui32;

    // Add slider
    while (f_item_cnt_ui32 < lv_data_slider_buffer.size())
    {
        // Get box sizer
        p_data_wxboxsizer = lv_data_sizer_buffer[lv_data_slider_buffer[f_item_cnt_ui32].sizer_index_d].p_data_wxboxsizer;
        // Get origin panel
        p_data_wxpanel = lv_data_panel_buffer[lv_data_sizer_buffer[lv_data_slider_buffer[f_item_cnt_ui32].sizer_index_d].panel_index_d].p_data_wxpanel;
        // Get new object ID
        lv_data_slider_buffer[f_item_cnt_ui32].object_id_i32 = wxNewId();
        // Set new name
        slider_name_str.Printf("id_slider_%u", f_item_cnt_ui32);
        // Create new slider
        lv_data_slider_buffer[f_item_cnt_ui32].p_data_wxslider = new wxSlider(p_data_wxpanel, lv_data_slider_buffer[f_item_cnt_ui32].object_id_i32, lv_data_slider_buffer[f_item_cnt_ui32].min_d, lv_data_slider_buffer[f_item_cnt_ui32].min_d, lv_data_slider_buffer[f_item_cnt_ui32].max_d, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, slider_name_str);
        if(lv_data_slider_buffer[f_item_cnt_ui32].p_data_wxslider)
        {
            // Insert in to sizer
            if(lv_data_slider_buffer[f_item_cnt_ui32].expand_b)
            {
                p_data_wxboxsizer->Add(lv_data_slider_buffer[f_item_cnt_ui32].p_data_wxslider, lv_data_slider_buffer[f_item_cnt_ui32].proportion_d, wxALL|wxEXPAND, 5);
            }
            else
            {
                p_data_wxboxsizer->Add(lv_data_slider_buffer[f_item_cnt_ui32].p_data_wxslider, lv_data_slider_buffer[f_item_cnt_ui32].proportion_d, wxALL, 5);
            }
            p_data_wxboxsizer->Fit(p_data_wxpanel);
            p_data_wxboxsizer->SetSizeHints(p_data_wxpanel);
            p_data_wxboxsizer->Layout();
            lp_main_wxauimanager->Update();
            // Bind event
            lv_data_slider_buffer[f_item_cnt_ui32].p_data_wxslider->Bind(wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&gui_frame::on_slider_update, this);
        }
        f_item_cnt_ui32++;
    }
    for (item_cnt_ui32 = 0 ; item_cnt_ui32 < lv_data_slider_buffer.size() ; item_cnt_ui32++)
    {
        if (lv_data_slider_buffer[item_cnt_ui32].update_b)
        {
            lv_data_slider_buffer[item_cnt_ui32].update_b = false;
            if(lv_data_slider_buffer[f_item_cnt_ui32].p_data_wxslider)
            {
                lv_data_slider_buffer[item_cnt_ui32].p_data_wxslider->SetValue((int)lv_data_slider_buffer[item_cnt_ui32].value_d);
            }
        }
    }

    return;
}

/** @brief Slider destructor event (must be called from GUI context)
 *
 * @param void
 * @return void
 *
 */

void gui_frame::on_clear_slider(void)
{
    lv_data_slider_buffer.clear();
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


