 /*
  *  WxBfIDE - A cross-platform brainfuck IDE
  *  Copyright (C) 2008-2012  Jeremy Salwen
  *
  *  This program is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  This program is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#include "IDEFrame.h"

//(*InternalHeaders(IDEFrame)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/artprov.h>
//*)
#include "bf_tableBase.h"
#include <wx/msgdlg.h>
#include <wx/aboutdlg.h>

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
const long IDEFrame::ID_CLEAR_TERMINAL_BUTTON = wxNewId();
const long IDEFrame::ID_MENU_NEW = wxNewId();
const long IDEFrame::ID_MENU_OPEN = wxNewId();
const long IDEFrame::ID_MENU_SAVE = wxNewId();
const long IDEFrame::ID_MENUITEM4 = wxNewId();
const long IDEFrame::ID_MENU_QUIT = wxNewId();
const long IDEFrame::ID_MENU_UNDO = wxNewId();
const long IDEFrame::ID_MENU_REDO = wxNewId();
const long IDEFrame::ID_MENU_COPY = wxNewId();
const long IDEFrame::ID_MENU_CUT = wxNewId();
const long IDEFrame::ID_MENU_PASTE = wxNewId();
const long IDEFrame::ID_MENU_ABOUT = wxNewId();
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


IDEFrame::IDEFrame(wxWindow* parent,wxWindowID id): c(m),
    OpenDialog(this, _("Open File"), wxEmptyString, wxEmptyString,
               _("BrainFuck files (*.b, *.bf)|*.b;*.bf|Text files (*.txt)|*.txt"),
               wxFD_OPEN, wxDefaultPosition),
    SaveDialog(this,_("Save File As"), wxEmptyString, wxEmptyString,
               _("BrainFuck files (*.b, *.bf)|*.b;*.bf|Text files (*.txt)|*.txt"),
               wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition)
{

    //(*Initialize(IDEFrame)
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer2;
    wxMenuItem* MenuRedo;

    Create(parent, wxID_ANY, _("Brainfuck IDE - New File"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(-1,-1));
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
    ClearButton = new wxButton(this, ID_CLEAR_TERMINAL_BUTTON, _("Clear Terminal"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CLEAR_TERMINAL_BUTTON"));
    FlexGridSizer2->Add(ClearButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    MenuBar1 = new wxMenuBar();
    FileMenu = new wxMenu();
    MenuNew = new wxMenuItem(FileMenu, ID_MENU_NEW, _("New"), wxEmptyString, wxITEM_NORMAL);
    MenuNew->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NORMAL_FILE")),wxART_MENU));
    FileMenu->Append(MenuNew);
    MenuOpen = new wxMenuItem(FileMenu, ID_MENU_OPEN, _("Open..."), wxEmptyString, wxITEM_NORMAL);
    MenuOpen->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_OPEN")),wxART_MENU));
    FileMenu->Append(MenuOpen);
    FileMenu->AppendSeparator();
    MenuSave = new wxMenuItem(FileMenu, ID_MENU_SAVE, _("Save"), wxEmptyString, wxITEM_NORMAL);
    MenuSave->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_SAVE")),wxART_MENU));
    FileMenu->Append(MenuSave);
    MenuSaveAs = new wxMenuItem(FileMenu, ID_MENUITEM4, _("Save As..."), wxEmptyString, wxITEM_NORMAL);
    MenuSaveAs->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_SAVE_AS")),wxART_MENU));
    FileMenu->Append(MenuSaveAs);
    FileMenu->AppendSeparator();
    MenuQuit = new wxMenuItem(FileMenu, ID_MENU_QUIT, _("Quit"), wxEmptyString, wxITEM_NORMAL);
    MenuQuit->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_QUIT")),wxART_MENU));
    FileMenu->Append(MenuQuit);
    MenuBar1->Append(FileMenu, _("File"));
    Menu2 = new wxMenu();
    MenuUndo = new wxMenuItem(Menu2, ID_MENU_UNDO, _("Undo"), wxEmptyString, wxITEM_NORMAL);
    MenuUndo->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_UNDO")),wxART_MENU));
    Menu2->Append(MenuUndo);
    MenuRedo = new wxMenuItem(Menu2, ID_MENU_REDO, _("Redo"), wxEmptyString, wxITEM_NORMAL);
    MenuRedo->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_REDO")),wxART_MENU));
    Menu2->Append(MenuRedo);
    Menu2->AppendSeparator();
    MenuCopy = new wxMenuItem(Menu2, ID_MENU_COPY, _("Copy"), wxEmptyString, wxITEM_NORMAL);
    MenuCopy->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_COPY")),wxART_MENU));
    Menu2->Append(MenuCopy);
    MenuCut = new wxMenuItem(Menu2, ID_MENU_CUT, _("Cut"), wxEmptyString, wxITEM_NORMAL);
    MenuCut->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_CUT")),wxART_MENU));
    Menu2->Append(MenuCut);
    MenuPaste = new wxMenuItem(Menu2, ID_MENU_PASTE, _("Paste"), wxEmptyString, wxITEM_NORMAL);
    MenuPaste->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_PASTE")),wxART_MENU));
    Menu2->Append(MenuPaste);
    MenuBar1->Append(Menu2, _("Edit"));
    Menu3 = new wxMenu();
    MenuAbout = new wxMenuItem(Menu3, ID_MENU_ABOUT, _("About"), wxEmptyString, wxITEM_NORMAL);
    MenuAbout->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_INFORMATION")),wxART_MENU));
    Menu3->Append(MenuAbout);
    MenuBar1->Append(Menu3, _("Help"));
    SetMenuBar(MenuBar1);
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_RUN_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IDEFrame::OnRunButtonClick);
    Connect(ID_STOP_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IDEFrame::OnStopButtonClick);
    Connect(ID_PAUSE_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IDEFrame::OnPauseButtonClick);
    Connect(ID_CONTINUE_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IDEFrame::OnContinueButtonClick);
    Connect(ID_STEP_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IDEFrame::OnStepButtonClick);
    Connect(ID_CLEAR_TERMINAL_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IDEFrame::OnClearButtonClick);
    Connect(ID_MENU_NEW,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&IDEFrame::OnMenuNewSelected);
    Connect(ID_MENU_OPEN,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&IDEFrame::OnMenuOpenSelected);
    Connect(ID_MENU_SAVE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&IDEFrame::OnMenuSaveSelected);
    Connect(ID_MENUITEM4,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&IDEFrame::OnMenuSaveAsSelected);
    Connect(ID_MENU_QUIT,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&IDEFrame::OnQuitButtonClick);
    Connect(ID_MENU_UNDO,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&IDEFrame::OnMenuUndoSelected);
    Connect(ID_MENU_REDO,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&IDEFrame::OnMenuRedoSelected);
    Connect(ID_MENU_COPY,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&IDEFrame::OnMenuCopySelected);
    Connect(ID_MENU_CUT,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&IDEFrame::OnMenuCutSelected);
    Connect(ID_MENU_PASTE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&IDEFrame::OnMenuPasteSelected);
    Connect(ID_MENU_ABOUT,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&IDEFrame::OnMenuAboutSelected);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&IDEFrame::OnClose);
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
    if(!confirmUnsaved() && event.CanVeto())
    {
        event.Veto(true);
    }
    else
    {
        this->Destroy();
    }
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
void IDEFrame::OnVmFinished(wxCommandEvent& e)
{
    CodeEditor->SetReadOnly(false);
    RunButton->Enable(true);
    StepButton->Enable(false);
    PauseButton->Enable(false);
    StopButton->Enable(false);
    ContinueButton->Enable(false);
    MenuNew->Enable(true);
    MenuOpen->Enable(true);
    MenuSave->Enable(true);
    MenuSaveAs->Enable(true);
}

bool IDEFrame::HasBreakpoint(unsigned int linenumber)
{
    return BreakPointsEnabled->GetValue() && CodeEditor->MarkerGet(linenumber);
}
void IDEFrame::clearStepCursor()
{
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
}


void IDEFrame::OnPauseButtonClick(wxCommandEvent& event)
{
    processing_thread->SetRunmode(stopped);
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
    MenuNew->Enable(false);
    MenuOpen->Enable(false);
    MenuSave->Enable(false);
    MenuSaveAs->Enable(false);

    clearStepCursor();
    reset_processing_thread();
    processing_thread->SetRunmode(running);
}


void IDEFrame::OnQuitButtonClick(wxCommandEvent& event)
{
    Close();
}


bool IDEFrame::confirmUnsaved()
{
    if(CodeEditor->GetModify())
    {
        wxString tmp=CurrentDocPath;
        if(tmp.IsEmpty())
        {
            tmp="Your file has not been saved...\nDo you want to save it?";
        }
        else
        {
            tmp<<" is modified...\nDo you want to save the changes?";
        }
        int result=wxMessageBox(tmp,"Save File",wxYES_NO|wxCANCEL|wxICON_QUESTION,this);
        if(result==wxCANCEL)
        {
            return false;
        }
        if(result==wxYES)
        {
            if(SaveDialog.ShowModal()==wxCANCEL)
            {
                return false;
            }
            else
            {
                CodeEditor->SaveFile(SaveDialog.GetPath());
                return true;
            }
        }
    }
    return true;
}
void IDEFrame::OnContinueButtonClick(wxCommandEvent& event)
{
    StepButton->Enable(false);
    PauseButton->Enable(true);
    ContinueButton->Enable(false);
    clearStepCursor();
    processing_thread->SetRunmode(continued);
}

void IDEFrame::OnMenuNewSelected(wxCommandEvent& event)
{
    if(!confirmUnsaved())
    {
        return;
    }
    CodeEditor->SetDocPointer(NULL);
    CurrentDocPath="";
    reset_processing_thread();
    SetTitle(wxString("BrainFuck IDE - New File"));
}

void IDEFrame::OnMenuOpenSelected(wxCommandEvent& event)
{
    if(!confirmUnsaved())
    {
        return;
    }
    /*From wxwidgets wiki*/
    // Creates a "open file" dialog with 4 file types
    if (OpenDialog.ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
    {
        CurrentDocPath = OpenDialog.GetPath();
        // Sets our current document to the file the user selected
        CodeEditor->LoadFile(CurrentDocPath); //Opens that file
        SetTitle(wxString("BrainFuck IDE - ") <<
                 OpenDialog.GetFilename()); // Set the Title to reflect the file open
        reset_processing_thread();
    }
}

void IDEFrame::OnMenuSaveSelected(wxCommandEvent& event)
{
    if(CurrentDocPath.IsEmpty())
    {
        OnMenuSaveAsSelected(event);
    }
    else
    {
        CodeEditor->SaveFile(CurrentDocPath);
        CodeEditor->SetModified(false);
    }
}

void IDEFrame::OnMenuSaveAsSelected(wxCommandEvent& event)
{
    if(SaveDialog.ShowModal()!=wxCANCEL)
    {
        CurrentDocPath=SaveDialog.GetPath();
        CodeEditor->SaveFile(CurrentDocPath);
        CodeEditor->SetModified(false);
    }
}

void IDEFrame::OnMenuUndoSelected(wxCommandEvent& event)
{
    CodeEditor->Undo();
}

void IDEFrame::OnMenuRedoSelected(wxCommandEvent& event)
{
    CodeEditor->Redo();
}

void IDEFrame::OnMenuCutSelected(wxCommandEvent& event)
{
    CodeEditor->Cut();
}

void IDEFrame::OnMenuCopySelected(wxCommandEvent& event)
{
    CodeEditor->Copy();
}

void IDEFrame::OnMenuPasteSelected(wxCommandEvent& event)
{
    CodeEditor->Paste();
}

void IDEFrame::OnMenuAboutSelected(wxCommandEvent& event)
{
    wxAboutDialogInfo inf;
    inf.SetName("WxBfIDE");
    inf.SetCopyright("(C) 2008-2012 Jeremy Salwen");
    inf.SetDescription("A cross-platform graphical Brainfuck debugger/IDE");
    inf.SetVersion("0.9");
    inf.SetWebSite("https://code.google.com/p/wxbfide");
    inf.SetLicense("\
    This program is free software: you can redistribute it and/or modify\n\
    it under the terms of the GNU General Public License as published by\n\
    the Free Software Foundation, either version 3 of the License, or\n\
    (at your option) any later version.\n\
\n\
    This program is distributed in the hope that it will be useful,\n\
    but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
    GNU General Public License for more details.\n\
\n\
    You should have received a copy of the GNU General Public License\n\
    along with this program.  If not, see <http://www.gnu.org/licenses/>.");
    wxAboutBox(inf);
}
