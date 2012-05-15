#ifndef IDEFRAME_H
#define IDEFRAME_H

//(*Headers(IDEFrame)
#include <wx/grid.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/stc/stc.h>
#include <wx/button.h>
#include <wx/splitter.h>
#include "BFTerm.h"
#include <wx/frame.h>
//*)

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
		wxStyledTextCtrl* CodeEditor;
		bf_table* DataGrid;
		wxSplitterWindow* SplitterWindow1;
		wxButton* ContinueButton;
		wxButton* ClearButton;
		wxSplitterWindow* SplitterWindow2;
		wxButton* QuitButton;
		BFTerm* Term1;
		wxCheckBox* BreakPointsEnabled;
		wxButton* RunButton;
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
		static const long ID_CLEARIO_BUTTON;
		static const long ID_QUIT_BUTTON;
		//*)
	protected:

	private:
        wxMutex m;
        wxCondition c;
		bf_interpreter_thread * processing_thread;

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
		//*)
		void reset_processing_thread();
        void OnMarginClicked(wxStyledTextEvent& event);
        void OnVmBreakpoint(wxCommandEvent&);
        void OnVmFinished(wxCommandEvent&);
        void clearStepCursor();
		DECLARE_EVENT_TABLE()
};

#endif
