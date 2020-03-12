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
#include "ap_uart_terminal_frame_h.h"

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
bool l_frame_show_bkp_b = false;
// application icon
#include "icon/lp_in_js_gui_ico_xpm.xpm"
//(*IdInit(gui_frame)
const long gui_frame::l_id_update_wxtimer = wxNewId();
const long gui_frame::l_id_js_quit_wxmenu = wxNewId();
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
    Create(parent, wxID_ANY, _("GUI application"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(815,440));
    lp_main_wxauimanager = new wxAuiManager(this, wxAUI_MGR_ALLOW_FLOATING|wxAUI_MGR_DEFAULT);
    lp_update_wxtimer.SetOwner(this, l_id_update_wxtimer);
    lp_update_wxtimer.Start(1, false);
    lp_main_wxmenubar = new wxMenuBar();
    lp_file_wxmenu = new wxMenu();
    lp_js_quit_wxmenu = new wxMenuItem(lp_file_wxmenu, l_id_js_quit_wxmenu, _("Quit\tAlt-F4"), _("Quit JS application"), wxITEM_NORMAL);
    lp_file_wxmenu->Append(lp_js_quit_wxmenu);
    lp_main_wxmenubar->Append(lp_file_wxmenu, _("&File"));
    lp_view_wxmenu = new wxMenu();
    lp_main_wxmenubar->Append(lp_view_wxmenu, _("View"));
    SetMenuBar(lp_main_wxmenubar);

    lp_main_wxauimanager->Connect(wxEVT_AUI_PANE_CLOSE,(wxObjectEventFunction)&gui_frame::on_frame_auimanager_pane_close,0,this);
    Connect(l_id_update_wxtimer,wxEVT_TIMER,(wxObjectEventFunction)&gui_frame::on_update_wxtimer_trigger);
    Connect(l_id_js_quit_wxmenu,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&gui_frame::on_js_quit_wxmenu_selected);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&gui_frame::on_close_event);
    Connect(wxEVT_SIZE,(wxObjectEventFunction)&gui_frame::on_frame_resize);
    //*)
    // Set frame icon
    icon_wximagelist->Add(wxIcon( lp_in_js_gui_ico_si8 ), wxColor(0xff, 0xff, 0xff));
    SetIcon(icon_wximagelist->GetIcon(0));
    delete icon_wximagelist;
    // Buffer initialization
    this->on_clear_panel();
    this->on_clear_sizer();
    this->on_clear_graph();
    this->on_clear_button();
    this->on_clear_slider();
    this->on_clear_static_text();
    this->on_clear_textctrl();
    this->on_clear_check_box();
    this->on_clear_gauge();
    this->on_clear_led();
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
    //(*Destroy(gui_frame)
    //*)
    this->lp_main_wxauimanager->UnInit();
    this->lp_update_wxtimer.Stop();
    // Buffer initialization
    this->on_clear_panel();
    this->on_clear_sizer();
    this->on_clear_graph();
    this->on_clear_button();
    this->on_clear_slider();
    this->on_clear_static_text();
    this->on_clear_textctrl();
    this->on_clear_check_box();
    this->on_clear_gauge();
    this->on_clear_led();
    // Close window
    this->Show(false);
    l_frmae_show_b = false;
    l_frame_show_bkp_b = false;
    return;
}

/** @brief Get AUI manager
 *
 * @param void
 * @return wxAuiManager : AUI object pointer
 *
 */

wxAuiManager* gui_frame::get_aui_manager (void)
{
    return this->lp_main_wxauimanager;
}

/** @brief Show frame
 *
 * @param [IN] status_b : Show status
 * @param [IN] name_str : Frame label text
 * @return void
 *
 */

void gui_frame::frame_show (bool status_b, wxString name_str)
{
    l_frmae_show_b = status_b;
    l_frame_show_bkp_b = !status_b;
    this->SetLabel(name_str);
    return;
}

/** @brief Close plug-in window
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void gui_frame::on_frame_auimanager_pane_close(wxAuiManagerEvent& event)
{
    event.GetPane()->Show(false);
    this->set_panel_view();
    return;
}

/** @brief Resize window
 *
 * @param [IN] event : Event parameter
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
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void gui_frame::on_close_event(wxCloseEvent& event)
{
    // Call event stop
    if (this->GetParent()->IsShown())
    {
        reinterpret_cast<main_frame*>(this->GetParent()->GetClientData())->stop_event();
    }
    else
    {
        this->GetParent()->Close();
    }
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
    // Frame show
    if (l_frmae_show_b != l_frame_show_bkp_b)
    {
        this->Show(l_frmae_show_b);
        l_frame_show_bkp_b = l_frmae_show_b;
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
    // Add gauge
    this->on_update_gauge();
    // Add led
    this->on_update_led();
    return;
}

/** @brief Menu quit event
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void gui_frame::on_js_quit_wxmenu_selected(wxCommandEvent& event)
{
    // Call event stop
    if (this->GetParent()->IsShown())
    {
        reinterpret_cast<main_frame*>(this->GetParent()->GetClientData())->stop_event();
    }
    else
    {
        this->GetParent()->Close();
    }
    return;
}

/**
* @}
*/

/**
* @}
*/

/*****************************************************END OF FILE************/




