#ifndef NEWFRAME_H
#define NEWFRAME_H

#include "bf_table.h"
#include "bf_interpreter_thread.h"
#include "wxTerminal.h"
#include "breakpoint_lister.h"
#include <iostream>
#include <wx/stc/stc.h>
//(*Headers(NewFrame)
#include <wx/grid.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/panel.h>
#include "terminalWx/terminalwx.h"
#include <wx/frame.h>
#include <wx/stattext.h>
//*)

class NewFrame: public wxFrame, public breakpoint_lister
{
	public:

		NewFrame(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~NewFrame();
        virtual bool HasBreakpoint(unsigned int linenumber);
		//(*Declarations(NewFrame)
		wxButton* StepButton;
		wxButton* StopButton;
		wxButton* PauseButton;
		wxPanel* Panel1;
		wxButton* TrimIOButton;
		wxPanel* Panel2;
		TerminalWx* Term1;
		wxGrid* DataGrid;
		wxButton* QuitButton;
		wxCheckBox* BreakPointsEnabled;
		wxStaticText* InputLabel;
		wxButton* RunButton;
		wxButton* ClearOutputButton;
		//*)
		wxStyledTextCtrl* ProgramBox;

		bf_interpreter_thread * processing_thread;
	protected:
        void reset_processing_thread();
        static const long ID_TEXTCTRL1;
		//(*Identifiers(NewFrame)
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT2;
		static const long ID_GRID1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON4;
		static const long ID_BUTTON5;
		static const long ID_BUTTON6;
		static const long ID_BUTTON8;
		static const long ID_BUTTON7;
		static const long ID_CHECKBOX1;
		static const long ID_TERM;
		static const long ID_PANEL2;
		static const long ID_PANEL1;
		//*)

	private:

		//(*Handlers(NewFrame)
		void OnPanel1Paint(wxPaintEvent& event);
		void OnTextCtrl2Text(wxCommandEvent& event);
		void OnGrid1CellLeftClick(wxGridEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnQuitButtonClick(wxCommandEvent& event);
		void OnRunButtonClick(wxCommandEvent& event);
		void OnStopButtonClick(wxCommandEvent& event);
		void OnDebugButtonClick(wxCommandEvent& event);
		void OnPauseButtonClick(wxCommandEvent& event);
		void OnStepButtonClick(wxCommandEvent& event);
		void OnSendInputButtonClick(wxCommandEvent& event);
		void OnClearOutputButtonClick(wxCommandEvent& event);
		void OnInputBoxText(wxCommandEvent& event);
		void OnTrimIOButtonClick(wxCommandEvent& event);
		void OnPanel1Paint1(wxPaintEvent& event);
		void OnClose(wxCloseEvent& event);
		//*)
        void OnMarginClicked(wxStyledTextEvent& event);
		DECLARE_EVENT_TABLE()
};

#endif
