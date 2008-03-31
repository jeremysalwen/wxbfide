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
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
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

bf_ideFrame::bf_ideFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(bf_ideFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxDLG_UNIT(parent,wxSize(291,223)));
    TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("Insert Program here."), wxPoint(8,8), wxDLG_UNIT(this,wxSize(148,196)), wxTE_PROCESS_ENTER|wxTE_PROCESS_TAB|wxTE_MULTILINE|wxTE_DONTWRAP, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    ArrayData = new wxGrid(this, ID_GRID1, wxPoint(240,8), wxSize(192,72), 0, _T("ID_GRID1"));
    ArrayData->CreateGrid(2,3000);
    StartButton = new wxButton(this, ID_BUTTON1, _("Start"), wxDLG_UNIT(this,wxPoint(0,202)), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    PauseButton = new wxButton(this, ID_BUTTON2, _("Pause"), wxDLG_UNIT(this,wxPoint(58,202)), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Button3 = new wxButton(this, ID_BUTTON3, _("Stop"), wxDLG_UNIT(this,wxPoint(176,202)), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Button4 = new wxButton(this, ID_BUTTON4, _("Step Into"), wxPoint(176,328), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    StepOverButton = new wxButton(this, ID_BUTTON5, _("Step Over"), wxDLG_UNIT(this,wxPoint(234,202)), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    TextCtrl2 = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxPoint(240,112), wxSize(192,88), wxTE_PROCESS_ENTER|wxTE_PROCESS_TAB|wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    TextCtrl3 = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxPoint(240,224), wxSize(192,96), wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Output"), wxPoint(240,208), wxSize(80,16), 0, _T("ID_STATICTEXT1"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Input"), wxPoint(240,88), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&bf_ideFrame::OnTextCtrl1Text1);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&bf_ideFrame::OnButton1Click);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&bf_ideFrame::OnPauseButtonClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&bf_ideFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&bf_ideFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&bf_ideFrame::OnClose);
    //*)
}

bf_ideFrame::~bf_ideFrame()
{
    //(*Destroy(bf_ideFrame)
    //*)
}

void bf_ideFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void bf_ideFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void bf_ideFrame::OnTextCtrl1Text(wxCommandEvent& event)
{
}


void bf_ideFrame::OnTextCtrl1Text1(wxCommandEvent& event)
{
}

void bf_ideFrame::OnButton1Click(wxCommandEvent& event)
{
}

void bf_ideFrame::OnClose(wxCloseEvent& event)
{
}

void bf_ideFrame::OnPauseButtonClick(wxCommandEvent& event)
{
}

void bf_ideFrame::OnCustom1Paint(wxPaintEvent& event)
{
}
