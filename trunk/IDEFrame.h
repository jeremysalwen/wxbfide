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
		wxSplitterWindow* SplitterWindow1;
		wxButton* ClearButton;
		wxSplitterWindow* SplitterWindow2;
		wxGrid* DataGrid;
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
		static const long ID_BUTTON1;
		static const long ID_CHECKBOX1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_BUTTON5;
		static const long ID_BUTTON6;
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
		//*)
		void reset_processing_thread();
        void OnMarginClicked(wxStyledTextEvent& event);
		DECLARE_EVENT_TABLE()
};

#endif
