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

typedef struct
{
    bool sizer_orientation_b;
    double parent_index_d;
    double panel_index_d;
    double proportion_d;
    bool panel_sizer_b;
    wxBoxSizer* p_data_wxboxsizer;
}sizer_buffer_t;

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

vector<sizer_buffer_t> lv_data_sizer_buffer;
uint32_t l_cnt_sizer_ui32 = 0;

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
uint32_t index_ui32 = lv_data_sizer_buffer.size();

    l_data_sizer_buffer.parent_index_d = sizer_index_d;
    l_data_sizer_buffer.sizer_orientation_b = horizontal_b;
    l_data_sizer_buffer.proportion_d = proportion_d;
    l_data_sizer_buffer.p_data_wxboxsizer = NULL;
    l_data_sizer_buffer.panel_index_d = 0;
    l_data_sizer_buffer.panel_sizer_b = false;
    lv_data_sizer_buffer.push_back(l_data_sizer_buffer);
    while(!lv_data_sizer_buffer[index_ui32].p_data_wxboxsizer){wxMilliSleep(1);}
    return index_ui32;
}

/** @brief Add sizer
 *
 * @param panel_index_d : Panel index
 * @param proportion_d : Relative proportion item in sizer
 * @param horizontal_b : Sizer orientation
 * @return uint32_t : New sizer buffer index
 *
 */

uint32_t gui_frame::add_panel_sizer (double panel_index_d, double proportion_d, bool horizontal_b)
{
sizer_buffer_t l_data_sizer_buffer;
uint32_t index_ui32 = lv_data_sizer_buffer.size();

    l_data_sizer_buffer.parent_index_d = index_ui32;
    l_data_sizer_buffer.sizer_orientation_b = horizontal_b;
    l_data_sizer_buffer.proportion_d = proportion_d;
    l_data_sizer_buffer.p_data_wxboxsizer = NULL;
    l_data_sizer_buffer.panel_index_d = panel_index_d;
    l_data_sizer_buffer.panel_sizer_b = true;
    lv_data_sizer_buffer.push_back(l_data_sizer_buffer);
    while(!lv_data_sizer_buffer[index_ui32].p_data_wxboxsizer){wxMilliSleep(1);}
    return index_ui32;
}

/** @brief Get sizer
 *
 * @param index_d : Sizer index
 * @return wxBoxSizer* : Box sizer object pointer
 *
 */

wxBoxSizer* gui_frame::get_sizer (double index_d)
{
wxBoxSizer* data_wxboxbizer = NULL;
    if (index_d < lv_data_sizer_buffer.size())
    {
        data_wxboxbizer = lv_data_sizer_buffer[index_d].p_data_wxboxsizer;
    }
    return data_wxboxbizer;
}

/** @brief Get sizer panel
 *
 * @param index_d : Sizer index
 * @return wxBoxSizer* : Box sizer object pointer
 *
 */

wxPanel* gui_frame::get_sizer_panel (double index_d)
{
wxPanel* data_wxpanel = NULL;
    if (index_d < lv_data_sizer_buffer.size())
    {
        data_wxpanel = this->get_panel(lv_data_sizer_buffer[index_d].panel_index_d);
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

void gui_frame::on_update_sizer(void)
{
wxBoxSizer* p_buffer_wxboxsizer = NULL;

    // Add sizer
    while (l_cnt_sizer_ui32 < lv_data_sizer_buffer.size())
    {
        // Create new sizer
        if(lv_data_sizer_buffer[l_cnt_sizer_ui32].sizer_orientation_b)
        {
            p_buffer_wxboxsizer = new wxBoxSizer(wxHORIZONTAL);
        }
        else
        {
            p_buffer_wxboxsizer = new wxBoxSizer(wxVERTICAL);
        }
        if (p_buffer_wxboxsizer)
        {
            // Insert sizer in to parent
            if (lv_data_sizer_buffer[l_cnt_sizer_ui32].parent_index_d < lv_data_sizer_buffer.size())
            {
                if (!lv_data_sizer_buffer[l_cnt_sizer_ui32].panel_sizer_b)
                {
                    lv_data_sizer_buffer[lv_data_sizer_buffer[l_cnt_sizer_ui32].parent_index_d].p_data_wxboxsizer->Add(p_buffer_wxboxsizer, lv_data_sizer_buffer[l_cnt_sizer_ui32].proportion_d, wxEXPAND, 5);
                    lv_data_sizer_buffer[l_cnt_sizer_ui32].panel_index_d = lv_data_sizer_buffer[lv_data_sizer_buffer[l_cnt_sizer_ui32].parent_index_d].panel_index_d;
                }
            }
            // Update
            p_buffer_wxboxsizer->Fit(this->get_panel(lv_data_sizer_buffer[l_cnt_sizer_ui32].panel_index_d));
            p_buffer_wxboxsizer->SetSizeHints(this->get_panel(lv_data_sizer_buffer[l_cnt_sizer_ui32].panel_index_d));
            // Save object
            lv_data_sizer_buffer[l_cnt_sizer_ui32].p_data_wxboxsizer = p_buffer_wxboxsizer;
        }
        l_cnt_sizer_ui32++;
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
    l_cnt_sizer_ui32 = 0;
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


