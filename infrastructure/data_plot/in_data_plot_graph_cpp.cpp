/**
  ****************************************************************************
  * @file    in_data_plot_graph_cpp.cpp
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

#include "in_data_plot_graph_h.h"

//(*InternalHeaders(data_plot)
#include <wx/intl.h>
#include <wx/string.h>
//*)

/**
  * @defgroup Transmitter_box
  * @brief Transmitter box
  * @{
  */

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

//(*IdInit(data_plot)
const long data_plot::l_id_graph_name_wxstatictext = wxNewId();
const long data_plot::l_id_x_axis_mpscalex = wxNewId();
const long data_plot::l_id_y_axis_mpscalex = wxNewId();
const long data_plot::l_id_graph_mpwindow = wxNewId();
const long data_plot::l_id_graph_signal_wxgrid = wxNewId();
const long data_plot::l_id_redraw_wxtimer = wxNewId();
//*)

/**
  ****************************************************************************
  * Event table
  ****************************************************************************
  */

BEGIN_EVENT_TABLE(data_plot,wxPanel)
	//(*EventTable(data_plot)
	//*)
END_EVENT_TABLE()

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Constructor
 *
 * @param [IN] p_parent_wxwindow : Pointer on Windows window
 * @param [IN] graph_label_str : Graph label
 * @param [IN] draph_range_d : Graph range
 * @param [IN] buffer_length_d : buffer length in (s)
 * @param [IN] time_step_d : Time stamp in (s)
 * @return void
 *
 */

data_plot::data_plot(wxWindow* p_parent_wxwindow, wxString graph_label_str, double draph_range_d, double buffer_length_d, double time_step_d)
{
wxWindow* parent = p_parent_wxwindow;
double data_buffer_cnt_d;

    // Initialize variable
    this->l_graph_range_d = draph_range_d;
    this->l_buffer_length_d = buffer_length_d;
    this->l_time_step_d = time_step_d;
    this->l_time_base_cnt_d = 0.0;
    //(*Initialize(data_plot)
    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
    lp_graph_wxboxsizer = new wxBoxSizer(wxVERTICAL);
    lp_graph_name_wxstatictext = new wxStaticText(this, l_id_graph_name_wxstatictext, _("Graph"), wxDefaultPosition, wxDefaultSize, 0, _T("l_id_graph_name_wxstatictext"));
    lp_graph_wxboxsizer->Add(lp_graph_name_wxstatictext, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_graph_mpwindow = new mpWindow(this, l_id_graph_mpwindow, wxDefaultPosition, wxDefaultSize, wxRAISED_BORDER|wxTAB_TRAVERSAL);
    lp_x_axis_mpscalex = new mpScaleX(_("time"), 1, true);
    lp_graph_mpwindow->AddLayer(lp_x_axis_mpscalex);
    lp_y_axis_mpscalex = new mpScaleY(_("value"), 4, true);
    lp_graph_mpwindow->AddLayer(lp_y_axis_mpscalex);
    lp_graph_mpwindow->UpdateAll();
    lp_graph_mpwindow->Fit();
    lp_graph_wxboxsizer->Add(lp_graph_mpwindow, 1, wxEXPAND, 5);
    lp_graph_signal_wxgrid = new wxGrid(this, l_id_graph_signal_wxgrid, wxDefaultPosition, wxDefaultSize, 0, _T("l_id_graph_signal_wxgrid"));
    lp_graph_signal_wxgrid->CreateGrid(1,0);
    lp_graph_signal_wxgrid->EnableEditing(true);
    lp_graph_signal_wxgrid->EnableGridLines(true);
    lp_graph_signal_wxgrid->SetDefaultCellFont( lp_graph_signal_wxgrid->GetFont() );
    lp_graph_signal_wxgrid->SetDefaultCellTextColour( lp_graph_signal_wxgrid->GetForegroundColour() );
    lp_graph_wxboxsizer->Add(lp_graph_signal_wxgrid, 0, wxEXPAND, 5);
    SetSizer(lp_graph_wxboxsizer);
    lp_redraw_wxtimer.SetOwner(this, l_id_redraw_wxtimer);
    lp_redraw_wxtimer.Start(20, false);
    lp_graph_wxboxsizer->Fit(this);
    lp_graph_wxboxsizer->SetSizeHints(this);

    Connect(l_id_redraw_wxtimer,wxEVT_TIMER,(wxObjectEventFunction)&data_plot::on_redraw_wxtimer_trigger);
    //*)
    this->lp_graph_signal_wxgrid->SetRowLabelSize(0);
    // Initialization time base
    for(data_buffer_cnt_d = (-this->l_buffer_length_d) ; data_buffer_cnt_d <= 0.0 ; (data_buffer_cnt_d += this->l_time_step_d))
    {
        this->lv_time_data_plot_d.push_back(data_buffer_cnt_d);
    }
    this->lp_graph_mpwindow->Fit(this->lv_time_data_plot_d[1], this->lv_time_data_plot_d[this->lv_time_data_plot_d.size()], (-this->l_graph_range_d),this->l_graph_range_d);
    // Initialization timer flag
    this->l_redraw_b = false;
    // Set graph name
    this->lp_graph_name_wxstatictext->SetLabel(graph_label_str);
	return;
}

/** @brief Destructor
 *
 * @param void
 * @return void
 *
 */

data_plot::~data_plot()
{
    //(*Destroy(data_plot)
	//*)
	this->lv_time_data_plot_d.clear();
    this->lv_graph_data_plot_buffer.clear();
    return;
}

/** @brief Insert signal in to graph
 *
 * @param [IN] signal_label_str : Signal name
 * @param [IN] signal_style_pen : Signal style
 * @return void
 *
 */

void data_plot::insert_signal (wxString signal_label_str, wxPen signal_style_pen)
{
data_plot_buffer signal_data_plot_buffer;
double data_buffer_cnt_d;
uint32_t end_index_ui32 = 0;

    signal_data_plot_buffer.data_signal_name_str = signal_label_str;
    signal_data_plot_buffer.data_signal_style_pen = signal_style_pen;
    signal_data_plot_buffer.p_buffer_measure_data_polygon = NULL;
    this->lv_graph_data_plot_buffer.push_back(signal_data_plot_buffer);
    if (this->lv_graph_data_plot_buffer.size())
    {
        end_index_ui32 = (this->lv_graph_data_plot_buffer.size() - 1);
    }
    for(data_buffer_cnt_d = 0.0 ; data_buffer_cnt_d <= this->l_buffer_length_d ; (data_buffer_cnt_d += this->l_time_step_d))
    {
        this->lv_graph_data_plot_buffer[end_index_ui32].v_buffer_data_plot_d.push_back(0.0);
    }
    this->l_redraw_b = true;
    return;
}

/** @brief Get number of signal in graph
 *
 * @param void
 * @return uint32_t : Number of signal in graph
 *
 */

uint32_t data_plot::get_signal (void)
{
    return this->lv_graph_data_plot_buffer.size();
}

/** @brief Insert data in to specific signal buffer
 *
 * @param [IN] index_ui32 : Signal data indec
 * @param [IN] data_d : data
 * @return uint8_t : status
 *
 */

uint8_t data_plot::insert_data (uint32_t index_ui32, double data_d)
{
uint8_t status_value_ui8 = 0;
uint32_t buffer_size_ui32 = this->lv_graph_data_plot_buffer.size();

    if((buffer_size_ui32) && (index_ui32 < buffer_size_ui32))
    {
        this->lv_graph_data_plot_buffer[index_ui32].v_buffer_data_plot_d.push_back(data_d);
        this->lv_graph_data_plot_buffer[index_ui32].v_buffer_data_plot_d.erase(this->lv_graph_data_plot_buffer[index_ui32].v_buffer_data_plot_d.begin());
        status_value_ui8 = 1;
    }
    return status_value_ui8;
}

/** @brief Increment time X scale (call after insert all single data)
 *
 * @param void
 * @return void
 *
 */

void data_plot::time_increment(void)
{
    this->l_time_base_cnt_d += this->l_time_step_d;
    this->lv_time_data_plot_d.push_back(this->l_time_base_cnt_d);
    this->lv_time_data_plot_d.erase(this->lv_time_data_plot_d.begin());
    this->l_redraw_b = true;
    return;
}

/** @brief Add new signal and redraw graph
 *
 * @param [IN] event : standard event input data
 * @return void
 *
 */

void data_plot::on_redraw_wxtimer_trigger(wxTimerEvent& event)
{
uint32_t signal_cnt_ui32;
wxString value_text_str;
uint32_t cols_num_ui32;

    if (this->l_redraw_b)
    {
        this->l_redraw_b = false;
        // Add new variable grid cell
        while ((uint32_t)this->lp_graph_signal_wxgrid->GetCols() < this->lv_graph_data_plot_buffer.size())
        {
            cols_num_ui32 = this->lp_graph_signal_wxgrid->GetCols();
            this->lp_graph_signal_wxgrid->AppendCols();
            this->lp_graph_signal_wxgrid->SetColLabelValue(cols_num_ui32, this->lv_graph_data_plot_buffer[cols_num_ui32].data_signal_name_str);
        }
        for (signal_cnt_ui32 = 0 ; signal_cnt_ui32 < this->lv_graph_data_plot_buffer.size() ; signal_cnt_ui32++)
        {
            if (this->lv_graph_data_plot_buffer[signal_cnt_ui32].p_buffer_measure_data_polygon == NULL)
            {
                this->lp_graph_mpwindow->AddLayer( this->lv_graph_data_plot_buffer[signal_cnt_ui32].p_buffer_measure_data_polygon = new mpPolygon(this->lv_graph_data_plot_buffer[signal_cnt_ui32].data_signal_name_str) );
                this->lv_graph_data_plot_buffer[signal_cnt_ui32].p_buffer_measure_data_polygon->SetPen( this->lv_graph_data_plot_buffer[signal_cnt_ui32].data_signal_style_pen );
            }
            this->lv_graph_data_plot_buffer[signal_cnt_ui32].p_buffer_measure_data_polygon->setPoints(this->lv_time_data_plot_d, this->lv_graph_data_plot_buffer[signal_cnt_ui32].v_buffer_data_plot_d, false );
            this->lp_graph_mpwindow->Fit(this->lv_time_data_plot_d[1], this->lv_time_data_plot_d[this->lv_time_data_plot_d.size()], (-this->l_graph_range_d),this->l_graph_range_d);
            // set text value
            value_text_str.Printf("%f",(float)this->lv_graph_data_plot_buffer[signal_cnt_ui32].v_buffer_data_plot_d.at(this->lv_graph_data_plot_buffer[signal_cnt_ui32].v_buffer_data_plot_d.size() - 1));
            this->lp_graph_signal_wxgrid->SetCellValue(value_text_str, 0, signal_cnt_ui32);
        }
    }
    return;
}

/**
* @}
*/

/*****************************************************END OF FILE************/
