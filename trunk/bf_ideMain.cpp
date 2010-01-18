/***************************************************************
 * Name:      bf_ideMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Jeremy Salwen (jeremybubs@gmail.com)
 * Created:   2008-03-23
 * Copyright: Jeremy Salwen ()
 * License:
 **************************************************************/

#include "bf_ideMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(bf_ideFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format) {
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f ) {
        #if defined(__WXMSW__)
        wxbuild << _T("-Windows");
        #elif defined(__UNIX__)
        wxbuild << _T("-Linux");
        #endif

        #if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
        #else
        wxbuild << _T("-ANSI build");
        #endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(bf_ideFrame)
const long bf_ideFrame::ID_TEXTCTRL1 = wxNewId();
const long bf_ideFrame::ID_GRID1 = wxNewId();
const long bf_ideFrame::ID_BUTTON1 = wxNewId();
const long bf_ideFrame::ID_BUTTON2 = wxNewId();
const long bf_ideFrame::ID_BUTTON3 = wxNewId();
const long bf_ideFrame::ID_BUTTON4 = wxNewId();
const long bf_ideFrame::ID_BUTTON5 = wxNewId();
const long bf_ideFrame::ID_TEXTCTRL2 = wxNewId();
const long bf_ideFrame::ID_TEXTCTRL3 = wxNewId();
const long bf_ideFrame::ID_STATICTEXT1 = wxNewId();
const long bf_ideFrame::ID_STATICTEXT2 = wxNewId();
const long bf_ideFrame::idMenuQuit = wxNewId();
const long bf_ideFrame::idMenuAbout = wxNewId();
const long bf_ideFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(bf_ideFrame,wxFrame)
    //(*EventTable(bf_ideFrame)
    //*)
END_EVENT_TABLE()

bf_ideFrame::bf_ideFrame(wxWindow* parent,wxWindowID id) {
    //(*Initialize(bf_ideFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxDLG_UNIT(parent,wxSize(292,222)));
    ProgramText = new wxTextCtrl(this, ID_TEXTCTRL1, _("Insert Program here."), wxPoint(8,8), wxDLG_UNIT(this,wxSize(148,196)), wxTE_PROCESS_ENTER|wxTE_PROCESS_TAB|wxTE_MULTILINE|wxTE_DONTWRAP, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    ArrayData = new bf_table(this, ID_GRID1, wxPoint(320,8), wxSize(256,112), 0, _T("ID_GRID1"));
    ArrayData->CreateGrid(2,3000);
    StartButton = new wxButton(this, ID_BUTTON1, _("Start"), wxDLG_UNIT(this,wxPoint(0,202)), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    PauseButton = new wxButton(this, ID_BUTTON2, _("Pause"), wxDLG_UNIT(this,wxPoint(58,202)), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    PauseButton->Disable();
    StopButton = new wxButton(this, ID_BUTTON3, _("Stop"), wxDLG_UNIT(this,wxPoint(117,202)), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    StopButton->Disable();
    StepIntoButton = new wxButton(this, ID_BUTTON4, _("Step Into"), wxPoint(352,432), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    StepIntoButton->Disable();
    StepOverButton = new wxButton(this, ID_BUTTON5, _("Step Over"), wxDLG_UNIT(this,wxPoint(234,202)), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    StepOverButton->Disable();
    InputBox = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxPoint(320,144), wxSize(256,120), wxTE_AUTO_SCROLL|wxTE_PROCESS_ENTER|wxTE_PROCESS_TAB|wxTE_MULTILINE|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    OutputBox = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxPoint(320,280), wxSize(256,136), wxTE_AUTO_SCROLL|wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    OutputLabel = new wxStaticText(this, ID_STATICTEXT1, _("Output"), wxPoint(328,264), wxSize(80,16), 0, _T("ID_STATICTEXT1"));
    InputLabel = new wxStaticText(this, ID_STATICTEXT2, _("Input"), wxPoint(328,120), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    MenuBar = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar);
    StatusBar = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar);

    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&bf_ideFrame::OnProgramTextText);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&bf_ideFrame::OnStartButtonClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&bf_ideFrame::OnPauseButtonClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&bf_ideFrame::OnStopButtonClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&bf_ideFrame::OnStepIntoButtonClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&bf_ideFrame::OnStepOverButtonClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&bf_ideFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&bf_ideFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&bf_ideFrame::OnClose);
    //*)
}

bf_ideFrame::~bf_ideFrame() {
    //(*Destroy(bf_ideFrame)
    //*)
}

void bf_ideFrame::OnQuit(wxCommandEvent& event) {
    Close();
}

void bf_ideFrame::OnAbout(wxCommandEvent& event) {
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void bf_ideFrame::OnClose(wxCloseEvent& event) {
}

void bf_ideFrame::OnPauseButtonClick(wxCommandEvent& event) {
}


void bf_ideFrame::OnStopButtonClick(wxCommandEvent& event) {
    ProgramText->SetEditable(true);
}

void bf_ideFrame::OnStepIntoButtonClick(wxCommandEvent& event) {
}

void bf_ideFrame::OnStepOverButtonClick(wxCommandEvent& event) {
}

void bf_ideFrame::OnStartButtonClick(wxCommandEvent& event) {
    prep_running();
    return;

}

void bf_ideFrame::OnProgramTextText(wxCommandEvent& event) {
}

void bf_ideFrame::prep_running() {
    running=true;
    ArrayData->GetTable()->reset_values();
    set_running_mode(true);
}

void bf_ideFrame::set_running_mode(bool is_running) {
    StartButton->Enable(!is_running);
    PauseButton->Enable(is_running);
    StopButton->Enable(is_running);
    StepIntoButton->Enable(is_running);
    StepOverButton->Enable(is_running);
    ProgramText->SetEditable(!is_running);
}

void bf_ideFrame::cleanup() {

}


bool bf_ideFrame::breakpoint(int line_number) {
    return false;  //temporary fix
}
