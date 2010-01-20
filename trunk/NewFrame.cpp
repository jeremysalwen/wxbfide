#include "NewFrame.h"

//(*InternalHeaders(NewFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

const long NewFrame::ID_TEXTCTRL1 = wxNewId();
//(*IdInit(NewFrame)
const long NewFrame::ID_BUTTON1 = wxNewId();
const long NewFrame::ID_TEXTCTRL3 = wxNewId();
const long NewFrame::ID_STATICTEXT2 = wxNewId();
const long NewFrame::ID_GRID1 = wxNewId();
const long NewFrame::ID_BUTTON2 = wxNewId();
const long NewFrame::ID_BUTTON4 = wxNewId();
const long NewFrame::ID_BUTTON5 = wxNewId();
const long NewFrame::ID_BUTTON6 = wxNewId();
const long NewFrame::ID_BUTTON8 = wxNewId();
const long NewFrame::ID_BUTTON7 = wxNewId();
const long NewFrame::ID_CHECKBOX1 = wxNewId();
const long NewFrame::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(NewFrame,wxFrame)
	//(*EventTable(NewFrame)
	//*)
	EVT_SCI_MARGINCLICK(-1,NewFrame::OnMarginClicked)
END_EVENT_TABLE()

NewFrame::NewFrame(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(NewFrame)
	Create(parent, id, _("BrainF*** Interpreter"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
	SetClientSize(wxSize(815,453));
	Move(wxDefaultPosition);
	Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(136,232), wxSize(816,453), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	RunButton = new wxButton(Panel1, ID_BUTTON1, _("Run"), wxPoint(24,408), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	InputBox = new wxTerminal(Panel1, ID_TEXTCTRL3, wxEmptyString, wxPoint(360,168), wxSize(440,208), wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	InputLabel = new wxStaticText(Panel1, ID_STATICTEXT2, _("Input/ Output"), wxPoint(360,144), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	DataGrid = new wxGrid(Panel1, ID_GRID1, wxPoint(360,40), wxSize(440,96), 0, _T("ID_GRID1"));
	StopButton = new wxButton(Panel1, ID_BUTTON2, _("Stop"), wxPoint(240,408), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	StopButton->Disable();
	StepButton = new wxButton(Panel1, ID_BUTTON4, _("Step"), wxPoint(432,408), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	StepButton->Disable();
	PauseButton = new wxButton(Panel1, ID_BUTTON5, _("Pause"), wxPoint(336,408), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	PauseButton->Disable();
	QuitButton = new wxButton(Panel1, ID_BUTTON6, _("Quit"), wxPoint(720,408), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
	ClearOutputButton = new wxButton(Panel1, ID_BUTTON8, _("Clear IO"), wxPoint(624,408), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
	TrimIOButton = new wxButton(Panel1, ID_BUTTON7, _("Trim IO"), wxPoint(528,408), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
	BreakPointsEnabled = new wxCheckBox(Panel1, ID_CHECKBOX1, _("Breakpoints"), wxPoint(120,408), wxSize(104,30), 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	BreakPointsEnabled->SetValue(false);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewFrame::OnRunButtonClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewFrame::OnStopButtonClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewFrame::OnStepButtonClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewFrame::OnPauseButtonClick);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewFrame::OnQuitButtonClick);
	Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewFrame::OnClearOutputButtonClick);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewFrame::OnTrimIOButtonClick);
	//*)

    wxGridCellAttr *w=new wxGridCellAttr();  //memory leak?
    w->SetReadOnly(true);
    DataGrid->SetRowAttr(1,w);
    DataGrid->SetColumnWidth(1,10);
    DataGrid->SetRowLabelSize(0);
    DataGrid->SetColLabelSize(0);
    DataGrid->DisableDragGridSize();
    bf_tableBase * b =new bf_tableBase;
    DataGrid->SetTable(b,true);
    DataGrid->SetMargins(0,0);
    //DataGrid->SetOrCalcColumnSizes(false);
    //DataGrid->SetOrCalcRowSizes(false);

    ProgramBox = new wxScintilla(Panel1, ID_TEXTCTRL1, wxPoint(16,16), wxSize(280,376), wxTE_MULTILINE, _T("ID_TEXTCTRL1"));
    ProgramBox->SetScrollWidth(260);
    ProgramBox->MarkerDefine(0,wxSCI_MARK_CIRCLE);
    ProgramBox->SetMarginWidth(0,20);
    ProgramBox->SetMarginSensitive(1,true);
    processing_thread=new bf_interpreter_thread(InputBox->output,new std::ostream(InputBox),ProgramBox->GetText(),b,this);
    processing_thread->Run();
}

NewFrame::~NewFrame()
{
	//(*Destroy(NewFrame)
	//*)

	delete processing_thread;
}

void NewFrame::OnQuitButtonClick(wxCommandEvent& event)
{
    Close();
}

void NewFrame::reset_processing_thread() {
    processing_thread->reset(ProgramBox->GetText());
}
void NewFrame::OnRunButtonClick(wxCommandEvent& event)
{
    ProgramBox->SetReadOnly(true);
    RunButton->Enable(false);
    StopButton->Enable(true);
    StepButton->Enable(false);
    PauseButton->Enable(true);
    reset_processing_thread();
    processing_thread->SetRunmode(running);
}

void NewFrame::OnMarginClicked(wxScintillaEvent& event) {
    int line=ProgramBox->LineFromPosition(event.GetPosition());
    if(ProgramBox->MarkerGet(line)) {
        ProgramBox->MarkerDelete(line,0);
    } else {
        ProgramBox->MarkerAdd(line,0);
    }
}

bool NewFrame::HasBreakpoint(unsigned int linenumber) {
    return BreakPointsEnabled->GetValue() && ProgramBox->MarkerGet(linenumber);
}

void NewFrame::OnStopButtonClick(wxCommandEvent& event)
{
    ProgramBox->SetReadOnly(false);
    RunButton->Enable(true);
    StepButton->Enable(false);
    PauseButton->Enable(false);
    reset_processing_thread();
    processing_thread->SetRunmode(stopped);
}


void NewFrame::OnPauseButtonClick(wxCommandEvent& event)
{
    RunButton->Enable(true);
    StepButton->Enable(true);
    PauseButton->Enable(false);
    StopButton->Enable(true);
   processing_thread->SetRunmode(paused);
}

void NewFrame::OnStepButtonClick(wxCommandEvent& event)
{
   processing_thread->SetRunmode(stepped);
}


void NewFrame::OnClearOutputButtonClick(wxCommandEvent& event)
{
    InputBox->Clear();
}


void NewFrame::OnTrimIOButtonClick(wxCommandEvent& event)
{
    InputBox->ClearExcess();
}
