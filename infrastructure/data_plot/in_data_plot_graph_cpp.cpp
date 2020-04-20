/**
  ****************************************************************************
  * @file    data_plot_cpp.cpp
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

#include "in_data_plot_graph_h.h"
//(*InternalHeaders(data_plot)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

//(*IdInit(data_plot)
const long data_plot::l_id_name_wxstatictext = wxNewId();
const long data_plot::l_id_pause_wxtogglebutton = wxNewId();
const long data_plot::l_id_zoom_wxbutton = wxNewId();
const long data_plot::l_id_zoom_plus_wxbutton = wxNewId();
const long data_plot::l_id_zoom_minus_wxbutton = wxNewId();
const long data_plot::l_id_legend_wxcheckbox = wxNewId();
const long data_plot::l_id_x_axis_mpscalex = wxNewId();
const long data_plot::l_id_y_axis_mpscalex = wxNewId();
const long data_plot::l_id_graph_mpwindow = wxNewId();
const long data_plot::l_id_graph_signal_wxgrid = wxNewId();
//*)

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @defgroup data_plot
  * @brief Plot real-time data
  * @{
  */

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
  * Local variable
  ****************************************************************************
  */

static const char *lp_play_ico_si8[] = {
"    16    16        8            1",
"` c #ffffff",
". c #20c040",
"# c #c0dcc0",
"a c #808000",
"b c #000080",
"c c #800080",
"d c #008080",
"e c #800000",
"````````````````",
"````````````````",
"`````.``````````",
"`````..`````````",
"`````...````````",
"`````....```````",
"`````.....``````",
"`````......`````",
"`````.....``````",
"`````....```````",
"`````...````````",
"`````..`````````",
"`````.``````````",
"````````````````",
"````````````````",
"````````````````"
};

static const char *lp_stop_ico_si8[] = {
"    16    16        8            1",
"` c #ffffff",
". c #e02040",
"# c #808000",
"a c #008000",
"b c #800080",
"c c #008080",
"d c #800000",
"e c #000080",
"````````````````",
"````````````````",
"````````````````",
"````````````````",
"````........````",
"````........````",
"````........````",
"````........````",
"````........````",
"````........````",
"````........````",
"````........````",
"````````````````",
"````````````````",
"````````````````",
"````````````````"
};

static const char *lp_zoom_ico_si8[] = {
"    16    16        8            1",
"` c #070707",
". c #939493",
"# c #525152",
"a c #cfd0cf",
"b c #313031",
"c c #aaabaa",
"d c #777877",
"e c #ffffff",
"eeeeeeedb``bceee",
"eeeeea```b```bee",
"eeeea``deeea#`be",
"eeeeb`.eea`#e#`d",
"eeea`beeeed`be`b",
"eeec`.eeeeec`c#`",
"eee.`.eeeeee.e#`",
"eeec`deeeeeeeebb",
"eeea`beeeeeeea`b",
"eeee#`#eeeeeeb`c",
"eeec```bcaad``#e",
"eec``````````dee",
"ec```#ead##.aeee",
"c```#eeeeeeeeeee",
"b``beeeeeeeeeeee",
"b`beeeeeeeeeeeee"
};

static const char *lp_zoom_plus_ico_si8[] = {
"    16    16        8            1",
"` c #040504",
". c #949694",
"# c #545254",
"a c #ccd2cc",
"b c #343234",
"c c #ffffff",
"d c #747a74",
"e c #acaaac",
"cccccccdb``beccc",
"ccccca```b```bcc",
"cccca``dccca#`bc",
"ccccb`.ca``.c#`d",
"ccca`bcca``.cc`b",
"ccce`.c``````.#`",
"ccc.`.c``````.#`",
"ccce`dcca``.ccbb",
"ccca`bcca``.ca`b",
"cccc#`#ccccccb`e",
"ccce```beaad``#c",
"cce``````````dcc",
"ce```#cad##.accc",
"e```#ccccccccccc",
"b``bcccccccccccc",
"b`bccccccccccccc"
};

static const char *lp_zoom_minus_ico_si8[] = {
"    16    16        8            1",
"` c #040504",
". c #949694",
"# c #545254",
"a c #ccd2cc",
"b c #343234",
"c c #ffffff",
"d c #747a74",
"e c #acaaac",
"cccccccdb``beccc",
"ccccca```b```bcc",
"cccca``dccca#`bc",
"ccccb`.cccccc#`d",
"ccca`bccaaaaaa`b",
"ccce`.c``````.#`",
"ccc.`.c``````.#`",
"ccce`dccccccccbb",
"ccca`bccccccca`b",
"cccc#`#ccccccb`e",
"ccce```beaad``#c",
"cce``````````dcc",
"ce```#cad##.accc",
"e```#ccccccccccc",
"b``bcccccccccccc",
"b`bccccccccccccc"
};

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Constructor
 *
 * @param [IN] p_parent_wxwindow : Parent window
 * @param [IN] name_str : Graph name
 * @param [IN] min_d : Graph minimum
 * @param [IN] max_d : Graph maximum
 * @param [IN] length_d : buffer length
 * @param [IN] step_d : Sample period step
 * @return void
 *
 */

data_plot::data_plot(wxWindow* p_parent_wxwindow, wxString name_str, double min_d, double max_d, double length_d, double step_d)
{
wxWindow* parent = p_parent_wxwindow;

    this->l_name_str = name_str;
    this->l_max_d = max_d;
    this->l_min_d = min_d;
    this->l_max_default_d = max_d;
    this->l_min_default_d = min_d;
    this->l_length_d = length_d;
    this->l_step_d = step_d;
    this->l_cnt_d = 0.0;
    //(*Initialize(data_plot)
    Create(parent, wxID_ANY, wxPoint(-1,-1), wxDefaultSize, wxALWAYS_SHOW_SB, _T("wxID_ANY"));
    lp_frame_wxboxsizer = new wxBoxSizer(wxVERTICAL);
    lp_name_wxstatictext = new wxStaticText(this, l_id_name_wxstatictext, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("l_id_name_wxstatictext"));
    wxFont lp_name_wxstatictextFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Tahoma"),wxFONTENCODING_DEFAULT);
    lp_name_wxstatictext->SetFont(lp_name_wxstatictextFont);
    lp_frame_wxboxsizer->Add(lp_name_wxstatictext, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_mathplot_setting_wxboxsizer = new wxBoxSizer(wxHORIZONTAL);
    lp_pause_wxtogglebutton = new wxToggleButton(this, l_id_pause_wxtogglebutton, wxEmptyString, wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("l_id_pause_wxtogglebutton"));
    lp_mathplot_setting_wxboxsizer->Add(lp_pause_wxtogglebutton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_zoom_wxbutton = new wxButton(this, l_id_zoom_wxbutton, wxEmptyString, wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("l_id_zoom_wxbutton"));
    lp_mathplot_setting_wxboxsizer->Add(lp_zoom_wxbutton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_zoom_plus_wxbutton = new wxButton(this, l_id_zoom_plus_wxbutton, wxEmptyString, wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("l_id_zoom_plus_wxbutton"));
    lp_mathplot_setting_wxboxsizer->Add(lp_zoom_plus_wxbutton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_zoom_minus_wxbutton = new wxButton(this, l_id_zoom_minus_wxbutton, wxEmptyString, wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("l_id_zoom_minus_wxbutton"));
    lp_mathplot_setting_wxboxsizer->Add(lp_zoom_minus_wxbutton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_legend_wxcheckbox = new wxCheckBox(this, l_id_legend_wxcheckbox, _("Legend"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("l_id_legend_wxcheckbox"));
    lp_legend_wxcheckbox->SetValue(true);
    lp_mathplot_setting_wxboxsizer->Add(lp_legend_wxcheckbox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lp_frame_wxboxsizer->Add(lp_mathplot_setting_wxboxsizer, 0, wxEXPAND, 5);
    lp_mathplot_graph_wxboxsizer = new wxBoxSizer(wxHORIZONTAL);
    lp_graph_mpwindow = new mpWindow(this, l_id_graph_mpwindow, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    lp_x_axis_mpscalex = new mpScaleX(_("Time"), 1, true);
    lp_graph_mpwindow->AddLayer(lp_x_axis_mpscalex);
    lp_y_axis_mpscalex = new mpScaleY(_("Value"), 4, true);
    lp_graph_mpwindow->AddLayer(lp_y_axis_mpscalex);
    lp_graph_mpwindow->UpdateAll();
    lp_graph_mpwindow->Fit();
    lp_mathplot_graph_wxboxsizer->Add(lp_graph_mpwindow, 1, wxEXPAND, 5);
    lp_frame_wxboxsizer->Add(lp_mathplot_graph_wxboxsizer, 1, wxEXPAND, 5);
    lp_grid_wxboxsizer = new wxBoxSizer(wxHORIZONTAL);
    lp_graph_signal_wxgrid = new wxGrid(this, l_id_graph_signal_wxgrid, wxDefaultPosition, wxDefaultSize, 0, _T("l_id_graph_signal_wxgrid"));
    lp_graph_signal_wxgrid->CreateGrid(1,0);
    lp_graph_signal_wxgrid->EnableEditing(true);
    lp_graph_signal_wxgrid->EnableGridLines(true);
    lp_graph_signal_wxgrid->SetDefaultCellFont( lp_graph_signal_wxgrid->GetFont() );
    lp_graph_signal_wxgrid->SetDefaultCellTextColour( lp_graph_signal_wxgrid->GetForegroundColour() );
    lp_grid_wxboxsizer->Add(lp_graph_signal_wxgrid, 1, wxALIGN_LEFT, 5);
    lp_frame_wxboxsizer->Add(lp_grid_wxboxsizer, 0, wxEXPAND, 5);
    SetSizer(lp_frame_wxboxsizer);
    icon_wximagelist = new wxImageList(16, 16, 1);
    lp_frame_wxboxsizer->Fit(this);
    lp_frame_wxboxsizer->SetSizeHints(this);

    Connect(l_id_pause_wxtogglebutton,wxEVT_COMMAND_TOGGLEBUTTON_CLICKED,(wxObjectEventFunction)&data_plot::on_pause_wxtogglebutton_toggle);
    Connect(l_id_zoom_wxbutton,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&data_plot::on_zoom_wxbutton_click);
    Connect(l_id_zoom_plus_wxbutton,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&data_plot::on_zoom_plus_wxbutton_click);
    Connect(l_id_zoom_minus_wxbutton,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&data_plot::on_zoom_minus_wxbutton_click);
    Connect(l_id_legend_wxcheckbox,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&data_plot::on_legend_wxcheckbox_click);
    //*)
    // Set button icon
    this->icon_wximagelist->Add(wxIcon( lp_play_ico_si8 ), wxColor(0xff, 0xff, 0xff));
    this->icon_wximagelist->Add(wxIcon( lp_stop_ico_si8 ), wxColor(0xff, 0xff, 0xff));
    this->icon_wximagelist->Add(wxIcon( lp_zoom_ico_si8 ), wxColor(0xff, 0xff, 0xff));
    this->icon_wximagelist->Add(wxIcon( lp_zoom_plus_ico_si8 ), wxColor(0xff, 0xff, 0xff));
    this->icon_wximagelist->Add(wxIcon( lp_zoom_minus_ico_si8 ), wxColor(0xff, 0xff, 0xff));
    // Set button ico
    this->lp_pause_wxtogglebutton->SetBitmap(icon_wximagelist->GetIcon(0));
    this->lp_pause_wxtogglebutton->SetBitmapPressed(icon_wximagelist->GetIcon(1));
    this->lp_zoom_wxbutton->SetBitmap(icon_wximagelist->GetIcon(2));
    this->lp_zoom_plus_wxbutton->SetBitmap(icon_wximagelist->GetIcon(3));
    this->lp_zoom_minus_wxbutton->SetBitmap(icon_wximagelist->GetIcon(4));
    delete icon_wximagelist;
    // Set graph name
    this->lp_name_wxstatictext->SetLabel(this->l_name_str);
    this->lp_graph_signal_wxgrid->SetRowLabelSize(0);
    this->lp_graph_mpinfolegend = new mpInfoLegend();
    this->lp_graph_mpwindow->AddLayer( this->lp_graph_mpinfolegend );
    this->lp_graph_mpwindow->EnableDoubleBuffer(true);
    this->lp_graph_mpinfolegend->Move(wxPoint(50, 10));
    this->lp_graph_mpinfolegend->SetVisible(true);
    this->time_init();
    this->fit();
    this->l_pause_b = false;
    this->l_sample_cnt_ui32 = 0;
    this->l_zoom_step_d = 0;
    this->l_zoom_cnt_ui32 = 0;
    this->pause(this->l_pause_b);
}

/** @brief Destructor
 *
 * @param void
 * @return void
 *
 */

data_plot::~data_plot(void)
{
    //(*Destroy(data_plot)
    //*)
    this->lv_time_d.clear();
    this->lv_signal_data_plot_buffer.clear();
}

/** @brief Add new plot signal
 *
 * @param [IN] signal_label_str : signal name
 * @param [IN] signal_style_pen : signal style
 * @return void
 *
 */

void data_plot::add(wxString signal_label_str, wxPen signal_style_pen)
{
data_plot_buffer signal_data_plot_buffer;
double data_buffer_cnt_d;

    signal_data_plot_buffer.data_signal_name_str = signal_label_str;
    signal_data_plot_buffer.data_signal_style_pen = signal_style_pen;
    signal_data_plot_buffer.p_buffer_measure_data_polygon = NULL;
    for(data_buffer_cnt_d = 0.0 ; data_buffer_cnt_d <= this->l_length_d ; (data_buffer_cnt_d += this->l_step_d))
    {
        signal_data_plot_buffer.v_buffer_data_plot_d.push_back(0.0);
    }
    // Add signal check box
    signal_data_plot_buffer.p_signal_wxcheckbox = new wxCheckBox(this, wxID_ANY, signal_data_plot_buffer.data_signal_name_str, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_ANY"));
    signal_data_plot_buffer.p_signal_wxcheckbox->SetValue(true);
    signal_data_plot_buffer.p_signal_wxcheckbox->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&data_plot::on_signal_wxcheckbox_click,0,this);
    this->lp_mathplot_setting_wxboxsizer->Add( signal_data_plot_buffer.p_signal_wxcheckbox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Layout();
    this->lv_signal_data_plot_buffer.push_back(signal_data_plot_buffer);
    return;
}

/** @brief Delete signal from math plot
 *
 * @param [IN] signal_label_str : signal name
 * @return void
 *
 */

void data_plot::erase(wxString signal_label_str)
{
uint32_t signal_cnt_ui32;
bool pause_bkp_b = this->l_pause_b;

    for(signal_cnt_ui32 = 0 ; signal_cnt_ui32 < this->get() ; signal_cnt_ui32++)
    {
        if(signal_label_str.IsSameAs(this->lv_signal_data_plot_buffer[signal_cnt_ui32].data_signal_name_str))
        {
            this->pause(true);
            this->show(signal_label_str, false);
            this->lv_signal_data_plot_buffer[signal_cnt_ui32].p_signal_wxcheckbox->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&data_plot::on_signal_wxcheckbox_click,0,this);
            this->lp_mathplot_setting_wxboxsizer->Detach( this->lv_signal_data_plot_buffer[signal_cnt_ui32].p_signal_wxcheckbox);
            delete this->lv_signal_data_plot_buffer[signal_cnt_ui32].p_signal_wxcheckbox;
            this->lp_graph_mpwindow->DelLayer(this->lp_graph_mpwindow->GetLayerByName(signal_label_str));
            this->lv_signal_data_plot_buffer.erase(this->lv_signal_data_plot_buffer.begin() + signal_cnt_ui32);
            Layout();
            this->pause(pause_bkp_b);
        }
    }
    return;
}

/** @brief Return number of signal buffer in graph
 *
 * @param void
 * @return uint32_t : Number of signal buffer
 *
 */

uint32_t data_plot::get(void)
{
    return this->lv_signal_data_plot_buffer.size();
}

/** @brief Set signal data by name
 *
 * @param [IN] signal_label_str : signal name
 * @param [IN] data_d : data
 * @return bool : Set data status
 *
 */

bool data_plot::set(wxString signal_label_str, double data_d)
{
bool status_value_b = false;
uint32_t signal_cnt_ui32;

    if(!this->l_pause_b)
    {
        for(signal_cnt_ui32 = 0 ; signal_cnt_ui32 < this->get() ; signal_cnt_ui32++)
        {
            if(signal_label_str.IsSameAs(this->lv_signal_data_plot_buffer[signal_cnt_ui32].data_signal_name_str))
            {
                if(signal_cnt_ui32 == 0)
                {
                    this->l_sample_cnt_ui32++;
                }
                this->lv_signal_data_plot_buffer[signal_cnt_ui32].v_buffer_data_plot_d.push_back(data_d);
                this->lv_signal_data_plot_buffer[signal_cnt_ui32].v_buffer_data_plot_d.erase(this->lv_signal_data_plot_buffer[signal_cnt_ui32].v_buffer_data_plot_d.begin());
                status_value_b = true;
            }
        }
    }
    return status_value_b;
}

/** @brief Set signal data by index
 *
 * @param [IN] signal_ui32 : signal index
 * @param [IN] data_d : data
 * @return bool : Set data status
 *
 */

bool data_plot::set(uint32_t signal_ui32, double data_d)
{
bool status_value_b = false;

    if(!this->l_pause_b)
    {
        if(signal_ui32 < this->get())
        {
            if(signal_ui32 == 0)
            {
                this->l_sample_cnt_ui32++;
            }
            this->lv_signal_data_plot_buffer[signal_ui32].v_buffer_data_plot_d.push_back(data_d);
            this->lv_signal_data_plot_buffer[signal_ui32].v_buffer_data_plot_d.erase(this->lv_signal_data_plot_buffer[signal_ui32].v_buffer_data_plot_d.begin());
            status_value_b = true;
        }
    }
    return status_value_b;
}

/** @brief Set signal visibility
 *
 * @param [IN] signal_label_str : signal name
 * @param [IN] show_b : Visibility state
 * @return void
 *
 */

void data_plot::show(wxString signal_label_str, bool show_b)
{
uint32_t signal_cnt_ui32;

    for (signal_cnt_ui32 = 0 ; signal_cnt_ui32 < this->get() ; signal_cnt_ui32++)
    {
        if (signal_label_str.IsSameAs(this->lv_signal_data_plot_buffer[signal_cnt_ui32].data_signal_name_str))
        {
            this->lv_signal_data_plot_buffer[signal_cnt_ui32].p_buffer_measure_data_polygon->SetVisible(show_b);
        }
    }
    return;
}

/** @brief Set logged data length and sample period
 *
 * @param [IN] length_d : Buffer length in [S]
 * @param [IN] step_d : Sample period in [S]
 * @return bool : Set parameter status
 *
 */

bool data_plot::set_time(double length_d, double step_d)
{
bool status_value_b = false;
uint32_t signal_cnt_ui32;
bool pause_bkp_b = this->l_pause_b;
double data_buffer_cnt_d;

    this->pause(true);
    // Store data
    this->l_length_d = length_d;
    this->l_step_d = length_d;
    // Update signal data
    for (signal_cnt_ui32 = 0 ; signal_cnt_ui32 < this->get() ; signal_cnt_ui32++)
    {
        this->lv_signal_data_plot_buffer[signal_cnt_ui32].v_buffer_data_plot_d.clear();
        for(data_buffer_cnt_d = 0.0 ; data_buffer_cnt_d <= this->l_length_d ; (data_buffer_cnt_d += this->l_step_d))
        {
            this->lv_signal_data_plot_buffer[signal_cnt_ui32].v_buffer_data_plot_d.push_back(0.0);
        }
        status_value_b = true;
    }
    // Update time axis range
    this->time_init();
    this->pause(pause_bkp_b);
    this->redraw();
    this->fit();
    return status_value_b;
}

/** @brief Set graph range
 *
 * @param [IN] max_d : Maximum fit value for Y axis
 * @param [IN] min_d : Minimum fit value for Y axis
 * @return void
 *
 */

void data_plot::set_range (double max_d, double min_d)
{
    this->l_max_d = max_d;
    this->l_min_d = min_d;
    this->fit();
    return;
}

/** @brief Redraw new data and set time cursor
 *
 * @param void
 * @return void
 *
 */

void data_plot::redraw(void)
{
uint32_t signal_cnt_ui32;
wxString value_text_str;
uint32_t cols_num_ui32;
uint32_t sample_cnt_ui32;

    if (!this->l_pause_b)
    {
        // Add new variable grid cell
        while ((uint32_t)this->lp_graph_signal_wxgrid->GetCols() < this->lv_signal_data_plot_buffer.size())
        {
            cols_num_ui32 = this->lp_graph_signal_wxgrid->GetCols();
            this->lp_graph_signal_wxgrid->AppendCols();
            this->lp_graph_signal_wxgrid->SetColLabelValue(cols_num_ui32, this->lv_signal_data_plot_buffer[cols_num_ui32].data_signal_name_str);
        }
        for (signal_cnt_ui32 = 0 ; signal_cnt_ui32 < this->get() ; signal_cnt_ui32++)
        {
            if (this->lv_signal_data_plot_buffer[signal_cnt_ui32].p_buffer_measure_data_polygon == NULL)
            {
                this->lp_graph_mpwindow->AddLayer( this->lv_signal_data_plot_buffer[signal_cnt_ui32].p_buffer_measure_data_polygon = new mpPolygon(this->lv_signal_data_plot_buffer[signal_cnt_ui32].data_signal_name_str) );
                this->lv_signal_data_plot_buffer[signal_cnt_ui32].p_buffer_measure_data_polygon->SetPen( this->lv_signal_data_plot_buffer[signal_cnt_ui32].data_signal_style_pen );
                this->lv_signal_data_plot_buffer[signal_cnt_ui32].p_buffer_measure_data_polygon->ShowName(false);
            }
            this->lv_signal_data_plot_buffer[signal_cnt_ui32].p_buffer_measure_data_polygon->setPoints(this->lv_time_d, this->lv_signal_data_plot_buffer[signal_cnt_ui32].v_buffer_data_plot_d, false );
            // set text value
            value_text_str.Printf("%f",(float)this->lv_signal_data_plot_buffer[signal_cnt_ui32].v_buffer_data_plot_d.at(this->lv_signal_data_plot_buffer[signal_cnt_ui32].v_buffer_data_plot_d.size() - 1));
            value_text_str.Replace(wxT(".000000"), wxT(""),true);
            this->lp_graph_signal_wxgrid->SetCellValue(value_text_str, 0, signal_cnt_ui32);
        }
        this->lp_graph_mpwindow->SetPosX(this->lv_time_d[0]);
        // Add time sample
        for(sample_cnt_ui32 = 0 ; sample_cnt_ui32 < this->l_sample_cnt_ui32 ; sample_cnt_ui32++)
        {
            // Time increment
            this->l_cnt_d += this->l_step_d;
            this->lv_time_d.push_back(this->l_cnt_d);
            this->lv_time_d.erase(this->lv_time_d.begin());
        }
        // Clear sample counter
        this->l_sample_cnt_ui32 = 0;
    }
    return;
}

/** @brief Set graph in to default zoom
 *
 * @param [IN] default_b : Fit type
 *    @arg true : Default fit
 *    @arg false : Automatic fit
 * @return void
 *
 */

void data_plot::fit(bool default_b)
{
uint32_t signal_cnt_ui32;
uint32_t data_cnt_ui32;
double max_d;
double min_d;

    if (default_b)
    {
        this->lp_graph_mpwindow->Fit(this->lv_time_d[0], this->lv_time_d[this->lv_time_d.size()], this->l_min_default_d,this->l_max_default_d);
    }
    else
    {
        //this->lp_graph_mpwindow->Fit();
        if(this->lv_signal_data_plot_buffer.size())
        {
            // Set initialization data
            this->l_max_d = this->lv_signal_data_plot_buffer[0].v_buffer_data_plot_d[0];
            this->l_min_d = this->l_max_d;
            // Find data min and max
            for(signal_cnt_ui32 = 0 ; signal_cnt_ui32 < this->lv_signal_data_plot_buffer.size() ; signal_cnt_ui32++)
            {
                if(this->lv_signal_data_plot_buffer[signal_cnt_ui32].p_signal_wxcheckbox->IsChecked())
                {
                    for(data_cnt_ui32 = 0 ; data_cnt_ui32 < this->lv_signal_data_plot_buffer[signal_cnt_ui32].v_buffer_data_plot_d.size() ; data_cnt_ui32++)
                    {
                        // Find max
                        if (this->l_max_d < this->lv_signal_data_plot_buffer[signal_cnt_ui32].v_buffer_data_plot_d[data_cnt_ui32])
                        {
                            this->l_max_d = this->lv_signal_data_plot_buffer[signal_cnt_ui32].v_buffer_data_plot_d[data_cnt_ui32];
                        }
                        // Find min
                        if (this->l_min_d > this->lv_signal_data_plot_buffer[signal_cnt_ui32].v_buffer_data_plot_d[data_cnt_ui32])
                        {
                            this->l_min_d = this->lv_signal_data_plot_buffer[signal_cnt_ui32].v_buffer_data_plot_d[data_cnt_ui32];
                        }
                    }
                }
            }
            this->l_zoom_step_d = ((this->l_max_d - this->l_min_d) / 100);
            max_d = (this->l_max_d + (this->l_zoom_cnt_ui32 * this->l_zoom_step_d));
            min_d = (this->l_min_d - (this->l_zoom_cnt_ui32 * this->l_zoom_step_d));
            // Set view
            this->lp_graph_mpwindow->Fit(this->lv_time_d[0], this->lv_time_d[this->lv_time_d.size()], min_d, max_d);
        }
    }
    return;
}

/** @brief Redraw data pause
 *
 * @param [IN] pause_b : Pause status
 *    @arg true : Show data is stopped
 *    @arg false : Show data is refreshed
 * @return void
 *
 */

void data_plot::pause(bool pause_b)
{
    this->l_pause_b = pause_b;
    this->lp_pause_wxtogglebutton->SetValue(pause_b);
    return;
}

/**
  ****************************************************************************
  * Local function
  ****************************************************************************
  */

/** @brief Initialize time axis
 *
 * @param void
 * @return void
 *
 */

void data_plot::time_init(void)
{
double data_buffer_cnt_d;

    // Clear buffer
    this->lv_time_d.clear();
    // Initialization time base
    for(data_buffer_cnt_d = (-this->l_length_d) ; data_buffer_cnt_d <= 0.0 ; (data_buffer_cnt_d += this->l_step_d))
    {
        this->lv_time_d.push_back(data_buffer_cnt_d);
    }
    return;
}

/** @brief Show or hide selected signal in math plot event
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void data_plot::on_signal_wxcheckbox_click(wxCommandEvent& event)
{
uint32_t signal_cnt_ui32;

    for (signal_cnt_ui32 = 0 ; signal_cnt_ui32 < this->get() ; signal_cnt_ui32++)
    {
        this->show(this->lv_signal_data_plot_buffer[signal_cnt_ui32].data_signal_name_str, this->lv_signal_data_plot_buffer[signal_cnt_ui32].p_signal_wxcheckbox->GetValue());
    }
    this->lp_graph_mpwindow->SetPosX(this->lv_time_d[0]);
    return;
}

/** @brief Fit graph window to default zoom event
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void data_plot::on_zoom_wxbutton_click(wxCommandEvent& event)
{
    this->fit();
    return;
}

/** @brief Zoom graph in
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void data_plot::on_zoom_plus_wxbutton_click(wxCommandEvent& event)
{
    if(this->l_zoom_cnt_ui32)
    {
        this->l_zoom_cnt_ui32--;
    }
    this->fit(false);
    return;
}

/** @brief Zoom graph out
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void data_plot::on_zoom_minus_wxbutton_click(wxCommandEvent& event)
{
    this->l_zoom_cnt_ui32++;
    this->fit(false);
    return;
}

/** @brief Pause data show event
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void data_plot::on_pause_wxtogglebutton_toggle(wxCommandEvent& event)
{
    this->pause((bool)event.GetSelection());
    return;
}

/** @brief Show or hide data legend event
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void data_plot::on_legend_wxcheckbox_click(wxCommandEvent& event)
{
    this->lp_graph_mpinfolegend->SetVisible((bool)event.GetSelection());
    this->lp_graph_mpwindow->SetPosX(this->lv_time_d[0]);
    return;
}

/**
* @}
*/

/**
* @}
*/

/***********************************************************END OF FILE************/
