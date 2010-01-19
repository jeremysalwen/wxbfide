#ifndef NEWFRAME_H
#define NEWFRAME_H

#include "bf_table.h"
#include "bf_interpreter_thread.h"
#include "wx/wxscintilla.h"
#include <iostream>
//(*Headers(NewFrame)
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/button.h>
#include <wx/frame.h>
//*)

class NewFrame: public wxFrame
{
	public:

		NewFrame(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~NewFrame();

		//(*Declarations(NewFrame)
		wxButton* StepButton;
		wxStaticText* InputLabel;
		wxPanel* Panel1;
		wxTextCtrl* InputBox;
		wxButton* PauseButton;
		wxTextCtrl* OutputBox;
		wxButton* StopButton;
		wxButton* RunButton;
		wxButton* DebugButton;
		wxGrid* DataGrid;
		wxStaticText* OutputLabel;
		wxButton* QuitButton;
		//*)
		wxScintilla* ProgramBox;

		bf_interpreter_thread * processing_thread;
	protected:
        void reset_processing_thread();
        static const long ID_TEXTCTRL1;
		//(*Identifiers(NewFrame)
		static const long ID_BUTTON1;
		static const long ID_TEXTCTRL2;
		static const long ID_TEXTCTRL3;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_GRID1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_BUTTON5;
		static const long ID_BUTTON6;
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
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
