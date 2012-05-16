#ifndef IDEFRAME_H
#define IDEFRAME_H

//(*Headers(IDEFrame)
#include <wx/grid.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/stc/stc.h>
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/splitter.h>
#include "BFTerm.h"
#include <wx/frame.h>
//*)

#include <wx/filedlg.h>
#include "breakpoint_lister.h"
#include "bf_interpreter_thread.h"
#include "bf_table.h"

DECLARE_EVENT_TYPE(EVT_VM_BREAKPOINTED, -1 )
DECLARE_EVENT_TYPE(EVT_VM_FINISHED, -1 )

class IDEFrame: public wxFrame, public breakpoint_lister
{
	public:

		IDEFrame(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~IDEFrame();

        bool HasBreakpoint(unsigned int linenumber);

		//(*Declarations(IDEFrame)
		wxButton* StepButton;
		wxButton* StopButton;
		wxButton* PauseButton;
		wxMenuItem* MenuSave;
		wxMenuItem* MenuUndo;
		wxStyledTextCtrl* CodeEditor;
		wxMenu* Menu3;
		wxMenuItem* MenuNew;
		bf_table* DataGrid;
		wxMenu* FileMenu;
		wxMenuItem* MenuPaste;
		wxSplitterWindow* SplitterWindow1;
		wxMenuItem* MenuQuit;
		wxButton* ContinueButton;
		wxButton* ClearButton;
		wxSplitterWindow* SplitterWindow2;
		wxMenuItem* MenuCopy;
		wxMenuItem* MenuOpen;
		BFTerm* Term1;
		wxCheckBox* BreakPointsEnabled;
		wxMenuBar* MenuBar1;
		wxMenuItem* MenuSaveAs;
		wxButton* RunButton;
		wxMenu* Menu2;
		wxMenuItem* MenuCut;
		wxMenuItem* MenuAbout;
		//*)


		//(*Identifiers(IDEFrame)
		static const long ID_CODE_EDITOR;
		static const long ID_GRID1;
		static const long ID_TERM;
		static const long ID_SPLITTERWINDOW2;
		static const long ID_SPLITTERWINDOW1;
		static const long ID_RUN_BUTTON;
		static const long ID_BREAKPOINT_CHECKBOX;
		static const long ID_STOP_BUTTON;
		static const long ID_PAUSE_BUTTON;
		static const long ID_CONTINUE_BUTTON;
		static const long ID_STEP_BUTTON;
		static const long ID_CLEAR_TERMINAL_BUTTON;
		static const long ID_MENU_NEW;
		static const long ID_MENU_OPEN;
		static const long ID_MENU_SAVE;
		static const long ID_MENUITEM4;
		static const long ID_MENU_QUIT;
		static const long ID_MENU_UNDO;
		static const long ID_MENU_REDO;
		static const long ID_MENU_COPY;
		static const long ID_MENU_CUT;
		static const long ID_MENU_PASTE;
		static const long ID_MENU_ABOUT;
		//*)
	protected:

	private:
        wxMutex m;
        wxCondition c;
		bf_interpreter_thread * processing_thread;

		wxString CurrentDocPath;
        wxFileDialog OpenDialog;
        wxFileDialog SaveDialog;

		//(*Handlers(IDEFrame)
		void OnClose(wxCloseEvent& event);
		void OnCodeEditorResize(wxSizeEvent& event);
		void OnStopButtonClick(wxCommandEvent& event);
		void OnPauseButtonClick(wxCommandEvent& event);
		void OnClearButtonClick(wxCommandEvent& event);
		void OnStepButtonClick(wxCommandEvent& event);
		void OnQuitButtonClick(wxCommandEvent& event);
		void OnRunButtonClick(wxCommandEvent& event);
		void OnContinueButtonClick(wxCommandEvent& event);
		void OnMenuNewSelected(wxCommandEvent& event);
		void OnMenuOpenSelected(wxCommandEvent& event);
		void OnMenuSaveSelected(wxCommandEvent& event);
		void OnMenuSaveAsSelected(wxCommandEvent& event);
		void OnMenuUndoSelected(wxCommandEvent& event);
		void OnMenuRedoSelected(wxCommandEvent& event);
		void OnMenuCutSelected(wxCommandEvent& event);
		void OnMenuCopySelected(wxCommandEvent& event);
		void OnMenuPasteSelected(wxCommandEvent& event);
		void OnMenuAboutSelected(wxCommandEvent& event);
		//*)
		void reset_processing_thread();
        void OnMarginClicked(wxStyledTextEvent& event);
        void OnVmBreakpoint(wxCommandEvent&);
        void OnVmFinished(wxCommandEvent&);
        void clearStepCursor();
        bool confirmUnsaved();
		DECLARE_EVENT_TABLE()
};

#endif
