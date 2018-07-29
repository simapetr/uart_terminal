#ifndef IN_DATA_PLOT_GRAPH_H_H_INCLUDED
#define IN_DATA_PLOT_GRAPH_H_H_INCLUDED

/**
  ****************************************************************************
  * @file    in_data_plot_graph_h.h
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    11.05.2015
  * @brief   Interpret real-time data
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
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/timer.h>
//*)

#include <vector>
using namespace std;

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @addtogroup data_plot
  * @{
  */

/**
  ****************************************************************************
  * Struct
  ****************************************************************************
  */

typedef struct
{
    vector<double> v_buffer_data_plot_d;
    mpPolygon *p_buffer_measure_data_polygon;
    wxString data_signal_name_str;
    wxPen data_signal_style_pen;
}data_plot_buffer;

/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */

class data_plot: public wxPanel
{
	public:

		data_plot(wxWindow* p_parent_wxwindow, double draph_range_d, double buffer_length_d, double time_step_d);
        ~data_plot(void);
        void insert_signal (wxString signal_label_str, wxPen signal_style_pen);
        uint32_t get_signal (void);
        uint8_t insert_data (uint32_t index_ui32, double data_d);
        void time_increment(void);
        void redraw_event(void);

    protected:

		//(*Identifiers(data_plot)
		static const long l_id_graph_name_wxstatictext;
		static const long l_id_x_axis_mpscalex;
		static const long l_id_y_axis_mpscalex;
		static const long l_id_graph_mpwindow;
		static const long l_id_graph_signal_wxgrid;
		static const long l_id_redraw_wxtimer;
		//*)

	private:

        //(*Handlers(data_plot)
        void on_redraw_wxtimer_trigger(wxTimerEvent& event);
        //*)

		//(*Declarations(data_plot)
		mpScaleY   *lp_y_axis_mpscalex;
		mpWindow* lp_graph_mpwindow;
		mpScaleX   *lp_x_axis_mpscalex;
		wxBoxSizer* lp_graph_wxboxsizer;
		wxGrid* lp_graph_signal_wxgrid;
		wxStaticText* lp_graph_name_wxstatictext;
		wxTimer lp_redraw_wxtimer;
		//*)

		bool l_redraw_b;
		double l_graph_range_d;
        double l_buffer_length_d;
        double l_time_base_cnt_d;
        double l_time_step_d;
        vector<double> lv_time_data_plot_d;
        vector<data_plot_buffer> lv_graph_data_plot_buffer;


		DECLARE_EVENT_TABLE()
};

/**
* @}
*/

#endif // IN_DATA_PLOT_GRAPH_H_H_INCLUDED
