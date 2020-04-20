/**
  ****************************************************************************
  * @file    file2str.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    05.04.2020
  * @brief   File to C++ string conveter
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

#include <wx/app.h>
#include <wx/file.h>
#include <wx/filename.h>
#include <vector>
using namespace std;

/**
  ****************************************************************************
  * Class
  ****************************************************************************
  */

class main_app : public wxApp
{
    public:

        virtual bool OnInit(void);

    private:

        wxString load(wxString path_str);
        void save(wxString path_str, wxString text_str);

        wxArrayString* lp_cmd_buffer_arraystring;
        wxFileName l_app_wxfilename;
        wxFileName l_doc_wxfilename;
        wxFileName l_src_wxfilename;
        wxString l_type_str;
        wxString l_var_str;
        wxString l_doc_str;
        wxString l_source_str;

};

// Run standard main function
IMPLEMENT_APP_NO_MAIN(main_app);

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */


/** @brief Windows main entry point
 *
 * @param [IN] argc : Standard argument counter
 * @param [IN] argv : Pointer on argument srting buffer
 * @return int : Termination state
 *
 */

int main(int argc, char *argv[])
{
    wxEntryStart( argc, argv );
    wxTheApp->CallOnInit();
    return 0;
}

/** @brief Application initialization
 *
 * @param void
 * @return void
 *
 */

bool main_app::OnInit(void)
{
int32_t cmd_cnt_i32;

    // Convert CMD argument
    this->lp_cmd_buffer_arraystring = new wxArrayString();
    for(cmd_cnt_i32 = 0 ; cmd_cnt_i32 < argc ; cmd_cnt_i32++)
    {
        this->lp_cmd_buffer_arraystring->Add(argv[cmd_cnt_i32]);
    }
    // Get program path
    this->l_app_wxfilename.Assign(this->lp_cmd_buffer_arraystring->Item(0));
    // Get text file path
    if (wxNOT_FOUND != this->lp_cmd_buffer_arraystring->Index(wxT("-d")))
    {
        this->l_doc_wxfilename.Assign(this->lp_cmd_buffer_arraystring->Item((this->lp_cmd_buffer_arraystring->Index(wxT("-d"))) + 1));
    }
    // Get source file path
    if (wxNOT_FOUND != this->lp_cmd_buffer_arraystring->Index(wxT("-s")))
    {
        this->l_src_wxfilename.Assign(this->lp_cmd_buffer_arraystring->Item((this->lp_cmd_buffer_arraystring->Index(wxT("-s"))) + 1));
    }
    // Get variable type
    if (wxNOT_FOUND != this->lp_cmd_buffer_arraystring->Index(wxT("-t")))
    {
        this->l_type_str = this->lp_cmd_buffer_arraystring->Item((this->lp_cmd_buffer_arraystring->Index(wxT("-t"))) + 1);
    }
    else
    {
        this->l_type_str = wxT("wxString");
    }
    // Get variable name
    if (wxNOT_FOUND != this->lp_cmd_buffer_arraystring->Index(wxT("-n")))
    {
        this->l_var_str = this->lp_cmd_buffer_arraystring->Item((this->lp_cmd_buffer_arraystring->Index(wxT("-n"))) + 1);
    }
    else
    {
        this->l_var_str = wxT("text_str");
    }
    this->l_source_str += wxT("  * @date    " __DATE__ "\n");
    printf("file2str V1.0 PORTTRONIC " __DATE__ "\n");
    printf("Source : %s\n", this->l_doc_wxfilename.GetFullName().To8BitData().data());
    printf("Generate : %s\n", this->l_src_wxfilename.GetFullName().To8BitData().data());
    printf("Variable type : %s\n", this->l_type_str.To8BitData().data());
    printf("Variable name : %s\n", this->l_var_str.To8BitData().data());
    // Load documentation
    this->l_doc_str = this->load(this->l_doc_wxfilename.GetFullPath());
    if (this->l_doc_str != wxEmptyString)
    {
        // Convert text to string
        this->l_doc_str.Replace('\r', "");
        this->l_doc_str.Replace('"', "\\\"");
        this->l_doc_str.Replace('\n', wxString::Format("\\n%c%c%c", '"', '\n', '"'));
        this->l_doc_str.RemoveLast();
        this->l_doc_str.RemoveLast();
        this->l_doc_str.RemoveLast();
        // Write header
        this->l_source_str = wxT("/**\n");
        this->l_source_str += wxT("  ****************************************************************************\n");
        this->l_source_str += wxString::Format("  * @file    %s\n", this->l_src_wxfilename.GetFullName().To8BitData().data());
        this->l_source_str += wxT("  * @author  file2str\n");
        this->l_source_str += wxString::Format("  * @brief   File variable %s %s\n", this->l_type_str.To8BitData().data(), this->l_var_str.To8BitData().data());
        this->l_source_str += wxT("  ****************************************************************************\n");
        this->l_source_str += wxT("  */\n");
        this->l_source_str += wxT("\n");
        this->l_source_str += wxT("/**\n");
        this->l_source_str += wxT("  ****************************************************************************\n");
        this->l_source_str += wxT("  * Variable\n");
        this->l_source_str += wxT("  ****************************************************************************\n");
        this->l_source_str += wxT("  */\n");
        this->l_source_str += wxT("\n");
        this->l_source_str += wxT("// File string\n");
        // Write text file
        this->l_source_str += wxString::Format("%s %s = wxT(\n\"%s\");\n", this->l_type_str.To8BitData().data(), this->l_var_str.To8BitData().data(), this->l_doc_str.To8BitData().data());
        // Write footer
        this->l_source_str += wxT("\n/*****************************************************END OF FILE************/\n");
        // Save generated file
        this->save(this->l_src_wxfilename.GetFullPath(), this->l_source_str);
    }
    return true;
}

/**
  ****************************************************************************
  * Local function
  ****************************************************************************
  */

/** @brief Load text file
 *
 * @param [IN] path_str : File path string
 * @return wxString : Read text
 *
 */

wxString main_app::load(wxString path_str)
{
wxFile* p_doc_wxfile = new wxFile();
wxString text_str = wxEmptyString;

    if(p_doc_wxfile->Exists(path_str))
    {
        p_doc_wxfile->Open(path_str);
        if(p_doc_wxfile->IsOpened())
        {
            p_doc_wxfile->ReadAll(&text_str);
            printf("Load file size : %u\n", (uint32_t)text_str.size());
        }
        else
        {
            printf("Load file is not open\n");
        }
    }
    else
    {
        printf("Load file is not exist\n");
    }
    delete p_doc_wxfile;
    return text_str;
}

/** @brief Save text file
 *
 * @param [IN] path_str : File path string
 * @param [IN] text_str : File text data
 * @return void
 *
 */

void main_app::save(wxString path_str, wxString text_str)
{
wxFile* p_src_wxfile = new wxFile();
wxString read_str;

    if(p_src_wxfile->Exists(path_str))
    {
        read_str = this->load(path_str);
        if(!read_str.IsSameAs(text_str))
        {
            p_src_wxfile->Open(path_str, wxFile::write);
            p_src_wxfile->Write(text_str);
            printf("Save file size : %u\n", (uint32_t)text_str.size());
        }
        else
        {
            printf("File is same\n");
        }
    }
    else
    {
        printf("Save new file\n");
        p_src_wxfile->Create(path_str, wxFile::write);
        p_src_wxfile->Write(text_str);
    }
    delete p_src_wxfile;
    return;
}

/*****************************************************END OF FILE************/
