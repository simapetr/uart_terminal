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



/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

vector<panel_buffer_t> lv_data_panel_buffer;

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
uint32_t panel_index_ui32 = lv_data_panel_buffer.size();

    l_data_panel_buffer.name_str = panel_name_str;
    l_data_panel_buffer.sizer_orientation_b = horizontal_b;
    l_data_panel_buffer.p_data_wxpanel = NULL;
    l_data_panel_buffer.sizer_index_d = 0;
    lv_data_panel_buffer.push_back(l_data_panel_buffer);
    wxMilliSleep(40);
    return panel_index_ui32;
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
static uint32_t f_panel_cnt_ui32 = 0;
sizer_buffer_t data_sizer_buffer;

    // Add panel
    while (f_panel_cnt_ui32 < lv_data_panel_buffer.size())
    {
        // Create new panel
        lv_data_panel_buffer[f_panel_cnt_ui32].p_data_wxpanel = new wxPanel(this, wxNewId(), wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, lv_data_panel_buffer[f_panel_cnt_ui32].name_str);
        if(lv_data_panel_buffer[f_panel_cnt_ui32].p_data_wxpanel)
        {
            lv_data_panel_buffer[f_panel_cnt_ui32].p_data_wxpanel->SetFocus();
            // Create new sizer
            data_sizer_buffer.sizer_orientation_b = lv_data_panel_buffer[f_panel_cnt_ui32].sizer_orientation_b;
            data_sizer_buffer.panel_index_d = f_panel_cnt_ui32;
            data_sizer_buffer.parent_index_d = lv_data_sizer_buffer.size();
            data_sizer_buffer.proportion_d = 0;
            if(lv_data_panel_buffer[f_panel_cnt_ui32].sizer_orientation_b)
            {
                data_sizer_buffer.p_data_wxboxsizer = new wxBoxSizer(wxHORIZONTAL);
            }
            else
            {
                data_sizer_buffer.p_data_wxboxsizer = new wxBoxSizer(wxVERTICAL);
            }
            lv_data_panel_buffer[f_panel_cnt_ui32].sizer_index_d = lv_data_sizer_buffer.size();
            lv_data_panel_buffer[f_panel_cnt_ui32].p_data_wxpanel->SetSizer(data_sizer_buffer.p_data_wxboxsizer);
            // Update
            data_sizer_buffer.p_data_wxboxsizer->Fit(lv_data_panel_buffer[f_panel_cnt_ui32].p_data_wxpanel);
            data_sizer_buffer.p_data_wxboxsizer->SetSizeHints(lv_data_panel_buffer[f_panel_cnt_ui32].p_data_wxpanel);
            // Add panel in to AUI
            lp_main_wxauimanager->AddPane(lv_data_panel_buffer[f_panel_cnt_ui32].p_data_wxpanel, wxAuiPaneInfo().DefaultPane().Caption(lv_data_panel_buffer[f_panel_cnt_ui32].name_str).CaptionVisible().MinimizeButton().MaximizeButton().PinButton().Maximize());
            lp_main_wxauimanager->Update();
            // Save sizer
            lv_data_sizer_buffer.push_back(data_sizer_buffer);
        }
        f_panel_cnt_ui32++;
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


