#ifndef AP_GRAPH_FRAME_H_H
#define AP_GRAPH_FRAME_H_H

/**
  ****************************************************************************
  * @file    ap_graph_frame_h.h
  * @author  Ing. Petr Simek
  * @version V1.1
  * @date    17.07.2018
  * @brief   Graph window component creator
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

//(*Headers(graph_frame)
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/timer.h>
//*)
#include "in_data_plot_graph_h.h"

/**
  * @addtogroup Application
  * @{
  */

/**
  * @addtogroup Graph
  * @{
  */

/**
  ****************************************************************************
  * Struct
  ****************************************************************************
  */

typedef struct
{
    double graph_range_d;
    double buffer_length_d;
    double time_step_d;
    data_plot* p_graph_data_plot;
}graph_buffer_t;

/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */

class graph_frame: public wxFrame
{
    public:

        graph_frame(wxWindow* p_parent_window, wxWindowID id_window_id = -1);
        virtual ~graph_frame();
        uint32_t add_graph (double graph_range_d, double buffer_length_d, double time_step_d);
        uint32_t insert_signal (uint32_t graph_ui32, wxString signal_label_str, uint32_t color_ui32 = 0, uint32_t width_ui32 = 1, uint32_t style_ui32 = 0);
        bool set_graph_data (uint32_t graph_ui32, vector<double>& pv_data_d);

    private:

        //(*Handlers(graph_frame)
        void on_update_wxtimer_trigger(wxTimerEvent& event);
        //*)

        //(*Identifiers(graph_frame)
        static const long l_id_graph_wxpanel;
        static const long l_id_update_wxtimer;
        //*)

        //(*Declarations(graph_frame)
        wxBoxSizer* lp_graph_wxboxsizer;
        wxTimer lp_update_wxtimer;
        wxPanel* lp_graph_wxpanel;
        //*)

        vector<graph_buffer_t> lv_data_graph_buffer;

        DECLARE_EVENT_TABLE()
};

/**
* @}
*/

/**
* @}
*/

/*****************************************************END OF FILE************/

#endif // AP_GRAPH_FRAME_H_H
