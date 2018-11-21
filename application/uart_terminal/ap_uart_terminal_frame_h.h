#ifndef AP_UART_TERMINAL_FRAME_H_H
#define AP_UART_TERMINAL_FRAME_H_H

/**
  ****************************************************************************
  * @file    ap_uart_terminal_frame_h.h
  * @author  Ing. Petr Simek
  * @version V1.1
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

//(*Headers(main_frame)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/led.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
#include <wx/tglbtn.h>
#include <wx/timer.h>
//*)
#include <wx/textdlg.h>
#include <wx/progdlg.h>

#include "hw_dr_uart_driver_h.h"
#include "in_config_ini_wrapper_h.h"
#include "in_jerryscript_port_h.h"

/**
  * @addtogroup Application
  * @{
  */

/**
  * @addtogroup UART_terminal
  * @{
  */

/**
  ****************************************************************************
  * Type
  ****************************************************************************
  */

typedef void (*send_event_fct)(void* p_parametr_void, uint8_t *p_data_sui8, uint32_t length_ui32);

/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */

class main_frame: public wxFrame
{
    public:

        main_frame(wxWindow* p_parent_window, wxArrayString* p_cmd_arg_arraystring);
        virtual ~main_frame();
        void gui (bool status_b);
        config_ini* get_project (void);
        void console_rx_enable (bool status_b);
        bool is_console_rx_enable (void);
        void printf(wxString console_text_str);
        void status(wxString status_text_str);
        void clear(void);
        void open_port(void);
        void close_port(void);
        uart_status_t get_open_status(void);
        void set_config (uart_cfg_t data_uart_cfg);
        uart_cfg_t get_config (void);
        wxString get_data (wxString text_str);
        void set_progress (wxString text_str, uint32_t progress_ui32);
        void set_send_event (send_event_fct data_send_event_fct, void* p_parametr_void);
        uint32_t run_script(wxString path_str);
        void stop_script(void);
        static void stop_event(void);


    private:

        //(*Handlers(main_frame)
        void main_panel_clear_button_click(wxCommandEvent& event);
        void main_panel_close_button_click(wxCommandEvent& event);
        void main_panel_open_button_click(wxCommandEvent& event);
        void main_panel_send_button_click(wxCommandEvent& event);
        void menu_bar_file_quit_item_selected(wxCommandEvent& event);
        void menu_bar_help_about_item_selected(wxCommandEvent& event);
        void on_port_control_dtr_wxcheckbox_click(wxCommandEvent& event);
        void on_port_control_rts_wxcheckbox_click(wxCommandEvent& event);
        void on_port_control_tx_wxcheckbox_click(wxCommandEvent& event);
        void on_script_load_wxbutton_click(wxCommandEvent& event);
        void on_dialog_caller_wxtimer_trigger(wxTimerEvent& event);
        void on_wx_gui_sync_wxtimer_trigger(wxTimerEvent& event);
        void on_script_run_wxtogglebutton_toggle(wxCommandEvent& event);
        //*)
        void main_panel_set_port_choice(void);
        void uart_rx_data(uint8_t *p_data_sui8, uint32_t length_ui32);
        static void uart_rx_event(void* p_parametr_void, uint32_t event_type_ui32, uint8_t *p_data_sui8, uint32_t length_ui32);

        //(*Identifiers(main_frame)
        static const long l_id_port_wxstatictext;
        static const long l_id_port_wxchoice;
        static const long l_id_speed_wxchoice;
        static const long l_id_length_wxchoice;
        static const long l_id_parity_wxchoice;
        static const long l_id_stop_bit_wxchoice;
        static const long l_id_clear_wxbutton;
        static const long l_id_close_wxbutton;
        static const long l_id_open_wxbutton;
        static const long l_id_text_cr_wxcheckbox;
        static const long l_id_text_lf_wxcheckbox;
        static const long l_id_port_control_dtr_wxcheckbox;
        static const long l_id_port_control_rts_wxcheckbox;
        static const long l_id_port_control_tx_wxcheckbox;
        static const long l_id_port_state_cts_wxled;
        static const long l_id_port_state_cts_wxstatictext;
        static const long l_id_port_state_dsr_wxled;
        static const long l_id_port_state_dsr_wxstatictext;
        static const long l_id_port_state_ring_wxled;
        static const long l_id_port_state_ring_wxstatictext;
        static const long l_id_port_state_rlsd_wxled;
        static const long l_id_port_state_rlsd_wxstatictext;
        static const long l_id_script_path_wxtextctrl;
        static const long l_id_script_load_wxbutton;
        static const long l_id_script_run_wxtogglebutton;
        static const long l_id_command_wxtextctrl;
        static const long l_id_hex_wxcheckbox;
        static const long l_id_send_wxbutton;
        static const long l_id_console_wxtextctrl;
        static const long l_id_main_wxpanel;
        static const long l_id_file_quit_item_wxmenu;
        static const long l_id_help_about_item_wxmenu;
        static const long l_id_bot_wxstatusbar;
        static const long l_id_dialog_caller_wxtimer;
        static const long l_id_wx_gui_sync_wxtimer;
        //*)

        //(*Declarations(main_frame)
        wxBoxSizer* lp_main_command_wxboxsizer;
        wxBoxSizer* lp_main_control_wxboxsizer;
        wxBoxSizer* lp_main_setting_wxboxsizer;
        wxBoxSizer* lp_main_wxboxsizer;
        wxButton* lp_clear_wxbutton;
        wxButton* lp_close_wxbutton;
        wxButton* lp_open_wxbutton;
        wxButton* lp_script_load_wxbutton;
        wxButton* lp_send_wxbutton;
        wxCheckBox* lp_hex_wxcheckbox;
        wxCheckBox* lp_port_control_dtr_wxcheckbox;
        wxCheckBox* lp_port_control_rts_wxcheckbox;
        wxCheckBox* lp_port_control_tx_wxcheckbox;
        wxCheckBox* lp_text_cr_wxcheckbox;
        wxCheckBox* lp_text_lf_wxcheckbox;
        wxChoice* lp_length_wxchoice;
        wxChoice* lp_parity_wxchoice;
        wxChoice* lp_port_wxchoice;
        wxChoice* lp_speed_wxchoice;
        wxChoice* lp_stop_bit_wxchoice;
        wxFileDialog* lp_script_wxfiledialog;
        wxLed* lp_port_state_cts_wxled;
        wxLed* lp_port_state_dsr_wxled;
        wxLed* lp_port_state_ring_wxled;
        wxLed* lp_port_state_rlsd_wxled;
        wxMenu* lp_file_wxmenu;
        wxMenu* lp_help_wxmenu;
        wxMenuBar* lp_top_wxmenubar;
        wxMenuItem* lp_file_quit_item_wxmenu;
        wxMenuItem* lp_help_about_item_wxmenu;
        wxPanel* lp_main_wxpanel;
        wxStaticBoxSizer* lp_port_control_wxstaticboxsizer;
        wxStaticBoxSizer* lp_port_state_wxstaticboxsizer;
        wxStaticBoxSizer* lp_script_wxstaticboxsizer;
        wxStaticBoxSizer* lp_text_control_wxstaticboxsizer;
        wxStaticText* lp_port_state_cts_wxstatictext;
        wxStaticText* lp_port_state_dsr_wxstatictext;
        wxStaticText* lp_port_state_ring_wxstatictext;
        wxStaticText* lp_port_state_rlsd_wxstatictext;
        wxStaticText* lp_port_wxstatictext;
        wxStatusBar* lp_bot_wxstatusbar;
        wxTextCtrl* lp_command_wxtextctrl;
        wxTextCtrl* lp_console_wxtextctrl;
        wxTextCtrl* lp_script_path_wxtextctrl;
        wxTimer lp_dialog_caller_wxtimer;
        wxTimer lp_wx_gui_sync_wxtimer;
        wxToggleButton* lp_script_run_wxtogglebutton;
        //*)
        bool l_open_b;
        bool l_run_b;
        bool l_stop_req_b;
        uart_port* p_communication_uart_port;
        HANDLE uart_thread_handle;
        DWORD uart_thread_id_dword;
        uint32_t uart_thread_run_ui32;
        uart_status_t l_data_uart_status;
        bool l_consle_rx_enable_b;
        config_ini *p_data_config_ini;
        jerryscript_c *lp_interpret_jerryscript;
        wxTextEntryDialog* lp_data_wxtextentrydialog;
        wxString l_dialog_text_str;
        wxString l_dialog_info_str;
        bool l_dialog_end_b;
        bool l_cts_b;
        bool l_dsr_b;
        bool l_ring_b;
        bool l_rlsd_b;

        wxProgressDialog *lp_data_wxprogressdialog;
        wxString l_progress_info_str;
        uint32_t l_progress_ui32;
        bool l_progress_end_b;
        void *lp_event_parameter_void;
        send_event_fct l_data_send_event_fct;

        wxArrayString* lp_cmd_arg_arraystring;
        bool l_script_debug_b;

        DECLARE_EVENT_TABLE()
};

/**
* @}
*/

/**
* @}
*/

/*****************************************************END OF FILE************/

#endif // AP_UART_TERMINAL_FRAME_H_H
