#ifndef AP_EDITOR_FRAME_H_H
#define AP_EDITOR_FRAME_H_H

/**
  ****************************************************************************
  * @file    ap_editor_frame_h.h
  * @author  Ing. Petr Simek
  * @version V1.5
  * @date    28.03.2020
  * @brief   Text editor window component creator
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

//(*Headers(editor_frame)
#include <in_jerryscript_editor_h.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
#include <wx/timer.h>
//*)

/**
  * @addtogroup Application
  * @{
  */

/**
  * @addtogroup Script_editor
  * @{
  */

/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */

class editor_frame: public wxFrame
{
    public:

        enum { e_path = 0, e_position = 1 };

        editor_frame(wxWindow* p_parent_window);
        virtual ~editor_frame();
        void load(wxString path_str);
        void run(bool status_b);

    private:

        static uint32_t start_event(void* p_parametr_void, uint8_t *p_data_sui8, uint32_t length_ui32);
        static uint32_t path_event(void* p_parametr_void, uint8_t *p_data_sui8, uint32_t length_ui32);
        //(*Handlers(editor_frame)
        void on_file_open_item_wxmenu_selected(wxCommandEvent& event);
        void on_file_save_item_wxmenu_selected(wxCommandEvent& event);
        void on_file_save_as_item_wxmenu_selected(wxCommandEvent& event);
        void on_close_event(wxCloseEvent& event);
        void on_help_about_item_wxmenu_selected(wxCommandEvent& event);
        void on_file_quit_item_wxmenu_selected(wxCommandEvent& event);
        void on_file_new_empty_item_wxmenu_selected(wxCommandEvent& event);
        void on_help_js_doc_item_wxmenu_selected(wxCommandEvent& event);
        void on_pos_wxtimer_trigger(wxTimerEvent& event);
        void on_search_find_item_wxmenu_selected(wxCommandEvent& event);
        void on_search_find_next_item_wxmenu_selected(wxCommandEvent& event);
        void on_search_find_prev_item_wxmenu_selected(wxCommandEvent& event);
        void on_search_replace_item_wxmenu_selected(wxCommandEvent& event);
        void on_search_goto_line_item_wxmenu_selected(wxCommandEvent& event);
        void on_file_new_template_item_wxmenu_selected(wxCommandEvent& event);
        //*)

        //(*Identifiers(editor_frame)
        static const long l_id_main_editor;
        static const long l_id_file_new_empty_item_wxmenu;
        static const long l_id_file_new_template_item_wxmenu;
        static const long l_id_file_new_item_wxmenu;
        static const long l_id_file_open_item_wxmenu;
        static const long l_id_file_save_item_wxmenu;
        static const long l_id_file_save_as_item_wxmenu;
        static const long l_id_file_quit_item_wxmenu;
        static const long l_id_search_find_item_wxmenu;
        static const long l_id_search_find_next_item_wxmenu;
        static const long l_id_search_find_prev_item_wxmenu;
        static const long l_id_search_replace_item_wxmenu;
        static const long l_id_search_goto_line_item_wxmenu;
        static const long l_id_help_about_item_wxmenu;
        static const long l_id_help_js_doc_item_wxmenu;
        static const long l_id_editor_wxstatusbar;
        static const long l_id_pos_wxtimer;
        //*)

        wxWindow* lp_parent_wxwindow;
        //(*Declarations(editor_frame)
        editor* lp_main_editor;
        wxBoxSizer* lp_main_wxboxsizer;
        wxMenu* l_file_new_item_wxmenu;
        wxMenu* lp_file_wxmenu;
        wxMenu* lp_help_wxmenu;
        wxMenu* lp_search_wxmenu;
        wxMenuBar* lp_main_wxmenubar;
        wxMenuItem* l_file_new_empty_item_wxmenu;
        wxMenuItem* l_file_new_template_item_wxmenu;
        wxMenuItem* l_file_open_item_wxmenu;
        wxMenuItem* l_file_quit_item_wxmenu;
        wxMenuItem* l_file_save_as_item_wxmenu;
        wxMenuItem* l_file_save_item_wxmenu;
        wxMenuItem* l_help_js_doc_item_wxmenu;
        wxMenuItem* l_search_find_item_wxmenu;
        wxMenuItem* l_search_find_next_item_wxmenu;
        wxMenuItem* l_search_find_prev_item_wxmenu;
        wxMenuItem* l_search_goto_line_item_wxmenu;
        wxMenuItem* l_search_replace_item_wxmenu;
        wxMenuItem* lp_help_about_item_wxmenu;
        wxStatusBar* lp_editor_wxstatusbar;
        wxTimer lp_pos_wxtimer;
        //*)

        DECLARE_EVENT_TABLE()
};

/**
* @}
*/

/**
* @}
*/

/*****************************************************END OF FILE************/

#endif // AP_EDITOR_FRAME_H_H
