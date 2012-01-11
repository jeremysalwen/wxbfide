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
const long IDEFrame::ID_BUTTON1 = wxNewId();
const long IDEFrame::ID_CHECKBOX1 = wxNewId();
const long IDEFrame::ID_BUTTON2 = wxNewId();
const long IDEFrame::ID_BUTTON3 = wxNewId();
const long IDEFrame::ID_BUTTON4 = wxNewId();
const long IDEFrame::ID_BUTTON5 = wxNewId();
const long IDEFrame::ID_BUTTON6 = wxNewId();
//*)

BEGIN_EVENT_TABLE(IDEFrame,wxFrame)
	//(*EventTable(IDEFrame)
	//*)
	EVT_STC_MARGINCLICK(-1,IDEFrame::OnMarginClicked)
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
	RunButton = new wxButton(this, ID_BUTTON1, _("Run"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer2->Add(RunButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BreakPointsEnabled = new wxCheckBox(this, ID_CHECKBOX1, _("Enable Breakpoints"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	BreakPointsEnabled->SetValue(false);
	FlexGridSizer2->Add(BreakPointsEnabled, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StopButton = new wxButton(this, ID_BUTTON2, _("Stop"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer2->Add(StopButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PauseButton = new wxButton(this, ID_BUTTON3, _("Pause"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer2->Add(PauseButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StepButton = new wxButton(this, ID_BUTTON4, _("Step"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer2->Add(StepButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ClearButton = new wxButton(this, ID_BUTTON5, _("Clear IO"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FlexGridSizer2->Add(ClearButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	QuitButton = new wxButton(this, ID_BUTTON6, _("Quit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
	FlexGridSizer2->Add(QuitButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IDEFrame::OnRunButtonClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IDEFrame::OnStopButtonClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IDEFrame::OnPauseButtonClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IDEFrame::OnStepButtonClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IDEFrame::OnClearButtonClick);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IDEFrame::OnQuitButtonClick);
	//*)
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

    processing_thread=new bf_interpreter_thread(&m,&c,Term1,"",b,this);
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
    int line=CodeEditor->LineFromPosition(event.GetPosition());
    if(CodeEditor->MarkerGet(line)) {
        CodeEditor->MarkerDelete(line,0);
    } else {
        CodeEditor->MarkerAdd(line,0);
    }
}

bool IDEFrame::HasBreakpoint(unsigned int linenumber) {
    return BreakPointsEnabled->GetValue() && CodeEditor->MarkerGet(linenumber);
}

void IDEFrame::OnStopButtonClick(wxCommandEvent& event)
{
    CodeEditor->SetReadOnly(false);
    RunButton->Enable(true);
    StepButton->Enable(false);
    PauseButton->Enable(false);
    reset_processing_thread();
    processing_thread->SetRunmode(stopped);
}


void IDEFrame::OnPauseButtonClick(wxCommandEvent& event)
{
    RunButton->Enable(true);
    StepButton->Enable(true);
    PauseButton->Enable(false);
    StopButton->Enable(true);
    processing_thread->SetRunmode(paused);
}

void IDEFrame::OnStepButtonClick(wxCommandEvent& event)
{
   processing_thread->SetRunmode(stepped);
}


void IDEFrame::OnClearButtonClick(wxCommandEvent& event)
{
    Term1->Reset();
}


void IDEFrame::reset_processing_thread() {
    processing_thread->reset(CodeEditor->GetText());
}
void IDEFrame::OnRunButtonClick(wxCommandEvent& event)
{
    CodeEditor->SetReadOnly(true);
    RunButton->Enable(false);
    StopButton->Enable(true);
    StepButton->Enable(false);
    PauseButton->Enable(true);
    reset_processing_thread();
    processing_thread->SetRunmode(running);
}


void IDEFrame::OnQuitButtonClick(wxCommandEvent& event)
{
    Close();
}

