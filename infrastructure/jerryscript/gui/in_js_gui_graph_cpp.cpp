/**
  ****************************************************************************
  * @file    in_js_gui_graph_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    10.09.2018
  * @brief   GUI window graph component
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
#include "in_data_plot_graph_h.h"

/**
  * @addtogroup Application
  * @{
  */

/**
  * @addtogroup GUI
  * @{
  */

/**
  * @addtogroup Graph
  * @brief GUI graph component
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
    double graph_range_d;
    double buffer_length_d;
    double time_step_d;
    data_plot* p_graph_data_plot;
}graph_buffer_t;

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

vector<graph_buffer_t> lv_data_graph_buffer;

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Add graph window
 *
 * @param [IN] sizer_index_d : Index in vector sizer buffer
 * @param [IN] name_str : Graph name
 * @param [IN] graph_range_d : Y access range
 * @param [IN] buffer_length_d : Buffer length in second
 * @param [IN] time_step_d : Sample time frequency
 * @return uint32_t : Graph window number
 *
 */

uint32_t gui_frame::add_graph (double sizer_index_d, wxString name_str, double graph_range_d, double buffer_length_d, double time_step_d)
{
graph_buffer_t data_graph_buffer;
uint32_t graph_index_ui32 = lv_data_graph_buffer.size();

    data_graph_buffer.name_str = name_str;
    data_graph_buffer.sizer_index_d = sizer_index_d;
    data_graph_buffer.graph_range_d = graph_range_d;
    data_graph_buffer.buffer_length_d = buffer_length_d;
    data_graph_buffer.time_step_d = time_step_d;
    data_graph_buffer.p_graph_data_plot = NULL;
    lv_data_graph_buffer.push_back(data_graph_buffer);
    wxMilliSleep(50);
    return graph_index_ui32;
}

/** @brief Insert signal in to graph
 *
 * @param [IN] graph_ui32 : Graph window number
 * @param [IN] signal_label_str : Signal name
 * @param [IN] color_ui32 : Signal color
 * @param [IN] width_ui32 : Signal width in pixel
 * @param [IN] style_ui32 : Pen style
 *   @arg 0 : Solid
 *   @arg 1 : Dot
 *   @arg 2 : Long dash
 *   @arg 3 : Short dash
 *   @arg 4 : Dot dash
 * @return uint32_t : Insert status
 *
 */

uint32_t gui_frame::insert_signal (uint32_t graph_ui32, wxString signal_label_str, uint32_t color_ui32, uint32_t width_ui32, uint32_t style_ui32)
{
uint32_t signal_ui32 = 0;
wxPen signal_style_pen;

    if (graph_ui32 < lv_data_graph_buffer.size())
    {
        signal_style_pen.SetColour(((unsigned char)color_ui32), ((unsigned char)(color_ui32 >> 8)), ((unsigned char)(color_ui32 >> 16)));
        signal_style_pen.SetWidth(width_ui32);
        signal_style_pen.SetStyle((style_ui32 + 100));
        if(lv_data_graph_buffer[graph_ui32].p_graph_data_plot)
        {
            lv_data_graph_buffer[graph_ui32].p_graph_data_plot->insert_signal(signal_label_str, signal_style_pen);
        }
    }
    return signal_ui32;
}

/** @brief Insert One sample for all signal in to graph window
 *
 * @param [IN] graph_ui32 : Graph window number
 * @param [IN] pv_data_d : signal data samples
 * @return bool : Insert data status
 *
 */

bool gui_frame::set_graph_data (uint32_t graph_ui32, vector<double>& pv_data_d)
{
bool status_b = false;
uint32_t signal_cnt_ui32;

    if (graph_ui32 < lv_data_graph_buffer.size())
    {
        if(lv_data_graph_buffer[graph_ui32].p_graph_data_plot)
        {
            for (signal_cnt_ui32 = 0 ; signal_cnt_ui32 < lv_data_graph_buffer[graph_ui32].p_graph_data_plot->get_signal() ; signal_cnt_ui32++)
            {
                lv_data_graph_buffer[graph_ui32].p_graph_data_plot->insert_data(signal_cnt_ui32, pv_data_d[signal_cnt_ui32]);
            }
            lv_data_graph_buffer[graph_ui32].p_graph_data_plot->time_increment();
        }
        status_b = true;
    }
    return status_b;
}

/**
  ****************************************************************************
  * Local function
  ****************************************************************************
  */

/** @brief Graph constructor event (must be called from GUI context)
 *
 * @param void
 * @return void
 *
 */

void gui_frame::on_update_graph(void)
{
static uint32_t f_graph_cnt_ui32 = 0;
wxPanel* p_data_wxpanel;
wxBoxSizer* p_data_wxboxsizer;

    // Add graph
    while (f_graph_cnt_ui32 < lv_data_graph_buffer.size())
    {
        // Get box sizer
        p_data_wxboxsizer = lv_data_sizer_buffer[lv_data_graph_buffer[f_graph_cnt_ui32].sizer_index_d].p_data_wxboxsizer;
        // Get origin panel
        p_data_wxpanel = lv_data_panel_buffer[lv_data_sizer_buffer[lv_data_graph_buffer[f_graph_cnt_ui32].sizer_index_d].panel_index_d].p_data_wxpanel;
        // Create new graph
        lv_data_graph_buffer[f_graph_cnt_ui32].p_graph_data_plot = new data_plot(p_data_wxpanel, lv_data_graph_buffer[f_graph_cnt_ui32].name_str, lv_data_graph_buffer[f_graph_cnt_ui32].graph_range_d, lv_data_graph_buffer[f_graph_cnt_ui32].buffer_length_d, lv_data_graph_buffer[f_graph_cnt_ui32].time_step_d);
        // Insert in to sizer
        p_data_wxboxsizer->Add(lv_data_graph_buffer[f_graph_cnt_ui32].p_graph_data_plot, 1, wxEXPAND, 5);
        p_data_wxboxsizer->Fit(p_data_wxpanel);
        p_data_wxboxsizer->SetSizeHints(p_data_wxpanel);
        p_data_wxboxsizer->Layout();
        lp_main_wxauimanager->Update();
        f_graph_cnt_ui32++;
    }
    return;
}

/** @brief Graph destructor event (must be called from GUI context)
 *
 * @param void
 * @return void
 *
 */

void gui_frame::on_clear_graph(void)
{
    lv_data_graph_buffer.clear();
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

/*****************************************************END OF FILE************/


