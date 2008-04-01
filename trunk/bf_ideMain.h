/***************************************************************
 * Name:      bf_ideMain.h
 * Purpose:   Defines Application Frame
 * Author:    Jeremy Salwen (jeremybubs@gmail.com)
 * Created:   2008-03-23
 * Copyright: Jeremy Salwen ()
 * License:
 **************************************************************/

#ifndef BF_IDEMAIN_H
#define BF_IDEMAIN_H

//(*Headers(bf_ideFrame)
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/grid.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include <iostream>
class bf_ideFrame: public wxFrame
{
    public:
        bf_ideFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~bf_ideFrame();
    private:
        const wxChar * program;
        const wxChar * currentIndex;
        void lockUpIDE();
        void processStep();
        //(*Handlers(bf_ideFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnTextCtrl1Text(wxCommandEvent& event);
        void OnTextCtrl1Text1(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnPauseButtonClick(wxCommandEvent& event);
        void OnCustom1Paint(wxPaintEvent& event);
        void OnStopButtonClick(wxCommandEvent& event);
        void OnStepIntoButtonClick(wxCommandEvent& event);
        void OnStepOverButtonClick(wxCommandEvent& event);
        void OnStartButtonClick(wxCommandEvent& event);
        void OnProgramTextText(wxCommandEvent& event);
        //*)

        //(*Identifiers(bf_ideFrame)
        static const long ID_TEXTCTRL1;
        static const long ID_GRID1;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_BUTTON5;
        static const long ID_TEXTCTRL2;
        static const long ID_TEXTCTRL3;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(bf_ideFrame)
        wxGrid* ArrayData;
        wxStaticText* InputLabel;
        wxButton* StartButton;
        wxButton* StepIntoButton;
        wxTextCtrl* InputBox;
        wxButton* PauseButton;
        wxTextCtrl* OutputBox;
        wxButton* StopButton;
        wxStaticText* OutputLabel;
        wxTextCtrl* ProgramText;
        wxStatusBar* StatusBar;
        wxButton* StepOverButton;
        wxMenuBar* MenuBar;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // BF_IDEMAIN_H