#include "IDEFrame.h"

//(*InternalHeaders(IDEFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)
#include "bf_tableBase.h"

//(*IdInit(IDEFrame)
const long IDEFrame::ID_CODE_EDITOR = wxNewId();
const long IDEFrame::ID_GRID1 = wxNewId();
const long IDEFrame::ID_TERM = wxNewId();
const long IDEFrame::ID_SPLITTERWINDOW2 = wxNewId();
const long IDEFrame::ID_SPLITTERWINDOW1 = wxNewId();
const long IDEFrame::ID_RUN_BUTTON = wxNewId();
const long IDEFrame::ID_BREAKPOINT_CHECKBOX = wxNewId();
const long IDEFrame::ID_STOP_BUTTON = wxNewId();
const long IDEFrame::ID_PAUSE_BUTTON = wxNewId();
const long IDEFrame::ID_CONTINUE_BUTTON = wxNewId();
const long IDEFrame::ID_STEP_BUTTON = wxNewId();
const long IDEFrame::ID_CLEARIO_BUTTON = wxNewId();
const long IDEFrame::ID_QUIT_BUTTON = wxNewId();
//*)

DEFINE_EVENT_TYPE(EVT_VM_BREAKPOINTED)
DEFINE_EVENT_TYPE(EVT_VM_FINISHED)

BEGIN_EVENT_TABLE(IDEFrame,wxFrame)
    //(*EventTable(IDEFrame)
    //*)
    EVT_STC_MARGINCLICK(-1,IDEFrame::OnMarginClicked)
    EVT_COMMAND(wxID_ANY,EVT_VM_BREAKPOINTED,IDEFrame::OnVmBreakpoint)
    EVT_COMMAND(wxID_ANY,EVT_VM_FINISHED,IDEFrame::OnVmFinished)
END_EVENT_TABLE()

/*
   This is taken from scintilla documentation,
   but isn't properly copied in wxStyledTextCtrl
*/
#define SCI_STYLE_LINENUMBER 33

IDEFrame::IDEFrame(wxWindow* parent,wxWindowID id): c(m)
{

    //(*Initialize(IDEFrame)
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer2;

    Create(parent, wxID_ANY, _("Brainfuck IDE"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    FlexGridSizer1 = new wxFlexGridSizer(2, 0, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(0);
    SplitterWindow1 = new wxSplitterWindow(this, ID_SPLITTERWINDOW1, wxDefaultPosition, wxSize(100,32), wxSP_3D, _T("ID_SPLITTERWINDOW1"));
    SplitterWindow1->SetMinSize(wxSize(10,10));
    SplitterWindow1->SetMinimumPaneSize(10);
    CodeEditor = new wxStyledTextCtrl(SplitterWindow1,ID_CODE_EDITOR,wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("ID_CODE_EDITOR"));
    CodeEditor->SetMarginWidth(0,CodeEditor->TextWidth(wxSTC_STYLE_LINENUMBER,"9999"));
    CodeEditor->SetMarginSensitive(1,true);
    CodeEditor->SetScrollWidth(wxDefaultSize.GetWidth());
    CodeEditor->MarkerDefine(0,wxSTC_MARK_CIRCLE);

    SplitterWindow2 = new wxSplitterWindow(SplitterWindow1, ID_SPLITTERWINDOW2, wxPoint(114,21), wxDefaultSize, wxSP_3D, _T("ID_SPLITTERWINDOW2"));
    SplitterWindow2->SetMinSize(wxSize(10,10));
    SplitterWindow2->SetMinimumPaneSize(10);
    DataGrid = new bf_table(SplitterWindow2, ID_GRID1, wxPoint(34,15), wxDLG_UNIT(SplitterWindow2,wxSize(-1,49)), 0, _T("ID_GRID1"));
    Term1 = new BFTerm(SplitterWindow2,&m,&c,ID_TERM,wxPoint(54,60),wxDefaultSize,_T("ID_TERM"));
    SplitterWindow2->SplitHorizontally(DataGrid, Term1);
    SplitterWindow1->SplitVertically(CodeEditor, SplitterWindow2);
    SplitterWindow1->SetSashPosition(200);
    FlexGridSizer1->Add(SplitterWindow1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2 = new wxFlexGridSizer(0, 100, 0, 0);
    RunButton = new wxButton(this, ID_RUN_BUTTON, _("Run"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RUN_BUTTON"));
    FlexGridSizer2->Add(RunButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BreakPointsEnabled = new wxCheckBox(this, ID_BREAKPOINT_CHECKBOX, _("Enable Breakpoints"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BREAKPOINT_CHECKBOX"));
    BreakPointsEnabled->SetValue(false);
    FlexGridSizer2->Add(BreakPointsEnabled, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StopButton = new wxButton(this, ID_STOP_BUTTON, _("Stop"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_STOP_BUTTON"));
    FlexGridSizer2->Add(StopButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PauseButton = new wxButton(this, ID_PAUSE_BUTTON, _("Pause"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PAUSE_BUTTON"));
    FlexGridSizer2->Add(PauseButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ContinueButton = new wxButton(this, ID_CONTINUE_BUTTON, _("Continue"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CONTINUE_BUTTON"));
    FlexGridSizer2->Add(ContinueButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StepButton = new wxButton(this, ID_STEP_BUTTON, _("Step"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_STEP_BUTTON"));
    FlexGridSizer2->Add(StepButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ClearButton = new wxButton(this, ID_CLEARIO_BUTTON, _("Clear IO"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CLEARIO_BUTTON"));
    FlexGridSizer2->Add(ClearButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    QuitButton = new wxButton(this, ID_QUIT_BUTTON, _("Quit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_QUIT_BUTTON"));
    FlexGridSizer2->Add(QuitButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_RUN_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IDEFrame::OnRunButtonClick);
    Connect(ID_STOP_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IDEFrame::OnStopButtonClick);
    Connect(ID_PAUSE_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IDEFrame::OnPauseButtonClick);
    Connect(ID_CONTINUE_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IDEFrame::OnContinueButtonClick);
    Connect(ID_STEP_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IDEFrame::OnStepButtonClick);
    Connect(ID_CLEARIO_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IDEFrame::OnClearButtonClick);
    Connect(ID_QUIT_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IDEFrame::OnQuitButtonClick);
    //*)
    CodeEditor->SetIndicatorCurrent(wxSTC_INDIC_CONTAINER);
    CodeEditor->IndicatorSetStyle(wxSTC_INDIC_CONTAINER,wxSTC_INDIC_BOX);
    CodeEditor->IndicatorSetForeground(wxSTC_INDIC_CONTAINER,0x0000ff);

    bf_tableBase * b =new bf_tableBase(DataGrid);

    DataGrid->SetTable(b,true);
    wxGridCellAttr *w=new wxGridCellAttr();  //memory leak?
    w->SetReadOnly(true);
    DataGrid->SetRowAttr(1,w);
    DataGrid->SetColumnWidth(1,10);
    DataGrid->SetRowLabelSize(0);
    DataGrid->SetColLabelSize(0);
    DataGrid->DisableDragGridSize();
    DataGrid->SetMargins(0,0);

    processing_thread=new bf_interpreter_thread(this->GetEventHandler(),this,&m,&c,Term1,"",b);
    processing_thread->Run();
}

IDEFrame::~IDEFrame()
{
    //(*Destroy(IDEFrame)
    //*)
}


void IDEFrame::OnClose(wxCloseEvent& event)
{
}

void IDEFrame::OnCodeEditorResize(wxSizeEvent& event)
{

}

void IDEFrame::OnMarginClicked(wxStyledTextEvent& event)
{
    wxMutexLocker l(m);
    int line=CodeEditor->LineFromPosition(event.GetPosition());
    if(CodeEditor->MarkerGet(line))
    {
        CodeEditor->MarkerDelete(line,0);
    }
    else
    {
        CodeEditor->MarkerAdd(line,0);
    }
}

void IDEFrame::OnVmBreakpoint(wxCommandEvent& e)
{
    RunButton->Enable(true);
    StepButton->Enable(true);
    PauseButton->Enable(false);
    StopButton->Enable(true);
    ContinueButton->Enable(true);
    int index=e.GetInt();
    CodeEditor->IndicatorFillRange(index,1);

}
void IDEFrame::OnVmFinished(wxCommandEvent& e) {
    CodeEditor->SetReadOnly(false);
    RunButton->Enable(true);
    StepButton->Enable(false);
    PauseButton->Enable(false);
    StopButton->Enable(false);
    ContinueButton->Enable(false);
}

bool IDEFrame::HasBreakpoint(unsigned int linenumber)
{
    return BreakPointsEnabled->GetValue() && CodeEditor->MarkerGet(linenumber);
}
void IDEFrame::clearStepCursor() {
    int progind;
    {
        wxMutexLocker l(m);
        progind=processing_thread->getProgramIndex();
    }
    CodeEditor->IndicatorClearRange(progind,1);
}
void IDEFrame::OnStopButtonClick(wxCommandEvent& event)
{
    wxCommandEvent e(EVT_VM_FINISHED,wxID_ANY);
    OnVmFinished(e);
    clearStepCursor();
    reset_processing_thread();
    processing_thread->SetRunmode(stopped);
}


void IDEFrame::OnPauseButtonClick(wxCommandEvent& event)
{
    processing_thread->SetRunmode(paused);
    {
        wxMutexLocker l(m);
        wxCommandEvent e(EVT_VM_BREAKPOINTED,wxID_ANY);
        e.SetInt(processing_thread->getProgramIndex());
        OnVmBreakpoint(e);
    }
}

void IDEFrame::OnStepButtonClick(wxCommandEvent& event)
{
    clearStepCursor();
    processing_thread->SetRunmode(stepped);
}


void IDEFrame::OnClearButtonClick(wxCommandEvent& event)
{
    Term1->Reset();
}


void IDEFrame::reset_processing_thread()
{
    processing_thread->reset(CodeEditor->GetText());
}
void IDEFrame::OnRunButtonClick(wxCommandEvent& event)
{
    CodeEditor->SetReadOnly(true);
    StopButton->Enable(true);
    StepButton->Enable(false);
    PauseButton->Enable(true);
    ContinueButton->Enable(false);
    clearStepCursor();
    reset_processing_thread();
    processing_thread->SetRunmode(running);
}


void IDEFrame::OnQuitButtonClick(wxCommandEvent& event)
{
    Close();
}




void IDEFrame::OnContinueButtonClick(wxCommandEvent& event)
{
    StepButton->Enable(false);
    PauseButton->Enable(true);
    ContinueButton->Enable(false);
    clearStepCursor();
    processing_thread->SetRunmode(continued);
}
