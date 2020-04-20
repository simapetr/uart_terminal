/**
  ****************************************************************************
  * @file    in_js_gui_gauge_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    10.09.2018
  * @brief   GUI window gauge component
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
#include <wx/gauge.h>

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
  * @addtogroup Gauge
  * @brief GUI gauge component
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
    double proportion_d;
    double expand_b;
    double size_d;
    bool update_b;
    double value_d;
    wxGauge* p_data_wxgauge;
    int32_t object_id_i32;
}gauge_buffer_t;

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

static vector<gauge_buffer_t> lv_data_gauge_buffer;
static uint32_t l_cnt_gauge_ui32 = 0;

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Add gauge
 *
 * @param sizer_index_d : Parent sizer index
 * @param proportion_d : Relative proportion item in sizer
 * @param expand_b : Expand
 * @param size_d : Gauge size
 * @return uint32_t : New gauge buffer index
 *
 */

uint32_t gui_frame::add_gauge (double sizer_index_d, double proportion_d, bool expand_b, double size_d)
{
gauge_buffer_t data_gauge_buffer;
uint32_t index_ui32 = lv_data_gauge_buffer.size();

    data_gauge_buffer.sizer_index_d = sizer_index_d;
    data_gauge_buffer.expand_b = expand_b;
    data_gauge_buffer.proportion_d = proportion_d;
    data_gauge_buffer.p_data_wxgauge = NULL;
    data_gauge_buffer.object_id_i32 = 0;
    data_gauge_buffer.size_d = size_d;
    data_gauge_buffer.value_d = 0;
    data_gauge_buffer.update_b = false;
    lv_data_gauge_buffer.push_back(data_gauge_buffer);
    while(!lv_data_gauge_buffer[index_ui32].p_data_wxgauge){wxMilliSleep(1);}
    wxMilliSleep(1);
    return index_ui32;
}

/** @brief Set gauge state
 *
 * @param gauge_index_d : Gauge index
 * @param value_d : New value
 * @return bool : Status
 *
 */

bool gui_frame::set_gauge (double gauge_index_d, double value_d)
{
bool status_b = false;

    if (gauge_index_d < lv_data_gauge_buffer.size())
    {
        lv_data_gauge_buffer[gauge_index_d].value_d = value_d;
        lv_data_gauge_buffer[gauge_index_d].update_b = true;
        status_b = true;
    }
    return status_b;
}

/** @brief Get gauge value
 *
 * @param gauge_index_d : Gauge index
 * @return double : Value
 *
 */

double gui_frame::get_gauge (double gauge_index_d)
{
double value_d = false;

    if (gauge_index_d < lv_data_gauge_buffer.size())
    {
        value_d = lv_data_gauge_buffer[gauge_index_d].value_d;
    }
    return value_d;
}

/**
  ****************************************************************************
  * Local function
  ****************************************************************************
  */

/** @brief Gauge constructor event (must be called from GUI context)
 *
 * @param void
 * @return void
 *
 */

void gui_frame::on_update_gauge(void)
{
wxPanel* p_data_wxpanel;
wxBoxSizer* p_data_wxboxsizer;
wxString gauge_name_str;
uint32_t item_cnt_ui32;
wxGauge* p_buffer_wxgauge = NULL;

    // Add check_box
    while (l_cnt_gauge_ui32 < lv_data_gauge_buffer.size())
    {
        // Get box sizer
        p_data_wxboxsizer = this->get_sizer(lv_data_gauge_buffer[l_cnt_gauge_ui32].sizer_index_d);
        // Get origin panel
        p_data_wxpanel = this->get_sizer_panel(lv_data_gauge_buffer[l_cnt_gauge_ui32].sizer_index_d);
        // Get new object ID
        lv_data_gauge_buffer[l_cnt_gauge_ui32].object_id_i32 = wxNewId();
        // Set new name
        gauge_name_str.Printf("id_slider_%u", l_cnt_gauge_ui32);
        // Create new check_box
        p_buffer_wxgauge = new wxGauge(p_data_wxpanel, lv_data_gauge_buffer[l_cnt_gauge_ui32].object_id_i32, lv_data_gauge_buffer[l_cnt_gauge_ui32].size_d, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, gauge_name_str);
        if (p_buffer_wxgauge)
        {
            // Insert in to sizer
            if(lv_data_gauge_buffer[l_cnt_gauge_ui32].expand_b)
            {
                p_data_wxboxsizer->Add(p_buffer_wxgauge, lv_data_gauge_buffer[l_cnt_gauge_ui32].proportion_d, wxALL|wxEXPAND, 5);
            }
            else
            {
                p_data_wxboxsizer->Add(p_buffer_wxgauge, lv_data_gauge_buffer[l_cnt_gauge_ui32].proportion_d, wxALL, 5);
            }
            p_data_wxboxsizer->Fit(p_data_wxpanel);
            p_data_wxboxsizer->SetSizeHints(p_data_wxpanel);
            p_data_wxboxsizer->Layout();
            lp_main_wxauimanager->Update();
            // Save object
            lv_data_gauge_buffer[l_cnt_gauge_ui32].p_data_wxgauge = p_buffer_wxgauge;
        }
        l_cnt_gauge_ui32++;
    }
    for (item_cnt_ui32 = 0 ; item_cnt_ui32 < lv_data_gauge_buffer.size() ; item_cnt_ui32++)
    {
        if (lv_data_gauge_buffer[item_cnt_ui32].update_b)
        {
            lv_data_gauge_buffer[item_cnt_ui32].update_b = false;
            if (lv_data_gauge_buffer[item_cnt_ui32].p_data_wxgauge)
            {
                lv_data_gauge_buffer[item_cnt_ui32].p_data_wxgauge->SetValue(lv_data_gauge_buffer[item_cnt_ui32].value_d);
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

void gui_frame::on_clear_gauge(void)
{
    lv_data_gauge_buffer.clear();
    l_cnt_gauge_ui32 = 0;
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


