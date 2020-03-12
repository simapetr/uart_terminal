#ifndef IN_JS_GUI_FRAME_H_H
#define IN_JS_GUI_FRAME_H_H

/**
  ****************************************************************************
  * @file    in_js_gui_frame_h.h
  * @author  Ing. Petr Simek
  * @version V1.1
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

//(*Headers(gui_frame)
#include <wx/aui/aui.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/timer.h>
//*)
#include <wx/panel.h>
#include <wx/sizer.h>

#include <vector>
using namespace std;

/**
  * @addtogroup Application
  * @{
  */

/**
  * @addtogroup GUI
  * @{
  */

/**
  ****************************************************************************
  * Struct
  ****************************************************************************
  */



/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */

class gui_frame: public wxFrame
{
    public:

        gui_frame(wxWindow* p_parent_window, void* p_jerryscript_void);
        virtual ~gui_frame();
        wxAuiManager* get_aui_manager (void);
        void frame_show (bool status_b, wxString name_str);
        uint32_t add_panel (wxString panel_name_str, bool horizontal_b);
        uint32_t get_panel_sizer (double panel_index_d);
        wxPanel* get_panel (double index_d);
        bool get_panel_show(double index_d);
        void set_panel_show(double index_d, bool show_b);
        void set_panel_view(void);
        uint32_t add_sizer (double sizer_index_d, double proportion_d, bool horizontal_b);
        uint32_t add_panel_sizer (double panel_index_d, double proportion_d, bool horizontal_b);
        wxBoxSizer* get_sizer (double index_d);
        wxPanel* get_sizer_panel (double index_d);
        uint32_t add_graph (double sizer_index_d, wxString name_str, double graph_range_d, double buffer_length_d, double time_step_d);
        uint32_t insert_signal (uint32_t graph_ui32, wxString signal_label_str, uint32_t color_ui32 = 0, uint32_t width_ui32 = 1, uint32_t style_ui32 = 0);
        bool set_graph_data (uint32_t graph_ui32, vector<double>& pv_data_d);
        uint32_t add_button (double sizer_index_d, wxString text_str, double proportion_d, bool expand_b);
        bool set_button_event (double button_index_d, wxString event_fct_str);
        uint32_t add_slider (double sizer_index_d, double min_d, double max_d, double proportion_d, bool expand_b);
        bool set_slider_event (double index_d, wxString event_fct_str);
        int32_t get_slider_data (double index_d);
        void set_slider_data (double index_d, double data_d);
        uint32_t add_static_text (double sizer_index_d, wxString text_str, double proportion_d, bool expand_b);
        bool set_static_text (double static_text_index_d, wxString text_str);
        uint32_t add_textctrl (double sizer_index_d, wxString text_str, double proportion_d, bool expand_b, bool multiline_b);
        bool set_textctrl (double static_text_index_d, wxString text_str);
        bool append_textctrl (double static_text_index_d, wxString text_str);
        wxString get_textctrl (double static_text_index_d, uint32_t line_ui32);
        uint32_t add_check_box (double sizer_index_d, wxString text_str, double proportion_d, bool expand_b, bool state_b);
        bool set_check_box_event (double check_box_index_d, wxString event_fct_str);
        bool set_check_box (double check_box_index_d, bool state_b);
        bool get_check_box (double check_box_index_d);
        uint32_t add_gauge (double sizer_index_d, double proportion_d, bool expand_b, double size_d);
        bool set_gauge (double check_box_index_d, double value_d);
        double get_gauge (double check_box_index_d);
        uint32_t add_led (double sizer_index_d, double on_color_d, double off_color_d);
        void set_led (double led_index_d, bool state_b);
        bool get_led (double led_index_d);

    private:



        //(*Handlers(gui_frame)
        void on_update_wxtimer_trigger(wxTimerEvent& event);
        void on_frame_auimanager_pane_close(wxAuiManagerEvent& event);
        void on_frame_resize(wxSizeEvent& event);
        void on_close_event(wxCloseEvent& event);
        void on_js_quit_wxmenu_selected(wxCommandEvent& event);
        void on_js_panel_view_wxmenu_selected(wxCommandEvent& event);
        //*)
        void on_update_panel(void);
        void on_clear_panel(void);
        void on_update_sizer(void);
        void on_clear_sizer(void);
        void on_update_graph(void);
        void on_clear_graph(void);
        void on_button_click(wxCommandEvent& event);
        void on_update_button(void);
        void on_clear_button(void);
        void on_slider_update(wxScrollEvent& event);
        void on_update_slider(void);
        void on_clear_slider(void);
        void on_update_static_text(void);
        void on_clear_static_text(void);
        void on_update_textctrl(void);
        void on_clear_textctrl(void);
        void on_check_box_click(wxCommandEvent& event);
        void on_update_check_box(void);
        void on_clear_check_box(void);
        void on_update_gauge(void);
        void on_clear_gauge(void);
        void on_update_led(void);
        void on_clear_led(void);

        //(*Identifiers(gui_frame)
        static const long l_id_update_wxtimer;
        static const long l_id_js_quit_wxmenu;
        //*)

        //(*Declarations(gui_frame)
        wxAuiManager* lp_main_wxauimanager;
        wxMenu* lp_file_wxmenu;
        wxMenu* lp_view_wxmenu;
        wxMenuBar* lp_main_wxmenubar;
        wxMenuItem* lp_js_quit_wxmenu;
        wxTimer lp_update_wxtimer;
        //*)

        void* lp_jerryscript_void;

        DECLARE_EVENT_TABLE()
};

/**
* @}
*/

/**
* @}
*/

/*****************************************************END OF FILE************/

#endif // IN_JS_GUI_FRAME_H_H
