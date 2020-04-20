#ifndef IN_JS_EDIT_TEXT_H_H_INCLUDED
#define IN_JS_EDIT_TEXT_H_H_INCLUDED

/**
  ****************************************************************************
  * @file    in_js_edit_text_h.h
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    26.03.2020
  * @brief   JerryScript text editor base on wxScintilla
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

#include "wx/stc/stc.h"
#include "in_js_edit_text_autocomp_h.h"
#include <wx/tooltip.h>
#include "in_thread_worker_h.h"
#include <vector>
using namespace std;

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @addtogroup JerryScript
  * @{
  */

/**
  * @addtogroup Edit_text
  * @{
  */

/**
  ****************************************************************************
  * Struct
  ****************************************************************************
  */

typedef struct
{
    wxString class_str;
    wxString method_str;
    wxString doc_str;
}autocomp_buffer_t;

/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */

class EditPrint;
class EditProperties;

class text_edit_c: public wxStyledTextCtrl
{
    friend class EditProperties;
    friend class EditPrint;

    public:

        enum { e_barce_bad = 0, e_barce = 1, e_select = 2 };
        enum { e_class = 0, e_method = 1, e_var = 2 };

        text_edit_c(wxWindow *p_parent_wxwindow, wxWindowID text_wxwindowid = wxID_ANY, const wxPoint &pos_wxpoint = wxDefaultPosition, const wxSize &panel_wxsize = wxDefaultSize, uint32_t style_ui32 = wxVSCROLL );
        ~text_edit_c(void);
        void load(wxString path_str);
        void save(wxString path_str);
        void text_highlight(void);

    private:

        static void worker(void* p_parametr_void);
        void auto_comp(void);
        void auto_info(void);
        void tab_comp(void);
        void brace_comp(void);
        void brace_highlight(void);
        void on_margin_click(wxStyledTextEvent &data_wxstyledtextrvent);
        void on_char_added(wxStyledTextEvent &data_wxstyledtextrvent);
        void on_change(wxStyledTextEvent &data_wxstyledtextrvent);
        void on_calltip_click(wxStyledTextEvent &data_wxstyledtextrvent);
        void on_key_down(wxKeyEvent &data_wxkeyevent);
        void on_key_up(wxKeyEvent &data_wxkeyevent);
        void on_mouse_left_up(wxMouseEvent &data_wxmouseevent);
        void on_mouse_wheel(wxMouseEvent &data_wxmouseevent);

        wxString l_filename_str;
        auto_comp_c* lp_data_auto_comp;
        autocomp_buffer_t l_class_autocomp_buffer;
        wxArrayString l_call_tip_arraystring;
        thread_c* lp_worker_thread;
        uint32_t l_call_tip_pos_ui32;
        wxString l_wordlist_lang_str;
        wxString l_wordlist_doc_str;
        wxString l_wordlist_fct_str;
        wxString l_wordlist_var_str;

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

#endif // IN_JS_EDIT_TEXT_H_H_INCLUDED
