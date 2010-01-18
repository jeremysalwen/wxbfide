#include "NewFrame.h"

//(*InternalHeaders(NewFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(NewFrame)
const long NewFrame::ID_BUTTON1 = wxNewId();
const long NewFrame::ID_TEXTCTRL1 = wxNewId();
const long NewFrame::ID_TEXTCTRL2 = wxNewId();
const long NewFrame::ID_TEXTCTRL3 = wxNewId();
const long NewFrame::ID_STATICTEXT1 = wxNewId();
const long NewFrame::ID_STATICTEXT2 = wxNewId();
const long NewFrame::ID_GRID1 = wxNewId();
const long NewFrame::ID_BUTTON2 = wxNewId();
const long NewFrame::ID_BUTTON3 = wxNewId();
const long NewFrame::ID_BUTTON4 = wxNewId();
const long NewFrame::ID_BUTTON5 = wxNewId();
const long NewFrame::ID_BUTTON6 = wxNewId();
const long NewFrame::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(NewFrame,wxFrame)
	//(*EventTable(NewFrame)
	//*)
END_EVENT_TABLE()

NewFrame::NewFrame(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(NewFrame)
	Create(parent, id, _("BrainF*** Interpreter"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
	SetClientSize(wxSize(581,453));
	Move(wxDefaultPosition);
	Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(136,232), wxSize(568,453), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	RunButton = new wxButton(Panel1, ID_BUTTON1, _("Run"), wxPoint(16,408), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	ProgramBox = new wxTextCtrl(Panel1, ID_TEXTCTRL1, _("Text"), wxPoint(16,16), wxSize(280,376), wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	OutputBox = new wxTextCtrl(Panel1, ID_TEXTCTRL2, _("Text"), wxPoint(312,288), wxSize(240,104), wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	InputBox = new wxTextCtrl(Panel1, ID_TEXTCTRL3, _("Text"), wxPoint(312,168), wxSize(240,88), wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	OutputLabel = new wxStaticText(Panel1, ID_STATICTEXT1, _("Output"), wxPoint(312,264), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	InputLabel = new wxStaticText(Panel1, ID_STATICTEXT2, _("Input"), wxPoint(312,144), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	DataGrid = new wxGrid(Panel1, ID_GRID1, wxPoint(312,32), wxSize(232,96), 0, _T("ID_GRID1"));
	StopButton = new wxButton(Panel1, ID_BUTTON2, _("Stop"), wxPoint(112,408), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	DebugButton = new wxButton(Panel1, ID_BUTTON3, _("Debug"), wxPoint(208,408), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	StepButton = new wxButton(Panel1, ID_BUTTON4, _("Step"), wxPoint(400,408), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	PauseButton = new wxButton(Panel1, ID_BUTTON5, _("Pause"), wxPoint(304,408), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	QuitButton = new wxButton(Panel1, ID_BUTTON6, _("Quit"), wxPoint(488,408), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewFrame::OnRunButtonClick);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewFrame::OnQuitButtonClick);
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
    processing_thread=new bf_interpreter_thread(new std::istream(InputBox),new std::ostream(OutputBox),ProgramBox->GetValue().c_str(),b);
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
    processing_thread->reset(new std::istream(InputBox),new std::ostream(OutputBox),ProgramBox->GetValue());
}
void NewFrame::OnRunButtonClick(wxCommandEvent& event)
{
    reset_processing_thread();
}

