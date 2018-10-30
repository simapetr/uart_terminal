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

typedef struct
{
    wxString name_str;
    double sizer_index_d;
    bool sizer_orientation_b;
    wxPanel* p_data_wxpanel;
}panel_buffer_t;

typedef struct
{
    bool sizer_orientation_b;
    double parent_index_d;
    double panel_index_d;
    double proportion_d;
    wxBoxSizer* p_data_wxboxsizer;
}sizer_buffer_t;

extern vector<panel_buffer_t> lv_data_panel_buffer;
extern vector<sizer_buffer_t> lv_data_sizer_buffer;

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
        void frame_show (bool status_b);
        uint32_t add_panel (wxString panel_name_str, bool horizontal_b);
        uint32_t get_panel_sizer (double panel_index_d);
        uint32_t add_sizer (double sizer_index_d, double proportion_d, bool horizontal_b);
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

    private:



        //(*Handlers(gui_frame)
        void on_update_wxtimer_trigger(wxTimerEvent& event);
        void on_frame_auimanager_pane_close(wxAuiManagerEvent& event);
        void on_frame_resize(wxSizeEvent& event);
        void on_close_event(wxCloseEvent& event);
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

        //(*Identifiers(gui_frame)
        static const long l_id_update_wxtimer;
        //*)

        //(*Declarations(gui_frame)
        wxAuiManager* lp_main_wxauimanager;
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
