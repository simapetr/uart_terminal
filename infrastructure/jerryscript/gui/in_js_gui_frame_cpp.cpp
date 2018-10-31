/**
  ****************************************************************************
  * @file    in_js_gui_frame_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    17.07.2018
  * @brief   GUI window component creator
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

//(*InternalHeaders(graph_frame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

/**
  * @defgroup Application
  * @brief Application layer
  * @{
  */

/**
  * @defgroup GUI
  * @brief GUI window
  * @{
  */

/**
  ****************************************************************************
  * Define
  ****************************************************************************
  */



/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

bool l_frmae_show_b = false;
// application icon
#include "icon/lp_signal_value_xpm.xpm"
//(*IdInit(gui_frame)
const long gui_frame::l_id_update_wxtimer = wxNewId();
//*)
#include <wx/imaglist.h>

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

BEGIN_EVENT_TABLE(gui_frame,wxFrame)
    //(*EventTable(gui_frame)
    //*)
END_EVENT_TABLE()

/** @brief Constructor
 *
 * @param [IN] parent : Pointer on window generated by OS for application
 * @param [IN] id : Window identification
 * @return void
 *
 */

gui_frame::gui_frame(wxWindow* parent, void* p_jerryscript_void)
{
wxImageList *icon_wximagelist = new wxImageList(16, 16, true, 1);

    // Save parent pointer
    this->lp_jerryscript_void = p_jerryscript_void;
    //(*Initialize(gui_frame)
    Create(parent, wxID_ANY, _("Graph"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(815,440));
    lp_main_wxauimanager = new wxAuiManager(this, wxAUI_MGR_ALLOW_FLOATING|wxAUI_MGR_DEFAULT);
    lp_update_wxtimer.SetOwner(this, l_id_update_wxtimer);
    lp_update_wxtimer.Start(2, false);

    lp_main_wxauimanager->Connect(wxEVT_AUI_PANE_CLOSE,(wxObjectEventFunction)&gui_frame::on_frame_auimanager_pane_close,0,this);
    Connect(l_id_update_wxtimer,wxEVT_TIMER,(wxObjectEventFunction)&gui_frame::on_update_wxtimer_trigger);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&gui_frame::on_close_event);
    Connect(wxEVT_SIZE,(wxObjectEventFunction)&gui_frame::on_frame_resize);
    //*)
    // Set frame icon
    icon_wximagelist->Add(wxIcon( lp_signal_value_si8 ), wxColor(0xff, 0xff, 0xff));
    SetIcon(icon_wximagelist->GetIcon(0));
    delete icon_wximagelist;
    // Buffer initialization
    this->on_clear_panel();
    this->on_clear_sizer();
    this->on_clear_graph();
    this->on_clear_button();
    this->on_clear_slider();
    this->on_clear_static_text();
    return;
}

/** @brief Destructor
 *
 * @param void
 * @return void
 *
 */

gui_frame::~gui_frame()
{
//uint32_t item_cnt_ui32 = 0;
    //(*Destroy(gui_frame)
    //*)
    //this->lp_update_wxtimer.Stop();
    //wxMilliSleep(20);
    /*while (item_cnt_ui32 < lv_data_panel_buffer.size())
    {
        delete lv_data_panel_buffer[item_cnt_ui32].p_data_wxpanel;
        item_cnt_ui32++;
    }*/
    //lv_data_panel_buffer.clear();
    /*item_cnt_ui32 = 0;
    while (item_cnt_ui32 < lv_data_graph_buffer.size())
    {
        delete lv_data_graph_buffer[item_cnt_ui32].p_graph_data_plot;
        item_cnt_ui32++;
    }*/
    //lv_data_graph_buffer.clear();
    //delete lp_main_wxauimanager;
    //this->GetParent()->Close();
    return;
}

/** @brief Show frame
 *
 * @param [IN] status_b : Show status
 * @return void
 *
 */

void gui_frame::frame_show (bool status_b)
{
    l_frmae_show_b = status_b;
    return;
}

/** @brief Close plug-in window
 *
 * @param  event : Event parameter
 * @return void
 *
 */

void gui_frame::on_frame_auimanager_pane_close(wxAuiManagerEvent& event)
{
    event.GetPane()->Show(false);
    return;
}

/** @brief Resize window
 *
 * @param  event : Event parameter
 * @return void
 *
 */

void gui_frame::on_frame_resize(wxSizeEvent& event)
{
    this->lp_main_wxauimanager->Update();
    return;
}

/** @brief Close window
 *
 * @param  event : Event parameter
 * @return void
 *
 */

void gui_frame::on_close_event(wxCloseEvent& event)
{
    // Call application close
    this->GetParent()->Close();
    return;
}

/** @brief Graph windows constructor (must be called from GUI context)
 *
 * @param [IN] event : wxTimer event data
 * @return void
 *
 */

void gui_frame::on_update_wxtimer_trigger(wxTimerEvent& event)
{
static bool f_frame_show_bkp_b = false;

    // Frame show
    if (l_frmae_show_b != f_frame_show_bkp_b)
    {
        this->Show(l_frmae_show_b);
        f_frame_show_bkp_b = l_frmae_show_b;
    }
    // Add panel
    this->on_update_panel();
    // Add sizer
    this->on_update_sizer();
    // Add graph
    this->on_update_graph();
    // Add button
    this->on_update_button();
    // Add slider
    this->on_update_slider();
    // Add static text
    this->on_update_static_text();
    // Add text control
    this->on_update_textctrl();
    // Add check box
    this->on_update_check_box();
    return;
}

/**
* @}
*/

/**
* @}
*/

/*****************************************************END OF FILE************/


