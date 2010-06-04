#include "wxTerminal.h"

BEGIN_EVENT_TABLE(wxTerminal,wxTextCtrl)
    //(*EventTable(NewFrame)
    //*)
    EVT_CHAR(wxTerminal::OnKeyPressed)
    EVT_TEXT_CUT(wxID_ANY,wxTerminal::OnTextCut)
    EVT_TEXT_PASTE(wxID_ANY,wxTerminal::OnTextPaste)
END_EVENT_TABLE()

wxTerminal::wxTerminal(wxWindow* parent, wxWindowID id, const wxString& value=wxString(), const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=0, const wxValidator& validator=wxDefaultValidator, const wxString& name=wxTextCtrlNameStr):wxTextCtrl(parent,id,value,pos,size,style,validator,name) {
    output=new std::stringstream();
    input=new std::ostream(this);
}

void wxTerminal::OnKeyPressed(wxKeyEvent& event) {
    SetInsertionPointEnd();
    if (event.GetKeyCode()!=WXK_BACK) {
        event.Skip();
    }

}

void wxTerminal::OnTextPaste(wxClipboardTextEvent& event) {
    if (wxTheClipboard->Open()) {
        wxTextDataObject data;
        wxTheClipboard->GetData( data );
        wxString text=data.GetText();
        *output<<text;
        output->flush();
        wxTheClipboard->Close();
    }
    event.Skip();
}

void wxTerminal::OnTextCut(wxClipboardTextEvent& event) {
    //Absorbs the event.
}
void wxTerminal::Clear() {
    output->str("");
    wxTextCtrl::Clear();
}
void wxTerminal::ClearExcess() {
    wxString tmp(output->str().c_str(), wxConvUTF8);
    SetValue(tmp);
}
wxTerminal::~wxTerminal() {
    delete output;
    delete input;
}
