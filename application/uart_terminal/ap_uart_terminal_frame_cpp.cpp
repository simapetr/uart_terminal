/**
  ****************************************************************************
  * @file    ap_uart_terminal_frame_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.5
  * @date    04.03.2014
  * @brief   Application window component creator
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

#include "ap_uart_terminal_frame_h.h"
#include <wx/msgdlg.h>
#include <wx/file.h>

//(*InternalHeaders(main_frame)
#include <wx/bitmap.h>
#include <wx/font.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include <wx/imaglist.h>
#include <wx/filename.h>

/**
  * @defgroup Application
  * @brief Application layer
  * @{
  */

/**
  * @defgroup UART_terminal
  * @brief UART terminal monitor
  * @{
  */

/**
  ****************************************************************************
  * Define
  ****************************************************************************
  */

#define d_ap_uart_terminal_tx_buffer_length 4096
#define d_ap_uart_terminal_status_port 0
#define d_ap_uart_terminal_status_script 1
#define d_ap_uart_terminal_info_script 2

/**
  ****************************************************************************
  * Struct
  ****************************************************************************
  */

typedef struct
{
    wxString text_str;
}console_buffer_t;

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

// GUI frame create flag
static bool l_frame_hide_b = false;
static bool l_frame_enable_b = false;
static bool l_frame_show_status_b = false;
static bool l_frame_gui_close_b = false;
static bool l_frame_status_b = false;
static bool l_frame_clear_b = false;
static bool l_frame_open_b = false;
static bool l_frame_close_b = false;
static bool l_frame_set_b = false;
static bool l_frame_rx_b = false;
// GUI sync state
static bool l_frame_hide_state_b = false;
static wxString l_frame_status_str;
static uart_cfg_t l_frame_data_uart_cfg;
static vector<console_buffer_t> lv_frame_main_console_buffer;
static uart_status_t l_frame_uart_status;
// application icon
#include "lp_uart_terminal_xpm.xpm"
#include "lp_editor_xpm.xpm"
#include "lp_open_xpm.xpm"
#include "lp_quit_xpm.xpm"
#include "lp_info_xpm.xpm"
#include "lp_js_xpm.xpm"
#include "lp_bin_xpm.xpm"
#include "lp_play_xpm.xpm"
#include "lp_stop_xpm.xpm"
#include "lp_connect_xpm.xpm"
#include "lp_disconnect_xpm.xpm"
//(*IdInit(main_frame)
const long main_frame::l_id_port_wxstatictext = wxNewId();
const long main_frame::l_id_port_wxchoice = wxNewId();
const long main_frame::l_id_speed_wxchoice = wxNewId();
const long main_frame::l_id_speed_wxtextctrl = wxNewId();
const long main_frame::l_id_length_wxchoice = wxNewId();
const long main_frame::l_id_parity_wxchoice = wxNewId();
const long main_frame::l_id_stop_bit_wxchoice = wxNewId();
const long main_frame::l_id_connect_wxtogglebutton = wxNewId();
const long main_frame::l_id_text_cr_wxcheckbox = wxNewId();
const long main_frame::l_id_text_lf_wxcheckbox = wxNewId();
const long main_frame::l_id_clear_wxbutton = wxNewId();
const long main_frame::l_id_port_control_dtr_wxcheckbox = wxNewId();
const long main_frame::l_id_port_control_rts_wxcheckbox = wxNewId();
const long main_frame::l_id_port_control_tx_wxcheckbox = wxNewId();
const long main_frame::l_id_port_state_cts_wxled = wxNewId();
const long main_frame::l_id_port_state_cts_wxstatictext = wxNewId();
const long main_frame::l_id_port_state_dsr_wxled = wxNewId();
const long main_frame::l_id_port_state_dsr_wxstatictext = wxNewId();
const long main_frame::l_id_port_state_ring_wxled = wxNewId();
const long main_frame::l_id_port_state_ring_wxstatictext = wxNewId();
const long main_frame::l_id_port_state_rlsd_wxled = wxNewId();
const long main_frame::l_id_port_state_rlsd_wxstatictext = wxNewId();
const long main_frame::l_id_script_path_wxtextctrl = wxNewId();
const long main_frame::l_id_editor_wxbutton = wxNewId();
const long main_frame::l_id_script_run_wxtogglebutton = wxNewId();
const long main_frame::l_id_command_wxtextctrl = wxNewId();
const long main_frame::l_id_hex_wxcheckbox = wxNewId();
const long main_frame::l_id_send_wxbutton = wxNewId();
const long main_frame::l_id_console_wxtextctrl = wxNewId();
const long main_frame::l_id_main_wxpanel = wxNewId();
const long main_frame::l_id_file_open_item_wxmenu = wxNewId();
const long main_frame::l_id_file_edit_item_wxmenu = wxNewId();
const long main_frame::l_id_file_quit_item_wxmenu = wxNewId();
const long main_frame::l_id_help_about_item_wxmenu = wxNewId();
const long main_frame::l_id_help_js_doc_item_wxmenu = wxNewId();
const long main_frame::l_id_bot_wxstatusbar = wxNewId();
const long main_frame::l_id_dialog_caller_wxtimer = wxNewId();
const long main_frame::l_id_wx_gui_sync_wxtimer = wxNewId();
//*)

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

BEGIN_EVENT_TABLE(main_frame,wxFrame)
    //(*EventTable(main_frame)
    //*)
END_EVENT_TABLE()

/** @brief Constructor
 *
 * @param [IN] parent : Pointer on window generated by OS for application
 * @param [IN] id : Window identification
 * @return void
 *
 */

main_frame::main_frame(wxWindow* parent, wxArrayString* p_cmd_arg_arraystring)
{
wxString cfg_path_str = wxEmptyString;
uint32_t data_bkp_ui32;
wxString text_str;
int32_t select_i32;

    // Save CMD parameter
    this->lp_cmd_arg_arraystring = p_cmd_arg_arraystring;
    // Set debug flag
    if (wxNOT_FOUND != this->lp_cmd_arg_arraystring->Index(wxT("-g")))
    {
        //this->l_script_debug_b = true;
        AllocConsole();
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
        printf("UART Terminal DBG :\n");
    }
    else
    {
        this->l_script_debug_b = false;
    }
    //(*Initialize(main_frame)
    Create(parent, wxID_ANY, _("uart terminal"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(815,440));
    lp_main_wxpanel = new wxPanel(this, l_id_main_wxpanel, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("l_id_main_wxpanel"));
    lp_main_wxboxsizer = new wxBoxSizer(wxVERTICAL);
    lp_main_setting_wxboxsizer = new wxBoxSizer(wxHORIZONTAL);
    lp_port_wxstatictext = new wxStaticText(lp_main_wxpanel, l_id_port_wxstatictext, _("Com"), wxDefaultPosition, wxDefaultSize, 0, _T("l_id_port_wxstatictext"));
    lp_main_setting_wxboxsizer->Add(lp_port_wxstatictext, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_port_wxchoice = new wxChoice(lp_main_wxpanel, l_id_port_wxchoice, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("l_id_port_wxchoice"));
    lp_port_wxchoice->SetToolTip(_("Commuication port"));
    lp_main_setting_wxboxsizer->Add(lp_port_wxchoice, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_speed_wxchoice = new wxChoice(lp_main_wxpanel, l_id_speed_wxchoice, wxDefaultPosition, wxSize(61,21), 0, 0, 0, wxDefaultValidator, _T("l_id_speed_wxchoice"));
    lp_speed_wxchoice->Append(_("Custom"));
    lp_speed_wxchoice->Append(_("110"));
    lp_speed_wxchoice->Append(_("300"));
    lp_speed_wxchoice->Append(_("1200"));
    lp_speed_wxchoice->Append(_("2400"));
    lp_speed_wxchoice->Append(_("4800"));
    lp_speed_wxchoice->Append(_("9600"));
    lp_speed_wxchoice->Append(_("14400"));
    lp_speed_wxchoice->SetSelection( lp_speed_wxchoice->Append(_("19200")) );
    lp_speed_wxchoice->Append(_("38400"));
    lp_speed_wxchoice->Append(_("57600"));
    lp_speed_wxchoice->Append(_("115200"));
    lp_speed_wxchoice->Append(_("128000"));
    lp_speed_wxchoice->Append(_("256000"));
    lp_speed_wxchoice->SetToolTip(_("Communication speed"));
    lp_main_setting_wxboxsizer->Add(lp_speed_wxchoice, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_speed_wxtextctrl = new wxTextCtrl(lp_main_wxpanel, l_id_speed_wxtextctrl, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("l_id_speed_wxtextctrl"));
    lp_speed_wxtextctrl->SetToolTip(_("User communication speed"));
    lp_main_setting_wxboxsizer->Add(lp_speed_wxtextctrl, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_length_wxchoice = new wxChoice(lp_main_wxpanel, l_id_length_wxchoice, wxDefaultPosition, wxSize(31,21), 0, 0, 0, wxDefaultValidator, _T("l_id_length_wxchoice"));
    lp_length_wxchoice->Append(_("5"));
    lp_length_wxchoice->Append(_("6"));
    lp_length_wxchoice->Append(_("7"));
    lp_length_wxchoice->SetSelection( lp_length_wxchoice->Append(_("8")) );
    lp_length_wxchoice->Append(_("9"));
    lp_length_wxchoice->SetToolTip(_("Bit length"));
    lp_main_setting_wxboxsizer->Add(lp_length_wxchoice, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_parity_wxchoice = new wxChoice(lp_main_wxpanel, l_id_parity_wxchoice, wxDefaultPosition, wxSize(61,21), 0, 0, 0, wxDefaultValidator, _T("l_id_parity_wxchoice"));
    lp_parity_wxchoice->SetSelection( lp_parity_wxchoice->Append(_("0 none")) );
    lp_parity_wxchoice->Append(_("1 odd"));
    lp_parity_wxchoice->Append(_("2 even"));
    lp_parity_wxchoice->Append(_("3 char"));
    lp_parity_wxchoice->Append(_("4 space"));
    lp_parity_wxchoice->SetToolTip(_("Parity"));
    lp_main_setting_wxboxsizer->Add(lp_parity_wxchoice, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_stop_bit_wxchoice = new wxChoice(lp_main_wxpanel, l_id_stop_bit_wxchoice, wxDefaultPosition, wxSize(31,21), 0, 0, 0, wxDefaultValidator, _T("l_id_stop_bit_wxchoice"));
    lp_stop_bit_wxchoice->SetSelection( lp_stop_bit_wxchoice->Append(_("0")) );
    lp_stop_bit_wxchoice->Append(_("1"));
    lp_stop_bit_wxchoice->Append(_("2"));
    lp_stop_bit_wxchoice->SetToolTip(_("Stop bits 0 - 1, 1 - 1.5, 2 - 2"));
    lp_main_setting_wxboxsizer->Add(lp_stop_bit_wxchoice, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_connect_wxtogglebutton = new wxToggleButton(lp_main_wxpanel, l_id_connect_wxtogglebutton, wxEmptyString, wxDefaultPosition, wxSize(23,23), wxBORDER_NONE, wxDefaultValidator, _T("l_id_connect_wxtogglebutton"));
    lp_main_setting_wxboxsizer->Add(lp_connect_wxtogglebutton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_main_wxboxsizer->Add(lp_main_setting_wxboxsizer, 0, wxEXPAND, 5);
    lp_main_control_wxboxsizer = new wxBoxSizer(wxHORIZONTAL);
    lp_text_control_wxstaticboxsizer = new wxStaticBoxSizer(wxHORIZONTAL, lp_main_wxpanel, _("Text mode"));
    lp_text_cr_wxcheckbox = new wxCheckBox(lp_main_wxpanel, l_id_text_cr_wxcheckbox, _("CR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("l_id_text_cr_wxcheckbox"));
    lp_text_cr_wxcheckbox->SetValue(false);
    lp_text_cr_wxcheckbox->SetToolTip(_("Add CR (0x0D) on the end of string"));
    lp_text_control_wxstaticboxsizer->Add(lp_text_cr_wxcheckbox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_text_lf_wxcheckbox = new wxCheckBox(lp_main_wxpanel, l_id_text_lf_wxcheckbox, _("LF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("l_id_text_lf_wxcheckbox"));
    lp_text_lf_wxcheckbox->SetValue(false);
    lp_text_lf_wxcheckbox->SetToolTip(_("Add LF (0x0A) on the end of string"));
    lp_text_control_wxstaticboxsizer->Add(lp_text_lf_wxcheckbox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_clear_wxbutton = new wxButton(lp_main_wxpanel, l_id_clear_wxbutton, wxEmptyString, wxDefaultPosition, wxSize(23,23), wxBORDER_NONE, wxDefaultValidator, _T("l_id_clear_wxbutton"));
    lp_text_control_wxstaticboxsizer->Add(lp_clear_wxbutton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_main_control_wxboxsizer->Add(lp_text_control_wxstaticboxsizer, 0, wxALL|wxEXPAND, 5);
    lp_port_control_wxstaticboxsizer = new wxStaticBoxSizer(wxHORIZONTAL, lp_main_wxpanel, _("Port control"));
    lp_port_control_dtr_wxcheckbox = new wxCheckBox(lp_main_wxpanel, l_id_port_control_dtr_wxcheckbox, _("DTR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("l_id_port_control_dtr_wxcheckbox"));
    lp_port_control_dtr_wxcheckbox->SetValue(false);
    lp_port_control_dtr_wxcheckbox->Disable();
    lp_port_control_wxstaticboxsizer->Add(lp_port_control_dtr_wxcheckbox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_port_control_rts_wxcheckbox = new wxCheckBox(lp_main_wxpanel, l_id_port_control_rts_wxcheckbox, _("RTS"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("l_id_port_control_rts_wxcheckbox"));
    lp_port_control_rts_wxcheckbox->SetValue(true);
    lp_port_control_rts_wxcheckbox->Disable();
    lp_port_control_wxstaticboxsizer->Add(lp_port_control_rts_wxcheckbox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_port_control_tx_wxcheckbox = new wxCheckBox(lp_main_wxpanel, l_id_port_control_tx_wxcheckbox, _("Tx"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("l_id_port_control_tx_wxcheckbox"));
    lp_port_control_tx_wxcheckbox->SetValue(true);
    lp_port_control_tx_wxcheckbox->Disable();
    lp_port_control_wxstaticboxsizer->Add(lp_port_control_tx_wxcheckbox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_main_control_wxboxsizer->Add(lp_port_control_wxstaticboxsizer, 0, wxALL|wxEXPAND, 5);
    lp_port_state_wxstaticboxsizer = new wxStaticBoxSizer(wxHORIZONTAL, lp_main_wxpanel, _("Port state"));
    lp_port_state_cts_wxled = new wxLed(lp_main_wxpanel,l_id_port_state_cts_wxled,wxColour(128,128,128),wxColour(0,255,0),wxColour(255,0,0),wxDefaultPosition,wxDefaultSize);
    lp_port_state_cts_wxled->Disable();
    lp_port_state_cts_wxled->SwitchOn();
    lp_port_state_wxstaticboxsizer->Add(lp_port_state_cts_wxled, 0, wxALL|wxSHAPED|wxFIXED_MINSIZE, 5);
    lp_port_state_cts_wxstatictext = new wxStaticText(lp_main_wxpanel, l_id_port_state_cts_wxstatictext, _("CTS"), wxDefaultPosition, wxDefaultSize, 0, _T("l_id_port_state_cts_wxstatictext"));
    lp_port_state_wxstaticboxsizer->Add(lp_port_state_cts_wxstatictext, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_port_state_dsr_wxled = new wxLed(lp_main_wxpanel,l_id_port_state_dsr_wxled,wxColour(128,128,128),wxColour(0,255,0),wxColour(255,0,0),wxDefaultPosition,wxDefaultSize);
    lp_port_state_dsr_wxled->Disable();
    lp_port_state_dsr_wxled->SwitchOn();
    lp_port_state_wxstaticboxsizer->Add(lp_port_state_dsr_wxled, 0, wxALL|wxSHAPED|wxFIXED_MINSIZE, 5);
    lp_port_state_dsr_wxstatictext = new wxStaticText(lp_main_wxpanel, l_id_port_state_dsr_wxstatictext, _("DSR"), wxDefaultPosition, wxDefaultSize, 0, _T("l_id_port_state_dsr_wxstatictext"));
    lp_port_state_wxstaticboxsizer->Add(lp_port_state_dsr_wxstatictext, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_port_state_ring_wxled = new wxLed(lp_main_wxpanel,l_id_port_state_ring_wxled,wxColour(128,128,128),wxColour(0,255,0),wxColour(255,0,0),wxDefaultPosition,wxDefaultSize);
    lp_port_state_ring_wxled->Disable();
    lp_port_state_ring_wxled->SwitchOn();
    lp_port_state_wxstaticboxsizer->Add(lp_port_state_ring_wxled, 0, wxALL|wxSHAPED|wxFIXED_MINSIZE, 5);
    lp_port_state_ring_wxstatictext = new wxStaticText(lp_main_wxpanel, l_id_port_state_ring_wxstatictext, _("RING"), wxDefaultPosition, wxDefaultSize, 0, _T("l_id_port_state_ring_wxstatictext"));
    lp_port_state_wxstaticboxsizer->Add(lp_port_state_ring_wxstatictext, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_port_state_rlsd_wxled = new wxLed(lp_main_wxpanel,l_id_port_state_rlsd_wxled,wxColour(128,128,128),wxColour(0,255,0),wxColour(255,0,0),wxDefaultPosition,wxDefaultSize);
    lp_port_state_rlsd_wxled->Disable();
    lp_port_state_rlsd_wxled->SwitchOn();
    lp_port_state_wxstaticboxsizer->Add(lp_port_state_rlsd_wxled, 0, wxALL|wxSHAPED|wxFIXED_MINSIZE, 5);
    lp_port_state_rlsd_wxstatictext = new wxStaticText(lp_main_wxpanel, l_id_port_state_rlsd_wxstatictext, _("RLSD"), wxDefaultPosition, wxDefaultSize, 0, _T("l_id_port_state_rlsd_wxstatictext"));
    lp_port_state_wxstaticboxsizer->Add(lp_port_state_rlsd_wxstatictext, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_main_control_wxboxsizer->Add(lp_port_state_wxstaticboxsizer, 0, wxALL|wxEXPAND, 5);
    lp_script_wxstaticboxsizer = new wxStaticBoxSizer(wxHORIZONTAL, lp_main_wxpanel, _("Script"));
    lp_script_path_wxtextctrl = new wxTextCtrl(lp_main_wxpanel, l_id_script_path_wxtextctrl, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, _T("l_id_script_path_wxtextctrl"));
    lp_script_wxstaticboxsizer->Add(lp_script_path_wxtextctrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_editor_wxbutton = new wxButton(lp_main_wxpanel, l_id_editor_wxbutton, wxEmptyString, wxDefaultPosition, wxSize(23,23), wxBORDER_NONE, wxDefaultValidator, _T("l_id_editor_wxbutton"));
    lp_script_wxstaticboxsizer->Add(lp_editor_wxbutton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_script_run_wxtogglebutton = new wxToggleButton(lp_main_wxpanel, l_id_script_run_wxtogglebutton, wxEmptyString, wxDefaultPosition, wxSize(23,23), wxBORDER_NONE, wxDefaultValidator, _T("l_id_script_run_wxtogglebutton"));
    lp_script_wxstaticboxsizer->Add(lp_script_run_wxtogglebutton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_main_control_wxboxsizer->Add(lp_script_wxstaticboxsizer, 1, wxALL|wxEXPAND, 5);
    lp_main_wxboxsizer->Add(lp_main_control_wxboxsizer, 0, wxEXPAND, 5);
    lp_main_command_wxboxsizer = new wxBoxSizer(wxHORIZONTAL);
    lp_command_wxtextctrl = new wxTextCtrl(lp_main_wxpanel, l_id_command_wxtextctrl, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("l_id_command_wxtextctrl"));
    lp_command_wxtextctrl->SetMaxLength(2048);
    wxFont lp_command_wxtextctrlFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    lp_command_wxtextctrl->SetFont(lp_command_wxtextctrlFont);
    lp_main_command_wxboxsizer->Add(lp_command_wxtextctrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_hex_wxcheckbox = new wxCheckBox(lp_main_wxpanel, l_id_hex_wxcheckbox, _("HEX"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("l_id_hex_wxcheckbox"));
    lp_hex_wxcheckbox->SetValue(false);
    lp_hex_wxcheckbox->SetToolTip(_("Hex imput type (0x24 0x35 -> 2435 send 2 byte)"));
    lp_main_command_wxboxsizer->Add(lp_hex_wxcheckbox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_send_wxbutton = new wxButton(lp_main_wxpanel, l_id_send_wxbutton, _("Send"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("l_id_send_wxbutton"));
    lp_send_wxbutton->Disable();
    lp_main_command_wxboxsizer->Add(lp_send_wxbutton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_main_wxboxsizer->Add(lp_main_command_wxboxsizer, 0, wxEXPAND, 5);
    lp_console_wxtextctrl = new wxTextCtrl(lp_main_wxpanel, l_id_console_wxtextctrl, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE, wxDefaultValidator, _T("l_id_console_wxtextctrl"));
    wxFont lp_console_wxtextctrlFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    lp_console_wxtextctrl->SetFont(lp_console_wxtextctrlFont);
    lp_main_wxboxsizer->Add(lp_console_wxtextctrl, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND, 5);
    lp_main_wxpanel->SetSizer(lp_main_wxboxsizer);
    lp_main_wxboxsizer->Fit(lp_main_wxpanel);
    lp_main_wxboxsizer->SetSizeHints(lp_main_wxpanel);
    lp_top_wxmenubar = new wxMenuBar();
    lp_file_wxmenu = new wxMenu();
    l_file_open_item_wxmenu = new wxMenuItem(lp_file_wxmenu, l_id_file_open_item_wxmenu, _("Open\tCtrl-O"), _("Open script"), wxITEM_NORMAL);
    l_file_open_item_wxmenu->SetBitmap(wxIcon(lp_open_si8));
    lp_file_wxmenu->Append(l_file_open_item_wxmenu);
    l_file_edit_item_wxmenu = new wxMenuItem(lp_file_wxmenu, l_id_file_edit_item_wxmenu, _("Editor\tCtrl-E"), _("Run script editor"), wxITEM_NORMAL);
    l_file_edit_item_wxmenu->SetBitmap(wxIcon(lp_editor_si8));
    lp_file_wxmenu->Append(l_file_edit_item_wxmenu);
    lp_file_wxmenu->AppendSeparator();
    lp_file_quit_item_wxmenu = new wxMenuItem(lp_file_wxmenu, l_id_file_quit_item_wxmenu, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    lp_file_quit_item_wxmenu->SetBitmap(wxIcon(lp_quit_si8));
    lp_file_wxmenu->Append(lp_file_quit_item_wxmenu);
    lp_top_wxmenubar->Append(lp_file_wxmenu, _("&File"));
    lp_help_wxmenu = new wxMenu();
    lp_help_about_item_wxmenu = new wxMenuItem(lp_help_wxmenu, l_id_help_about_item_wxmenu, _("About\tF1"), _("Show info about uart terminal application"), wxITEM_NORMAL);
    lp_help_about_item_wxmenu->SetBitmap(wxIcon(lp_info_si8));
    lp_help_wxmenu->Append(lp_help_about_item_wxmenu);
    lp_help_wxmenu->AppendSeparator();
    lp_js_doc_item_wxmenu = new wxMenuItem(lp_help_wxmenu, l_id_help_js_doc_item_wxmenu, _("JS doc"), _("Documentation internal JerryScript class"), wxITEM_NORMAL);
    lp_js_doc_item_wxmenu->SetBitmap(wxIcon(lp_js_si8));
    lp_help_wxmenu->Append(lp_js_doc_item_wxmenu);
    lp_top_wxmenubar->Append(lp_help_wxmenu, _("Help"));
    SetMenuBar(lp_top_wxmenubar);
    lp_bot_wxstatusbar = new wxStatusBar(this, l_id_bot_wxstatusbar, 0, _T("l_id_bot_wxstatusbar"));
    int __wxStatusBarWidths_1[3] = { -1, -1, -8 };
    int __wxStatusBarStyles_1[3] = { wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL };
    lp_bot_wxstatusbar->SetFieldsCount(3,__wxStatusBarWidths_1);
    lp_bot_wxstatusbar->SetStatusStyles(3,__wxStatusBarStyles_1);
    SetStatusBar(lp_bot_wxstatusbar);
    lp_script_wxfiledialog = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE|wxFD_OPEN, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    lp_dialog_caller_wxtimer.SetOwner(this, l_id_dialog_caller_wxtimer);
    lp_dialog_caller_wxtimer.Start(100, false);
    lp_wx_gui_sync_wxtimer.SetOwner(this, l_id_wx_gui_sync_wxtimer);

    Connect(l_id_speed_wxchoice,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&main_frame::on_speed_wxchoice_select);
    Connect(l_id_connect_wxtogglebutton,wxEVT_COMMAND_TOGGLEBUTTON_CLICKED,(wxObjectEventFunction)&main_frame::on_connect_wxtogglebutton_toggle);
    Connect(l_id_clear_wxbutton,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&main_frame::main_panel_clear_button_click);
    Connect(l_id_port_control_dtr_wxcheckbox,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&main_frame::on_port_control_dtr_wxcheckbox_click);
    Connect(l_id_port_control_rts_wxcheckbox,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&main_frame::on_port_control_rts_wxcheckbox_click);
    Connect(l_id_port_control_tx_wxcheckbox,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&main_frame::on_port_control_tx_wxcheckbox_click);
    Connect(l_id_editor_wxbutton,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&main_frame::on_editor_wxbutton_click);
    Connect(l_id_script_run_wxtogglebutton,wxEVT_COMMAND_TOGGLEBUTTON_CLICKED,(wxObjectEventFunction)&main_frame::on_script_run_wxtogglebutton_toggle);
    Connect(l_id_send_wxbutton,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&main_frame::main_panel_send_button_click);
    Connect(l_id_file_open_item_wxmenu,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&main_frame::on_script_load_wxbutton_click);
    Connect(l_id_file_edit_item_wxmenu,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&main_frame::on_editor_wxbutton_click);
    Connect(l_id_file_quit_item_wxmenu,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&main_frame::menu_bar_file_quit_item_selected);
    Connect(l_id_help_about_item_wxmenu,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&main_frame::menu_bar_help_about_item_selected);
    Connect(l_id_help_js_doc_item_wxmenu,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&main_frame::on_js_doc_item_wxmenu_selected);
    Connect(l_id_dialog_caller_wxtimer,wxEVT_TIMER,(wxObjectEventFunction)&main_frame::on_dialog_caller_wxtimer_trigger);
    Connect(l_id_wx_gui_sync_wxtimer,wxEVT_TIMER,(wxObjectEventFunction)&main_frame::on_wx_gui_sync_wxtimer_trigger);
    //*)

    // Create port
    this->lp_communication_uart_port = NULL;
    this->lp_communication_uart_port = new uart_port();
    this->main_panel_set_port_choice();
    this->lp_bot_wxstatusbar->SetStatusText(wxT("Disconnect"), d_ap_uart_terminal_status_port);
    // Create absolute path for configuration file
    if (this->lp_cmd_arg_arraystring->Item(0).GetChar(this->lp_cmd_arg_arraystring->Item(0).Length()) == wxFileName::GetPathSeparator())
    {
        cfg_path_str = this->lp_cmd_arg_arraystring->Item(0).BeforeLast(wxFileName::GetPathSeparator()).BeforeLast(wxFileName::GetPathSeparator());
    }
    else
    {
        cfg_path_str = this->lp_cmd_arg_arraystring->Item(0).BeforeLast(wxFileName::GetPathSeparator());
    }
    cfg_path_str += "\\config.ini";
    // Open configuration file
    this->lp_data_config_ini = NULL;
    this->lp_data_config_ini = new config_ini(cfg_path_str);
    // Check for script path set
    if ((this->lp_cmd_arg_arraystring->GetCount() == 2) && (wxNOT_FOUND != this->lp_cmd_arg_arraystring->Item(1).Find(wxT(".js"))))
    {
        // Run drag&drop script
        this->set(this->lp_cmd_arg_arraystring->Item(1));
    }
    else
    {
        // Read last script path
        this->set(this->lp_data_config_ini->get_string(wxT("CONFIGURATION/script_path"),wxT("")));
    }
    // Create text editor
    this->lp_data_editor_frame = new editor_frame(this);
    // Restore editor window position
    this->lp_data_editor_frame->Move(wxPoint(this->lp_data_config_ini->get_value(wxT("EDITOR/pos_x"), wxT("10")),this->lp_data_config_ini->get_value(wxT("EDITOR/pos_y"), wxT("10"))));
    if (this->lp_data_config_ini->get_value(wxT("EDITOR/siz_exp"), wxT("0")))
    {
        this->lp_data_editor_frame->Maximize();
    }
    else
    {
        this->lp_data_editor_frame->SetClientSize(wxSize(this->lp_data_config_ini->get_value(wxT("EDITOR/siz_w"), wxT("800")), this->lp_data_config_ini->get_value(wxT("EDITOR/siz_h"), wxT("500"))));
    }
    if(this->lp_data_config_ini->get_value(wxT("EDITOR/show"), wxT("0")))
    {
        this->lp_data_editor_frame->Show();
    }
    // Set frame icon
    SetIcon(wxIcon(lp_uart_terminal_si8));
    // Set button icon
    this->lp_editor_wxbutton->SetBitmap(wxIcon(lp_editor_si8));
    this->lp_clear_wxbutton->SetBitmap(wxIcon(lp_bin_si8));
    this->lp_script_run_wxtogglebutton->SetBitmap(wxIcon(lp_play_si8));
    this->lp_script_run_wxtogglebutton->SetBitmapPressed(wxIcon(lp_stop_si8));
    this->lp_connect_wxtogglebutton->SetBitmap(wxIcon(lp_disconnect_si8));
    this->lp_connect_wxtogglebutton->SetBitmapPressed(wxIcon(lp_connect_si8));
    // Load port configuration
    this->lp_port_wxchoice->SetSelection(this->lp_data_config_ini->get_value(wxT("CONFIGURATION/port"),wxT("0")));
    this->lp_length_wxchoice->SetSelection(this->lp_data_config_ini->get_value(wxT("CONFIGURATION/bit_length"),wxT("3")));
    this->lp_parity_wxchoice->SetSelection(this->lp_data_config_ini->get_value(wxT("CONFIGURATION/parity"),wxT("0")));
    this->lp_stop_bit_wxchoice->SetSelection(this->lp_data_config_ini->get_value(wxT("CONFIGURATION/stop_bit"),wxT("0")));
    this->lp_hex_wxcheckbox->SetValue(this->lp_data_config_ini->get_value(wxT("CONFIGURATION/hex_data"),wxT("0")));
    this->lp_text_cr_wxcheckbox->SetValue(this->lp_data_config_ini->get_value(wxT("CONFIGURATION/add_cr"),wxT("0")));
    this->lp_text_lf_wxcheckbox->SetValue(this->lp_data_config_ini->get_value(wxT("CONFIGURATION/add_lf"),wxT("0")));
    this->lp_command_wxtextctrl->WriteText(this->lp_data_config_ini->get_string(wxT("CONFIGURATION/data"),wxT("")));
    select_i32 = this->lp_speed_wxchoice->FindString(this->lp_data_config_ini->get_string(wxT("CONFIGURATION/speed"),wxT("19200")));
    if(wxNOT_FOUND != select_i32)
    {
        this->lp_speed_wxchoice->SetSelection(select_i32);
        this->lp_speed_wxtextctrl->Show(false);
    }
    else
    {
        this->lp_speed_wxchoice->SetSelection(0);
        wxSscanf(this->lp_data_config_ini->get_string(wxT("CONFIGURATION/speed"),wxT("19200")),wxT("%u"),&data_bkp_ui32);
        text_str.Printf("%u",data_bkp_ui32);
        this->lp_speed_wxtextctrl->WriteText(text_str);
        this->lp_speed_wxtextctrl->Show(true);
    }
    // Initialization script interpreter
    this->lp_interpret_jerryscript = NULL;
    // Initialization dialog
    this->l_dialog_end_b = true;
    this->lp_data_wxprogressdialog = NULL;
    this->l_progress_info_str = wxEmptyString;
    this->l_progress_end_b = true;
    l_frame_rx_b = true;
    // Initialization LED
    this->l_cts_b = true;
    this->l_dsr_b = true;
    this->l_ring_b = true;
    this->l_rlsd_b = true;
    this->lp_wx_gui_sync_wxtimer.Start(10, false);
    // Initialization open state
    this->l_open_b = false;
    // Initialization close state
    this->l_run_b = false;
    // Initialize stop request
    l_frame_gui_close_b = false;
    // Initialize event
    this->lp_event_parameter_void = NULL;
    this->l_data_send_event_fct = NULL;
    // Initialize script project
    this->lp_script_config_ini = NULL;
    // Restore window position
    Move(wxPoint(this->lp_data_config_ini->get_value(wxT("POSITION/pos_x"), wxT("10")),this->lp_data_config_ini->get_value(wxT("POSITION/pos_y"), wxT("10"))));
    if (this->lp_data_config_ini->get_value(wxT("POSITION/siz_exp"), wxT("0")))
    {
        Maximize();
    }
    else
    {
        SetClientSize(wxSize(this->lp_data_config_ini->get_value(wxT("POSITION/siz_w"), wxT("800")), this->lp_data_config_ini->get_value(wxT("POSITION/siz_h"), wxT("500"))));
    }
    this->Show();
    // Init state flag
    this->l_script_start_b = false;
    this->l_script_stop_b = false;
    // run script path
    if ((this->lp_cmd_arg_arraystring->GetCount() == 2) && (wxNOT_FOUND != this->lp_cmd_arg_arraystring->Item(1).Find(wxT(".js"))))
    {
        // Run drag&drop script
        this->run();
    }
    return;
}

/** @brief Destructor
 *
 * @param void
 * @return void
 *
 */

main_frame::~main_frame()
{
int pos_x_int = 0;
int pos_y_int = 0;
int siz_w_int = 0;
int siz_h_int = 0;
uint32_t data_bkp_ui32;
wxString text_str;

    //(*Destroy(main_frame)
    //*)
    // Save window position
    this->GetPosition(&pos_x_int, &pos_y_int);
    this->lp_data_config_ini->set_value(wxT("POSITION/pos_x"), pos_x_int);
    this->lp_data_config_ini->set_value(wxT("POSITION/pos_y"), pos_y_int);
    if (IsMaximized())
    {
        this->lp_data_config_ini->set_value(wxT("POSITION/siz_exp"), 1);
    }
    else
    {
        GetClientSize(&siz_w_int, &siz_h_int);
        this->lp_data_config_ini->set_value(wxT("POSITION/siz_w"), siz_w_int);
        this->lp_data_config_ini->set_value(wxT("POSITION/siz_h"), siz_h_int);
        this->lp_data_config_ini->set_value(wxT("POSITION/siz_exp"), 0);
    }
    // Save editor position
    this->lp_data_editor_frame->GetPosition(&pos_x_int, &pos_y_int);
    this->lp_data_config_ini->set_value(wxT("EDITOR/pos_x"), pos_x_int);
    this->lp_data_config_ini->set_value(wxT("EDITOR/pos_y"), pos_y_int);
    if (this->lp_data_editor_frame->IsMaximized())
    {
        this->lp_data_config_ini->set_value(wxT("EDITOR/siz_exp"), 1);
    }
    else
    {
        this->lp_data_editor_frame->GetClientSize(&siz_w_int, &siz_h_int);
        this->lp_data_config_ini->set_value(wxT("EDITOR/siz_w"), siz_w_int);
        this->lp_data_config_ini->set_value(wxT("EDITOR/siz_h"), siz_h_int);
        this->lp_data_config_ini->set_value(wxT("EDITOR/siz_exp"), 0);
    }
    if(this->lp_data_editor_frame->IsShown())
    {
        this->lp_data_config_ini->set_value(wxT("EDITOR/show"), 1);
    }
    else
    {
        this->lp_data_config_ini->set_value(wxT("EDITOR/show"), 0);
    }
    // Close port
    this->close_port();
    // Save configuration
    this->lp_data_config_ini->set_value(wxT("CONFIGURATION/port"),this->lp_port_wxchoice->GetSelection());
    if(this->lp_speed_wxchoice->GetSelection())
    {
        this->lp_data_config_ini->set_string(wxT("CONFIGURATION/speed"),this->lp_speed_wxchoice->GetString(this->lp_speed_wxchoice->GetSelection()));
    }
    else
    {
        wxSscanf(this->lp_speed_wxtextctrl->GetLineText(0),wxT("%u"),&data_bkp_ui32);
        text_str.Printf("%u",data_bkp_ui32);
        this->lp_data_config_ini->set_string(wxT("CONFIGURATION/speed"),text_str);
    }
    this->lp_data_config_ini->set_value(wxT("CONFIGURATION/bit_length"),this->lp_length_wxchoice->GetSelection());
    this->lp_data_config_ini->set_value(wxT("CONFIGURATION/parity"),this->lp_parity_wxchoice->GetSelection());
    this->lp_data_config_ini->set_value(wxT("CONFIGURATION/stop_bit"),this->lp_stop_bit_wxchoice->GetSelection());
    this->lp_data_config_ini->set_value(wxT("CONFIGURATION/hex_data"),this->lp_hex_wxcheckbox->GetValue());
    this->lp_data_config_ini->set_value(wxT("CONFIGURATION/add_cr"),this->lp_text_cr_wxcheckbox->GetValue());
    this->lp_data_config_ini->set_value(wxT("CONFIGURATION/add_lf"),this->lp_text_lf_wxcheckbox->GetValue());
    this->lp_data_config_ini->set_string(wxT("CONFIGURATION/data"),this->lp_command_wxtextctrl->GetLineText(0));
    this->lp_data_config_ini->set_string(wxT("CONFIGURATION/script_path"),this->lp_script_path_wxtextctrl->GetLineText(0));
    // Stop timer
    this->lp_wx_gui_sync_wxtimer.Stop();
    this->lp_dialog_caller_wxtimer.Stop();
    wxMilliSleep(110);
    // Terminate JavaScript
    if(this->lp_interpret_jerryscript)
    {
        this->lp_interpret_jerryscript->stop();
    }
    return;
}

/** @brief Set script path
 *
 * @param [IN] path_str : Script path
 * @return void
 *
 */

void main_frame::set(wxString path_str)
{
    // Clear old path
    this->lp_script_path_wxtextctrl->Clear();
    // Set path
    this->lp_script_path_wxtextctrl->WriteText(path_str);
    return;
}

/** @brief Run Loaded script
 *
 * @param [IN] status_b : Run state
 *   @arg true : Run
 *   @arg false : Stop
 * @return void
 *
 */

void main_frame::run(bool status_b)
{
    if (status_b)
    {
        this->l_script_start_b = true;
        this->lp_script_run_wxtogglebutton->SetValue(true);
        this->lp_data_editor_frame->run(true);
    }
    else
    {
        this->l_script_stop_b = true;
        this->lp_script_run_wxtogglebutton->SetValue(false);
        this->lp_data_editor_frame->run(false);
    }
    return;
}

/** @brief Get script path
 *
 * @param void
 * @return wxString : Script path
 *
 */

wxString main_frame::get(void)
{
    return this->lp_script_path_wxtextctrl->GetLineText(0);
}

/** @brief Set frame show status
 *
 * @param [IN] status_b : Show GUI frame
 * @return void
 *
 */

void main_frame::gui (bool status_b)
{
    l_frame_show_status_b = status_b;
    l_frame_enable_b = true;
    wxMilliSleep(40);
    return;
}

/** @brief Get project configuration object
 *
 * @param [IN] status_b : Show GUI frame
 * @return void
 *
 */

config_ini* main_frame::get_project (void)
{
    return this->lp_script_config_ini;
}

/** @brief Hide main frame from JerryScript
 *
 * @param [IN] status_b : Show main frame
 * @return void
 *
 */

void main_frame::js_hide(bool status_b)
{
    l_frame_hide_state_b = status_b;
    l_frame_hide_b = true;
    while(l_frame_hide_b){wxMilliSleep(1);}
    wxMilliSleep(1);
    return;
}

/** @brief Set RX data show status
 *
 * @param [IN] status_b : Show RX data status
 * @return void
 *
 */

void main_frame::console_rx_enable (bool status_b)
{
    l_frame_rx_b = status_b;
    return;
}

/** @brief Get RX console show status
 *
 * @param void
 * @return bool : Actual console enable status
 *
 */

bool main_frame::is_console_rx_enable (void)
{
    return l_frame_rx_b;
}

/** @brief Print string on console from JerryScript
 *
 * @param [IN] console_text_str : Print text
 * @return void
 *
 */

void main_frame::js_printf(wxString console_text_str)
{
console_buffer_t bfr_console_buffer;

    // Add data in to buffer
    bfr_console_buffer.text_str = console_text_str;
    lv_frame_main_console_buffer.push_back(bfr_console_buffer);
    return;
}

/** @brief Print string on status bar from JerryScript
 *
 * @param [IN] console_text_str : Print text
 * @return void
 *
 */

void main_frame::js_status(wxString status_text_str)
{
    l_frame_status_str = status_text_str;
    l_frame_status_b = true;
    while(l_frame_status_b){wxMilliSleep(1);}
    wxMilliSleep(1);
    return;
}

/** @brief Print string on status bar
 *
 * @param [IN] console_text_str : Print text
 * @return void
 *
 */

void main_frame::status(wxString status_text_str)
{
    this->lp_bot_wxstatusbar->SetStatusText(status_text_str, d_ap_uart_terminal_info_script);
    return;
}

/** @brief Clear console text from JerryScript
 *
 * @param void
 * @return void
 *
 */

void main_frame::js_clear(void)
{
    l_frame_clear_b = true;
    while(l_frame_clear_b){wxMilliSleep(1);}
    wxMilliSleep(1);
    return;
}

/** @brief Clear console text
 *
 * @param void
 * @return void
 *
 */

void main_frame::clear(void)
{
    this->lp_console_wxtextctrl->Clear();
    return;
}

/** @brief Open UART form JerryScript
 *
 * @param void
 * @return void
 *
 */

void main_frame::js_open_port(void)
{
    l_frame_open_b = true;
    while(l_frame_open_b){wxMilliSleep(1);}
    wxMilliSleep(1);
    return;
}

/** @brief Open UART with GUI setting
 *
 * @param void
 * @return void
 *
 */

void main_frame::open_port(void)
{
static wxString text_bfr_str;
uart_cfg_t data_uart_cfg;

    if((this->lp_communication_uart_port != NULL) && (!this->l_open_b))
    {
        // Get port configuration
        data_uart_cfg = this->get_config();
        // Open port
        this->l_data_uart_status = this->lp_communication_uart_port->open(&data_uart_cfg);
        l_frame_uart_status = this->l_data_uart_status;
        if(this->l_data_uart_status == e_07_opened)
        {
        }
        else
        {
            if(this->l_data_uart_status == e_01_open)
            {
                // Create read event
                this->lp_communication_uart_port->set((uart_event_fct)&this->uart_rx_event, this);
                text_bfr_str.Printf(wxT("Connect"));
                this->lp_bot_wxstatusbar->SetStatusText(text_bfr_str, d_ap_uart_terminal_status_port);
                // Disable settings component
                this->lp_port_wxchoice->Disable();
                this->lp_speed_wxchoice->Disable();
                this->lp_speed_wxtextctrl->Disable();
                this->lp_length_wxchoice->Disable();
                this->lp_parity_wxchoice->Disable();
                this->lp_stop_bit_wxchoice->Disable();
                // Enable component
                this->lp_send_wxbutton->Enable();
                this->lp_port_control_dtr_wxcheckbox->Enable();
                this->lp_port_control_rts_wxcheckbox->Enable();
                this->lp_port_control_tx_wxcheckbox->Enable();
                // Set connection button
                this->lp_connect_wxtogglebutton->SetValue(true);
                // Set state LED
                if (this->lp_communication_uart_port->get(e_cts))
                {
                    this->l_cts_b = true;
                }
                else
                {
                    this->l_cts_b = false;
                }
                if (this->lp_communication_uart_port->get(e_dsr))
                {
                    this->l_dsr_b = true;
                }
                else
                {
                    this->l_dsr_b = false;
                }
                if (this->lp_communication_uart_port->get(e_ring))
                {
                    this->l_ring_b = true;
                }
                else
                {
                    this->l_ring_b = false;
                }
                if (this->lp_communication_uart_port->get(e_rlsd))
                {
                    this->l_rlsd_b = true;
                }
                else
                {
                    this->l_rlsd_b = false;
                }
                this->l_open_b = true;
            }
            else
            {
                text_bfr_str.Printf(wxT("uart error %d"),this->lp_communication_uart_port->get_state());
                this->lp_communication_uart_port->close();
                if(this->l_data_uart_status == e_00_open_error)
                {
                    // Check for new COM
                    this->main_panel_set_port_choice();
                }
                this->lp_bot_wxstatusbar->SetStatusText(text_bfr_str, d_ap_uart_terminal_status_port);
            }
        }
    }
    return;
}

/** @brief Close port from JerryScript
 *
 * @param void
 * @return void
 *
 */

void main_frame::js_close_port(void)
{
    l_frame_close_b = true;
    while(l_frame_close_b){wxMilliSleep(1);}
    wxMilliSleep(1);
    return;
}

/** @brief Close port wit GUI setting
 *
 * @param void
 * @return void
 *
 */

void main_frame::close_port(void)
{
    if((this->lp_communication_uart_port != NULL) && (this->l_open_b))
    {
        // Close port
        this->lp_communication_uart_port->close();
        // Enable settings component
        this->lp_port_wxchoice->Enable();
        this->lp_speed_wxchoice->Enable();
        this->lp_speed_wxtextctrl->Enable();
        this->lp_length_wxchoice->Enable();
        this->lp_parity_wxchoice->Enable();
        this->lp_stop_bit_wxchoice->Enable();
        // Disable send
        this->lp_send_wxbutton->Disable();
        this->lp_port_control_dtr_wxcheckbox->Disable();
        this->lp_port_control_rts_wxcheckbox->Disable();
        this->lp_port_control_tx_wxcheckbox->Disable();
        // Set connection button
        this->lp_connect_wxtogglebutton->SetValue(false);
        this->lp_bot_wxstatusbar->SetStatusText(wxT("Disconnect"), d_ap_uart_terminal_status_port);
        this->l_open_b = false;
    }
    return;
}

/** @brief Get port open status from JerryScript
 *
 * @param void
 * @return uart_status_t : UART port status
 *
 */

uart_status_t main_frame::js_get_open_status(void)
{
    return l_frame_uart_status;
}

/** @brief Get port open status
 *
 * @param void
 * @return uart_status_t : UART port status
 *
 */

uart_status_t main_frame::get_open_status(void)
{
    return this->l_data_uart_status;
}

/** @brief Set UART port from JerryScript
 *
 * @param [IN] data_uart_cfg : UART port configuration structure
 * @return void
 *
 */

void main_frame::js_set_config(uart_cfg_t data_uart_cfg)
{
    // Set new configuration
    l_frame_data_uart_cfg = data_uart_cfg;
    l_frame_set_b = true;
    while(l_frame_set_b){wxMilliSleep(1);}
    wxMilliSleep(1);
    return;
}

/** @brief Set UART port settings in GUI
 *
 * @param [IN] data_uart_cfg : UART port configuration structure
 * @return void
 *
 */

void main_frame::set_config(uart_cfg_t data_uart_cfg)
{
wxString text_str;
int32_t select_i32;

    text_str.Printf("%u",data_uart_cfg.port_num_ui8);
    select_i32 = this->lp_port_wxchoice->FindString(text_str);
    if(wxNOT_FOUND != select_i32)
    {
        this->lp_port_wxchoice->SetSelection(select_i32);
    }
    text_str.Printf("%u",data_uart_cfg.baudrate_ui32);
    select_i32 = this->lp_speed_wxchoice->FindString(text_str);
    if(wxNOT_FOUND != select_i32)
    {
        this->lp_speed_wxchoice->SetSelection(select_i32);
        this->lp_speed_wxtextctrl->Show(false);
    }
    else
    {
        this->lp_speed_wxchoice->SetSelection(0);
        this->lp_speed_wxtextctrl->Show(true);
        this->lp_speed_wxtextctrl->Clear();
        this->lp_speed_wxtextctrl->WriteText(text_str);
    }
    text_str.Printf("%u",data_uart_cfg.bit_length_ui8);
    select_i32 = this->lp_length_wxchoice->FindString(text_str);
    if(wxNOT_FOUND != select_i32)
    {
        this->lp_length_wxchoice->SetSelection(select_i32);
    }
    this->lp_parity_wxchoice->SetSelection(data_uart_cfg.parity_ui8);
    this->lp_stop_bit_wxchoice->SetSelection(data_uart_cfg.stop_bits_ui8);
    this->lp_main_setting_wxboxsizer->Layout();
    return;
}

/** @brief Get UART port settings from GUI
 *
 * @param void
 * @return data_uart_cfg : UART port configuration structure
 *
 */

uart_cfg_t main_frame::get_config(void)
{
uart_cfg_t data_uart_cfg;
uint32_t data_bkp_ui32;

    // Get port number
    wxSscanf(lp_port_wxchoice->GetString(lp_port_wxchoice->GetSelection()),wxT("%u"),&data_bkp_ui32);
    data_uart_cfg.port_num_ui8 = data_bkp_ui32;
    // Get speed
    if (lp_speed_wxchoice->GetSelection())
    {
        wxSscanf(lp_speed_wxchoice->GetString(lp_speed_wxchoice->GetSelection()),wxT("%u"),&data_bkp_ui32);
    }
    else
    {
        wxSscanf(this->lp_speed_wxtextctrl->GetLineText(0),wxT("%u"),&data_bkp_ui32);
    }
    data_uart_cfg.baudrate_ui32 = data_bkp_ui32;
    // Get length
    wxSscanf(lp_length_wxchoice->GetString(lp_length_wxchoice->GetSelection()),wxT("%u"),&data_bkp_ui32);
    data_uart_cfg.bit_length_ui8 = data_bkp_ui32;
    // Get parity
    wxSscanf(lp_parity_wxchoice->GetString(lp_parity_wxchoice->GetSelection()),wxT("%u"),&data_bkp_ui32);
    data_uart_cfg.parity_ui8 = data_bkp_ui32;
    // Get stop bit
    wxSscanf(lp_stop_bit_wxchoice->GetString(lp_stop_bit_wxchoice->GetSelection()),wxT("%u"),&data_bkp_ui32);
    data_uart_cfg.stop_bits_ui8 = data_bkp_ui32;
    // Set timeout
    data_uart_cfg.bite_timeout_ui32 = 0;
    return data_uart_cfg;
}

/** @brief Get data from input dialog
 *
 * @param [IN] text_str : Dialog text
 * @return wxString : Input text
 *
 */

wxString main_frame::get_data(wxString text_str)
{
    this->l_dialog_text_str = wxEmptyString;
    this->l_dialog_info_str = text_str;
    this->l_dialog_end_b = false;
    while(!this->l_dialog_end_b)
    {
        wxMilliSleep(100);
    }
    return this->l_dialog_text_str;
}

/** @brief Set progress dialog
 *
 * @param [IN] text_str : Dialog text
 * @param [IN] progress_ui32 : Progress
 * @return void
 *
 */

void main_frame::set_progress(wxString text_str, uint32_t progress_ui32)
{
    if (text_str != wxEmptyString)
    {
        this->l_progress_info_str = text_str;
    }
    this->l_progress_ui32 = progress_ui32;
    this->l_progress_end_b = false;
    return;
}

/** @brief Set external event after send button click
 *
 * @param [IN] data_send_event_fct : Event function pointer
 * @param [IN] p_parametr_void : Event function parameter
 * @return void
 *
 */

void main_frame::set_send_event(send_event_fct data_send_event_fct, void* p_parametr_void)
{
    this->lp_event_parameter_void = p_parametr_void;
    this->l_data_send_event_fct = data_send_event_fct;
    return;
}

/** @brief Run JS script
 *
 * @param [IN] path_str : Script path
 * @return void
 *
 */

uint32_t main_frame::run_script(wxString path_str)
{
uint32_t run_status_ui32 = 0;
static bool f_init_b = false;
static wxString script_file_str;
wxString config_path_str;

    if ((path_str != wxEmptyString) && (!this->l_run_b))
    {
        // Create script interpreter object
        if(this->lp_interpret_jerryscript == NULL)
        {
            // Load JavaScript interpreter
            this->lp_interpret_jerryscript = new jerryscript_c(this->lp_communication_uart_port, (void*)this, this->l_script_debug_b, f_init_b);
            f_init_b = true;
        }
        if(this->lp_interpret_jerryscript)
        {
            wxFile* p_stcipt_wxfile = new wxFile(path_str);
            if(p_stcipt_wxfile->IsOpened())
            {
                p_stcipt_wxfile->ReadAll(&script_file_str);
                if (script_file_str != wxEmptyString)
                {
                    if (this->lp_script_config_ini)
                    {
                        delete this->lp_script_config_ini;
                    }
                    config_path_str = path_str;
                    config_path_str.Replace(".js", ".ini");
                    // Create Script configuration
                    this->lp_script_config_ini = new config_ini(config_path_str);
                    // Run script
                    run_status_ui32 = this->lp_interpret_jerryscript->run(script_file_str);
                    this->l_run_b = true;
                    wxMilliSleep(300);
                    p_stcipt_wxfile->Close();
                }
            }
            delete p_stcipt_wxfile;
        }
    }
    return run_status_ui32;
}

/** @brief Stop JS script
 *
 * @param void
 * @return uint32_t : Stop status
 *
 */

uint32_t main_frame::stop_script(void)
{
uint32_t status_ui32 = 0;

    if(this->l_run_b)
    {
        if(this->lp_interpret_jerryscript)
        {
            status_ui32 = this->lp_interpret_jerryscript->stop();
            // Wait for script complete terminate must wait for call registered exit function
            if(status_ui32)
            {
                // Load JavaScript interpreter
                delete this->lp_interpret_jerryscript;
                this->lp_interpret_jerryscript = NULL;
                this->l_run_b = false;
            }
        }
    }
    return status_ui32;
}

/** @brief Stop JS script event
 *
 * @param void
 * @return void
 *
 */

void main_frame::stop_event(void)
{
    l_frame_gui_close_b = true;
    return;
}

/** @brief Quit item selected event
 *
 * @param [IN] event : standard event input data
 * @return void
 *
 */

void main_frame::menu_bar_file_quit_item_selected(wxCommandEvent& event)
{
    Close();
    return;
}

/** @brief About item selected event
 *
 * @param [IN] event : standard event input data
 * @return void
 *
 */

void main_frame::menu_bar_help_about_item_selected(wxCommandEvent& event)
{
    wxMessageBox( _("UART terminal V2.0 RC4\nBUILD : " __DATE__ "\nPORTTRONIC(c)\nwxWidget 3.0.4\nJerryScript 2.2.0\nMinGW 5.1.0. x64"), _("About"));
    return;
}

/** @brief JerryScript internal class documentation
 *
 * @param [IN] event : standard event input data
 * @return void
 *
 */

void main_frame::on_js_doc_item_wxmenu_selected(wxCommandEvent& event)
{
    // Show help for JerryScript
    ShellExecute( NULL, _T( "open" ), _T( "js_doc.chm" ), NULL, NULL, SW_NORMAL );
    return;
}

/** @brief Clear data from console
 *
 * @param [IN] event : standard event input data
 * @return void
 *
 */

void main_frame::main_panel_clear_button_click(wxCommandEvent& event)
{
    this->clear();
}

/** @brief Set port choice component
 *
 * @param void
 * @return void
 *
 */

void main_frame::main_panel_set_port_choice(void)
{
uint8_t port_cnt_ui8 = 0;
wxString port_text_str = wxEmptyString;
string *available_port_str = NULL;
static uint8_t selected_port_ui8 = 0;

    // Read pointer on com array
    available_port_str = this->lp_communication_uart_port->get_port();
    // Read selected port
    if (selected_port_ui8 != 0)
    {
        wxSscanf(lp_port_wxchoice->GetString(lp_port_wxchoice->GetSelection()),wxT("%u"),&selected_port_ui8);
    }
    // Clear port choice
    this->lp_port_wxchoice->Clear();
    // Append port in to choice
    for (port_cnt_ui8 = 0 ; port_cnt_ui8 < (uint8_t)available_port_str->size() ; port_cnt_ui8++)
    {
        port_text_str.Printf("%u", (uint8_t)available_port_str->at(port_cnt_ui8));
        if((selected_port_ui8 == 0) && (port_cnt_ui8 == 0))
        {
            this->lp_port_wxchoice->SetSelection(this->lp_port_wxchoice->Append(port_text_str));
            selected_port_ui8 = (uint8_t)available_port_str->at(port_cnt_ui8);
        }
        else if((selected_port_ui8 != 0) && (selected_port_ui8 == (uint8_t)available_port_str->at(port_cnt_ui8)))
        {
            this->lp_port_wxchoice->SetSelection(this->lp_port_wxchoice->Append(port_text_str));
            selected_port_ui8 = (uint8_t)available_port_str->at(port_cnt_ui8);
        }
        else
        {
            this->lp_port_wxchoice->Append(port_text_str);
        }
    }
    return;
}

/** @brief Connect/Disconnect UART port
 *
 * @param [IN] event : standard event input data
 * @return void
 *
 */

void main_frame::on_connect_wxtogglebutton_toggle(wxCommandEvent& event)
{
    if (this->lp_connect_wxtogglebutton->GetValue())
    {
        l_frame_open_b = true;
        l_frame_rx_b = true;
    }
    else
    {
        l_frame_close_b = true;
    }
    return;
}

/** @brief Send data on UART port
 *
 * @param [IN] event : standard event input data
 * @return void
 *
 */

void main_frame::main_panel_send_button_click(wxCommandEvent& event)
{
uint16_t data_length_ui16 = 0, data_cnt_ui16 = 0;
uint8_t data_tx_buffer_sui8[d_ap_uart_terminal_tx_buffer_length];
unsigned int data_tx_bkp_ui32 = 0;
wxString data_str;
wxString data_text_str;

    if (this->lp_communication_uart_port != NULL)
    {
        data_str = this->lp_command_wxtextctrl->GetLineText(0);
        data_length_ui16 = data_str.Length();
        if (this->lp_hex_wxcheckbox->GetValue())
        {
            data_length_ui16 /= 2;
            for (data_cnt_ui16 = 0 ; data_cnt_ui16 <= data_length_ui16; data_cnt_ui16++)
            {
                data_text_str = wxEmptyString;
                data_text_str += data_str[2*data_cnt_ui16];
                data_text_str += data_str[2*data_cnt_ui16+1];
                wxSscanf(data_text_str,wxT("%02x"),&data_tx_bkp_ui32);
                data_tx_buffer_sui8[data_cnt_ui16] = (uint8_t)data_tx_bkp_ui32;
            }
        }
        else
        {
            for (data_cnt_ui16 = 0 ; data_cnt_ui16 < data_length_ui16 ; data_cnt_ui16++)
            {
                wxSscanf(data_str[data_cnt_ui16],wxT("%c"),&data_tx_buffer_sui8[data_cnt_ui16]);
            }
            if (this->lp_text_cr_wxcheckbox->GetValue())
            {
                data_length_ui16++;
            }
            if (this->lp_text_cr_wxcheckbox->GetValue())
            {
                data_tx_buffer_sui8[data_cnt_ui16] = 0x0D;
                data_cnt_ui16++;
            }
            if (this->lp_text_lf_wxcheckbox->GetValue())
            {
                data_length_ui16++;
            }
            if (this->lp_text_lf_wxcheckbox->GetValue())
            {
                data_tx_buffer_sui8[data_cnt_ui16] = 0x0A;
                data_cnt_ui16++;
            }
        }
        if (l_frame_rx_b)
        {
            if (this->lp_communication_uart_port->send(&data_tx_buffer_sui8[0], data_length_ui16) != 1)
            {
                this->lp_bot_wxstatusbar->SetStatusText(wxT("data do not transmit"), d_ap_uart_terminal_status_port);
            }

        }
        else
        {
            if (this->l_data_send_event_fct)
            {
                this->l_data_send_event_fct(this->lp_event_parameter_void, &data_tx_buffer_sui8[0], data_length_ui16);
            }
            else
            {
                this->lp_bot_wxstatusbar->SetStatusText(wxT("JS event not registered"), d_ap_uart_terminal_status_port);
            }
        }
    }
    return;
}

/** @brief Load new script
 *
 * @param [IN] event : standard event input data
 * @return void
 *
 */

void main_frame::on_script_load_wxbutton_click(wxCommandEvent& event)
{
    this->lp_script_wxfiledialog->SetWindowStyleFlag(wxFD_OPEN);
    this->lp_script_wxfiledialog->SetMessage(wxT("Open JS script"));
    this->lp_script_wxfiledialog->SetWildcard(wxT("JavaScript (*.js)|*.js"));
    if (this->lp_script_wxfiledialog->ShowModal() == wxID_OK)
    {
        if (this->lp_script_wxfiledialog->GetPath() != wxEmptyString)
        {
            this->set(this->lp_script_wxfiledialog->GetPath());
            this->lp_data_editor_frame->load(this->lp_script_wxfiledialog->GetPath());
        }
    }
    return;
}

/** @brief RUN script
 *
 * @param [IN] event : standard event input data
 * @return void
 *
 */

void main_frame::on_script_run_wxtogglebutton_toggle(wxCommandEvent& event)
{
    this->run(this->lp_script_run_wxtogglebutton->GetValue());
    return;
}

/** @brief Set DTR communication line
 *
 * @param [IN] event : standard event input data
 * @return void
 *
 */

void main_frame::on_port_control_dtr_wxcheckbox_click(wxCommandEvent& event)
{
    this->lp_communication_uart_port->set(e_dtr , (uint8_t)this->lp_port_control_dtr_wxcheckbox->GetValue());
    return;
}

/** @brief Set RTS communication line
 *
 * @param [IN] event : standard event input data
 * @return void
 *
 */

void main_frame::on_port_control_rts_wxcheckbox_click(wxCommandEvent& event)
{
    this->lp_communication_uart_port->set(e_rts, (uint8_t)this->lp_port_control_rts_wxcheckbox->GetValue());
    return;
}

/** @brief Set Tx communication line (default log 1)
 *
 * @param [IN] event : standard event input data
 * @return void
 *
 */

void main_frame::on_port_control_tx_wxcheckbox_click(wxCommandEvent& event)
{
    this->lp_communication_uart_port->set(e_break, (uint8_t)this->lp_port_control_tx_wxcheckbox->GetValue());
    return;
}

/** @brief Processing read data form UART
 *
 * @param [IN] p_data_sui8 : Read data
 * @param [IN] length_ui32 : Read data
 * @return void
 *
 */

void main_frame::uart_rx_data(uint8_t *p_data_sui8, uint32_t length_ui32)
{
wxString text_str, data_str;
uint32_t data_cnt_ui32;

    data_str = wxEmptyString;
    text_str = wxEmptyString;

    for(data_cnt_ui32 = 0 ; data_cnt_ui32 < length_ui32 ; data_cnt_ui32++)
    {
        if (this->lp_hex_wxcheckbox->GetValue())
        {
            text_str.Printf(wxT("%02x"),(uint8_t)p_data_sui8[data_cnt_ui32]);
            data_str += text_str;
        }
        else
        {
            text_str.Printf(wxT("%c"),p_data_sui8[data_cnt_ui32]);
            data_str += text_str;
        }
    }
    if (this->lp_hex_wxcheckbox->GetValue())
    {
        data_str += "\n";
    }
    // Show data
    this->js_printf(data_str);
    return;
}

/** @brief Data in UART buffer event
 *
 * @param [IN] p_parametr_void : Handle on registered object
 * @param [IN] event_type_ui32 : Event type field
 * @param [IN] p_data_sui8 : Buffer with data
 * @param [IN] length_ui32 : Data length
 * @return void
 *
 */

void main_frame::uart_rx_event(void* p_parametr_void, uint32_t event_type_ui32, uint8_t *p_data_sui8, uint32_t length_ui32)
{
	main_frame *p_bkp_this = (main_frame*)p_parametr_void;
    if (event_type_ui32 & EV_RXCHAR)
    {
        if (l_frame_rx_b)
        {
            p_bkp_this->uart_rx_data(p_data_sui8, length_ui32);
        }
    }
    if (event_type_ui32 & EV_CTS)
    {
        if (p_bkp_this->lp_communication_uart_port->get(e_cts))
        {
            p_bkp_this->l_cts_b = true;
        }
        else
        {
            p_bkp_this->l_cts_b = false;
        }
    }
    if (event_type_ui32 & EV_DSR)
    {
        if (p_bkp_this->lp_communication_uart_port->get(e_dsr))
        {
            p_bkp_this->l_dsr_b = true;
        }
        else
        {
            p_bkp_this->l_dsr_b = false;
        }
    }
    if (event_type_ui32 & EV_RING)
    {
        if (p_bkp_this->lp_communication_uart_port->get(e_ring))
        {
            p_bkp_this->l_ring_b = true;
        }
        else
        {
            p_bkp_this->l_ring_b = false;
        }
    }
    if (event_type_ui32 & EV_RLSD)
    {
        if (p_bkp_this->lp_communication_uart_port->get(e_rlsd))
        {
            p_bkp_this->l_rlsd_b = true;
        }
        else
        {
            p_bkp_this->l_rlsd_b = false;
        }
    }
    return;
}

/** @brief GUI update timer (GUI must be called from GUI thread)
 *
 * @param [IN] event : standard event input data
 * @return void
 *
 */

void main_frame::on_dialog_caller_wxtimer_trigger(wxTimerEvent& event)
{
    // Input dialog
    if (!this->l_dialog_end_b)
    {
        lp_dialog_caller_wxtimer.Stop();
        this->lp_data_wxtextentrydialog = new wxTextEntryDialog(this, this->l_dialog_info_str , wxT("Input data"), wxEmptyString, wxOK|wxCANCEL|wxCENTRE|wxWS_EX_VALIDATE_RECURSIVELY, wxDefaultPosition);
        if (this->lp_data_wxtextentrydialog->ShowModal() == wxID_OK)
        {
            this->l_dialog_text_str = this->lp_data_wxtextentrydialog->GetValue();
        }
        this->l_dialog_end_b = true;
        lp_dialog_caller_wxtimer.Start(100, false);
        delete this->lp_data_wxtextentrydialog;
    }
    // Progress dialog
    if (!this->l_progress_end_b)
    {
        if (this->l_progress_ui32 < 101)
        {
            if(this->lp_data_wxprogressdialog == NULL)
            {
                this->lp_data_wxprogressdialog = new wxProgressDialog(wxT("Progress"), this->l_progress_info_str, 100, this, wxPD_APP_MODAL|wxPD_AUTO_HIDE | wxPD_CAN_ABORT );
                this->lp_data_wxprogressdialog->ShowModal();
            }
            else
            {
                this->lp_data_wxprogressdialog->Update(this->l_progress_ui32);
            }
        }
        else
        {
            delete this->lp_data_wxprogressdialog;
            this->lp_data_wxprogressdialog = NULL;
        }
        this->l_progress_end_b = true;
    }
    if(this->lp_data_wxprogressdialog)
    {
        if(false == this->lp_data_wxprogressdialog->Update(this->l_progress_ui32))
        {
            this->l_progress_end_b = false;
            this->l_progress_ui32 = 101;
        }
    }
    return;
}

/** @brief Sync timer for UART control signal (wxLed update must by called from GUI thread)
 *
 * @param [IN] event : standard event input data
 * @return void
 *
 */

void main_frame::on_wx_gui_sync_wxtimer_trigger(wxTimerEvent& event)
{
static bool f_cts_old_b = false;
static bool f_dsr_old_b = false;
static bool f_ring_old_b = false;
static bool f_rlsd_old_b = false;
wxCommandEvent data_wxcommandevent;

    // Call exit event
    if (l_frame_gui_close_b)
    {
        this->lp_script_run_wxtogglebutton->SetValue(false);
        this->on_script_run_wxtogglebutton_toggle(data_wxcommandevent);
        l_frame_gui_close_b = false;
    }
    // Add console text
    if(lv_frame_main_console_buffer.size())
    {
        while(lv_frame_main_console_buffer.size())
        {
            this->lp_console_wxtextctrl->SetInsertionPointEnd();
            this->lp_console_wxtextctrl->WriteText(lv_frame_main_console_buffer[0].text_str);
            lv_frame_main_console_buffer.erase(lv_frame_main_console_buffer.begin() + 0);
        }
    }
    // Set status
    if(l_frame_status_b)
    {
        this->status(l_frame_status_str);
        l_frame_status_b = false;
    }
    // Clear port
    if(l_frame_clear_b)
    {
        this->clear();
        l_frame_clear_b = false;
    }
    // Open port
    if(l_frame_open_b)
    {
        this->open_port();
        l_frame_open_b = false;
    }
    // Close port
    if(l_frame_close_b)
    {
        this->close_port();
        l_frame_close_b = false;
    }
    // Set port
    if(l_frame_set_b)
    {
        if(!l_frame_data_uart_cfg.port_num_ui8)
        {
            l_frame_data_uart_cfg.port_num_ui8 = this->get_config().port_num_ui8;
        }
        this->set_config(l_frame_data_uart_cfg);
        l_frame_set_b = false;
    }
    // Main frame hide
    if(l_frame_hide_b)
    {
        this->Show(l_frame_hide_state_b);
        l_frame_hide_b = false;
    }
    // Start script
    if(this->l_script_start_b)
    {
        this->l_script_start_b = false;
        if (this->lp_script_path_wxtextctrl->GetLineText(0) != wxEmptyString)
        {
            // Start Java Script
            switch(this->run_script(this->lp_script_path_wxtextctrl->GetLineText(0)))
            {
                case 0:
                {
                    this->lp_bot_wxstatusbar->SetStatusText(wxT("Script thread RUN ERROR"), d_ap_uart_terminal_status_script);
                }
                break;
                case 1:
                {
                    this->lp_bot_wxstatusbar->SetStatusText(wxT("Script RUN"), d_ap_uart_terminal_status_script);
                }
                break;
                case 2:
                {
                    this->lp_bot_wxstatusbar->SetStatusText(wxT("Script already RUN"), d_ap_uart_terminal_status_script);
                }
                break;
                default:
                {
                    this->lp_bot_wxstatusbar->SetStatusText(wxT("Unknown ERROR"), d_ap_uart_terminal_status_script);
                }
                break;
            }
        }

    }
    // Stop script request
    if(this->l_script_stop_b)
    {
        // Stop JavaScript
        if(this->stop_script())
        {
            this->l_script_stop_b = false;
        }
    }
    // Set com control line status
    if(this->l_open_b)
    {
        // Set CTS state
        if (f_cts_old_b != this->l_cts_b)
        {
            if (this->l_cts_b)
            {
               this->lp_port_state_cts_wxled->SwitchOn();
            }
            else
            {
                this->lp_port_state_cts_wxled->SwitchOff();
            }
        }
        f_cts_old_b = this->l_cts_b;
        // Set DSR state
        if (f_dsr_old_b != this->l_dsr_b)
        {
            if (this->l_dsr_b)
            {
                this->lp_port_state_dsr_wxled->SwitchOn();
            }
            else
            {
                this->lp_port_state_dsr_wxled->SwitchOff();
            }
        }
        f_dsr_old_b = this->l_dsr_b;
        // Set RING state
        if (f_ring_old_b != this->l_ring_b)
        {
            if (this->l_ring_b)
            {
                this->lp_port_state_ring_wxled->SwitchOn();
            }
            else
            {
                this->lp_port_state_ring_wxled->SwitchOff();
            }
        }
        f_ring_old_b = this->l_ring_b;
        // Set RLSD state
        if (f_rlsd_old_b != this->l_rlsd_b)
        {
            if (this->l_rlsd_b)
            {
                this->lp_port_state_rlsd_wxled->SwitchOn();
            }
            else
            {
                this->lp_port_state_rlsd_wxled->SwitchOff();
            }
        }
        f_rlsd_old_b = this->l_rlsd_b;
    }
    return;
}

/** @brief Change port baudrate
 *
 * @param [IN] event : standard event input data
 * @return void
 *
 */

void main_frame::on_speed_wxchoice_select(wxCommandEvent& event)
{
    if(lp_speed_wxchoice->GetString(lp_speed_wxchoice->GetSelection()).IsSameAs("Custom"))
    {
        this->lp_speed_wxtextctrl->Show(true);
    }
    else
    {
        this->lp_speed_wxtextctrl->Show(false);
    }
    this->lp_main_setting_wxboxsizer->Layout();
    return;
}

/** @brief Open/Close script editor
 *
 * @param [IN] event : standard event input data
 * @return void
 *
 */

void main_frame::on_editor_wxbutton_click(wxCommandEvent& event)
{
    if(event.GetId() == l_id_file_edit_item_wxmenu)
    {
        this->lp_data_editor_frame->Show();
    }
    else
    {
        if(this->lp_data_editor_frame->IsShown())
        {
            this->lp_data_editor_frame->Show(false);
        }
        else
        {
            this->lp_data_editor_frame->Show();
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

/*****************************************************END OF FILE************/
