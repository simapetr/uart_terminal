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
    wxMenuItem* p_view_wxmenu;
    uint32_t view_menu_id_ui32;
    bool show_b;
    bool show_bkp_b;
}panel_buffer_t;

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

static vector<panel_buffer_t> lv_data_panel_buffer;
static uint32_t l_cnt_panel_ui32 = 0;
static bool l_update_menu_b = false;
static bool l_update_show_b = false;

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Add AUI panel
 *
 * @param [IN] panel_name_str : Panel name
 * @param [IN] horizontal_b : Sizer orientation
 * @return uint32_t : new panel buffer index
 *
 */

uint32_t gui_frame::add_panel (wxString panel_name_str, bool horizontal_b)
{
panel_buffer_t l_data_panel_buffer;
uint32_t index_ui32 = lv_data_panel_buffer.size();

    l_data_panel_buffer.name_str = panel_name_str;
    l_data_panel_buffer.sizer_orientation_b = horizontal_b;
    l_data_panel_buffer.p_data_wxpanel = NULL;
    l_data_panel_buffer.p_view_wxmenu = NULL;
    l_data_panel_buffer.sizer_index_d = 0;
    lv_data_panel_buffer.push_back(l_data_panel_buffer);
    while(!lv_data_panel_buffer[index_ui32].p_data_wxpanel){wxMilliSleep(1);}
    wxMilliSleep(1);
    return index_ui32;
}

/** @brief Get panel main sizer
 *
 * @param [IN] panel_index_d : Panel index
 * @return uint32_t : Sizer index
 *
 */

uint32_t gui_frame::get_panel_sizer (double panel_index_d)
{
uint32_t sizer_index_ui32 = 0;
wxBoxSizer* p_data_wxboxsizer;

    if (panel_index_d < lv_data_panel_buffer.size())
    {
        // Add main sizer
        lv_data_panel_buffer[panel_index_d].sizer_index_d = this->add_panel_sizer(panel_index_d, 1, lv_data_panel_buffer[panel_index_d].sizer_orientation_b);
        // Get box sizer
        p_data_wxboxsizer = this->get_sizer(lv_data_panel_buffer[panel_index_d].sizer_index_d);
        lv_data_panel_buffer[panel_index_d].p_data_wxpanel->SetSizer(p_data_wxboxsizer);
        // Update
        p_data_wxboxsizer->Fit(lv_data_panel_buffer[panel_index_d].p_data_wxpanel);
        p_data_wxboxsizer->SetSizeHints(lv_data_panel_buffer[panel_index_d].p_data_wxpanel);
        // Set index
        sizer_index_ui32 = lv_data_panel_buffer[panel_index_d].sizer_index_d;
    }
    return sizer_index_ui32;
}

/** @brief Get sizer
 *
 * @param [IN] index_d : Sizer index
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

/** @brief Get panel show
 *
 * @param [IN] index_d : Panel index
 * @return bool : Show status
 *
 */

bool gui_frame::get_panel_show(double index_d)
{
bool status_b = false;

    if (index_d < lv_data_panel_buffer.size())
    {
        status_b = lv_data_panel_buffer[index_d].show_b;
    }
    return status_b;
}

/** @brief Set panel show
 *
 * @param [IN] index_d : Panel index
 * @param [IN] show_b : Show status
 * @return void
 *
 */

void gui_frame::set_panel_show(double index_d, bool show_b)
{
    if (index_d < lv_data_panel_buffer.size())
    {
        lv_data_panel_buffer[index_d].show_b = show_b;
        l_update_show_b = true;
    }
    return;
}

/** @brief Set view status for all panel
 *
 * @param void
 * @return void
 *
 */

void gui_frame::set_panel_view(void)
{
    l_update_menu_b = true;
    return;
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
wxString text_str;
uint32_t panel_cnt_ui32;

    // Add panel
    while(l_cnt_panel_ui32 < lv_data_panel_buffer.size())
    {
        // Create new panel
        p_buffer_wxpanel = new wxPanel(this, wxNewId(), wxDefaultPosition, wxSize(640,480), wxTAB_TRAVERSAL, lv_data_panel_buffer[l_cnt_panel_ui32].name_str);
        if(p_buffer_wxpanel)
        {
            p_buffer_wxpanel->SetFocus();
            // Add panel in to AUI
            lp_main_wxauimanager->AddPane(p_buffer_wxpanel, wxAuiPaneInfo().Name(lv_data_panel_buffer[l_cnt_panel_ui32].name_str).DefaultPane().Caption(lv_data_panel_buffer[l_cnt_panel_ui32].name_str).CaptionVisible().MinimizeButton().MaximizeButton().PinButton().Maximize());
            lp_main_wxauimanager->Update();
            // Add view menu
            lv_data_panel_buffer[l_cnt_panel_ui32].view_menu_id_ui32 = wxNewId();
            text_str.Printf("Set view panel ");
            text_str += lv_data_panel_buffer[l_cnt_panel_ui32].name_str;
            lv_data_panel_buffer[l_cnt_panel_ui32].p_view_wxmenu = new wxMenuItem(lp_view_wxmenu, lv_data_panel_buffer[l_cnt_panel_ui32].view_menu_id_ui32, lv_data_panel_buffer[l_cnt_panel_ui32].name_str, text_str, wxITEM_CHECK);
            if(lv_data_panel_buffer[l_cnt_panel_ui32].p_view_wxmenu)
            {
                lp_view_wxmenu->Append(lv_data_panel_buffer[l_cnt_panel_ui32].p_view_wxmenu);
                SetMenuBar(lp_main_wxmenubar);
                Connect(lv_data_panel_buffer[l_cnt_panel_ui32].view_menu_id_ui32, wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&gui_frame::on_js_panel_view_wxmenu_selected);
            }
            // Save object
            lv_data_panel_buffer[l_cnt_panel_ui32].p_data_wxpanel = p_buffer_wxpanel;
        }
        l_cnt_panel_ui32++;
    }
    // Update Menu
    if(l_update_menu_b)
    {
        for(panel_cnt_ui32 = 0 ; panel_cnt_ui32 < lv_data_panel_buffer.size() ; panel_cnt_ui32++)
        {
            if(lv_data_panel_buffer[panel_cnt_ui32].p_view_wxmenu && this->lp_main_wxauimanager && (lv_data_panel_buffer[panel_cnt_ui32].name_str != wxEmptyString))
            {
                lv_data_panel_buffer[panel_cnt_ui32].show_b = this->lp_main_wxauimanager->GetPane(lv_data_panel_buffer[panel_cnt_ui32].name_str).IsShown();
                lv_data_panel_buffer[panel_cnt_ui32].show_bkp_b = lv_data_panel_buffer[panel_cnt_ui32].show_b;
                lv_data_panel_buffer[panel_cnt_ui32].p_view_wxmenu->Check(lv_data_panel_buffer[panel_cnt_ui32].show_b);
            }
        }
        l_update_menu_b = false;
    }
    // Update show
    if(l_update_show_b)
    {
        for(panel_cnt_ui32 = 0 ; panel_cnt_ui32 < lv_data_panel_buffer.size() ; panel_cnt_ui32++)
        {
            if(lv_data_panel_buffer[panel_cnt_ui32].show_b != lv_data_panel_buffer[panel_cnt_ui32].show_bkp_b)
            {
                this->lp_main_wxauimanager->GetPane(lv_data_panel_buffer[panel_cnt_ui32].name_str).Show(lv_data_panel_buffer[panel_cnt_ui32].show_b);
                lv_data_panel_buffer[panel_cnt_ui32].p_view_wxmenu->Check(lv_data_panel_buffer[panel_cnt_ui32].show_b);
                this->lp_main_wxauimanager->Update();
                lv_data_panel_buffer[panel_cnt_ui32].show_bkp_b = lv_data_panel_buffer[panel_cnt_ui32].show_b;
            }
        }
        l_update_show_b = false;
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

/** @brief AUI pane view control
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void gui_frame::on_js_panel_view_wxmenu_selected(wxCommandEvent& event)
{
uint32_t panel_cnt_ui32;

    for(panel_cnt_ui32 = 0 ; panel_cnt_ui32 < lv_data_panel_buffer.size() ; panel_cnt_ui32++)
    {
        if(event.GetId() == (int)lv_data_panel_buffer[panel_cnt_ui32].view_menu_id_ui32)
        {
            this->lp_main_wxauimanager->GetPane(lv_data_panel_buffer[panel_cnt_ui32].name_str).Show(event.GetSelection());
            this->lp_main_wxauimanager->Update();
        }
    }
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


