/**
  ****************************************************************************
  * @file    in_js_edit_text_cpp.cpp
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

#include "in_js_edit_text_h.h"

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
  * @defgroup Edit_text
  * @brief JavaScript text editor
  * @{
  */

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

#include "lp_class_public_xpm.xpm"
#include "lp_method_public_xpm.xpm"
#include "lp_var_public_xpm.xpm"

#include "in_js_edit_text_doc_h.h"

static const wxString l_word_char_str(_T("zyxwvutsrqponmlkjihgfedcba_ZYXWVUTSRQPONMLKJIHGFEDCBA9876543210"));

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

text_edit_c::text_edit_c(wxWindow *p_parent_wxwindow, wxWindowID text_wxwindowid, const wxPoint &pos_wxpoint, const wxSize &panel_wxsize, uint32_t style_ui32): wxStyledTextCtrl (p_parent_wxwindow, text_wxwindowid, pos_wxpoint, panel_wxsize, style_ui32)
{
wxFont set_wxfont(10, wxMODERN, wxNORMAL, wxNORMAL);
uint32_t cnt_ui32;

    StyleClearAll();
    // Use all the bits in the style byte as styles, not indicators.
    SetStyleBits(8);
    // Set lexer
    SetLexer(wxSTC_LEX_CPP);
    // Set default font for all style
    for(cnt_ui32 = 0 ; cnt_ui32 < wxSTC_STYLE_LASTPREDEFINED ; cnt_ui32++)
    {
        StyleSetFont(cnt_ui32, set_wxfont);
        StyleSetBackground(cnt_ui32, wxColour (wxT("WHITE")));
        StyleSetForeground(cnt_ui32, wxColour (wxT("BLACK")));
        StyleSetBold(cnt_ui32, false);
        StyleSetItalic(cnt_ui32, false);
        StyleSetUnderline(cnt_ui32, false);
        StyleSetVisible(cnt_ui32, true);
        StyleSetCase(cnt_ui32, false);
    }
    // set margin for line numbers
    SetMarginType(0, wxSTC_MARGIN_NUMBER);
    StyleSetForeground(wxSTC_STYLE_LINENUMBER, *wxBLACK);
    StyleSetBackground(wxSTC_STYLE_LINENUMBER, wxColour(240, 240, 240));
    SetMarginWidth(0, TextWidth(wxSTC_STYLE_LINENUMBER, wxT("_999999")));
    // annotations style
    StyleSetBackground((wxSTC_STYLE_LASTPREDEFINED + 1), wxColour(244, 220, 220));
    StyleSetForeground((wxSTC_STYLE_LASTPREDEFINED + 1), *wxBLACK);
    StyleSetSizeFractional((wxSTC_STYLE_LASTPREDEFINED + 1), (StyleGetSizeFractional(wxSTC_STYLE_DEFAULT)*4)/5);
    // set common styles
    StyleSetForeground(wxSTC_STYLE_DEFAULT, wxColour (wxT("DARK GREY")));
    StyleSetForeground(wxSTC_STYLE_INDENTGUIDE, wxColour (wxT("DARK GREY")));
    // Set keyword list
    this->l_wordlist_lang_str = wxT("new delete default this super typeof "
                                 "class private protected public export static enum "
                                 "function return void finally yield package "
                                 "switch case break if else for while do continue try catch throw with "
                                 "var const "
                                 "true false null "
                                 "arguments await debugger eval extends implements import "
                                 "in instanceof interface let ");
    SetKeyWords(0, this->l_wordlist_lang_str.To8BitData().data());
    this->l_wordlist_doc_str = wxT("a addindex addtogroup anchor arg attention author b brief bug c "
                                 "class code date def defgroup deprecated dontinclude e em endcode "
                                 "endhtmlonly endif endlatexonly endlink endverbatim enum example "
                                 "exception f$ f[ f] file fn hideinitializer htmlinclude "
                                 "htmlonly if image include ingroup internal invariant interface "
                                 "latexonly li line link mainpage name namespace nosubgrouping note "
                                 "overload p page par param post pre ref relates remarks return "
                                 "retval sa section see showinitializer since skip skipline struct "
                                 "subsection test throw todo typedef union until var verbatim "
                                 "verbinclude version warning weakgroup $ @ \"\" & < > # { }");
    SetKeyWords(2, this->l_wordlist_doc_str.To8BitData().data());
    // Default
    StyleSetForeground(wxSTC_C_DEFAULT, wxColour(wxT("BLACK")));
    // Comment
    StyleSetForeground(wxSTC_C_COMMENT, wxColour(160,160,160));
    // Comment line
    StyleSetForeground(wxSTC_C_COMMENTLINE, wxColour(190,190,230));
    // Comment DOC
    StyleSetForeground(wxSTC_C_COMMENTDOC, wxColour(128,128,255));
    StyleSetBold(wxSTC_C_COMMENTDOC, true);
    // Number
    StyleSetForeground(wxSTC_C_NUMBER, wxColour(240,0,240));
    // Keyword
    StyleSetForeground(wxSTC_C_WORD, wxColour(0,0,160));
    StyleSetBold(wxSTC_C_WORD, true);
    // String
    StyleSetForeground(wxSTC_C_STRING, wxColour(0,0,255));
    // Character
    StyleSetForeground(wxSTC_C_CHARACTER, wxColour(224,160,0));
    // Operator
    StyleSetForeground(wxSTC_C_OPERATOR, wxColour(255,0,0));
    // Keyword user
    StyleSetForeground(wxSTC_C_WORD2, wxColour(0,160,160));
    // Keyword class
    StyleSetForeground(wxSTC_C_GLOBALCLASS, wxColour(0,160,0));
    StyleSetBold(wxSTC_C_GLOBALCLASS, true);
    // Keyword DOC
    StyleSetForeground(wxSTC_C_COMMENTDOCKEYWORD, wxColour(0,128,128));
    // Keyword DOC error
    StyleSetForeground(wxSTC_C_COMMENTDOCKEYWORDERROR, wxColour(128,0,0));
    // Set dummy info margin
    SetMarginType(1, wxSTC_MARGIN_SYMBOL);
    SetMarginWidth(1, 0);
    SetMarginSensitive(1, false);
    // Set code folding
    SetMarginType(2, wxSTC_MARGIN_SYMBOL);
    SetMarginMask(2, wxSTC_MASK_FOLDERS);
    StyleSetBackground(2, *wxWHITE);
    SetMarginWidth(2, 16);
    SetMarginSensitive(2, true);
    SetProperty(wxT("fold"), wxT("1"));
    SetProperty(wxT("fold.html"), wxT("1"));
    SetProperty(wxT("fold.comment"), wxT("1"));
    SetProperty(wxT("fold.preprocessor"), wxT("1"));
    SetFoldFlags(wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED);
    MarkerDefine(wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS, *wxWHITE, *wxBLACK);
    MarkerDefine(wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS,  *wxWHITE, *wxBLACK);
    MarkerDefine(wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_VLINE, *wxWHITE, *wxBLACK);
    MarkerDefine(wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_LCORNER, *wxWHITE, *wxBLACK);
    MarkerDefine(wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS, *wxWHITE, *wxBLACK);
    MarkerDefine(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS, *wxWHITE, *wxBLACK);
    MarkerDefine(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_TCORNER, *wxWHITE, *wxBLACK);
    // set spaces and indention
    SetTabWidth(4);
    SetUseTabs(true);
    SetTabIndents(false);
    SetBackSpaceUnIndents(true);
    SetIndent(4);
    // others
    SetViewEOL(false);
    SetIndentationGuides(false);
    SetEdgeColumn(80);
    SetEdgeMode(wxSTC_EDGE_NONE);
    SetViewWhiteSpace(wxSTC_WS_INVISIBLE);
    SetOvertype(false);
    SetReadOnly(false);
    SetWrapMode(wxSTC_WRAP_NONE);
    // set visibility
    SetVisiblePolicy(wxSTC_VISIBLE_STRICT|wxSTC_VISIBLE_SLOP, 1);
    SetXCaretPolicy(wxSTC_CARET_EVEN|wxSTC_VISIBLE_STRICT|wxSTC_CARET_SLOP, 1);
    SetYCaretPolicy(wxSTC_CARET_EVEN|wxSTC_VISIBLE_STRICT|wxSTC_CARET_SLOP, 1);
    // annotations
    AnnotationSetVisible(wxSTC_ANNOTATION_BOXED);
    // miscellaneous
    SetLayoutCache(wxSTC_CACHE_PAGE);
    // Set brace indicator
    IndicatorSetForeground(text_edit_c::e_barce_bad, wxColour(255, 0, 0));
    IndicatorSetStyle(text_edit_c::e_barce_bad, wxSTC_INDIC_ROUNDBOX);
    IndicatorSetAlpha(text_edit_c::e_barce_bad, 100);
    BraceBadLightIndicator(true, text_edit_c::e_barce_bad);
    IndicatorSetForeground(text_edit_c::e_barce, wxColour(0, 255, 255));
    IndicatorSetStyle(text_edit_c::e_barce, wxSTC_INDIC_ROUNDBOX);
    IndicatorSetAlpha(text_edit_c::e_barce, 100);
    BraceHighlightIndicator(true, text_edit_c::e_barce);
    // Set select indicator
    IndicatorSetForeground(text_edit_c::e_select, wxColour(255, 0, 0));
    IndicatorSetStyle(text_edit_c::e_select, wxSTC_INDIC_ROUNDBOX);
    IndicatorSetAlpha(text_edit_c::e_select, 100);
    IndicatorSetOutlineAlpha(text_edit_c::e_select, 255);
    // Initialize Autocompetation engine
    this->lp_data_auto_comp = new auto_comp_c();
    // Load documentation
    if(this->lp_data_auto_comp)
    {
        this->lp_data_auto_comp->load_h(l_js_doc_file_str);
    }
    // Set autocompetation image
    this->ClearRegisteredImages();
    this->RegisterImage(text_edit_c::e_class, lp_class_public_si8);
    this->RegisterImage(text_edit_c::e_method, lp_method_public_si8);
    this->RegisterImage(text_edit_c::e_var, lp_var_public_si8);
    this->AutoCompSetMaxHeight(14);
    this->AutoCompSetTypeSeparator(wxT('\n'));
    this->AutoCompSetSeparator(wxT('\r'));
    this->AutoCompSetAutoHide(true);
    // Create Worker thread
    this->lp_worker_thread = new thread_c(this, this->worker);
    // Set code folding event
    Bind(wxEVT_STC_MARGINCLICK, &text_edit_c::on_margin_click, this);
    Bind(wxEVT_STC_CHARADDED, &text_edit_c::on_char_added, this);
    Bind(wxEVT_STC_CHANGE, &text_edit_c::on_change, this);
    Bind(wxEVT_STC_CALLTIP_CLICK, &text_edit_c::on_calltip_click, this);
    Bind(wxEVT_KEY_DOWN, &text_edit_c::on_key_down, this);
    Bind(wxEVT_KEY_UP, &text_edit_c::on_key_up, this);
    Bind(wxEVT_LEFT_UP, &text_edit_c::on_mouse_left_up, this);
    Bind(wxEVT_MOUSEWHEEL, &text_edit_c::on_mouse_wheel, this);
    return;
}

/** @brief Destructor
 *
 * @param void
 * @return void
 *
 */

text_edit_c::~text_edit_c(void)
{
    this->lp_worker_thread->stop();
    return;
}

/** @brief Load text file
 *
 * @param [IN] path_str : File path
 * @return void
 *
 */

void text_edit_c::load(wxString path_str)
{
    this->LoadFile(path_str);
    if(this->lp_worker_thread)
    {
        // Run script
        this->lp_worker_thread->signal();
    }
    return;
}

/** @brief Save text file
 *
 * @param [IN] path_str : File path
 * @return void
 *
 */

void text_edit_c::save(wxString path_str)
{
    this->SaveFile(path_str);
    return;
}

/** @brief Highlight all selected text duplicate
 *
 * @param void
 * @return void
 *
 */

void text_edit_c::text_highlight(void)
{
wxString selected_str;
int sel_begin;
int position_int;
int text_length_int = this->GetLength();
int flag_int = wxSTC_FIND_WHOLEWORD;
uint32_t str_cnt_ui32;

    // Highlight all same selected text
    selected_str = this->GetSelectedText();
    if(selected_str.length() >= 2)
    {
        // Get selected position
        this->GetSelection(&sel_begin, NULL);
        // Select indicator
        this->SetIndicatorCurrent(text_edit_c::e_select);
        // Clear old selection
        this->IndicatorClearRange(0, this->GetLength());
        // Set word background
        this->IndicatorSetForeground(text_edit_c::e_select, wxColour(255, 0, 0));
        // Check if selected is word
        for(str_cnt_ui32 = 0 ; str_cnt_ui32 < selected_str.length() ; str_cnt_ui32++)
        {
            if(l_word_char_str.Find(selected_str[str_cnt_ui32]) == wxNOT_FOUND)
            {
                flag_int = wxSTC_FIND_MATCHCASE;
                str_cnt_ui32 = selected_str.length();
                // Set match background
                this->IndicatorSetForeground(text_edit_c::e_select, wxColour(255, 255, 0));
            }
        }
        for(
            position_int = this->FindText(0, text_length_int, selected_str, flag_int) ;
            position_int != wxSTC_INVALID_POSITION ;
            position_int = this->FindText(position_int += selected_str.length(), text_length_int, selected_str, flag_int)
           )
        {
            if(sel_begin != position_int)
            {
                this->IndicatorFillRange(position_int, selected_str.length());
            }
        }
    }
    else
    {
        // Clear old selection
        this->SetIndicatorCurrent(text_edit_c::e_select);
        this->IndicatorClearRange(0, this->GetLength());
    }
    return;
}

/**
  ****************************************************************************
  * Private
  ****************************************************************************
  */

void text_edit_c::worker(void* p_parametr_void)
{
text_edit_c* p_bkp_this = (text_edit_c*)p_parametr_void;

    if(p_bkp_this->lp_data_auto_comp)
    {
        // Parse script again
        p_bkp_this->lp_data_auto_comp->load_js(p_bkp_this->GetText());
        // Load global word for lexer
        p_bkp_this->lp_data_auto_comp->load_lex(auto_comp_c::e_fct, p_bkp_this->l_wordlist_fct_str);
        p_bkp_this->SetKeyWords(auto_comp_c::e_fct, p_bkp_this->l_wordlist_fct_str.To8BitData().data());
        p_bkp_this->lp_data_auto_comp->load_lex(auto_comp_c::e_var, p_bkp_this->l_wordlist_var_str);
        p_bkp_this->SetKeyWords(auto_comp_c::e_var, p_bkp_this->l_wordlist_var_str.To8BitData().data());
    }
    return;
}

/** @brief Get autocompetation info
 *
 * @param void
 * @return void
 *
 */

void text_edit_c::auto_comp(void)
{
int add_pos_int = (this->GetCurrentPos() - 1);
wxArrayString command_arraystring;
wxString info_str;

    this->AnnotationClearAll();
    if(this->GetCharAt(add_pos_int) == '.')
    {
        while(this->GetCharAt(add_pos_int) == '.')
        {
            command_arraystring.Insert(this->GetTextRange(this->WordStartPosition(add_pos_int, true), this->WordEndPosition(add_pos_int, true)), 0);
            add_pos_int = (this->WordStartPosition((add_pos_int - 1), true) - 1);
        }
        command_arraystring.Add(wxEmptyString);
    }
    else
    {
        add_pos_int = (this->WordStartPosition(GetCurrentPos(), true) - 1);
        command_arraystring.Add(this->GetTextRange(this->WordStartPosition(GetCurrentPos(), true), this->WordEndPosition(GetCurrentPos(), true)));
        if(this->GetCharAt(add_pos_int) == '.')
        {
            while(this->GetCharAt(add_pos_int) == '.')
            {
                command_arraystring.Insert(this->GetTextRange(this->WordStartPosition(add_pos_int, true), this->WordEndPosition(add_pos_int, true)), 0);
                add_pos_int = (this->WordStartPosition((add_pos_int - 1), true) - 1);
            }
        }
    }
    // Get autocompetation info string
    if(this->lp_data_auto_comp)
    {
        info_str = this->lp_data_auto_comp->get(command_arraystring);
    }
    if(info_str != wxEmptyString)
    {
        if(command_arraystring.size() == 1)
        {
            if(command_arraystring.Last().size() > 1)
            {
                this->AutoCompShow(command_arraystring.Last().size(),info_str);
            }
        }
        else
        {
            this->AutoCompShow(command_arraystring.Last().size(),info_str);
        }
    }
    else
    {
        this->AutoCompCancel();
    }
    return;
}

/** @brief Get automatic object info
 *
 * @param void
 * @return void
 *
 */

void text_edit_c::auto_info(void)
{
int add_pos_int = (this->GetCurrentPos() - 1);
wxString word_str = wxEmptyString;
wxString info_str = wxEmptyString;

wxArrayString command_arraystring;

    if(this->GetCharAt(add_pos_int) == '(')
    {
        command_arraystring.Insert(this->GetTextRange(this->WordStartPosition(add_pos_int, true), this->WordEndPosition(add_pos_int, true)), 0);
        add_pos_int = (this->WordStartPosition((add_pos_int - 1), true) - 1);
        while(this->GetCharAt(add_pos_int) == '.')
        {
            command_arraystring.Insert(this->GetTextRange(this->WordStartPosition(add_pos_int, true), this->WordEndPosition(add_pos_int, true)), 0);
            add_pos_int = (this->WordStartPosition((add_pos_int - 1), true) - 1);
        }
        add_pos_int++;
        word_str = this->GetTextRange(add_pos_int, (this->GetCurrentPos() - 1));
        this->l_call_tip_arraystring.clear();
        if(this->lp_data_auto_comp)
        {
            this->l_call_tip_arraystring = this->lp_data_auto_comp->get_info(command_arraystring);
        }
        this->l_call_tip_pos_ui32 = 0;
        if(this->l_call_tip_arraystring.size())
        {
            this->CallTipUseStyle(1);
            if(this->l_call_tip_arraystring.size() > 1)
            {
                info_str = wxT('\001');
                info_str += wxT('\002');
                info_str += wxString::Format("[%u/%u]\n", (this->l_call_tip_pos_ui32 + 1), (uint32_t)this->l_call_tip_arraystring.size());
                info_str += this->l_call_tip_arraystring[this->l_call_tip_pos_ui32];
                this->CallTipShow(this->GetCurrentPos(),info_str);
            }
            else
            {
                this->CallTipShow(this->GetCurrentPos(),this->l_call_tip_arraystring[this->l_call_tip_pos_ui32]);
            }

        }
        else
        {
            this->CallTipCancel();
        }
    }
    else
    {
        this->CallTipCancel();
    }
    return;
}

/** @brief Text layout autocompetation
 *
 * @param void
 * @return void
 *
 */

void text_edit_c::tab_comp(void)
{
int current_line_int = this->GetCurrentLine();
int line_ind_int = 0;
wxString line_str;

    switch((char)this->GetCharAt((this->GetCurrentPos() - 1)))
    {
        case '\n':
        {
            // Tabulator automatic insert
            if(current_line_int > 0)
            {
                line_ind_int = this->GetLineIndentation(current_line_int - 1);
                line_str = this->GetLine(current_line_int - 1);
            }
            if(line_ind_int != 0)
            {
                this->SetLineIndentation(current_line_int, line_ind_int);
                this->GotoPos(this->GetLineEndPosition(current_line_int));
                if(line_str.Find('{') != wxNOT_FOUND)
                {
                    this->InsertText(this->GetCurrentPos(), "\t");
                    this->GotoPos(this->GetLineEndPosition(current_line_int));
                }
            }
            else
            {
                if(line_str.Find('{') != wxNOT_FOUND)
                {
                    this->InsertText(this->GetCurrentPos(), "\t");
                    this->GotoPos(this->GetLineEndPosition(current_line_int));
                }
            }
        }
        break;
        default:
        {

        }
        break;
    }
    return;
}

/** @brief Brace automatic paire
 *
 * @param [IN] char_i8 : Added char
 * @return void
 *
 */

void text_edit_c::brace_comp(void)
{
int current_line_int = this->GetCurrentLine();
int line_ind_int = 0;

    switch((char)this->GetCharAt((this->GetCurrentPos() - 1)))
    {
        case '{':
        {
            int pos_bkp_int = this->GetCurrentPos();
            InsertText(this->GetCurrentPos(), "\n");
            GotoPos(this->GetCurrentPos() + 1);
            current_line_int++;
            if(current_line_int > 0)
            {
                line_ind_int = this->GetLineIndentation(current_line_int - 1);
            }
            if(line_ind_int != 0)
            {
                this->SetLineIndentation(current_line_int, line_ind_int);
                this->GotoPos(this->GetLineEndPosition(current_line_int));
            }
            wxString text_str;
            text_str.Printf("%c",'}');
            this->InsertText(this->GetCurrentPos(), text_str);
            this->GotoPos(pos_bkp_int);
        }
        break;
        case '(':
        {
            if((this->GetCharAt(this->GetCurrentPos()) == ' ') || (this->GetCharAt(this->GetCurrentPos()) == '\r') || (this->GetCharAt(this->GetCurrentPos()) == '\n') || (this->GetCharAt(this->GetCurrentPos()) == ')' || (this->GetCharAt(this->GetCurrentPos()) == ']')))
            {
                this->InsertText(GetCurrentPos(), ")");
            }
        }
        break;
        case '[':
        {
            if((this->GetCharAt(this->GetCurrentPos()) == ' ') || (this->GetCharAt(this->GetCurrentPos()) == '\r') || (this->GetCharAt(this->GetCurrentPos()) == '\n') || (this->GetCharAt(this->GetCurrentPos()) == ')' || (this->GetCharAt(this->GetCurrentPos()) == ']')))
            {
                this->InsertText(this->GetCurrentPos(), "]");
            }
        }
        break;
        case '"':
        {
            if((this->GetCharAt(this->GetCurrentPos()) == ' ') || (this->GetCharAt(this->GetCurrentPos()) == '\r') || (this->GetCharAt(this->GetCurrentPos()) == '\n'))
            {
                this->InsertText(this->GetCurrentPos(), "\"");
            }
        }
        break;
        case 0x27:
        {
            if((this->GetCharAt(this->GetCurrentPos()) == ' ') || (this->GetCharAt(this->GetCurrentPos()) == '\r') || (this->GetCharAt(this->GetCurrentPos()) == '\n'))
            {
                this->InsertText(this->GetCurrentPos(), "'");
            }
        }
        default:
        {

        }
        break;
    }
    return;
}

/** @brief Highlight complement barce
 *
 * @param void
 * @return void
 *
 */

void text_edit_c::brace_highlight(void)
{
static const wxString f_brace_str(_T("{[()]}"));
int begin_pos_int = wxSTC_INVALID_POSITION;
int end_pos_int = wxSTC_INVALID_POSITION ;

    if(f_brace_str.Find((wxChar)this->GetCharAt(this->GetCurrentPos() - 1)) != wxNOT_FOUND)
    {
        begin_pos_int = (this->GetCurrentPos() - 1);
    }
    else if(f_brace_str.Find((wxChar)this->GetCharAt(this->GetCurrentPos())) != wxNOT_FOUND)
    {
        begin_pos_int = this->GetCurrentPos();
    }
    else
    {
        this->BraceHighlight(wxSTC_INVALID_POSITION, wxSTC_INVALID_POSITION);
    }
    if(begin_pos_int > wxSTC_INVALID_POSITION)
    {
        // Get complement brace
        end_pos_int = this->BraceMatch(begin_pos_int);
        // Highlight grace
        if(wxSTC_INVALID_POSITION != end_pos_int)
        {
            this->BraceHighlight(begin_pos_int, end_pos_int);
        }
        else
        {
            this->BraceBadLight(begin_pos_int);
        }
    }
    return;
}

/** @brief Margin click event
 *
 * @param [IN] data_wxstyledtextrvent : Event data
 * @return void
 *
 */

void text_edit_c::on_margin_click(wxStyledTextEvent &data_wxstyledtextrvent)
{
int line_click_int;
int level_click_int;

    if (data_wxstyledtextrvent.GetMargin() == 2)
    {
        line_click_int = this->LineFromPosition(data_wxstyledtextrvent.GetPosition());
        level_click_int = this->GetFoldLevel(line_click_int);
        if((level_click_int & wxSTC_FOLDLEVELHEADERFLAG) > 0)
        {
            this->ToggleFold(line_click_int);
        }
    }
    return;
}

/** @brief Char added event
 *
 * @param [IN] data_wxstyledtextrvent : Event data
 * @return void
 *
 */

void text_edit_c::on_char_added(wxStyledTextEvent &data_wxstyledtextrvent)
{
    // Class autocompetation
    this->auto_comp();
    // Brace automation
    this->brace_comp();
    // Write layout automation
    this->tab_comp();
    // Enable autohide
    this->AutoCompSetAutoHide(true);
    return;
}

/** @brief Text changed
 *
 * @param [IN] data_wxstyledtextrvent : Event data
 * @return void
 *
 */

void text_edit_c::on_change(wxStyledTextEvent &data_wxstyledtextrvent)
{
    if(this->lp_worker_thread)
    {
        // Run script
        this->lp_worker_thread->signal();
    }
    return;
}

/** @brief Char added event
 *
 * @param [IN] data_wxstyledtextrvent : Event data
 * @return void
 *
 */

void text_edit_c::on_calltip_click(wxStyledTextEvent &data_wxstyledtextrvent)
{
wxString info_str;
bool change_b = true;

    switch (data_wxstyledtextrvent.GetPosition())
    {
        case 1:
        {
            // up
            if(this->l_call_tip_pos_ui32)
            {
                this->l_call_tip_pos_ui32--;
            }
            else
            {
                change_b = false;
            }
        }
        break;
        case 2:
        {
            // down
            if(this->l_call_tip_pos_ui32 < this->l_call_tip_arraystring.size())
            {
                this->l_call_tip_pos_ui32++;
            }
            else
            {
                change_b = false;
            }
        }
        break;
        default:
        {
            // elsewhere
            change_b = false;
        }
        break;
    }
    if((this->l_call_tip_pos_ui32 < this->l_call_tip_arraystring.size()) && change_b)
    {
        info_str = wxT('\001');
        info_str += wxT('\002');
        info_str += wxString::Format("[%u/%u]\n", (this->l_call_tip_pos_ui32 + 1), (uint32_t)this->l_call_tip_arraystring.size());
        info_str += this->l_call_tip_arraystring[this->l_call_tip_pos_ui32];
        this->CallTipCancel();
        this->CallTipShow(this->GetCurrentPos(),info_str);
        data_wxstyledtextrvent.Skip();
    }
    return;
}

/** @brief Key down event
 *
 * @param [IN] data_wxkeyevent : Event data
 * @return void
 *
 */

void text_edit_c::on_key_down(wxKeyEvent &data_wxkeyevent)
{
static int last_key_int = 0;
int key_int = data_wxkeyevent.GetKeyCode();

    switch(key_int)
    {
        case 0x132:
        {
            // Shift
            if(last_key_int == 0x134)
            {
                // Disable autohide
                this->AutoCompSetAutoHide(false);
                this->auto_comp();
            }
        }
        break;
        case 0x134:
        {
            // Ctrl
            if(last_key_int == 0x132)
            {
                // Disable autohide
                this->AutoCompSetAutoHide(false);
                this->auto_comp();
            }
        }
        break;
        default:
        {

        }
        break;
    }
    last_key_int = key_int;
    // Skip to next event
    data_wxkeyevent.Skip();
    return;
}

/** @brief Key up event
 *
 * @param [IN] data_wxkeyevent : Event data
 * @return void
 *
 */

void text_edit_c::on_key_up(wxKeyEvent &data_wxkeyevent)
{
    // highlight text
    this->text_highlight();
    // Highlight complement brace
    this->brace_highlight();
    // Show object info
    this->auto_info();
    // Skip to next event
    data_wxkeyevent.Skip();
    return;
}

/** @brief Left mouse button up event
 *
 * @param [IN] data_wxmouseevent : Event data
 * @return void
 *
 */

void text_edit_c::on_mouse_left_up(wxMouseEvent &data_wxmouseevent)
{
    // highlight text
    this->text_highlight();
    // Highlight complement brace
    this->brace_highlight();
    // Show object info
    this->auto_info();
    // Skip to next event
    data_wxmouseevent.Skip();
}

/** @brief Left mouse button up event
 *
 * @param [IN] data_wxmouseevent : Event data
 * @return void
 *
 */

void text_edit_c::on_mouse_wheel(wxMouseEvent &data_wxmouseevent)
{
    // Cancel all calltip
    this->CallTipCancel();
    // Skip to next event
    data_wxmouseevent.Skip();
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
