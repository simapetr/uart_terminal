/**
  ****************************************************************************
  * @file    in_jerryscript_editor_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    28.03.2020
  * @brief   JerryScript file editor panel
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

#include "in_jerryscript_editor_h.h"

//(*InternalHeaders(editor)
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include <wx/msgdlg.h>
#include <wx/icon.h>
#include <wx/filename.h>
#include <Lmcons.h>

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @defgroup JerryScript
  * @brief JavaScript interpret
  * @{
  */

/**
  * @defgroup Editor
  * @brief JavaScript text file editor
  * @{
  */

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

#include "lp_play_xpm.xpm"
#include "lp_stop_xpm.xpm"
#include "lp_open_xpm.xpm"
#include "lp_save_xpm.xpm"
#include "lp_saveas_xpm.xpm"
#include "lp_find_xpm.xpm"
#include "lp_replace_xpm.xpm"
#include "lp_new_xpm.xpm"
#include "lp_new_template_xpm.xpm"

//(*IdInit(editor)
const long editor::l_id_save_wxbutton = wxNewId();
const long editor::l_id_save_as_wxbutton = wxNewId();
const long editor::l_id_new_wxbutton = wxNewId();
const long editor::l_id_new_template_wxbutton = wxNewId();
const long editor::l_id_open_wxbutton = wxNewId();
const long editor::l_id_file_wxstaticline = wxNewId();
const long editor::l_id_search_wxbutton = wxNewId();
const long editor::l_id_replace_wxbutton = wxNewId();
const long editor::l_id_search_wxstaticline = wxNewId();
const long editor::l_id_script_run_wxtogglebutton = wxNewId();
const long editor::l_id_main_text_edit = wxNewId();
const long editor::l_id_edit_event_wxtimer = wxNewId();
//*)

/**
  ****************************************************************************
  * Event table
  ****************************************************************************
  */

BEGIN_EVENT_TABLE(editor,wxPanel)
	//(*EventTable(editor)
	//*)
END_EVENT_TABLE()

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Constructor
 *
 * @param [IN] p_parent_wxwindow : Parent window
 * @param [IN] text_wxwindowid : Parent window ID string
 * @param [IN] pos_wxpoint : Parent window
 * @param [IN] panel_wxsize : Panle size
 * @param [IN] style_ui32 : Panel style
 * @return void
 *
 */

editor::editor(wxWindow *p_parent_wxwindow, wxWindowID text_wxwindowid, const wxPoint &pos_wxpoint, const wxSize &panel_wxsize, uint32_t style_ui32)
{
wxWindow *parent = p_parent_wxwindow;

    this->lp_parent_wxwindow = p_parent_wxwindow;
	//(*Initialize(editor)
	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(490,192), wxBORDER_NONE|wxTAB_TRAVERSAL, _T("wxID_ANY"));
	lp_main_wxboxsizer = new wxBoxSizer(wxVERTICAL);
	lp_tool_wxboxsizer = new wxBoxSizer(wxHORIZONTAL);
	lp_save_wxbutton = new wxButton(this, l_id_save_wxbutton, wxEmptyString, wxDefaultPosition, wxSize(23,23), wxBORDER_NONE, wxDefaultValidator, _T("l_id_save_wxbutton"));
	lp_save_wxbutton->Disable();
	lp_tool_wxboxsizer->Add(lp_save_wxbutton, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lp_save_as_wxbutton = new wxButton(this, l_id_save_as_wxbutton, wxEmptyString, wxDefaultPosition, wxSize(23,23), wxBORDER_NONE, wxDefaultValidator, _T("l_id_save_as_wxbutton"));
	lp_tool_wxboxsizer->Add(lp_save_as_wxbutton, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lp_new_wxbutton = new wxButton(this, l_id_new_wxbutton, wxEmptyString, wxDefaultPosition, wxSize(23,23), wxBORDER_NONE, wxDefaultValidator, _T("l_id_new_wxbutton"));
	lp_tool_wxboxsizer->Add(lp_new_wxbutton, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lp_new_template_wxbutton = new wxButton(this, l_id_new_template_wxbutton, wxEmptyString, wxDefaultPosition, wxSize(23,23), wxBORDER_NONE, wxDefaultValidator, _T("l_id_new_template_wxbutton"));
	lp_tool_wxboxsizer->Add(lp_new_template_wxbutton, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lp_open_wxbutton = new wxButton(this, l_id_open_wxbutton, wxEmptyString, wxDefaultPosition, wxSize(23,23), wxBORDER_NONE, wxDefaultValidator, _T("l_id_open_wxbutton"));
	lp_tool_wxboxsizer->Add(lp_open_wxbutton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lp_file_wxstaticline = new wxStaticLine(this, l_id_file_wxstaticline, wxDefaultPosition, wxSize(1,23), wxLI_HORIZONTAL, _T("l_id_file_wxstaticline"));
	lp_tool_wxboxsizer->Add(lp_file_wxstaticline, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lp_search_wxbutton = new wxButton(this, l_id_search_wxbutton, wxEmptyString, wxDefaultPosition, wxSize(23,23), wxBORDER_NONE, wxDefaultValidator, _T("l_id_search_wxbutton"));
	lp_tool_wxboxsizer->Add(lp_search_wxbutton, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lp_replace_wxbutton = new wxButton(this, l_id_replace_wxbutton, wxEmptyString, wxDefaultPosition, wxSize(23,23), wxBORDER_NONE, wxDefaultValidator, _T("l_id_replace_wxbutton"));
	lp_tool_wxboxsizer->Add(lp_replace_wxbutton, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lp_search_wxstaticline = new wxStaticLine(this, l_id_search_wxstaticline, wxDefaultPosition, wxSize(1,23), wxLI_HORIZONTAL, _T("l_id_search_wxstaticline"));
	lp_tool_wxboxsizer->Add(lp_search_wxstaticline, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lp_script_run_wxtogglebutton = new wxToggleButton(this, l_id_script_run_wxtogglebutton, wxEmptyString, wxDefaultPosition, wxSize(23,23), wxBORDER_NONE, wxDefaultValidator, _T("l_id_script_run_wxtogglebutton"));
	lp_tool_wxboxsizer->Add(lp_script_run_wxtogglebutton, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lp_main_wxboxsizer->Add(lp_tool_wxboxsizer, 0, wxEXPAND, 5);
	lp_main_text_edit = new text_edit_c(this,l_id_main_text_edit,wxDefaultPosition,wxDefaultSize);
	lp_main_wxboxsizer->Add(lp_main_text_edit, 1, wxEXPAND, 5);
	SetSizer(lp_main_wxboxsizer);
	lp_script_wxfiledialog = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE|wxFD_OPEN, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
	lp_edit_event_wxtimer.SetOwner(this, l_id_edit_event_wxtimer);
	lp_edit_event_wxtimer.Start(50, false);
		// NOTE: In order for events to connect properly you must set the ID of this wxFindReplaceDialog to -1 in wxSmith.
	lp_text_wxfindreplacedialog = new wxFindReplaceDialog(this, &findReplaceData_1, _("Search"), 0);
	SetSizer(lp_main_wxboxsizer);
	Layout();

	Connect(l_id_save_wxbutton,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&editor::on_save_wxbutton_click);
	Connect(l_id_save_as_wxbutton,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&editor::on_save_as_wxbutton_click);
	Connect(l_id_new_wxbutton,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&editor::on_new_wxbutton_click);
	Connect(l_id_new_template_wxbutton,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&editor::on_new_template_wxbutton_click);
	Connect(l_id_open_wxbutton,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&editor::on_open_wxbutton_click);
	Connect(l_id_search_wxbutton,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&editor::on_search_wxbutton_click);
	Connect(l_id_replace_wxbutton,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&editor::on_replace_wxbutton_click);
	Connect(l_id_script_run_wxtogglebutton,wxEVT_COMMAND_TOGGLEBUTTON_CLICKED,(wxObjectEventFunction)&editor::on_script_run_wxtogglebutton_toggle);
	Connect(l_id_edit_event_wxtimer,wxEVT_TIMER,(wxObjectEventFunction)&editor::on_edit_event_wxtimer_trigger);
	Connect(wxID_ANY,wxEVT_COMMAND_FIND,(wxObjectEventFunction)&editor::on_text_wxfindreplacedialog_find);
	Connect(wxID_ANY,wxEVT_COMMAND_FIND_NEXT,(wxObjectEventFunction)&editor::on_text_wxfindreplacedialog_findnext);
	Connect(wxID_ANY,wxEVT_COMMAND_FIND_REPLACE,(wxObjectEventFunction)&editor::on_text_wxfindreplacedialog_replace);
	Connect(wxID_ANY,wxEVT_COMMAND_FIND_REPLACE_ALL,(wxObjectEventFunction)&editor::on_text_wxfindreplacedialog_replaceall);
	Connect(wxID_ANY,wxEVT_COMMAND_FIND_CLOSE,(wxObjectEventFunction)&editor::on_text_wxfindreplacedialog_close);
	//*)
	// Set button icon
	this->lp_save_wxbutton->SetBitmap(wxIcon(lp_save_si8));
	this->lp_save_as_wxbutton->SetBitmap(wxIcon(lp_saveas_si8));
	this->lp_new_wxbutton->SetBitmap(wxIcon(lp_new_si8));
	this->lp_new_template_wxbutton->SetBitmap(wxIcon(lp_new_template_si8));
	this->lp_search_wxbutton->SetBitmap(wxIcon(lp_find_si8));
	this->lp_replace_wxbutton->SetBitmap(wxIcon(lp_replace_si8));
    this->lp_open_wxbutton->SetBitmap(wxIcon(lp_open_si8));
    this->lp_script_run_wxtogglebutton->SetBitmap(wxIcon(lp_play_si8));
    this->lp_script_run_wxtogglebutton->SetBitmapPressed(wxIcon(lp_stop_si8));
    // Initialize event function
    this->l_main_editor_event_buffer[e_start].data_editor_event_fct = NULL;
    this->l_main_editor_event_buffer[e_path].data_editor_event_fct = NULL;
    return;
}

/** @brief Destructor
 *
 * @param void
 * @return void
 *
 */

editor::~editor()
{
    // Save script
    if(this->lp_main_text_edit->IsModified())
    {
        if(wxMessageBox(wxT("Script is modified Do you want save it?"), wxT("Save change"), (wxYES_NO | wxCANCEL | wxICON_INFORMATION)) == wxYES)
        {
            this->save();
        }
    }
	//(*Destroy(editor)
	//*)
    return;
}

/** @brief Load file
 *
 * @param void
 * @return void
 *
 */

void editor::load(void)
{
static wxString path_str;

    this->lp_script_wxfiledialog->SetWindowStyleFlag(wxFD_OPEN);
    this->lp_script_wxfiledialog->SetMessage(wxT("Open file"));
    this->lp_script_wxfiledialog->SetWildcard(wxT("JavaScript (*.js)|*.js"));
    if (this->lp_script_wxfiledialog->ShowModal() == wxID_OK)
    {
        if (this->lp_script_wxfiledialog->GetPath() != wxEmptyString)
        {
            // Open in editor
            this->load(this->lp_script_wxfiledialog->GetPath());
        }
    }
    return;
}

/** @brief Load file
 *
 * @param [IN] path_str : File path
 * @return void
 *
 */

void editor::load(wxString path_str)
{
    // Load file
    if(path_str != wxEmptyString)
    {
        this->lp_main_text_edit->load(path_str);
    }
    // Set path
    if(this->l_main_editor_event_buffer[e_path].data_editor_event_fct)
    {
        this->l_main_editor_event_buffer[e_path].data_editor_event_fct(this->l_main_editor_event_buffer[e_path].p_parametr_void, (uint8_t*)&path_str, sizeof(wxString*));
    }
    this->l_file_path_str = path_str;
    return;
}

/** @brief Save file
 *
 * @param void
 * @return void
 *
 */

void editor::save(void)
{
    if(this->l_file_path_str != wxEmptyString)
    {
        this->lp_main_text_edit->save(this->l_file_path_str);
    }
    return;
}

/** @brief Save file as
 *
 * @param void
 * @return bool : Status
 *
 */

bool editor::save_as(void)
{
bool status_b = false;

    this->lp_script_wxfiledialog->SetWindowStyleFlag(wxFD_SAVE);
    this->lp_script_wxfiledialog->SetMessage(wxT("Save file"));
    this->lp_script_wxfiledialog->SetWildcard(wxT("JavaScript (*.js)|*.js"));
    if (this->lp_script_wxfiledialog->ShowModal() == wxID_OK)
    {
        if (this->lp_script_wxfiledialog->GetPath() != wxEmptyString)
        {
            // Set new path
            this->l_file_path_str = this->lp_script_wxfiledialog->GetPath();
            // Save to new file
            this->lp_main_text_edit->save(this->l_file_path_str);
            this->load(this->l_file_path_str);
            status_b = true;
        }
    }
    return status_b;
}

/** @brief Find dialog show
 *
 * @param void
 * @return void
 *
 */

void editor::find(void)
{
    // Set flag
    this->findReplaceData_1.SetFlags(wxFR_DOWN);
    // Open find dialog
	if(this->lp_text_wxfindreplacedialog)
    {
        this->lp_text_wxfindreplacedialog->Show(false);
        delete this->lp_text_wxfindreplacedialog;
        this->lp_text_wxfindreplacedialog = NULL;
        this->lp_text_wxfindreplacedialog = new wxFindReplaceDialog(this, &this->findReplaceData_1, _("Search"), 0);
        this->lp_text_wxfindreplacedialog->Show();
    }
    else
    {
        this->lp_text_wxfindreplacedialog = new wxFindReplaceDialog(this, &this->findReplaceData_1, _("Search"), 0);
        this->lp_text_wxfindreplacedialog->Show();
    }
    return;
}

/** @brief Find next word
 *
 * @param void
 * @return void
 *
 */

void editor::find_next(void)
{
int flag_int = this->findReplaceData_1.GetFlags();

    flag_int |= wxFR_DOWN;
    this->findReplaceData_1.SetFlags(flag_int);
    if(this->lp_text_wxfindreplacedialog)
    {
        this->lp_text_wxfindreplacedialog->SetData(&this->findReplaceData_1);
    }
    this->find_from(this->findReplaceData_1.GetFindString(), this->l_find_index_int, flag_int);
    return;
}

/** @brief Find previous word
 *
 * @param void
 * @return void
 *
 */

void editor::find_prev(void)
{
int flag_int = this->findReplaceData_1.GetFlags();

    flag_int &= (int)~((int)wxFR_DOWN);
    this->findReplaceData_1.SetFlags(flag_int);
    if(this->lp_text_wxfindreplacedialog)
    {
        this->lp_text_wxfindreplacedialog->SetData(&this->findReplaceData_1);
    }
    this->find_from(this->findReplaceData_1.GetFindString(), this->l_find_index_int, flag_int);
    return;
}

/** @brief Replace dialog show
 *
 * @param void
 * @return void
 *
 */

void editor::replace(void)
{
    // Set flag
    this->findReplaceData_1.SetFlags(wxFR_DOWN | wxFR_WHOLEWORD | wxFR_MATCHCASE);
    this->findReplaceData_1.SetFindString(this->lp_main_text_edit->GetSelectedText());
    this->findReplaceData_1.SetReplaceString(wxEmptyString);
    // Open replace dialog
    if(this->lp_text_wxfindreplacedialog)
    {
        this->lp_text_wxfindreplacedialog->Show(false);
        delete this->lp_text_wxfindreplacedialog;
        this->lp_text_wxfindreplacedialog = NULL;
        this->lp_text_wxfindreplacedialog = new wxFindReplaceDialog(this, &this->findReplaceData_1, _("Replace"), wxFR_REPLACEDIALOG);
        this->lp_text_wxfindreplacedialog->Show();
    }
    else
    {
        this->lp_text_wxfindreplacedialog = new wxFindReplaceDialog(this, &this->findReplaceData_1, _("Replace"), wxFR_REPLACEDIALOG);
        this->lp_text_wxfindreplacedialog->Show();
    }
    return;
}

/** @brief Replace dialog show
 *
 * @param void
 * @return void
 *
 */

void editor::goto_line(void)
{
int line_int = 0;

    this->lp_data_wxtextentrydialog = new wxTextEntryDialog(this , wxString::Format("Line (0 - %u)", this->lp_main_text_edit->GetLineCount()), wxT("Goto line"), wxEmptyString, wxOK|wxCANCEL|wxCENTRE|wxWS_EX_VALIDATE_RECURSIVELY, wxDefaultPosition);
    if (this->lp_data_wxtextentrydialog->ShowModal() == wxID_OK)
    {
        wxSscanf(this->lp_data_wxtextentrydialog->GetValue(), "%d",&line_int);
        this->goto_line((int32_t)line_int);
    }
    return;
}

/** @brief New file
 *
 * @param void
 * @return void
 *
 */

void editor::new_file(void)
{
    if(this->save_as())
    {
        this->lp_main_text_edit->SetText(wxEmptyString);
        this->save();
    }
    return;
}

/** @brief New template file
 *
 * @param void
 * @return void
 *
 */

void editor::new_template(void)
{
wxString template_str;
TCHAR username_tchar[257];
DWORD size_dword = 256;
wxFileName doc_wxfilename;
wxDateTime value_wxdatetime;

    if(this->save_as())
    {
        // set path
        doc_wxfilename.Assign(this->l_file_path_str);
        // Set template data
        template_str = wxT("/**\n");
        template_str += wxT("  ****************************************************************************\n");
        template_str += wxString::Format("  * @file %s\n", doc_wxfilename.GetFullName().To8BitData().data());
        // Get logged user name
        if(GetUserName((TCHAR*)username_tchar, &size_dword))
        {
            template_str += wxString::Format("  * @author %s\n", username_tchar);
        }
        else
        {
            template_str += wxT("  * @author \n");
        }
        template_str += wxT("  * @version V1.0\n");
        // Get date
        value_wxdatetime.Set((time_t)wxGetUTCTime());
        template_str += wxString::Format("  * @date %02u.%02u.%04u\n", value_wxdatetime.GetDay(0), (value_wxdatetime.GetMonth(0) + 1), value_wxdatetime.GetYear(0));
        template_str += wxT("  * @brief \n");
        template_str += wxT("  ****************************************************************************\n");
        template_str += wxT("  * @attention\n");
        template_str += wxT("  * <h2><center>&copy; ");
        template_str += this->get_organization();
        template_str += wxT(" </center></h2>\n");
        template_str += wxT("  ****************************************************************************\n");
        template_str += wxT("  */\n");
        template_str += wxT("\n");
        template_str += wxT("/**\n");
        template_str += wxT("  ****************************************************************************\n");
        template_str += wxT("  * Variable\n");
        template_str += wxT("  ****************************************************************************\n");
        template_str += wxT("  */\n");
        template_str += wxT("\n");
        template_str += wxT("\n");
        template_str += wxT("\n");
        template_str += wxT("/**\n");
        template_str += wxT("  ****************************************************************************\n");
        template_str += wxT("  * Initialize\n");
        template_str += wxT("  ****************************************************************************\n");
        template_str += wxT("  */\n");
        template_str += wxT("\n");
        template_str += wxT("// Register exit function\n");
        template_str += wxT("reg_exit(\"exit\");\n");
        template_str += wxT("setup();\n");
        template_str += wxT("\n");
        template_str += wxT("/**\n");
        template_str += wxT("  ****************************************************************************\n");
        template_str += wxT("  * Function\n");
        template_str += wxT("  ****************************************************************************\n");
        template_str += wxT("  */\n");
        template_str += wxT("\n");
        template_str += wxT("/** @brief Setup\n");
        template_str += wxT(" *\n");
        template_str += wxT(" * @param\n");
        template_str += wxT(" * @return\n");
        template_str += wxT(" *\n");
        template_str += wxT(" */\n");
        template_str += wxT("\n");
        template_str += wxT("function setup()\n");
        template_str += wxT("{\n");
        template_str += wxT("}\n");
        template_str += wxT("\n");
        template_str += wxT("/** @brief Exit event\n");
        template_str += wxT(" *\n");
        template_str += wxT(" * @param\n");
        template_str += wxT(" * @return\n");
        template_str += wxT(" *\n");
        template_str += wxT(" */\n");
        template_str += wxT("\n");
        template_str += wxT("function exit()\n");
        template_str += wxT("{\n");
        template_str += wxT("}\n");
        // Write footer
        template_str += wxT("\n/*****************************************************END OF FILE************/\n");
        this->lp_main_text_edit->SetText(template_str);
        this->save();
    }
    return;
}

/** @brief Set event function
 *
 * @param [IN] type_ui8 : Event type
 *   @arg e_start : Script start
 *   @arg e_path : Set script path
 * @param [IN] p_parametr_void : File path
 * @param [IN] data_editor_event_fct : File path
 * @return void
 *
 */

void editor::set(uint8_t type_ui8, void* p_parametr_void, editor_event_fct data_editor_event_fct)
{
    if(type_ui8 <= e_path)
    {
        this->l_main_editor_event_buffer[type_ui8].p_parametr_void = p_parametr_void;
        this->l_main_editor_event_buffer[type_ui8].data_editor_event_fct = data_editor_event_fct;
    }
    return;
}

/** @brief Get cursor position
 *
 * @param void
 * @return wxString : Cursor position string
 *
 */

wxString editor::get(void)
{
wxString pos_str;
int pos_int = lp_main_text_edit->GetCurrentPos();
int line_int = (lp_main_text_edit->GetCurrentLine() + 1);
int col_int = (lp_main_text_edit->GetLineLength(lp_main_text_edit->GetCurrentLine()) - (lp_main_text_edit->GetLineEndPosition(lp_main_text_edit->GetCurrentLine()) - pos_int));

    pos_str.Printf("Line %d, Col %d, Pos %d ", line_int, col_int, pos_int);
    return pos_str;
}

/** @brief Set run button state
 *
 * @param [IN] status_b : Run state
 *   @arg true : Run
 *   @arg false : Stop
 * @return void
 *
 */

void editor::run(bool status_b)
{
    if (status_b)
    {
        this->lp_script_run_wxtogglebutton->SetValue(true);
    }
    else
    {
        this->lp_script_run_wxtogglebutton->SetValue(false);
    }
    return;
}

/**
  ****************************************************************************
  * Private function
  ****************************************************************************
  */

/** @brief Find word and set view
 *
 * @param [IN] event : Event parameter
 * @return bool : find status
 *
 */

bool editor::find_from(wxString text_str, int pos_int, int flag_int)
{
bool status_b = false;
int find_flag_int = 0;

    this->l_find_index_int = pos_int;
    if(flag_int & wxFR_WHOLEWORD)
    {
        find_flag_int += wxSTC_FIND_WHOLEWORD;
    }
    if(flag_int & wxFR_MATCHCASE)
    {
        find_flag_int += wxSTC_FIND_MATCHCASE;
    }
    if(flag_int & wxFR_DOWN)
    {
        // Check find next
        if(this->lp_main_text_edit->GetSelectedText().IsSameAs(text_str, false))
        {
            this->l_find_index_int += text_str.size();
        }
        this->l_find_index_int = this->lp_main_text_edit->FindText(this->l_find_index_int, this->lp_main_text_edit->GetLength(), text_str, find_flag_int);
    }
    else
    {
        // Check find next
        if(this->lp_main_text_edit->GetSelectedText().IsSameAs(text_str, false))
        {
            this->l_find_index_int -= 1;
        }
        this->l_find_index_int = this->lp_main_text_edit->FindText(this->l_find_index_int, 0, text_str, find_flag_int);
    }
    if(this->l_find_index_int != wxSTC_INVALID_POSITION)
    {
        this->lp_main_text_edit->SetCurrentPos(this->l_find_index_int);
        this->lp_main_text_edit->SetFirstVisibleLine(this->lp_main_text_edit->GetCurrentLine());
        this->lp_main_text_edit->SetSelection(this->l_find_index_int, (this->l_find_index_int + text_str.size()));
        this->lp_main_text_edit->text_highlight();
        status_b = true;
    }
    return status_b;
}

/** @brief Go to line
 *
 * @param [IN] line_i32 : Line number
 * @return void
 *
 */

void editor::goto_line(int32_t line_i32)
{
    if((int)line_i32 > this->lp_main_text_edit->GetLineCount())
    {
        line_i32 = this->lp_main_text_edit->GetLineCount();
    }
    if(line_i32)
    {
        line_i32--;
    }
    this->lp_main_text_edit->SetFirstVisibleLine((int)line_i32);
    return;
}

/** @brief Get organization name from win reg
 *
 * @param void
 * @return string : Pointer on available port array
 *
 */

wxString editor::get_organization(void)
{
wxString data_str = wxEmptyString;
HKEY registry_hkey;
LONG registry_read_res_long;
WCHAR szBuffer[512];
DWORD dwBufferSize = sizeof(szBuffer);

    // Open reg
    registry_read_res_long = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ, &registry_hkey);
    // Get the class name and the value count.
    if (ERROR_SUCCESS == registry_read_res_long)
    {
        registry_read_res_long = RegQueryValueExW(registry_hkey, L"RegisteredOrganization", 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
        if (ERROR_SUCCESS == registry_read_res_long)
        {
            data_str.Printf("%s", szBuffer);
        }
        // Close reg
        RegCloseKey(registry_hkey);
    }
    return data_str;
}

/** @brief Save document event
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void editor::on_save_wxbutton_click(wxCommandEvent& event)
{
    this->save();
    return;
}

/** @brief Save as document event
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void editor::on_save_as_wxbutton_click(wxCommandEvent& event)
{
    this->save_as();
    return;
}

/** @brief Create new document event
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void editor::on_new_wxbutton_click(wxCommandEvent& event)
{
    // Save to new file
    this->new_file();
    return;
}

/** @brief Create new template document event
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void editor::on_new_template_wxbutton_click(wxCommandEvent& event)
{
    this->new_template();
    return;
}

/** @brief Open document event
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void editor::on_open_wxbutton_click(wxCommandEvent& event)
{
    this->load();
    return;
}

/** @brief Script run event
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void editor::on_script_run_wxtogglebutton_toggle(wxCommandEvent& event)
{
uint8_t data_ui8;

    // Save file
    if(this->lp_main_text_edit->IsModified() && (this->lp_script_run_wxtogglebutton->GetValue()))
    {
        this->save();
    }
    // Run script
    if(this->l_main_editor_event_buffer[e_start].data_editor_event_fct)
    {
        data_ui8 = this->lp_script_run_wxtogglebutton->GetValue();
        this->lp_script_run_wxtogglebutton->SetValue(this->l_main_editor_event_buffer[e_start].data_editor_event_fct(this->l_main_editor_event_buffer[e_start].p_parametr_void, &data_ui8, 1));
    }
    return;
}

/** @brief Script run event
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void editor::on_edit_event_wxtimer_trigger(wxTimerEvent& event)
{
static bool mod_state_b = false;

    if(mod_state_b != this->lp_main_text_edit->IsModified())
    {
        mod_state_b = this->lp_main_text_edit->IsModified();
        if(mod_state_b)
        {
            lp_save_wxbutton->Enable();
        }
        else
        {
            lp_save_wxbutton->Disable();
        }
    }
    return;
}

/** @brief Search in file event
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void editor::on_search_wxbutton_click(wxCommandEvent& event)
{
    this->find();
    return;
}

/** @brief Repalce in file event
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void editor::on_replace_wxbutton_click(wxCommandEvent& event)
{
    this->replace();
    return;
}

/** @brief Find dialog event close
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void editor::on_text_wxfindreplacedialog_close(wxFindDialogEvent& event)
{
    if(this->lp_text_wxfindreplacedialog)
    {
        this->lp_text_wxfindreplacedialog->Show(false);
        delete this->lp_text_wxfindreplacedialog;
        this->lp_text_wxfindreplacedialog = NULL;
    }
    return;
}

/** @brief Find dialog event find
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void editor::on_text_wxfindreplacedialog_find(wxFindDialogEvent& event)
{
    this->find_from(event.GetFindString(), this->lp_main_text_edit->GetCurrentPos(), event.GetFlags());
    return;
}

/** @brief Find dialog event find next
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void editor::on_text_wxfindreplacedialog_findnext(wxFindDialogEvent& event)
{
    this->find_from(event.GetFindString(), this->l_find_index_int, event.GetFlags());
    return;
}

/** @brief Find dialog event replace
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void editor::on_text_wxfindreplacedialog_replace(wxFindDialogEvent& event)
{
    if(this->find_from(event.GetFindString(), this->lp_main_text_edit->GetCurrentPos(), event.GetFlags()))
    {
        this->lp_main_text_edit->ReplaceSelection(event.GetReplaceString());
        this->lp_main_text_edit->SetSelection(this->l_find_index_int, (this->l_find_index_int + event.GetReplaceString().size()));
    }
    return;
}

/** @brief Find dialog event replace all
 *
 * @param [IN] event : Event parameter
 * @return void
 *
 */

void editor::on_text_wxfindreplacedialog_replaceall(wxFindDialogEvent& event)
{
    while(this->find_from(event.GetFindString(), 0, event.GetFlags()))
    {
        this->lp_main_text_edit->ReplaceSelection(event.GetReplaceString());
    }
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
