/**
  ****************************************************************************
  * @file    in_js_gui_sizer_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    10.09.2018
  * @brief   GUI window sizer component
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
  * @addtogroup Sizer
  * @brief GUI sizer component
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

vector<sizer_buffer_t> lv_data_sizer_buffer;

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Add sizer
 *
 * @param sizer_index_d : Parent sizer index
 * @param proportion_d : Relative proportion item in sizer
 * @param horizontal_b : Sizer orientation
 * @return uint32_t : New sizer buffer index
 *
 */

uint32_t gui_frame::add_sizer (double sizer_index_d, double proportion_d, bool horizontal_b)
{
sizer_buffer_t l_data_sizer_buffer;
uint32_t sizer_index_ui32 = lv_data_sizer_buffer.size();

    l_data_sizer_buffer.parent_index_d = sizer_index_d;
    l_data_sizer_buffer.sizer_orientation_b = horizontal_b;
    l_data_sizer_buffer.proportion_d = proportion_d;
    l_data_sizer_buffer.p_data_wxboxsizer = NULL;
    l_data_sizer_buffer.panel_index_d = 0;
    lv_data_sizer_buffer.push_back(l_data_sizer_buffer);
    wxMilliSleep(40);
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

void gui_frame::on_update_sizer(void)
{
static uint32_t f_sizer_cnt_ui32 = 0;

    // Add sizer
    while (f_sizer_cnt_ui32 < lv_data_sizer_buffer.size())
    {
        if (lv_data_sizer_buffer[f_sizer_cnt_ui32].p_data_wxboxsizer == NULL)
        {
            // Create new sizer
            if(lv_data_sizer_buffer[f_sizer_cnt_ui32].sizer_orientation_b)
            {
                lv_data_sizer_buffer[f_sizer_cnt_ui32].p_data_wxboxsizer = new wxBoxSizer(wxHORIZONTAL);
            }
            else
            {
                lv_data_sizer_buffer[f_sizer_cnt_ui32].p_data_wxboxsizer = new wxBoxSizer(wxVERTICAL);
            }
            // Insert sizer in to parent
            if (lv_data_sizer_buffer[f_sizer_cnt_ui32].parent_index_d < lv_data_sizer_buffer.size())
            {
                lv_data_sizer_buffer[lv_data_sizer_buffer[f_sizer_cnt_ui32].parent_index_d].p_data_wxboxsizer->Add(lv_data_sizer_buffer[f_sizer_cnt_ui32].p_data_wxboxsizer, lv_data_sizer_buffer[f_sizer_cnt_ui32].proportion_d, wxEXPAND, 5);
            }
            lv_data_sizer_buffer[f_sizer_cnt_ui32].panel_index_d = lv_data_sizer_buffer[lv_data_sizer_buffer[f_sizer_cnt_ui32].parent_index_d].panel_index_d;
            // Update
            lv_data_sizer_buffer[f_sizer_cnt_ui32].p_data_wxboxsizer->Fit(lv_data_panel_buffer[lv_data_sizer_buffer[f_sizer_cnt_ui32].panel_index_d].p_data_wxpanel);
            lv_data_sizer_buffer[f_sizer_cnt_ui32].p_data_wxboxsizer->SetSizeHints(lv_data_panel_buffer[lv_data_sizer_buffer[f_sizer_cnt_ui32].panel_index_d].p_data_wxpanel);

        }
        f_sizer_cnt_ui32++;
    }
    return;
}

/** @brief panel destructor event (must be called from GUI context)
 *
 * @param void
 * @return void
 *
 */

void gui_frame::on_clear_sizer(void)
{
    lv_data_sizer_buffer.clear();
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


