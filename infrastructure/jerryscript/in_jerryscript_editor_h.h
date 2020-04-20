#ifndef IN_JERRYSCRIPT_EDITOR_H_H_INCLUDED
#define IN_JERRYSCRIPT_EDITOR_H_H_INCLUDED

/**
  ****************************************************************************
  * @file    in_jerryscript_editor_h.h
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

//(*Headers(editor)
#include <in_js_edit_text_h.h>
#include <wx/button.h>
#include <wx/fdrepdlg.h>
#include <wx/filedlg.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/tglbtn.h>
#include <wx/timer.h>
//*)
#include <wx/fdrepdlg.h>
#include <wx/textdlg.h>

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @addtogroup JerryScript
  * @{
  */

/**
  * @addtogroup Editor
  * @{
  */

/**
  ****************************************************************************
  * Type
  ****************************************************************************
  */

typedef uint32_t (*editor_event_fct)(void* p_parametr_void, uint8_t *p_data_sui8, uint32_t length_ui32);

/**
  ****************************************************************************
  * Struct
  ****************************************************************************
  */

typedef struct
{
    editor_event_fct data_editor_event_fct;
    void* p_parametr_void;
}editor_event_buffer_t;

/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */

class editor: public wxPanel
{
	public:

	    enum { e_start = 0, e_path = 1 };

		editor(wxWindow *p_parent_wxwindow, wxWindowID text_wxwindowid = wxID_ANY, const wxPoint &pos_wxpoint = wxDefaultPosition, const wxSize &panel_wxsize = wxDefaultSize, uint32_t style_ui32 = wxVSCROLL );
		virtual ~editor();
		void load(void);
		void load(wxString path_str);
		void save(void);
		bool save_as(void);
		void find(void);
		void find_next(void);
		void find_prev(void);
		void replace(void);
		void goto_line(void);
		void new_file(void);
		void new_template(void);
		void set(uint8_t type_ui8, void* p_parametr_void, editor_event_fct data_editor_event_fct);
		wxString get(void);
		void run(bool status_b);

		//(*Declarations(editor)
		text_edit_c* lp_main_text_edit;
		wxBoxSizer* lp_main_wxboxsizer;
		wxBoxSizer* lp_tool_wxboxsizer;
		wxButton* lp_new_template_wxbutton;
		wxButton* lp_new_wxbutton;
		wxButton* lp_open_wxbutton;
		wxButton* lp_replace_wxbutton;
		wxButton* lp_save_as_wxbutton;
		wxButton* lp_save_wxbutton;
		wxButton* lp_search_wxbutton;
		wxFileDialog* lp_script_wxfiledialog;
		wxFindReplaceData findReplaceData_1;
		wxFindReplaceDialog* lp_text_wxfindreplacedialog;
		wxStaticLine* lp_file_wxstaticline;
		wxStaticLine* lp_search_wxstaticline;
		wxTimer lp_edit_event_wxtimer;
		wxToggleButton* lp_script_run_wxtogglebutton;
		//*)

	protected:

		//(*Identifiers(editor)
		static const long l_id_save_wxbutton;
		static const long l_id_save_as_wxbutton;
		static const long l_id_new_wxbutton;
		static const long l_id_new_template_wxbutton;
		static const long l_id_open_wxbutton;
		static const long l_id_file_wxstaticline;
		static const long l_id_search_wxbutton;
		static const long l_id_replace_wxbutton;
		static const long l_id_search_wxstaticline;
		static const long l_id_script_run_wxtogglebutton;
		static const long l_id_main_text_edit;
		static const long l_id_edit_event_wxtimer;
		//*)

	private:

        bool find_from(wxString text_str, int pos_int, int flag_int);
        void goto_line(int32_t line_i32);
        wxString get_organization(void);
		//(*Handlers(editor)
		void on_script_run_wxtogglebutton_toggle(wxCommandEvent& event);
		void on_save_wxbutton_click(wxCommandEvent& event);
		void on_open_wxbutton_click(wxCommandEvent& event);
		void on_edit_event_wxtimer_trigger(wxTimerEvent& event);
		void on_save_as_wxbutton_click(wxCommandEvent& event);
		void on_new_wxbutton_click(wxCommandEvent& event);
		void on_search_wxbutton_click(wxCommandEvent& event);
		void on_replace_wxbutton_click(wxCommandEvent& event);
		void on_text_wxfindreplacedialog_close(wxFindDialogEvent& event);
		void on_text_wxfindreplacedialog_find(wxFindDialogEvent& event);
		void on_text_wxfindreplacedialog_findnext(wxFindDialogEvent& event);
		void on_text_wxfindreplacedialog_replace(wxFindDialogEvent& event);
		void on_text_wxfindreplacedialog_replaceall(wxFindDialogEvent& event);
		void on_new_template_wxbutton_click(wxCommandEvent& event);
		//*)

		wxWindow* lp_parent_wxwindow;
		wxString l_file_path_str;
		editor_event_buffer_t l_main_editor_event_buffer[2];
		int l_find_index_int;
		wxTextEntryDialog* lp_data_wxtextentrydialog;

		DECLARE_EVENT_TABLE()
};

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

#endif // IN_JERRYSCRIPT_EDITOR_H_H_INCLUDED
