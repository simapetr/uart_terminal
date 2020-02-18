/**
  ****************************************************************************
  * @file    in_js_gui_panel_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    10.09.2018
  * @brief   GUI window panel component
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

/**
  * @addtogroup Application
  * @{
  */

/**
  * @addtogroup GUI
  * @{
  */

/**
  * @addtogroup Panel
  * @brief GUI panel component
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
    wxString name_str;
    double sizer_index_d;
    bool sizer_orientation_b;
    wxPanel* p_data_wxpanel;
}panel_buffer_t;

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

static vector<panel_buffer_t> lv_data_panel_buffer;
static uint32_t l_cnt_panel_ui32 = 0;

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Add AUI panel
 *
 * @param panel_name_str : Panel name
 * @param horizontal_b : Sizer orientation
 * @return uint32_t : new panel buffer index
 *
 */

uint32_t gui_frame::add_panel (wxString panel_name_str, bool horizontal_b)
{
panel_buffer_t l_data_panel_buffer;
uint32_t index_ui32 = lv_data_panel_buffer.size();
wxBoxSizer* p_data_wxboxsizer;

    l_data_panel_buffer.name_str = panel_name_str;
    l_data_panel_buffer.sizer_orientation_b = horizontal_b;
    l_data_panel_buffer.p_data_wxpanel = NULL;
    l_data_panel_buffer.sizer_index_d = 0;
    lv_data_panel_buffer.push_back(l_data_panel_buffer);
    while(!lv_data_panel_buffer[index_ui32].p_data_wxpanel){wxMilliSleep(1);}
    wxMilliSleep(1);
    lv_data_panel_buffer[index_ui32].sizer_index_d = this->add_panel_sizer(index_ui32, 1, horizontal_b);
    // Get box sizer
    p_data_wxboxsizer = this->get_sizer(lv_data_panel_buffer[index_ui32].sizer_index_d);
    lv_data_panel_buffer[index_ui32].p_data_wxpanel->SetSizer(p_data_wxboxsizer);
    // Update
    p_data_wxboxsizer->Fit(lv_data_panel_buffer[index_ui32].p_data_wxpanel);
    p_data_wxboxsizer->SetSizeHints(lv_data_panel_buffer[index_ui32].p_data_wxpanel);
    return index_ui32;
}

/** @brief Get panel main sizer
 *
 * @param panel_index_d : Panel index
 * @return uint32_t : Sizer index
 *
 */

uint32_t gui_frame::get_panel_sizer (double panel_index_d)
{
uint32_t sizer_index_ui32 = 0;

    if (panel_index_d < lv_data_panel_buffer.size())
    {
        sizer_index_ui32 = lv_data_panel_buffer[panel_index_d].sizer_index_d;
    }
    return sizer_index_ui32;
}

/** @brief Get sizer
 *
 * @param index_d : Sizer index
 * @return wxBoxSizer* : Box sizer object pointer
 *
 */

wxPanel* gui_frame::get_panel (double index_d)
{
wxPanel* data_wxpanel = NULL;
    if (index_d < lv_data_panel_buffer.size())
    {
        data_wxpanel = lv_data_panel_buffer[index_d].p_data_wxpanel;
    }
    return data_wxpanel;
}

/**
  ****************************************************************************
  * Local function
  ****************************************************************************
  */

/** @brief Panel constructor event (must be called from GUI context)
 *
 * @param void
 * @return void
 *
 */

void gui_frame::on_update_panel(void)
{
wxPanel* p_buffer_wxpanel = NULL;

    // Add panel
    while (l_cnt_panel_ui32 < lv_data_panel_buffer.size())
    {
        // Create new panel
        p_buffer_wxpanel = new wxPanel(this, wxNewId(), wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, lv_data_panel_buffer[l_cnt_panel_ui32].name_str);
        if(p_buffer_wxpanel)
        {
            p_buffer_wxpanel->SetFocus();
            // Add panel in to AUI
            lp_main_wxauimanager->AddPane(p_buffer_wxpanel, wxAuiPaneInfo().Name(lv_data_panel_buffer[l_cnt_panel_ui32].name_str).DefaultPane().Caption(lv_data_panel_buffer[l_cnt_panel_ui32].name_str).CaptionVisible().MinimizeButton().MaximizeButton().PinButton().Maximize());
            lp_main_wxauimanager->Update();
            // Save object
            lv_data_panel_buffer[l_cnt_panel_ui32].p_data_wxpanel = p_buffer_wxpanel;
        }
        l_cnt_panel_ui32++;
    }
    return;
}

/** @brief Panel destructor event (must be called from GUI context)
 *
 * @param void
 * @return void
 *
 */

void gui_frame::on_clear_panel(void)
{
    lv_data_panel_buffer.clear();
    l_cnt_panel_ui32 = 0;
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


