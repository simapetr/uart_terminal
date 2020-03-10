#ifndef DATA_PLOT_H_H_INCLUDED
#define DATA_PLOT_H_H_INCLUDED

/**
  ****************************************************************************
  * @file    data_plot_h.h
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    11.05.2015
  * @brief   Data graph
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

//(*Headers(data_plot)
#include <mathplot.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/grid.h>
#include <wx/imaglist.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/tglbtn.h>
//*)

#include <vector>
using namespace std;

/**
  * @addtogroup data_plot
  * @{
  */

/**
  ****************************************************************************
  * Typedef
  ****************************************************************************
  */

typedef struct
{
    vector<double> v_buffer_data_plot_d;
    mpPolygon *p_buffer_measure_data_polygon;
    wxString data_signal_name_str;
    wxPen data_signal_style_pen;
    wxCheckBox* p_signal_wxcheckbox;
}data_plot_buffer;

/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */

class data_plot: public wxPanel
{
    public :

        data_plot(wxWindow* p_parent_wxwindow, wxString name_str, double min_d, double max_d, double length_d, double step_d);
        ~data_plot(void);
        void add(wxString signal_label_str, wxPen signal_style_pen);
        void erase(wxString signal_label_str);
        uint32_t get(void);
        bool set(wxString signal_label_str, double data_d);
        bool set(uint32_t signal_ui32, double data_d);
        void show(wxString signal_label_str, bool show_b);
        bool set_time(double length_d, double step_d);
        void set_range(double max_d, double min_d);
        void redraw(void);
        void fit(bool default_b = true);
        void pause(bool pause_b);

    protected:

        //(*Identifiers(data_plot)
        static const long l_id_name_wxstatictext;
        static const long l_id_pause_wxtogglebutton;
        static const long l_id_zoom_wxbutton;
        static const long l_id_zoom_plus_wxbutton;
        static const long l_id_zoom_minus_wxbutton;
        static const long l_id_legend_wxcheckbox;
        static const long l_id_x_axis_mpscalex;
        static const long l_id_y_axis_mpscalex;
        static const long l_id_graph_mpwindow;
        static const long l_id_graph_signal_wxgrid;
        //*)

    private :

        void time_init(void);
        void on_signal_wxcheckbox_click(wxCommandEvent& event);
        //(*Handlers(data_plot)
        void on_zoom_wxbutton_click(wxCommandEvent& event);
        void on_zoom_plus_wxbutton_click(wxCommandEvent& event);
        void on_zoom_minus_wxbutton_click(wxCommandEvent& event);
        void on_pause_wxtogglebutton_toggle(wxCommandEvent& event);
        void on_legend_wxcheckbox_click(wxCommandEvent& event);
        //*)

        wxString l_name_str;
        double l_max_d;
        double l_min_d;
        double l_max_default_d;
        double l_min_default_d;
        double l_zoom_step_d;
        uint32_t l_zoom_cnt_ui32;
        double l_length_d;
        double l_cnt_d;
        double l_step_d;
        vector<double> lv_time_d;
        vector<data_plot_buffer> lv_signal_data_plot_buffer;
        uint32_t l_sample_cnt_ui32;
        mpInfoLegend* lp_graph_mpinfolegend;
        bool l_pause_b;
        //(*Declarations(data_plot)
        mpScaleX   *lp_x_axis_mpscalex;
        mpScaleY   *lp_y_axis_mpscalex;
        mpWindow* lp_graph_mpwindow;
        wxBoxSizer* lp_frame_wxboxsizer;
        wxBoxSizer* lp_grid_wxboxsizer;
        wxBoxSizer* lp_mathplot_graph_wxboxsizer;
        wxBoxSizer* lp_mathplot_setting_wxboxsizer;
        wxButton* lp_zoom_minus_wxbutton;
        wxButton* lp_zoom_plus_wxbutton;
        wxButton* lp_zoom_wxbutton;
        wxCheckBox* lp_legend_wxcheckbox;
        wxGrid* lp_graph_signal_wxgrid;
        wxImageList* icon_wximagelist;
        wxStaticText* lp_name_wxstatictext;
        wxToggleButton* lp_pause_wxtogglebutton;
        //*)

        DECLARE_EVENT_TABLE()

};

/**
* @}
*/

/****************************************************** END OF FILE *********/

#endif // DATA_PLOT_H_H_INCLUDED
